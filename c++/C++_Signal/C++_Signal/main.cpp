//
//  main.cpp
//  C++_Signal
//
//  Created by sunjian on 2024/11/4.
//

#include <iostream>
#include "Signal.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    auto signal = Signal::GetInstance();
    signal->doSomething();
    auto signel1 = Signal::GetInstance();
    signel1->doSomething();
    return 0;
}
