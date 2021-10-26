#ifndef EX4_2__DFS_H_
#define EX4_2__DFS_H_
#include <stack>
#include <map>
#include "Searcher.h"
template  <typename T,typename Solution>
class DFS : public Searcher<T,Solution> {
  void DFSVisit(ISearchable<T>* & searchable,State<T> & vstate){
    if(searchable->getGoalState().getColor()=='w'){
      this->increaseNodesChecked();
    }
    vstate.setColor('g');
    if(vstate.getState()==searchable->getInintialState().getState()){
      vstate.setd(vstate.getCost());
    }
    else{
      vstate.setd(vstate.getcameFrom()->getd()+vstate.getCost());
    }
    for(State<T>* w:searchable->getAllPossibleStates(vstate)) {
      if (w->getColor() == 'w') {
        w->setcameFrom(&vstate);
        w->setdirection(vstate.getState().direction(w->getState()));
        DFSVisit(searchable, *w);
      }
    }
    vstate.setColor('b');
  }
  Solution search(ISearchable<T>* searchable) override {

    searchable->getInintialState().setd(searchable->getInintialState().getCost());
    searchable->getInintialState().setcameFrom(nullptr);
    this->setNumberOfNodes(0);
    DFSVisit(searchable,searchable->getInintialState());
    //cout<<"NumberOfNodes "<<this->getNumberOfNodesEvaluated()<<"\n"<<endl;
    return this->backtrace(searchable->getInintialState(),searchable->getGoalState());
  }
 public:
  Searcher<T,Solution>* copy() override {
    return new DFS();
  }
};

#endif //EX4_2__DFS_H_
