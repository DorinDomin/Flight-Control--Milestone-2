//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_2__MYCLIENTHANDLER_H_
#define EX4_2__MYCLIENTHANDLER_H_
#include <unistd.h>
#include "ClientHandler.h"
#include "vector"
#include "algorithm"
#include "string.h"
#include "MazeProblem.h"
using namespace std;
template<typename Problem, typename Solution>
class MyClientHandler : public ClientHandler {
  Solver<Problem, Solution> *solver;
  CacheManager<Problem,Solution> *cm;
 public:
  MyClientHandler(const MyClientHandler& m1){
    this->solver=m1.solver;
    this->cm=m1.cm;
  }
  MyClientHandler* copy(){
    //CacheManager<Problem,Solution>* cachem=this->cm->copy();
    Solver<Problem,Solution>* solver1=this->solver->copy();
    return new MyClientHandler(solver1,cm);
  }
  MyClientHandler(Solver<Problem, Solution> *solver2, CacheManager<Problem,Solution> *cm2) : ClientHandler() {
    this->solver = solver2;
    this->cm = cm2;
  }
  void handleClient(int clientsocket) override {
    vector<vector<string> > matrix;
    char b=' ';
    string buffer2="";
    //Reads line of matrix
    read(clientsocket, &b, 1);
    while(b!='\n'){
      if(b!=' '&&b!='\r'){
        buffer2+=b;
      }
      read(clientsocket, &b, 1);
    }
    int curr = 0;
    int next = buffer2.find(',');
    int lines = 0;
    int j;
    vector<string> empty;
    //Loops over entire matrix

    while (buffer2.find("end")==string::npos&&buffer2.find("end\n")==string::npos&&buffer2.find("end\r\n")==string::npos) {
      j = 0;
      matrix.push_back(empty);
      //Inserts line read into our matrix object
      while (next != int(string::npos)) {
        (matrix[lines]).push_back(buffer2.substr(curr, next - curr));
        j++;
        curr = next+1;
        next = buffer2.find(',',curr+1);
      }
      (matrix[lines]).push_back(buffer2.substr(curr, buffer2.length()));
      lines++;
      buffer2="";
      //Reads next line
      read(clientsocket, &b, 1);
      while(b!='\n'&&buffer2.find("en")==string::npos){
        if(b!=' '&&b!='\r'){
          buffer2+=b;
        }
        read(clientsocket, &b, 1);
        if(buffer2.find("en")!=string::npos){
          buffer2+=b;
        }
      }
      curr=0;
      next = buffer2.find(',');
    }

    //Moves matrix to matrix2
    vector<vector<State<Point>>> matrix2;
    for(unsigned int i=0;i<matrix.size()-2;i++){
      matrix2.push_back(vector<State<Point>>());
      for(unsigned int t=0;t<matrix[i].size();t++){
        matrix2[i].push_back(State<Point>());
        matrix2[i][t]=State<Point>(Point(i,t));
        matrix2[i][t].setCost(stoi(matrix[i][t]));
      }
    }

    Point sPoint(stoi(matrix[matrix.size()-2][0]),stoi(matrix[matrix.size()-2][1]));
    Point ePoint(stoi(matrix[matrix.size()-1][0]),stoi(matrix[matrix.size()-1][1]));
    //Creates a MazeProblem
    MazeProblem maze_problem(matrix2[sPoint.getX()][sPoint.getY()],matrix2[ePoint.getX()][ePoint.getY()],matrix2);
    //Checks if a solution to our problem exists
    if (cm->solutionExists(maze_problem)) {
      string msg =(cm->getSolution(maze_problem))+ '\n';
      send(clientsocket, msg.c_str(), msg.length(), 0);
      //If not calculates it
    } else {
      Solution solution=solver->solve(maze_problem);
      string msg = (solution) + '\n';
      cm->saveSolution(maze_problem, solution);
      send(clientsocket, msg.c_str(), msg.length(), 0);
    }
  }

  Solver<Problem,Solution>* getSolver(){
    return this->solver;
  }
  CacheManager<Problem,Solution>* getCacheManager(){
    return this->cm;
  }
};
#endif //EX4_2__MYCLIENTHANDLER_H_
