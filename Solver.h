#ifndef EX4__SOLVER_H_
#define EX4__SOLVER_H_
#include <string>
using namespace std;
template <typename Problem, typename Solution>
class Solver{
 public:
  virtual Solution solve(Problem)=0;
  virtual ~Solver(){
  }
  virtual Solver<Problem,Solution>* copy()=0;
};
#endif //EX4__SOLVER_H_
