/*
 * Source file of the ROS node that translates ROS messages to the
 * binary command of the manipulator and vice versa.
 *
 */

// ROS HEADER
#include "ros/ros.h"
#include "std_msgs/Bool.h"

// STANDARD HEADER
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Communication
#include <mitsubishi_melfa/MelfaCommand.h>
#include <mitsubishi_melfa/UDPCommunication.hpp>
#include <mitsubishi_melfa/CommandBuffer.hpp>

using namespace std;

// global buffer
const double dMin_Reserve_Storage = 0.1;
const unsigned int uiBuffer_Length = 5000;
CommandBuffer CommandBuffer(uiBuffer_Length);

// global on/off switch
bool bAnytime_Stop;
bool bBuffer_Overflow;

// subscriber callbacks
void new_command_callback(const mitsubishi_melfa::MelfaCommand& New_Command) 
{
    // make sure no buffer overflow occurs
    double dRemainingCapacity = CommandBuffer.getRemainingCapacity();
    cout << "Remaining Buffer Capacity: " << dRemainingCapacity << endl;

    // if buffer overflow is imminent, stop robot. Otherwise store command
    if(dRemainingCapacity <= dMin_Reserve_Storage)
    {
            bBuffer_Overflow = true;
    }
    else
    {
            CommandBuffer.pushNewCommand(New_Command);
    }
    return;
}

void anytime_stop_callback(const std_msgs::Bool& bStop) 
{
    bAnytime_Stop = bStop.data;
    return;
}

