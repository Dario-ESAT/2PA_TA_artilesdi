#include <stdio.h>

#include <vector>
#include <thread>
unsigned int g_bitcoins = 0;

void MineMoreBitcoins(unsigned int bc){
  for (unsigned int i = 0; i < bc; i++) {
    g_bitcoins += 1;
  }
  
  return;
}

int main(int argc, char** argv){
  int num_cores = std::thread::hardware_concurrency();
  printf("Number or cores detected %d\n", num_cores);

  std::vector<std::thread*> threds;

  for (int i = 0; i < num_cores; i++) {
    std::thread* t = new std::thread(MineMoreBitcoins,1000000000);
    threds.push_back(t);
  }

  printf("All threds go\n");

  for (int i = 0; i < num_cores; i++) {
    threds[i]->join();
  }
  printf("Bitcoins %d\n",g_bitcoins);
  return 0;
}