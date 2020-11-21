#include "Semaphore.h"
#include <iostream>
#include <thread>
#include <vector>
static const int num_threads = 100;
int sharedVariable=0;
/*! \fn updateTask(std::shared_ptr<Semaphore> mutex, int numUpdates)
    \brief An Implementation of Mutual Exclusion using Semaphores
    \param mutex creates a mutual exclusion
    \param numUpdates increment one thread, then the other showing mutual exclusion
   Uses C++11 features such as mutex and condition variables to implement an example of a rendezvous for threads
*/
/*! displays a message that is split in to 2 sections to show how a rendezvous works*/
void updateTask(std::shared_ptr<Semaphore> mutex, int numUpdates){
   mutex->Wait();
  for(int i=0;i<numUpdates;i++){
    //UPDATE SHARED VARIABLE HERE!
    sharedVariable++;
  }
  mutex->Signal();
}
/*!
  \fn main(void)
  \brief An Implementation of Mutual Exclusion using Semaphores with the semaphore set to 1, this allows whatever thread to get there first to run.
*/
int main(void){
  std::vector<std::thread> vt(num_threads);
  std::shared_ptr<Semaphore> aSemaphore( new Semaphore(1));
  /**< Launch the threads  */
  int i=0;
  for(std::thread& t: vt){
    t=std::thread(updateTask,aSemaphore,1000);
  }
  std::cout << "Launched from the main\n";
  /**< Join the threads with the main thread */
  for (auto& v :vt){
      v.join();
  }
  std::cout << sharedVariable << std::endl;
  return 0;
}
