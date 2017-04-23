// Source file of UDPCommunication class

#include <mitsubishi_melfa/UDPCommunication.hpp>

UDPCommunication::UDPCommunication()
{
  // for socket communication and verification
  m_uiInvalid_Socket = INT_MAX;
  m_iSocket_Error = -1;
  m_uiNo_Flags_Set = 0;
  m_uiMax_Buffer_Length = 512;

  // set IP adress
  strcpy(m_pcDestination_IP_Address, "192.168.0.20");

  // set port
  m_usPort = 10000;
}


bool UDPCommunication::initSocket()
{
  // clear
  memset(&m_strDestination_Socket_Address, 0, sizeof(m_strDestination_Socket_Address));

  // convert the host address cp from IPv4 numbers-and-dots notation into binary data in network byte order   
  unsigned long ulDestinationAddress;
  ulDestinationAddress = inet_addr(m_pcDestination_IP_Address);

  //copy to socket structure    
  memcpy(&m_strDestination_Socket_Address.sin_addr, &ulDestinationAddress, sizeof(ulDestinationAddress));

  // convert the unsigned short integer hostshort from host byte order to network byte order and save to structure
  m_strDestination_Socket_Address.sin_port=htons(m_usPort);

  // IPv4 Internet protocols
  m_strDestination_Socket_Address.sin_family=AF_INET;

  // Socket creation: socket(int domain, int type, int protocol);
  m_Destination_Socket=socket(AF_INET, SOCK_DGRAM, 0);

  if (m_Destination_Socket == m_uiInvalid_Socket) 
  {
    std::cerr << "ERROR: Socket initialization unsuccessful" << std::endl;
    return(false);
  }
  else
  {
    std::cout << "Socket initialized." << std::endl;
    return(true);
  }

}

bool UDPCommunication::sendToRobot(MXTCMD MXTsend)
{
  char sendText[m_uiMax_Buffer_Length];
  int iNum_Bytes_Sent;

  // set send variable to zero   
  memset(sendText, 0, m_uiMax_Buffer_Length);
  //copy command to send variable
  memcpy(sendText, &MXTsend, sizeof(MXTsend));

  // send data to control box
  // ssize_t sendto(      int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
  iNum_Bytes_Sent=sendto(m_Destination_Socket, sendText, sizeof(MXTCMD), m_uiNo_Flags_Set, (LPSOCKADDR) &m_strDestination_Socket_Address, sizeof(m_strDestination_Socket_Address));
  
  // check whether send was successful
  int status;
  if (iNum_Bytes_Sent != sizeof(MXTCMD)) 
  {
    std::cerr << "ERROR: sendto unsuccessful" << std::endl;
    status=close(m_Destination_Socket);

    if (status == m_iSocket_Error)
    {
        std::cerr << "ERROR: close unsuccessful" << std::endl;
    }

      return(0);
  }
  else
  {
    //std::cout << "Send successful." << std::endl;

    // if everything went according to plan
    return(true);
  }


}

bool UDPCommunication::completedCommand()
{    
  fd_set SockSet;// Socket group used with select
  timeval sTimeOut;// For timeout setting

  //check whether robot has completed command
  FD_ZERO(&SockSet);// SockSet initialization
  FD_SET(m_Destination_Socket, &SockSet);// Socket registration
  sTimeOut.tv_sec = 1;// Transmission timeout setting (sec)
  sTimeOut.tv_usec = 0;// (u sec)    

  int status;
  status = select(m_Destination_Socket+1, &SockSet, (fd_set *)NULL, (fd_set *)NULL, &sTimeOut);

  if(status == m_iSocket_Error) 
  {
    return(1);
  }

  bool bReady;
  bReady = (status > 0) && (FD_ISSET(m_Destination_Socket, &SockSet) != 0);

  if(bReady)
  {
    //std::cout << "Command completed." << std::endl;
  }
  else
  {
    std::cout << "Command not yet completed." << std::endl;
  }

  return(bReady);

}

MXTCMD UDPCommunication::recieveFromToRobot()
{    
  MXTCMD MXTrecv;
  memset(&MXTrecv, 0, sizeof(MXTrecv));

  // get response of robot
  int iNum_Recieved_Bytes;
  char recvText[m_uiMax_Buffer_Length];
  iNum_Recieved_Bytes=recvfrom(m_Destination_Socket, recvText, m_uiMax_Buffer_Length, m_uiNo_Flags_Set, NULL, NULL);

  // check if recieve was successful 
  int status;   
  if (iNum_Recieved_Bytes == m_iSocket_Error) 
  {
    std::cerr << "ERROR: recvfrom unsuccessful" << std::endl;
    status=close(m_Destination_Socket);

    if (status == m_iSocket_Error)
    {
      std::cerr << "ERROR: close unsuccessful" << std::endl;
    }
    
  }
  else
  {
    //std::cout << "Recieve successful." << std::endl;
  }

  // copy recieved text into command format
  memcpy(&MXTrecv, recvText, sizeof(MXTrecv));
  //return answer
  return(MXTrecv);
}


void UDPCommunication::closeSocket()
{    
  //Close socket
  int status;
  status=close(m_Destination_Socket);

  if (status == m_iSocket_Error)
  {
    std::cerr << "ERROR: close unsuccessful" << std::endl;
  }
  else
  {
    std::cout << "Socket closure successful." << std::endl;
  }
}

