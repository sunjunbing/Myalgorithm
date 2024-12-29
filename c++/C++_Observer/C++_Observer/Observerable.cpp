//
//  Observerable.cpp
//  C++_Observer
//
//  Created by sunjian on 2024/11/4.
//

#include "Observerable.hpp"

Observerable::Observerable(){
    
}

Observerable::~Observerable(){
    
}

void Observerable::Attach(Observer *observer) {
    if(observer == NULL) return;
    //c++list 的遍历
    auto it = m_observers.begin();//这是一个指针
    for (; it != m_observers.end(); it++) {
        if (*it == observer) {
            return;
        }
    }
    m_observers.push_back(observer);
}

void Observerable::Detach(Observer *observer){
    if(observer == NULL || m_observers.empty()){ return; }
    m_observers.remove(observer);
}

