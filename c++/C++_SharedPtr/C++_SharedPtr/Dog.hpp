//
//  Dog.hpp
//  C++_SharedPtr
//
//  Created by sunjian on 2024/11/2.
//

#ifndef Dog_hpp
#define Dog_hpp

#include <stdio.h>
#include <iostream>
#include "Person.hpp"
#include <memory>

using namespace std;
class Person;
class Dog {
public:
    weak_ptr<Person> master;
    void run();
};

#endif /* Dog_hpp */
