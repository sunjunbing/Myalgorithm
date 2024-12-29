//
//  Square.hpp
//  C++_Class
//
//  Created by sunjian on 2024/11/3.
//

#ifndef Square_hpp
#define Square_hpp

#include <stdio.h>
#include "Shape.hpp"

class Square : public Shape {
public:
    virtual double Area();
    Square(double len);
    
private:
    double m_len;
};

#endif /* Square_hpp */
