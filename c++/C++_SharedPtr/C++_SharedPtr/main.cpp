//
//  main.cpp
//  C++_SharedPtr
//
//  Created by sunjian on 2024/11/2.
//

#include <iostream>
#include <memory.h>
#include "Person.hpp"
#include <stdio.h>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//    {
//        //unique_ptr类似于单利，只能被一个对象所持有， 被能被复制和赋值
//        //可以同过move 语法操作
//        auto p1 = make_unique<int>(10);//make_unique<T>(参数)
//        auto person = make_unique<Person>(10, "Lucy");
//        auto person2 = move(person);//通过move 语句之后，person 的所有权交给person2，person 会被销毁
//        cout << person2.get()->age << endl;
//    }
//    
//    //shared_ptr: 使用引用计数，循环引用的问题
//    auto p1 = make_shared<Person>(18, "LiLei");
//    {
//        auto p2 = p1;
//        cout << (*(p1.get())).name << endl;
//        cout << p2.get()->age << endl;
//        cout << p2.use_count() << endl;
//    }
//    cout << p1.use_count() << endl;
    
    
    
    {
        //weak_ptr:解决循环引用的问题
        auto dog = make_shared<Dog>();
        auto person = make_shared<Person>(20, "Mile");
        person->dog = dog;
        dog->master = person;
    }

    
    return 0;
}
