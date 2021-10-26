#ifndef EX4__CACHEMANAGER_H_
#define EX4__CACHEMANAGER_H_
#include <list>
#include <set>
#include <fstream>
#include <sstream>
#include "string"
using namespace std;
template<typename Problem, typename Solution>
class CacheManager{
 public:
  virtual bool solutionExists(Problem)=0;
  virtual Solution getSolution(Problem)=0;
  virtual void saveSolution(Problem,Solution)=0;
  virtual ~CacheManager(){};
  CacheManager<Problem,Solution>(){}
  CacheManager<Problem,Solution>* copy(){}

};
#endif //EX4__CACHEMANAGER_H_
