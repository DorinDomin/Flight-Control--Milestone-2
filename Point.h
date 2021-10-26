//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_2__POINT_H_
#define EX4_2__POINT_H_

class Point {
  int x;
  int y;
 public:
  Point(){
    this->x=0;
    this->y=0;
  }
  //Builder from string
  Point(string s){
    string s2="";
    for(unsigned int i=0;i<s.length();i++){
      if(s[i]!=' '){
        s2+=s[i];
      }
    }
    this->x=stoi(s.substr(0,s.find(',')));
    this->y=stoi(s.substr(s.find(',')+1,s.length()));
  }
  //Builder from ints
  Point(int newx,int newy){
    this->x=newx;
    this->y=newy;
  }
  //Gets x
  int getX(){
    return x;
  }
  //Sets x
  void setX(int newx){
    this->x=newx;
  }
  //Gets y
  int getY(){
    return y;
  }
  //Sets y
  void setY(int newy){
    this->y=newy;
  }
  //Sets x and y
  void setPoint(int newx,int newy){
    this->x=newx;
    this->y=newy;
  }
  //Defines <
  bool operator<(Point p) const{
    return this->x<p.getX()&&this->y<p.getY();
  }
  //Defines ==
  bool operator==(Point p) const{
    return this->x==p.getX()&&this->y==p.getY();
  }
  //Defines !=
  bool operator!=(Point p) const{
    return this->x!=p.getX()||this->y!=p.getY();
  }
  //Gets direction between this point and another
  string direction(Point p){
    if(this->getX()==p.getX()&&this->getY()==p.getY()-1){
      return "Right";
    }
    if(this->getX()==p.getX()&&this->getY()==p.getY()+1){
      return "Left";
    }
    if(this->getX()==p.getX()-1&&this->getY()==p.getY()){
      return "Down";
    }
    if(this->getX()==p.getX()+1&&this->getY()==p.getY()){
      return "Up";
    }
    return "";
  }
  //Calculates distance between two points
  static double getDistance(Point p1,Point p2){
    return sqrt(pow(p1.getX()-p2.getX(),2)+pow(p1.getY()-p2.getY(),2));
  }
};

#endif //EX4_2__POINT_H_
