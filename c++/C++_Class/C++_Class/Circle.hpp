//
//  Circle.hpp
//  C++_Class
//
//  Created by sunjian on 2024/11/3.
//

#ifndef Circle_hpp
#define Circle_hpp

#include <stdio.h>
#include "Shape.hpp"

class Circle : public Shape {
public:
    virtual double Area();//要知道领导想要啥
    Circle(double radius);
    /*
     Circle 的内存布局
     virtual List Pointer = 8Bytes
     Shape.m_color = 4Bytes
     m_test1 = 4Bytes
     m_radius = 16Bytes;
     b = 4Bytes;
     8 + 4 + 8 = 20,但必须是 8 的整数倍 所以是 24 Bytes
     */
    
private:
    int m_test1 = 10;
    double m_radius;
    int m_test = 10;
};

#endif /* Circle_hpp */
