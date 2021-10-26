#ifndef EX4__SERVER_SIDE_H_
#define EX4__SERVER_SIDE_H_
#include <mutex>
#include <netinet/in.h>
#include "ClientHandler.h"
using namespace std;
mutex mutex_lock2;
mutex mutex_lock3;
namespace server_side
{
class Server{
 public:
  virtual void open(int port,ClientHandler * c)=0;
  virtual void stop()=0;
  virtual ~Server(){

  }
};
}
#endif //EX4__SERVER_SIDE_H_
