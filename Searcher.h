//
// Created by netanel on 11/01/2020.
//

#ifndef EX4_2__SEARCHER_H_
#define EX4_2__SEARCHER_H_
#include "State.h"
#include "ISearcher.h"
#include "queue"
using namespace std;
Point P(-1,-1);
template  <typename T,typename Solution>
class Searcher:public ISearcher<T,Solution>{
  //Comparator for our priorityqueue

 protected:
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
  priority_queue<State<T>*,vector<State<T>*>,bestCompare> openQueue;//=new priority_queue<State<T>,vector<State<T>>,CustomCompare>
  int evaluatedNodes=0;

 public:
  Searcher(){
  };
  virtual Searcher<T,Solution>* copy()=0;
  int OpenListSize(){
    return openQueue.size();
  };
  int getNumberOfNodesEvaluated() override {
    return evaluatedNodes;
  }
  priority_queue<State<T>*,vector<State<T>*>,bestCompare>* initializeQueue(){
    return new priority_queue<State<T>*,vector<State<T>*>,bestCompare>();
  }
  void setList(priority_queue<State<T>*,vector<State<T>*>,bestCompare> openQueue2){
    this->openQueue=openQueue2;
  }
  void increaseNodesChecked(){
    this->evaluatedNodes++;
  }
  void setNumberOfNodes(int num){
    this->evaluatedNodes=num;
  }
  virtual Solution search(ISearchable<T> * searchable)=0;
 protected:
  //Empties the current list
  void EmptyList(){
    while(OpenListSize()>0){
      popOpenList();
    }
  }
  //Pop from list
  State<T>* popOpenList(){
    evaluatedNodes++;
    State<T>* t=openQueue.top();
    openQueue.pop();
    return t;
  }
  //Push to list
  void addToOpenList(State<T>* state){
    openQueue.push(state);
  }
  //Backtraces path
  Solution backtrace(State<T> & start,State<T> & goal){
    Solution solution;
    solution=(goal.getdirection())+"("+to_string(int(goal.getd()))+")";
    while(goal.getState()!=start.getState()){
      goal=*(goal.getcameFrom());
      if(goal.getState()==start.getState()){
        break;
      }
      solution=(goal.getdirection())+"("+to_string(int(goal.getd()))+"),"+solution;
    }
    return solution;
  }
  //Checks if list contains given state
  bool openContains(State<T> s){
    list <State<T>*> temp;
    bool flag=false;
    while(!openQueue.empty()) {
      if (openQueue.top()->getState() == s.getState()) {
        flag = true;
        break;
      }
      State<T>* t = openQueue.top();
      temp.push_back(t);
      openQueue.pop();
    }
    while(!temp.empty()){
      State<T>* t = temp.back();
      openQueue.push(t);
      temp.pop_back();
    }
    return flag;
  }

};
#endif //EX4_2__SEARCHER_H_
