//
// Created by netanel on 18/01/2020.
//

#ifndef EX4_2__ASTAR_H_
#define EX4_2__ASTAR_H_
#include <set>
#include "Searcher.h"

template  <typename T,typename Solution>
class AStar : public Searcher<T,Solution> {
  struct bestCompare{
    bool operator()(State<T>* left,State<T>* right){
      if(P.getX()==-1){
        return left->getd()>right->getd();
      }
      else{
        double first=left->getd()+T::getDistance((*left).getState(),P);
        double second=right->getd()+T::getDistance((*right).getState(),P);
        return first>second;
      }
    }
  };
  Searcher<T,Solution>* copy() override {
    return new AStar();
  }
  Solution search(ISearchable<T>* searchable) override {

    this->EmptyList();
    this->setNumberOfNodes(0);
    P=searchable->getGoalState().getState();
    this->openQueue.push(&searchable->getInintialState());
    searchable->getInintialState().setd(searchable->getInintialState().getCost());
    State<T>* mint;
    while(!(this->openQueue.empty())) {
      mint=this->popOpenList();
      //this->openQueue.pop();
      if (mint->getState() == searchable->getGoalState().getState()) {
        //cout<<"NumberOfNodes "<<this->getNumberOfNodesEvaluated()<<"\n"<<endl;
        return this->backtrace(searchable->getInintialState(), searchable->getGoalState());
      }
      for (State<T> *w:searchable->getAllPossibleStates(*mint)) {
        if(mint->getd()+w->getCost()<w->getd()){
          w->setd(mint->getd()+w->getCost());
          w->setcameFrom(mint);
          w->setdirection(mint->getState().direction(w->getState()));
          if(!(this->openContains(*w))){
            this->addToOpenList(w);
          }
        }
      }
    }
    return "failure";
  }
};

#endif //EX4_2__ASTAR_H_
