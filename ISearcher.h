//
// Created by netanel on 11/01/2020.
//

#ifndef EX4_2__ISEARCHER_H_
#define EX4_2__ISEARCHER_H_
#include "ISearchable.h"
template <typename T,typename Solution>
class ISearcher{
 public:
  virtual Solution search (ISearchable<T>* searchable)=0;
  virtual int getNumberOfNodesEvaluated()=0;
  virtual ~ISearcher(){
  }
};
#endif //EX4_2__ISEARCHER_H_
