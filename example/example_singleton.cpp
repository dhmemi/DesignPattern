//
// Created by Admin on 2019.3.11.
//
#include <iostream>
#include "deps/singleton.hpp"


class ExampleClass {
public:
    void doSomething()
    {
        std::cout << "self addr:" << this <<std::endl;
    }
private:
    SINGLETON_THIS_CLASS(ExampleClass);
};


int main()
{
    ExampleClass* ptr = deps::Singleton<ExampleClass>::Instance();
    ExampleClass* ptr2 = deps::Singleton<ExampleClass>::Instance();
    ptr->doSomething();
    ptr2->doSomething();
    return 0;
}