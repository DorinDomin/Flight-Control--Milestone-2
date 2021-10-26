//
// Created by netanel on 13/01/2020.
//

#ifndef EX4_2__BFS_H_
#define EX4_2__BFS_H_

#include <set>
#include <map>
#include "Searcher.h"
template  <typename T,typename Solution>
class BFS : public Searcher<T,Solution> {
  Solution search(ISearchable<T>* searchable) override {
    int flag=false;
    this->setNumberOfNodes(0);
    queue<State<T>*> algqueue;
    searchable->getInintialState().setColor('g');
    searchable->getInintialState().setd(searchable->getInintialState().getCost());
    searchable->getInintialState().setcameFrom(nullptr);
    algqueue.push(&(searchable->getInintialState()));
    while(!algqueue.empty()){
      State<T>* v= algqueue.front();
      algqueue.pop();
      if(!flag){
        this->increaseNodesChecked();
      }
      if(searchable->getGoalState().getState()==v->getState()){
        flag=true;
      }
      for(State<T>* w:searchable->getAllPossibleStates(*v)){
        if (w->getColor()=='w'){
          w->setColor('g');
          w->setd(v->getd()+w->getCost());
          w->setcameFrom(v);
          w->setdirection(v->getState().direction(w->getState()));
          algqueue.push(w);
        }
        if(w->getState()==searchable->getGoalState().getState()){
          break;
        }
      }
      v->setColor('b');
    }
    //cout<<"NumberOfNodes "<<this->getNumberOfNodesEvaluated()<<"\n"<<endl;
    return this->backtrace(searchable->getInintialState(),searchable->getGoalState());
  }
 public:
  Searcher<T,Solution>* copy() override {
    return new BFS();
  }
};

#endif //EX4_2__BFS_H_
