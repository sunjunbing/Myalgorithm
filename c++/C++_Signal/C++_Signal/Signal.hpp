//
//  Signal.hpp
//  C++_Signal
//
//  Created by sunjian on 2024/11/4.
//

#ifndef Signal_hpp
#define Signal_hpp

#include <stdio.h>
#include <iostream>


class Signal {
public:
    static const Signal* GetInstance();
    static void doSomething(){
        std::cout << "Do something" << std::endl;
    }
private:
    Signal();
    ~Signal();
    static Signal* This;//他是一个全局变量
};

#endif /* Signal_hpp */
