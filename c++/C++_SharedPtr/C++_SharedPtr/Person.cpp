//
//  Person.cpp
//  C++_SharedPtr
//
//  Created by sunjian on 2024/11/2.
//

#include "Person.hpp"

using namespace std;

Person::Person(int age, string name):age(age),name(name){
    
}

Person::~Person(){
    printf("delete a person \n");
}
