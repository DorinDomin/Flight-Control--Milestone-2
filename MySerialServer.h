//
// Created by netanel on 07/01/2020.
//
#include "server_side.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include <thread>
using namespace std;
mutex mutex_lock6;
bool runServer2 = true;

#ifndef EX4__MYSERIALSERVER_H_
#define EX4__MYSERIALSERVER_H_
using namespace server_side;
class MySerialServer : public server_side::Server {
 public:
  void stop();
  void runWhile(int &sockfd, sockaddr_in &address, ClientHandler * c);
  void open(int port ,ClientHandler * c);
};
void MySerialServer::stop() {
  mutex_lock6.lock();
  if (runServer2) {
    runServer2 = false;
  }
  mutex_lock6.unlock();
}
void MySerialServer::runWhile(int &sockfd, sockaddr_in &address,ClientHandler * c) {
  int client_socket;
  // set timeout
  timeval tv;
  tv.tv_sec=30;
  tv.tv_usec=0;
  setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,(const char *)&tv,sizeof(tv));
  while (true) {
    mutex_lock6.lock();
    if(!runServer2){
      mutex_lock6.unlock();
      break;
    }
    mutex_lock6.unlock();
    //Socket Accepts Client
    client_socket = accept(sockfd, (struct sockaddr *) &address, (socklen_t *) &address);
    if(client_socket==-1) {
      if(errno==EWOULDBLOCK){
        cout<<"TIMEOUT"<<endl;
        stop();
      }
      else{
        cout << "Error Accepting Client" << endl;
        throw ("Error accepting client");
      }
    }
    else {
      cout << "opened connection with client" << endl;
      //handle client
      c->handleClient(client_socket);
    }
    close(client_socket);
  }
  //Closes sockets
  close(sockfd);
}
void MySerialServer::open(int port,ClientHandler * client_handler) {
  //Creates Socket
  int sockfd = 0;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    cout << "1" << endl;
    throw ("Error creating socket");
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  //Binds socket to ip and port
  while (true) {
    if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
      cout << "Could not bind socket to ip" << endl;
    } else {
      break;
    }
  }
  //Starts Listening
  if (listen(sockfd, SOMAXCONN) == -1) {
    cout << "3" << endl;
    throw ("Error during listening command");
  }
  cout << "opening server" << endl;
  std::thread helpClients(&MySerialServer::runWhile, this, ref(sockfd), ref(address),client_handler);
  helpClients.detach();
  while (true){
    mutex_lock6.lock();
    if(!runServer2){
      mutex_lock6.unlock();
      break;
    }
    mutex_lock6.unlock();
  }
  //runWhile(sockfd,address,port);
}
#endif //EX4__MYSERIALSERVER_H_
