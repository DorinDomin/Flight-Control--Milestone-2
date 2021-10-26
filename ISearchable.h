//
// Created by netanel on 11/01/2020.
//

#ifndef EX4_2__ISEARCHABLE_H_
#define EX4_2__ISEARCHABLE_H_
#include "State.h"
#include "list"
using namespace std;
template <typename T>
class ISearchable{
 public:
  virtual State<T> & getInintialState()=0;
  virtual State<T> & getGoalState()=0;
  virtual list<State<T> *> getAllPossibleStates(State<T> s)=0;
  virtual ~ISearchable(){

  }
};
#endif //EX4_2__ISEARCHABLE_H_
