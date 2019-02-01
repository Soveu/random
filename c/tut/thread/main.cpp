#include<thread>
#include<fstream>
#include<chrono>

void func(){
  std::ofstream cerr("/dev/stderr");
  std::this_thread::sleep_for(std::chrono::seconds(3));
  cerr << "Hello from thread 1!\n";
  cerr.flush();
}

int main(){
  std::ofstream cout("/dev/stdout");
  cout << "Spawning thread...\n";
  cout.flush();
  
  std::thread t(func);
//  t.detach(); //doesnt work
  cout << t.get_id();
  t.join();

  return 0;
}

