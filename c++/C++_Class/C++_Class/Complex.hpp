//
//  Complex.hpp
//  C++_Class
//
//  Created by sunjian on 2024/11/3.
//

#ifndef Complex_hpp
#define Complex_hpp


#include <stdio.h>
#include <iostream>

using namespace std;

class Complex {
public:
    Complex();
    Complex(int real, int image);
    Complex(const Complex& x);//拷贝构造
    int GetReal(){
        return m_real;
    }
    void SetReal(int real){
        m_real = real;
    }
    int GetImage(){
        return m_image;
    }
    void SetImage(int image){
        m_image = image;
    }
    virtual ~Complex();
    
    Complex operator+ (const Complex& x);
    /*
     const修饰其左边的内容，左边没有看右边
     const Complex& x; x只能指向 Complex 的类型的地址
     */
    Complex& operator= (const Complex& x);
    
    Complex& operator++();//前置++
    Complex operator++(int);//后置++
    
    //友元函数
    //重载 << 
    friend ostream& operator<<(ostream& os, const Complex& x);
    friend istream& operator>>(istream& is, Complex& x);
    
private:
    int m_real;
    int m_image;
};

#endif /* Complex_hpp */
