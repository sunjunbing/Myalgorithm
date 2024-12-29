//
//  String.hpp
//  C++_Class
//
//  Created by sunjian on 2024/11/3.
//

#ifndef String_hpp
#define String_hpp

#include <stdio.h>
#include <iostream>

using namespace std;

class String {
public:
    String(const char *str = NULL);
    String(const String& other);                //拷贝构造函数
    String(String&& other);                     //移动构造函数
    ~String();
    String& operator=(const String& other);
    String& operator=(String&& rhs)noexcept;   //移动赋值运算符
    friend ostream& operator<<(ostream& os, const String& s);
private:
    char *m_data;
};

#endif /* String_hpp */
