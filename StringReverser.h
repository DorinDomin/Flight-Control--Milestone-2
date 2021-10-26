#ifndef EX4__STRINGREVERSER_H_
#define EX4__STRINGREVERSER_H_
#include <string>
#include "Solver.h"
using namespace std;
class StringReverser: public Solver<string,string>{
 public:
  string solve(string str) override{
    string str2;
    //Reverses the string
    for(int i=str.length()-1;i>=0;i--){
      str2+=str[i];
    }
    return str2;
  }
  Solver<string,string>* copy(){
    return new StringReverser();
  }
};
#endif //EX4__STRINGREVERSER_H_
