//
//  Shape.hpp
//  C++_Class
//
//  Created by sunjian on 2024/11/3.
//

#ifndef Shape_hpp
#define Shape_hpp

#include <stdio.h>
#include <iostream>

class Shape{
public:
    virtual double Area() = 0;//纯虚函数，Shape 不能有具体的实例对象，类似于 Java 的 interface, Abstruct Class 抽象类，virtual 实现机制
//    virtual void Show() = 0;
    void Display();
private:
    int m_color1 = 10;
    int m_color = 15;
};

#endif /* Shape_hpp */
