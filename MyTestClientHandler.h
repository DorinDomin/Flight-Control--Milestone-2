#ifndef EX4__MYTESTCLIENTHANDLER_H_
#define EX4__MYTESTCLIENTHANDLER_H_
#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <iostream>
using namespace std;
template <typename Problem, typename Solution>
class MyTestClientHandler: public ClientHandler {
  Solver<Problem, Solution> *solver;
  CacheManager<Problem,Solution> *cm;
 public:
  //Builder
  MyTestClientHandler(Solver<Problem, Solution> *solver2, CacheManager<Problem,Solution> *cm2){
    this->solver = solver2;
    this->cm = cm2;
  }
  MyTestClientHandler* copy(){
    Solver<Problem,Solution>* solver1=this->solver->copy();
    return new MyTestClientHandler(solver1,cm);
  }
  void handleClient(int clientsocket) override {
    char c = '0';
    string buffer = "";
    //Reads until '\n'
    while (c != '\r'&&c!='\n') {
      read(clientsocket, &c, 1);
      if(c=='\r'){
      }
      else {
        buffer += c;
      }
    }

    //Loops until end
    while (buffer != "end\n"&&buffer!="end") {
      //Checks if solution exists
      if (cm->solutionExists(buffer)) {
        string msg = cm->getSolution(buffer) + '\n';
        send(clientsocket, msg.c_str(), msg.length(), 0);
        //If it doesn't then solves the problem
      } else {
        string msg = solver->solve(buffer) + '\n';
        cm->saveSolution(buffer, solver->solve(buffer));
        send(clientsocket, msg.c_str(), msg.length(), 0);
      }
      buffer = "";
      c = '\n';
      //Reads next line
      while (c == '\n'||c=='\r') {
        read(clientsocket, &c, 1);
      }
      buffer+=c;
      while (c != '\r'&&c!='\n') {
        read(clientsocket, &c, 1);
        if(c=='\r'){
        }
        else {
          buffer += c;
        }
      }
    }
    //instream.flush();
  }
};
#endif //EX4__MYTESTCLIENTHANDLER_H_
