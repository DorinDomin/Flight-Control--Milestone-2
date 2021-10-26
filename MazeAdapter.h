//
// Created by netanel on 12/01/2020.
//

#ifndef EX4_2__MAZEADAPTER_H_
#define EX4_2__MAZEADAPTER_H_
#include "Solver.h"
#include "MazeProblem.h"
#include "Searcher.h"
class MazeAdapter: public Solver<MazeProblem, string>{
 Searcher<Point,string> * searcher;
 public:
  MazeAdapter(Searcher<Point,string> * searcher2){
    this->searcher=searcher2;
  }
  string solve(MazeProblem maze) override {
    return searcher->search(&maze);
  }
  Solver* copy() override {
    MazeAdapter* maze_adapter=new MazeAdapter(searcher->copy());
    return maze_adapter;
  }
};
#endif //EX4_2__MAZEADAPTER_H_
