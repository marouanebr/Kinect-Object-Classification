// Header of melfa communication class
#ifndef UDPCOMMUNICATION_HPP
#define UDPCOMMUNICATION_HPP

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <limits.h>
#include <fstream>
// message struct
#include "UDPCommand.h"
// for sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


/**
 * @brief The UDPCommunication class handles the network communication betwen computer and manipulator.
 */

class  UDPCommunication
{
  private:
    typedef u_int SOCKET;
    typedef struct sockaddr *LPSOCKADDR;    

    /**
     * @brief m_uiInvalid_Socket Error code for the case "Invalid Socket"
     */
    unsigned int m_uiInvalid_Socket;

    /**
     * @brief m_iSocket_Error Error code for faulty socket
     */
    int m_iSocket_Error;

    /**
     * @brief m_uiNo_Flags_Set
     */
    unsigned int m_uiNo_Flags_Set;

    /**
     * @brief m_uiMax_Buffer_Length Defines the maximum length of the controller command
     */
    unsigned int m_uiMax_Buffer_Length;

    /**
     * @brief m_Destination_Socket Hold the adress of the destination socket
     */
    SOCKET m_Destination_Socket;

    /**
     * @brief m_pcDestination_IP_Address Holds the IP adress set for the computer
     */
    char m_pcDestination_IP_Address[512];

    /**
     * @brief m_usPort Holds the port set for the computer
     */
    unsigned short m_usPort;
    struct sockaddr_in  m_strDestination_Socket_Address;

public:
    /**
   * @brief This is the constructor of the UDP communication class
   */
    UDPCommunication();

    /**
     * @brief This function initializes the network connection between the controller and the computer
     * @return boolean
     */
    bool initSocket();

    /**
     * @brief This function sends a binary command to the controller
     * @param MXTsend Data structure defined by Mitusbishi electric. Command for the Controller.
     * @return boolean
     */
    bool sendToRobot(MXTCMD MXTsend);

    /**
     * @brief This function receives a binary command from the controller
     * @return Data structure defined by Mitusbishi electric. Command from the Controller.
     */
    MXTCMD recieveFromToRobot();

    /**
     * @brief This function checks whether the manipulator has already processed its current command.
     * @return boolean
     */
    bool completedCommand();

    /**
     * @brief This function closes the network connection.
     */
    void closeSocket();
};

#endif
