//
// Created by netanel on 11/01/2020.
//

#ifndef EX4_2__STATE_H_
#define EX4_2__STATE_H_
#include <cmath>
template <typename T>
class State{
  //Fields
  T state;
  double cost=0;
  State<T>* cameFrom;
  char color='w';
  string direction="";
  int d=1000000;
 public:
  //Builders
  State(T state2){
    this->state=state2;
  }
  State(int x){
    this->state=state(x,x);
  }
  State(){
  }

  //Defines ==
  bool operator==(const State<T> s) const{
    return state.d==s.state.d;
  }
  //Gets cost
  double getCost(){
    return cost;
  }
  //Sets Cost
  void setCost(double c){
    this->cost=c;
  }
  //Gets camefrom
  State<T>* getcameFrom(){
    return cameFrom;
  }
  //Sets camefrom
  void setcameFrom(State<T>* s){
    this->cameFrom=s;
  }
  //Gets state
  T getState(){
    return state;
  }
  //Sets state
  void setState(T p){
    this->state=p;
  }
  //Sets color
  void setColor(char c){
    this->color=c;
  }
  //Gets color
  char getColor(){
    return this->color;
  }
  //Sets d
  void setd(double num){
    this->d = num;
  }
  //Gets d
  double getd(){
    return this->d;
  }
  //Sets direction
  void setdirection(string c){
    this->direction =c;
  }
  //Gets direction
  string getdirection(){
    return this->direction;
  }
  //Gets distance
  static int getdistance(State<T> p1,State<T> p2){
    return T::getDistance(p1.getState(),p2.getState());
  }
};
#endif //EX4_2__STATE_H_
