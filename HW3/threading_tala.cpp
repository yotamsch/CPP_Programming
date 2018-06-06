#include <iostream>
#include <thread>
#include <vector>

static bool isFinished = false;

void DoWork()
{
    using namespace::std::literals::chrono_literals;
 //   std::cout<< std::this_thread::get_id << std::endl;

    while(!isFinished){
        std::cout << "working..id=" << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(2s);
    }
}

int main(){
    std::vector<std::thread> thvector(3);
    for(int i=0; i<3; i++){
        thvector[i] = std::thread(DoWork);
    }
    std::cin.get();
    isFinished = true;
    for(auto& th:thvector){
        th.join();
    }
    std::cin.get();
    return 0;
}