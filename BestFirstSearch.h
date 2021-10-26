//
// Created by netanel on 11/01/2020.
//

#ifndef EX4_2__BESTFIRSTSEARCH_H_
#define EX4_2__BESTFIRSTSEARCH_H_
#include "Searcher.h"
#include "set"
template  <typename T,typename Solution>
class BestFirstSearch:public Searcher<T,Solution>{
 private:
  bool listContains(list<State<T>*> s, State<T> p){
    bool flag=false;
    list<State<T>*> s2;
    while(!s.empty()){
      State<T>* p2=s.back();
      if(p.getState()==p2->getState()){
        return true;
      }
      s2.push_back(p2);
      s.pop_back();
    }
    while(!s2.empty()){
      State<T>* p2=s2.back();
      s.push_back(p2);
      s2.pop_back();
    }
    return flag;
  }
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
 public:
  Solution search(ISearchable<T>* searchable) override {
    this->EmptyList();
    this->setNumberOfNodes(0);
    searchable->getInintialState().setd(searchable->getInintialState().getCost());
    this->addToOpenList(&(searchable->getInintialState()));
    list<State<T>*> closed;
    while(this->OpenListSize()>0){
      State<T> *n=this->popOpenList();
      closed.push_back(n);
      if(n->getState()==searchable->getGoalState().getState()){
        //cout<<"NumberOfNodes "<<this->getNumberOfNodesEvaluated()<<"\n"<<endl;
        return this->backtrace(searchable->getInintialState(),searchable->getGoalState());
      }
      list<State<T>*> successors=searchable->getAllPossibleStates(*n);
      for(State<T>* s:successors){
        if(s->getd()>s->getCost()+n->getd()){
          s->setd(s->getCost()+n->getd());
        }
        if(!listContains(closed,*s)&&!this->openContains(*s)){
          s->setcameFrom(n);
          s->setdirection(n->getState().direction(s->getState()));
          this->addToOpenList(s);
          //cout<<"";
        }
        else{
          if(s->getd()>n->getd()+s->getCost()){
            if(!this->openContains(*s)){
              this->addToOpenList(s);
            }
            else{
              s->setcameFrom(n);
              s->setdirection(n->getState().direction(s->getState()));
              s->setCost(n->getd()+s->getCost());
            }
          }
        }
      }
    }
  }
  Searcher<T,Solution>* copy() override {
    return new BestFirstSearch();
  }
};
#endif //EX4_2__BESTFIRSTSEARCH_H_
