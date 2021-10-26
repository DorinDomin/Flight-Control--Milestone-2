//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_2__MAZEPROBLEM_H_
#define EX4_2__MAZEPROBLEM_H_

#include <vector>
#include "ISearchable.h"
#include "Point.h"
class MazeProblem : public ISearchable<Point> {
 private:
  State<Point> InitialState, GoalState;
  vector<vector<State<Point>>> maze;
 public:
  MazeProblem(State<Point> & initial, State<Point> & Goal, vector<vector<State<Point>>> & maze2) {
    this->InitialState = initial;
    this->GoalState = Goal;
    this->maze = maze2;
  }
  bool operator<(const MazeProblem & m2) const {
    return maze.size()<(m2.getMaze().size());
  }
  State<Point> & getInintialState() override {
    return maze[InitialState.getState().getX()][InitialState.getState().getY()];
  }
  State<Point> & getGoalState() override {
    return maze[GoalState.getState().getX()][GoalState.getState().getY()];
  }
  vector<vector<State<Point>>> getMaze() const {
    return maze;
  }

  list<State<Point>*> getAllPossibleStates(State<Point> s) {
    int sx = s.getState().getX();
    int sy = s.getState().getY();
    list<State<Point>*> retlist;

    //right
    if (sy < int(maze[sx].size()-1) && maze[sx][sy+1].getCost()!=-1) {
      retlist.push_back(&maze[sx][sy+1]);
    }
    //down
    if (sx < int(maze.size()-1) && maze[sx+1][sy].getCost()!=-1) {
      retlist.push_back(&(maze[sx+1][sy]));
    }
    //up
    if (sx >= 1 && maze[sx-1][sy].getCost()!=-1) {
      retlist.push_back(&maze[sx-1][sy]);
    }
    //left
    if (sy >= 1 && maze[sx][sy-1].getCost()!=-1) {
      retlist.push_back(&maze[sx][sy-1]);
    }
    return retlist;
  }
  //Defines c_str method for cache
  string c_str(){
    string str="";
    for(vector<State<Point>> v: maze){
      for (State<Point> w:v){
        str+=::to_string(w.getCost())+",";
      }
    }
    str+=::to_string(getInintialState().getState().getX())+","+::to_string(getInintialState().getState().getY())+","+
        ::to_string(getGoalState().getState().getX())+","+::to_string(getGoalState().getState().getX());
    return str;
  }
};
#endif //EX4_2__MAZEPROBLEM_H_
