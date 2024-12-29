//
//  Complex.cpp
//  C++_Class
//
//  Created by sunjian on 2024/11/3.
//

#include "Complex.hpp"
#include <iostream>

using namespace std;

Complex::Complex(){
    m_real = 0;
    m_image = 0;
    cout << "Complex()" << endl;
}

Complex::Complex(int real, int image):m_real(real),m_image(image){
    cout << "Complex(int real, int image)" << endl;
}

Complex::Complex(const Complex& x){
    m_real = x.m_real;
    m_image = x.m_image;
    cout << "Complex(const Complex& x)" << endl;
}

Complex::~Complex(){
    cout << "~Complex()" << endl;
}

Complex Complex::operator+(const Complex &x){
    return Complex(m_real+x.m_real, m_image+x.m_image);
}


Complex& Complex::operator=(const Complex &x){
    if(this != &x){
        m_real = x.m_real;
        m_image = x.m_image;
    }
    return *this;//this是一个指针，指向当前对象，返回this的间接应用
}

Complex& Complex::operator++(){
    m_real++;
    m_image++;
    return *this;
}

Complex Complex::operator++(int){
//    Complex temp(*this);//这里造成拷贝构造
//    m_real++;
//    m_image++;
//    return Complex();
    return Complex(m_real++, m_image++);//这样会避免拷贝构造
}

ostream& operator<<(ostream& os, const Complex& x){
    os << "real value is: " << x.m_real << ", " << "image value is: " << x.m_image;
    return os;
}

istream& operator>>(istream& is, Complex& x){
    is >> x.m_real >> x.m_image;
    return is;
}
