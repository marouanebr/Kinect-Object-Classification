// sample.cpp
// for Linux

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "strdef2.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define NO_FLAGS_SET 0
#define MAXBUFLEN 512

// for kbhit & getch
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

// those definition is from winsock.h
/*
 * The new type to be used in all
 * instances which refer to sockets.
 */
typedef u_int           SOCKET;
/*
/*
 * This is used instead of -1, since the
 * SOCKET type is unsigned.
 */
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)
typedef struct sockaddr *LPSOCKADDR;


// substitute for Windows kbhit()
// http://tricky-code.net/mine/c/mc06linuxkbhit.php
int kbhit(void){
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// substitute  for windows <conio.h> getch()
//http://cboard.cprogramming.com/faq-board/27714-faq-there-getch-conio-equivalent-linux-unix.html
int getch( ) {
  struct termios oldt,
                 newt;
  int            ch;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return ch;
}


int main() {
  struct sockaddr_in destSockAddr;
  SOCKET destSocket;
  unsigned long destAddr;
  int status;
  int numsnt;
  int numrcv;
  char sendText[MAXBUFLEN];
  char recvText[MAXBUFLEN];
  char dst_ip_address[MAXBUFLEN];
  unsigned short port;
  char msg[MAXBUFLEN];
  char buf[MAXBUFLEN];
  char type, type_mon[4];
  unsigned short IOSendType;// Send input/output signal data designation
  unsigned short IORecvType;// Reply input/output signal data designation
  unsigned short IOBitTop=0;
  unsigned short IOBitMask=0xffff;
  unsigned short IOBitData=0;
  unsigned int tmpVar; // to input data from sscanf()

  cout << " Input connection destination IP address (192.168.0.20) -> ";
  //cout << " Input connection destination IP address (10.0.206.70) -> ";
  cin.getline(dst_ip_address, MAXBUFLEN);

  if(dst_ip_address[0]==0) strcpy(dst_ip_address, "192.168.0.20");
  //if(dst_ip_address[0]==0) strcpy(dst_ip_address, "10.0.206.70");

  cout << " Input connection destination port No. (10000) -> ";
  cin.getline(msg, MAXBUFLEN);
  
  if(msg[0]!=0) port=atoi(msg);
  else port=10000;
  
  cout << " R/C has I/O signal(ex.Std remote I/O,hand,remote I/O for CC-link,etc.)\n";
  cout << "   Use input/output signal?([Y] /*[N])-> ";
  cin.getline(msg, MAXBUFLEN);
  
  if(msg[0]!=0 && (msg[0]=='Y' || msg[0]=='y')) {
    cout << "What is target? Input signal/output signal(*[I]nput /[O]utput)-> ";
    cin.getline(msg, MAXBUFLEN);

    switch(msg[0]) {
    case 'O':// Set target to output signal
    case 'o':
      IOSendType = MXT_IO_OUT;
      IORecvType = MXT_IO_OUT;
      break;
    case 'I':// Set target to input signal
    case 'i':
    default:
      IOSendType = MXT_IO_NULL;
      IORecvType = MXT_IO_IN;
      break;
    }
    
    cout << " Input head bit No. (0 to 32767)-> ";
    cin.getline(msg, MAXBUFLEN);
    
    if(msg[0]!=0) IOBitTop = atoi(msg);
    else IOBitTop = 0;
  
    if(IOSendType==MXT_IO_OUT) { // Only for output signal
      cout << "Input bit mask pattern for output as hexadecimal (0000 to FFFF)-> ";

      cin.getline(msg, MAXBUFLEN);
      if(msg[0]!=0) {
	sscanf(msg,"%04x",&tmpVar);
	IOBitMask = static_cast<unsigned short>(tmpVar);
      }
      else IOBitMask = 0;
      cout << "Input bit data for output as hexadecimal (0000 to FFFF)-> ";
      cin.getline(msg, MAXBUFLEN);
      if(msg[0]!=0){
	sscanf(msg,"%04x",(uint *) &tmpVar);
	IOBitData = static_cast<unsigned short>(tmpVar);
      }
      else IOBitData = 0;
      
    }
  }
  cout <<" --- Input the data type of command. --- \n";
  cout <<"[0: None / 1: XYZ / 2:JOINT / 3: PULSE]\n";
  cout <<" -- please input the number -- [0] - [3]-> ";
  cin.getline(msg, MAXBUFLEN);
  type = atoi(msg);
  
  for(int k=0; k<4; k++) {
    sprintf (msg," --- input the data type of monitor ( %d-th ) --- \n", k);
      cout << msg;
      cout << "[0: None]\n";
      cout << "[1: XYZ / 2:JOINT / 3: PULSE] Command value \n";
      cout << "[4: XYZ/ 5: JOINT/ 6: PULSE] Command value after the filter process \n";
      cout << "[7: XYZ/ 8:JOINT/ 9:PULSE] Feedback value. \n";
      cout << "[10: Electric current value / 11: Electric current feedback] ... Electric current value. \n";
      cout << "Input the numeral [0] to [11] -> ";
      cin.getline(msg, MAXBUFLEN);
      type_mon[k] = atoi(msg);
  }
  sprintf(msg, "IP=%s / PORT=%d / Send Type=%d / Monitor Type0/1/2/3=%d/%d/%d/%d"
	  , dst_ip_address, port , type
	  , type_mon[0], type_mon[1], type_mon[2], type_mon[3]);
  cout << msg << endl;
  cout << " [g]= End MXT mode / [d]= Monitor data display \n";
  cout << "   [0/1/2/3]= Change of monitor data display \n";
  cout << " [z/x]= Inc/Dec 1st command(X/J1/p1) by the delta amount. \n";
  cout << " [a/s]= Inc/Dec 2nd command(Y/J2/p2) by the delta amount. \n";
  cout << " [q/w]= Inc/Dec 3rd command(Z/J3/p3) by the delta amount. \n";
  cout << " [Shift+c]= [CAUTION! Move Very quick!!] Return to initial position. \n";
  cout << "  Is it all right? [Enter:Start MXT] / [Ctrl+C:Abort] : ";
  cin.getline(msg, MAXBUFLEN);
  
  // IP address, port, etc., setting
  memset(&destSockAddr, 0, sizeof(destSockAddr));
  destAddr=inet_addr(dst_ip_address);
  memcpy(&destSockAddr.sin_addr, &destAddr, sizeof(destAddr));
  destSockAddr.sin_port=htons(port);
  destSockAddr.sin_family=AF_INET;
  // Socket creation
  destSocket=socket(AF_INET, SOCK_DGRAM, 0);
  
  if (destSocket == INVALID_SOCKET) {
    cerr << "ERROR: socket unsuccessful" << endl;
    return(1);
  }

  MXTCMD MXTsend;
  MXTCMD MXTrecv;
  JOINT jnt_now;
  POSE pos_now;
  PULSE pls_now;
  unsigned long counter = 0;
  int loop = 1;
  int disp = 0;
  int disp_data = 0;
  int ch;
  float delta1=(float)0.0;
  float delta2=(float)0.0;
  float delta3=(float)0.0;
  long ratio=1;
  int retry;
  fd_set SockSet;// Socket group used with select
  timeval sTimeOut;// For timeout setting
  float r2d = 180.0/3.141592;

  
  memset(&MXTsend, 0, sizeof(MXTsend));
  memset(&jnt_now, 0, sizeof(JOINT));
  memset(&pos_now, 0, sizeof(POSE));
  memset(&pls_now, 0, sizeof(PULSE));

  while(loop) {
    memset(&MXTsend, 0, sizeof(MXTsend));
    memset(&MXTrecv, 0, sizeof(MXTrecv));

    // Transmission data creation
    if(loop==1) {// Only first time
      MXTsend.Command = MXT_CMD_NULL;
      MXTsend.SendType = MXT_TYP_NULL;
      MXTsend.RecvType = type;
      MXTsend.SendIOType = MXT_IO_NULL;
      MXTsend.RecvIOType = IOSendType;
      MXTsend.CCount = counter = 0;
    }
    else {// Second and following times
      MXTsend.Command = MXT_CMD_MOVE;
      MXTsend.SendType = type;
      MXTsend.RecvType = type_mon[0];
      MXTsend.RecvType1= type_mon[1];
      MXTsend.RecvType2= type_mon[2];
      MXTsend.RecvType3= type_mon[3];
      switch(type) {
      case MXT_TYP_JOINT:
	memcpy(&MXTsend.dat.jnt, &jnt_now, sizeof(JOINT));
	MXTsend.dat.jnt.j1 += (float)(delta1*ratio*3.141592/180.0);
	MXTsend.dat.jnt.j2 += (float)(delta2*ratio*3.141592/180.0);
	MXTsend.dat.jnt.j3 += (float)(delta3*ratio*3.141592/180.0);
	break;
      case MXT_TYP_POSE:
	memcpy(&MXTsend.dat.pos, &pos_now, sizeof(POSE));
	MXTsend.dat.pos.w.x += (delta1*ratio);
	MXTsend.dat.pos.w.y += (delta2*ratio);
	MXTsend.dat.pos.w.z += (delta3*ratio);
	break;
      case MXT_TYP_PULSE:
	memcpy(&MXTsend.dat.pls, &pls_now, sizeof(PULSE));
	MXTsend.dat.pls.p1 += (long)((delta1*ratio)*10);
	MXTsend.dat.pls.p2 += (long)((delta2*ratio)*10);
	MXTsend.dat.pls.p3 += (long)((delta3*ratio)*10);
	break;
      default:
	break;
      }
      
      MXTsend.SendIOType = IOSendType;
      MXTsend.RecvIOType = IORecvType;
      MXTsend.BitTop = IOBitTop;
      MXTsend.BitMask =IOBitMask;
      MXTsend.IoData = IOBitData;
      MXTsend.CCount = counter;
    }
    
    // Keyboard input
    // [q]=End / [d]= Display the monitor data, or none / [0/1/2/3]= Change of monitor data display
    // [z/x]=Increment/decrement first command data transmitted by the delta amount
    while(kbhit()!=0) {
      ch=getch();
      switch(ch) {
      case 'G':
      case 'g':
	MXTsend.Command = MXT_CMD_END;
	loop = 0;
	break;
      case 'Z':
      case 'z':
	delta1 += (float)0.5;
	break;
      case 'X':
      case 'x':
	delta1 -= (float)0.5;
	break;
      case 'A':
      case 'a':
	delta2 += (float)0.5;
	break;
      case 'S':
      case 's':
	delta2 -= (float)0.5;
	break;
      case 'Q':
      case 'q':
	delta3 += (float)0.5;
	break;
      case 'W':
      case 'w':
	delta3 -= (float)0.5;
	break; 
      case 'C':
	delta1 = (float)0.0;
	delta2 = (float)0.0;
	delta3 = (float)0.0;
	break;
      case 'd':
	disp = ~disp;
	break;
      case '0': case '1': case '2': case '3':
	disp_data = ch - '0';
	break;
      }
    }
    
    memset(sendText, 0, MAXBUFLEN);
    memcpy(sendText, &MXTsend, sizeof(MXTsend));

    if(disp) {
      sprintf(buf, "Send (%ld):",counter);
      cout << buf << endl;
    }
    numsnt=sendto(destSocket, sendText, sizeof(MXTCMD), NO_FLAGS_SET
		  , (LPSOCKADDR) &destSockAddr, sizeof(destSockAddr));
    
    if (numsnt != sizeof(MXTCMD)) {
      cerr << "ERROR: sendto unsuccessful" << endl;
      status=close(destSocket);

      if (status == SOCKET_ERROR)
	cerr << "ERROR: close unsuccessful" << endl;

      return(1);
    }

    memset(recvText, 0, MAXBUFLEN);
    retry = 1;// No. of reception retries

    while(retry) {
      FD_ZERO(&SockSet);// SockSet initialization
      FD_SET(destSocket, &SockSet);// Socket registration
      sTimeOut.tv_sec = 1;// Transmission timeout setting (sec)
      sTimeOut.tv_usec = 0;// (u sec)
      status = select(destSocket+1, &SockSet, (fd_set *)NULL, (fd_set *)NULL, &sTimeOut);

      if(status == SOCKET_ERROR) {
	return(1);
      }
      // If it receives by the time-out
      if((status > 0) && (FD_ISSET(destSocket, &SockSet) != 0)) {
	numrcv=recvfrom(destSocket, recvText, MAXBUFLEN, NO_FLAGS_SET, NULL, NULL);
	
	if (numrcv == SOCKET_ERROR) {
	  
	  cerr << "ERROR: recvfrom unsuccessful" << endl;
	  status=close(destSocket);
	  
	  if (status == SOCKET_ERROR)
	    cerr << "ERROR: close unsuccessful" << endl;

	  return(1);
	}
	
	memcpy(&MXTrecv, recvText, sizeof(MXTrecv));
	char str[10];
	
	if(MXTrecv.SendIOType==MXT_IO_IN)
	  sprintf(str,"IN%04x", MXTrecv.IoData);
	else if(MXTrecv.SendIOType==MXT_IO_OUT)
	  sprintf(str,"OT%04x", MXTrecv.IoData);
	else sprintf(str,"------");
	
	int DispType;
	void *DispData;

	switch(disp_data) {
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
	
	switch(DispType) {
	case MXT_TYP_JOINT:
	case MXT_TYP_FJOINT:
	case MXT_TYP_FB_JOINT:
	  if(loop==1) {
	    memcpy(&jnt_now, DispData, sizeof(JOINT));
	    loop = 2;
	  }
	  if(disp) {
	    JOINT *j=(JOINT*)DispData;
	    sprintf(buf, "Receive (%d): TCount=%d Type(JOINT)=%d\n %7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f (%s)"
		    ,MXTrecv.CCount,MXTrecv.TCount,DispType
		    ,(j->j1)*r2d,(j->j2)*r2d,(j->j3)*r2d,(j->j4)*r2d,(j->j5)*r2d,(j->j6)*r2d,(j->j7)*r2d,(j->j8)*r2d, str);
	    cout << buf << endl;
	    //		    ,j->j1, j->j2, j->j3 ,j->j4, j->j5, j->j6, j->j7, j->j8, str);
	    
	  }
	  break;
	case MXT_TYP_POSE:
	case MXT_TYP_FPOSE:
	case MXT_TYP_FB_POSE:
	  if(loop==1) {
	    memcpy(&pos_now, &MXTrecv.dat.pos, sizeof(POSE));
	    loop = 2;
	  }
	  if(disp) {
	    POSE *p=(POSE*)DispData;
	    sprintf(buf, "Receive (%d): TCount=%d Type(POSE)=%d\n %7.2f,%7.2f,%7.2f,%7.2f,%7.2f,%7.2f, %04x,%04x (%s)"
		    ,MXTrecv.CCount,MXTrecv.TCount,DispType
		    ,p->w.x, p->w.y, p->w.z, p->w.a, p->w.b, p->w.c
		    , p->sflg1, p->sflg2, str);
	    cout << buf << endl;
	  }
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
	  if(disp) {
	    PULSE *l=(PULSE*)DispData;
	    sprintf(buf, "Receive (%d): TCount=%d Type(PULSE/OTHER)=%d\n %d,%d,%d,%d,%d,%d,%d,%d (%s)"
		    ,MXTrecv.CCount,MXTrecv.TCount,DispType
		    ,l->p1, l->p2, l->p3, l->p4, l->p5, l->p6, l->p7, l->p8, str);
	    cout << buf << endl;
	  }
	  break;
	case MXT_TYP_NULL:
	  if(loop==1) {
	    loop = 2;
	  }
	  if(disp) {
	    sprintf(buf, "Receive (%d): TCount=%d Type(NULL)=%d\n (%s)"
		    ,MXTrecv.CCount,MXTrecv.TCount, DispType, str);
	    cout << buf << endl;
	  }
	  break;
	default:
	  cout << "Bad data type.\n" << endl;
	  break;
	}
	
	counter++;// Count up only when communication is successful
	retry=0;// Leave reception loop
      }
      else { // Reception timeout
	cout << "... Receive Timeout! <Push [Enter] to stop the program>" << endl;
	
	retry--;// No. of retries subtraction
	if(retry==0) loop=0; // End program if No. of retries is 0
      }
    } /* while(retry) */
  } /* while(loop) */
  // End
  
  cout << "/// End /// ";
  sprintf(buf, "counter = %ld", counter);
  cout << buf << endl;

  //Close socket
  status=close(destSocket);

  if (status == SOCKET_ERROR)
    cerr << "ERROR: close unsuccessful" << endl;
  
  return 0;
}
