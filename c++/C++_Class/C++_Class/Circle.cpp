//
//  Circle.cpp
//  C++_Class
//
//  Created by sunjian on 2024/11/3.
//

#include "Circle.hpp"

double Circle::Area() {
    return 3.14 * m_radius * m_radius;
}

Circle::Circle(double radius):m_radius(radius){
}

