//
//  Signal.cpp
//  C++_Signal
//
//  Created by sunjian on 2024/11/4.
//

#include "Signal.hpp"

Signal* Signal::This = NULL;
const Signal* Signal::GetInstance(){
    if(!This){
        This = new Signal();
    }
    return This;
}

Signal::Signal(){
    
}
Signal::~Signal(){
    
}