// MAIN 
int main(int argc, char **argv) {


    // Init ROS node
    ros::init(argc, argv, "mitsubishi_melfa_communication");
    // ROS handle
    ros::NodeHandle rosNodeHandle;
    // Init publisher to broadcast current status
    ros::Publisher Status_Publisher = rosNodeHandle.advertise<mitsubishi_melfa::MelfaCommand>("mitsubishi_melfa_status", 1000, true); 
    // Init subscriber to receive commands
    ros::Subscriber Command_Subscriber = rosNodeHandle.subscribe("mitsubishi_target_sample_positions",1000, new_command_callback);
    // Init subscriber to receive "Anytime_Stop" signal
    ros::Subscriber AnytimeStop_Subscriber = rosNodeHandle.subscribe("mitsubishi_anytime_stop",1000, anytime_stop_callback);	

    // set robot to "on"
    bAnytime_Stop = false;
    bBuffer_Overflow = false;

    // Init Control/Recieve data type. Can later be changed via MelfaCommandMessage.
    int iControl_type;
    char cData_Type_Monitor[4];

    iControl_type = 1;
    cData_Type_Monitor[0] = 1;
    cData_Type_Monitor[1] = 4;
    cData_Type_Monitor[2] = 7;
    cData_Type_Monitor[3] = 10;  

    // Init communication Class
    UDPCommunication Communicator;

    // Robot command specific variables. See data structure.
    unsigned short IOSendType;// Send input/output signal data designation
    unsigned short IORecvType;// Reply input/output signal data designation
    unsigned short IOBitTop=0;
    unsigned short IOBitMask=0xffff;
    unsigned short IOBitData=0;

    MXTCMD MXTsend;
    MXTCMD MXTrecv;
    JOINT jnt_now;
    POSE pos_now;
    PULSE pls_now;

    // other vars (loops, etc.)
    int status;
    int loop = 1;
    unsigned long counter = 0;
    int disp_data = 0;
    int retry;

    //set to zero
    memset(&MXTsend, 0, sizeof(MXTsend));
    memset(&jnt_now, 0, sizeof(JOINT));
    memset(&pos_now, 0, sizeof(POSE));
    memset(&pls_now, 0, sizeof(PULSE));

    // variables to iterate over a position controlled trajectory. essentially the offset from robot starting position
    float fOffset_Start_Pos_X = (float)0.0;
    float fOffset_Start_Pos_Y = (float)0.0;
    float fOffset_Start_Pos_Z = (float)0.0;
    float fOffset_Orientation_X = (float)0.0;
    float fOffset_Orientation_Y = (float)0.0;
    float fOffset_Orientation_Z = (float)0.0;

    // variables to iterate over a joint controlled trajectory. essentially the offset from starting joint configuration
    float fOffset_Start_Angle_J1 = (float)0.0;
    float fOffset_Start_Angle_J2 = (float)0.0;
    float fOffset_Start_Angle_J3 = (float)0.0;
    float fOffset_Start_Angle_J4 = (float)0.0;
    float fOffset_Start_Angle_J5 = (float)0.0;
    float fOffset_Start_Angle_J6 = (float)0.0;

    // MAIN LOOP
    bool bSocketStatus;
    bSocketStatus = Communicator.initSocket();

    while(loop && ros::ok() && bSocketStatus)
    {
            memset(&MXTsend, 0, sizeof(MXTsend));
            memset(&MXTrecv, 0, sizeof(MXTrecv));

            // Transmission data creation
            if(loop==1)
            {   // Only for the first control cycle
                MXTsend.Command = MXT_CMD_NULL;
                MXTsend.SendType = MXT_TYP_NULL;
                MXTsend.RecvType = iControl_type;
                MXTsend.SendIOType = MXT_IO_NULL;
                MXTsend.RecvIOType = IOSendType;
                MXTsend.CCount = counter = 0;
            }
            else
            {   // Second and following times
                MXTsend.Command = MXT_CMD_MOVE;
                MXTsend.SendType = iControl_type;
                MXTsend.RecvType = cData_Type_Monitor[0];
                MXTsend.RecvType1= cData_Type_Monitor[1];
                MXTsend.RecvType2= cData_Type_Monitor[2];
                MXTsend.RecvType3= cData_Type_Monitor[3];

                switch(iControl_type)
                {
                    case MXT_TYP_JOINT:
                            // get initial joint configuration
                            memcpy(&MXTsend.dat.jnt, &jnt_now, sizeof(JOINT));
                            // add angle offset to initial joint configuration
                            MXTsend.dat.jnt.j1 += (float)(fOffset_Start_Angle_J1 * 3.141592/180.0);
                            MXTsend.dat.jnt.j2 += (float)(fOffset_Start_Angle_J2 * 3.141592/180.0);
                            MXTsend.dat.jnt.j3 += (float)(fOffset_Start_Angle_J3 * 3.141592/180.0);
                            MXTsend.dat.jnt.j4 += (float)(fOffset_Start_Angle_J4 * 3.141592/180.0);
                            MXTsend.dat.jnt.j5 += (float)(fOffset_Start_Angle_J5 * 3.141592/180.0);
                            MXTsend.dat.jnt.j6 += (float)(fOffset_Start_Angle_J6 * 3.141592/180.0);
                            break;
                    case MXT_TYP_POSE:
                            // get initial position
                            memcpy(&MXTsend.dat.pos, &pos_now, sizeof(POSE));
                            // add offset to initial position
                            MXTsend.dat.pos.w.x += fOffset_Start_Pos_X;
                            MXTsend.dat.pos.w.y += fOffset_Start_Pos_Y;
                            MXTsend.dat.pos.w.z += fOffset_Start_Pos_Z;
                            MXTsend.dat.pos.w.a += fOffset_Orientation_X;
                            MXTsend.dat.pos.w.b += fOffset_Orientation_Y;
                            MXTsend.dat.pos.w.c += fOffset_Orientation_Z;
                            break;
                    case MXT_TYP_PULSE:
                            cout << "Command type Pulse not supported. Shutting down." << endl;
                            Communicator.closeSocket();
                            return(0);
                            break;
                    default:
                            break;
                }
                // set other binary command specific variables. For explanation see data structure.
                MXTsend.SendIOType = IOSendType;
                MXTsend.RecvIOType = IORecvType;
                MXTsend.BitTop = IOBitTop;
                MXTsend.BitMask =IOBitMask;
                MXTsend.IoData = IOBitData;
                MXTsend.CCount = counter;
            }

            // check if robot is supposed to move
            if(bAnytime_Stop || bBuffer_Overflow)
            {
                cout << "Anytime_Stop activated or buffer overflow imminent. Shutting down." << endl;
                Communicator.closeSocket();
                return(0);
            }

            // send data to Robot
            bool bSendStatus;
            bSendStatus = Communicator.sendToRobot(MXTsend);
            if(!bSendStatus)
            {
                Communicator.closeSocket();
                return(0);
            }

            //  unpack new command in queue if queue is not emtpy
            bool bIsBufferEmpty;
            bIsBufferEmpty = CommandBuffer.isBufferEmpty();
            if(!bIsBufferEmpty)
            {
                mitsubishi_melfa::MelfaCommand NextCommand;
                NextCommand = CommandBuffer.popNextCommand();

                iControl_type = NextCommand.iControl_type;
                cData_Type_Monitor[0] = NextCommand.Type_Monitor1;
                cData_Type_Monitor[1] = NextCommand.Type_Monitor2;
                cData_Type_Monitor[2] = NextCommand.Type_Monitor3;
                cData_Type_Monitor[3] = NextCommand.Type_Monitor4;

                if(iControl_type == MXT_TYP_POSE)
                {
                    fOffset_Start_Pos_X = (float) (NextCommand.x);
                    fOffset_Start_Pos_Y = (float) (NextCommand.y);
                    fOffset_Start_Pos_Z = (float) (NextCommand.z);
                    fOffset_Orientation_X = (float) (NextCommand.rot_x);
                    fOffset_Orientation_Y = (float) (NextCommand.rot_y);
                    fOffset_Orientation_Z = (float) (NextCommand.rot_z);
                }
                else if(iControl_type == MXT_TYP_JOINT)
                {
                    fOffset_Start_Angle_J1 = (float) NextCommand.j1;
                    fOffset_Start_Angle_J2 = (float) NextCommand.j2;
                    fOffset_Start_Angle_J3 = (float) NextCommand.j3;
                    fOffset_Start_Angle_J4 = (float) NextCommand.j4;
                    fOffset_Start_Angle_J5 = (float) NextCommand.j5;
                    fOffset_Start_Angle_J6 = (float) NextCommand.j6;
                }
                else
                {
                    cout << "Invalid command type. Shutting down." << endl;
                    Communicator.closeSocket();
                    return(0);
                }
            }

            // No. of reception retries
            retry = 1;
            bool bRobotCompletedCommand;
            while(retry)
            {
                // Check whether command is finished
                bRobotCompletedCommand = Communicator.completedCommand();
                if(bRobotCompletedCommand)
                {
                    // when it does, receive status
                    MXTrecv = Communicator.recieveFromToRobot();

                    //break up recieved data
                    int DispType;
                    void *DispData;
                    switch(disp_data)
                    {
                      case 0:
                                DispType = MXTrecv.RecvType;
                                DispData = &MXTrecv.dat;
                                break;
                      case 1:
                                DispType = MXTrecv.RecvType1;
                                DispData = &MXTrecv.dat1;
                                break;
                      case 2:
                                DispType = MXTrecv.RecvType2;
                                DispData = &MXTrecv.dat2;
                                break;
                      case 3:
                                DispType = MXTrecv.RecvType3;
                                DispData = &MXTrecv.dat3;
                                break;
                      default:
                            break;
                    }

                    // wrap in ROS message
                    mitsubishi_melfa::MelfaCommand MelfaStatus;
                    switch(DispType)
                    {
                        case MXT_TYP_JOINT:
                        case MXT_TYP_FJOINT:
                        case MXT_TYP_FB_JOINT:
                                if(loop==1)
                                {
                                    //save starting angles
                                    memcpy(&jnt_now, DispData, sizeof(JOINT));
                                    loop = 2;
                                }
                                //get Data
                                JOINT *p_joints;
                                p_joints=(JOINT*)DispData;

                                //wrap information to ROS message
                                MelfaStatus.iControl_type = 2;
                                MelfaStatus.j1 = p_joints->j1;
                                MelfaStatus.j2 = p_joints->j2;
                                MelfaStatus.j3 = p_joints->j3;
                                MelfaStatus.j4 = p_joints->j4;
                                MelfaStatus.j5 = p_joints->j5;
                                MelfaStatus.j6 = p_joints->j6;

                                break;
                        case MXT_TYP_POSE:
                        case MXT_TYP_FPOSE:
                        case MXT_TYP_FB_POSE:
                                if(loop==1)
                                {
                                    //save starting position
                                    memcpy(&pos_now, &MXTrecv.dat.pos, sizeof(POSE));
                                    loop = 2;
                                }
                                //get Data
                                POSE *p;
                                p=(POSE*)DispData;

                                //wrap information to ROS message
                                MelfaStatus.iControl_type = 1;
                                MelfaStatus.x = p->w.x;
                                MelfaStatus.y = p->w.y;
                                MelfaStatus.z = p->w.z;
                                MelfaStatus.rot_x = p->w.a;
                                MelfaStatus.rot_y = p->w.b;
                                MelfaStatus.rot_z = p->w.c;

                                break;
                        case MXT_TYP_PULSE:
                        case MXT_TYP_FPULSE:
                        case MXT_TYP_FB_PULSE:
                        case MXT_TYP_CMDCUR:
                        case MXT_TYP_FBKCUR:
                                if(loop==1) {
                                  memcpy(&pls_now, &MXTrecv.dat.pls, sizeof(PULSE));
                                  loop = 2;
                                }
                                // TODO: wrap to ROS message if control type becomes of interest.
                                break;
                        case MXT_TYP_NULL:
                                if(loop==1) {
                                  loop = 2;
                                }
                                break;
                        default:
                                cout << "Bad data type.\n" << endl;
                                break;
                    }
                    // publish status
                    Status_Publisher.publish(MelfaStatus);
                    // Count up only when communication is successful
                    counter++;
                    // Leave reception loop
                    retry=0;
                    // call ROS callbacks
                    ros::spinOnce();
                }
                // Reception timeout
                else
                {
                    cout << "... Receive Timeout! <Push [Enter] to stop the program>" << endl;
                    // No. of retries subtraction
                    retry--;

                    if(retry==0)
                    {
                        // End program if No. of retries is 0
                        loop=0;
                    }
                }
            } /* while(retry) */
        } /* while(loop) */

        // End. Close network connection.
        Communicator.closeSocket();
        return (0);
}

