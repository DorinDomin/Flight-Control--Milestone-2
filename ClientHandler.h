#include <iostream>
#ifndef EX4__CLIENTHANDLER_H_
#define EX4__CLIENTHANDLER_H_
class ClientHandler{
 public:
  virtual void handleClient(int){}
  virtual ~ClientHandler(){}
  ClientHandler(){}
  ClientHandler(const ClientHandler &){}
  virtual ClientHandler* copy()=0;
};
#endif //EX4__CLIENTHANDLER_H_
