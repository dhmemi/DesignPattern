//
// Created by Admin on 2019.3.13.
//
#include "deps/thread_manager.hpp"
#include <chrono>

std::default_random_engine rnd_eng;

void func(int time){
    std::cout << "thread [" << std::this_thread::get_id() << "] will sleep " << time << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
}

int main()
{
    ThreadManager::Init("thread_main");
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++){
            int time = int(rnd_eng())%60;
            std::string name = "thread__" + std::to_string(i) + "__" + std::to_string(j);
            ThreadManager::new_thread(name, func, time);
        }
    }
    return 0;
}