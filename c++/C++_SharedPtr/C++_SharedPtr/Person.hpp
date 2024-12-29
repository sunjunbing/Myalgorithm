//
//  Person.hpp
//  C++_SharedPtr
//
//  Created by sunjian on 2024/11/2.
//

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>
#include "Dog.hpp"

using namespace std;
class Dog;
class Person {
public:
    int age;
    string name;
    shared_ptr<Dog> dog;
    
    Person(int age, string name);
    ~Person();
private:
};

#endif /* Person_hpp */
