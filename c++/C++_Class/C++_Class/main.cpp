//
//  main.cpp
//  C++_Class
//
//  Created by sunjian on 2024/11/3.
//

#include <iostream>
#include "Complex.hpp"
#include "String.hpp"
#include "Circle.hpp"
#include "Square.hpp"

void test1(){
    Complex c1(1, 2);
    Complex c2(2, 3);
    

    Complex c3;
    c3 = c1 + c2;
    
    Complex d(c3);//这里进行拷贝构造
    
    Complex e;
    e = d++;
    cout << e << endl;
    e = ++d;
    cout << e << endl;
    
    Complex f;
    cin >> f;
    cout << f << endl;
    
}

void test2(){
    String s("你好");
    cout << s << endl;
    
    String s2 = s;//调用拷贝构造函数
    cout << s2 << endl;
    
    String s2A(move(s));//调用移动构造函数
    cout << s2A << endl;
    
    String s3;
    s3 = s2;//调用赋值函数
    cout << s3 << endl;
    
    String s3A; //这是无参构造函数
    s3A = move(s2A);
    cout << s3A << endl;
}

void test3(){
    Circle circle(3.0);
    Square square(3.0);
    
    Shape* shape[] = {&circle, &square};
    
    for(int i = 0; i < 2; i++){
        (*shape[i]).Display();
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
//    test1();

//    test2();
    
    test3();
    
    return 0;
}
