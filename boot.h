#ifndef EX4__BOOT_H_
#define EX4__BOOT_H_

#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "StringReverser.h"
#include "MyClientHandler.h"
#include "FileCacheManager.h"
#include "MazeProblem.h"
#include "MazeAdapter.h"
#include "BFS.h"
#include "DFS.h"
#include "AStar.h"
#include "BestFirstSearch.h"
#include "MyParallelServer.h"
namespace boot
{
class Main{
 public:

  static void main(int argc,char *argv[]){
    MyParallelServer server;
    algoNUM=4;//BFS=1 DFS=2 BEST=3 A*=4
    //MyTestClientHandler<string,string> my_test_client_handler(new StringReverser(),new FileCacheManager<string,string>());
    MyClientHandler<MazeProblem,string> my_test_client_handler(new MazeAdapter(new AStar<Point, string>),new FileCacheManager<MazeProblem,string>());
    int port;
    if(argc<2){
      port=5600;
    }
    else{
      port=stoi(argv[1]);
    }
    server.open(port,&my_test_client_handler);
  }
};
}
#endif //EX4__BOOT_H_
