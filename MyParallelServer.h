//
// Created by dorin on 15/01/2020.
//
#include <iostream>
#include "server_side.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <ctime>
//using namespace std;
#ifndef EX4__MYPARALLELSERVER_H_
#define EX4__MYPARALLELSERVER_H_
using namespace server_side;
#define limitTime 45
sockaddr_in socketaddress;
int socketfd=0;
bool waiting=false;
int connections=0;
list<ClientHandler*> clienthandlers;
class MyParallelServer : public server_side::Server {
 public:
  void stop();
  void open(int port, ClientHandler *c);
  static void openNewThread(ClientHandler *c);
};
void MyParallelServer::openNewThread(ClientHandler *c){
  int client_socket;
  // set timeout
  timeval tv;
  tv.tv_sec=120;
  tv.tv_usec=0;
  setsockopt(socketfd,SOL_SOCKET,SO_RCVTIMEO,(const char *)&tv,sizeof(tv));
  //Socket Accepts Client
  client_socket = accept(socketfd, (struct sockaddr *) &socketaddress, (socklen_t *) &socketaddress);
  if(client_socket==-1) {
    if(errno==EWOULDBLOCK){
      cout<<"TIMEOUT"<<endl;
      return;
    }
    else{
      cout << "Error Accepting Client" << endl;
      //throw ("Error accepting client");
    }
  }
  mutex_lock2.lock();
  connections++;
  waiting=false;
  mutex_lock2.unlock();
  //mutex_lock2.lock();
  ClientHandler * cc=c->copy();
  cc->handleClient(client_socket);
  //c->handleClient(client_socket);
  //mutex_lock2.unlock();
  //delete (cc);
  mutex_lock2.lock();
  connections--;
  mutex_lock2.unlock();
  //cout<<"END"<<endl;
  return;
}
void MyParallelServer::stop() {
}
void MyParallelServer::open(int port, ClientHandler *c) {
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == -1) {
    cout << "1" << endl;
    throw ("Error creating socket");
  }
  socketaddress.sin_family = AF_INET;
  socketaddress.sin_addr.s_addr = INADDR_ANY;
  socketaddress.sin_port = htons(port);
  while (true) {
    if (bind(socketfd, (struct sockaddr *) &socketaddress, sizeof(socketaddress)) == -1) {
      cout << "Could not bind socket to ip" << endl;
    } else {
      break;
    }
  }
  if (listen(socketfd, SOMAXCONN) == -1) {
    throw ("Error during listening command");
  }
  while(true){
    mutex_lock2.lock();
    if(!waiting){
      thread t(openNewThread,c);
      t.detach();
      waiting=true;
    }
    mutex_lock2.unlock();
    clock_t start = clock();
    double duration = (clock() - start) / (double) CLOCKS_PER_SEC;
    mutex_lock2.lock();
    while (connections == 0 && 2000*duration < limitTime) {
      mutex_lock2.unlock();
      this_thread::sleep_for(chrono::milliseconds(200));
      //cout<<"dur: "+ to_string(2000*duration)<<endl;
      duration = (clock() - start) / (double) CLOCKS_PER_SEC;
      mutex_lock2.lock();
    }
    mutex_lock2.unlock();
    mutex_lock2.lock();
    if (connections == 0 && 2000*duration >= limitTime) {
      mutex_lock2.unlock();
      cout << "parallel TIMEOUT" << endl;
      break;
    }
    //this_thread::sleep_for(chrono::milliseconds(20));
    mutex_lock2.unlock();
  }
  close(socketfd);
}

#endif //EX4__MYPARALLELSERVER_H_
