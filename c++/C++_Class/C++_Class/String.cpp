//
//  String.cpp
//  C++_Class
//
//  Created by sunjian on 2024/11/3.
//

#include "String.hpp"
#include <iostream>
#include <string>

String::String(const char *str){
    cout << "构造函数" << endl;
    if(str == NULL){
        m_data = new char[1];
        *m_data = '\0';
    }else{
        int len = (int)strlen(str);
        if(len > 0){
            m_data = new char[len+1];
            if (m_data != NULL) {
                strcpy(m_data, str);
            }
        }
    }
}

String::String(const String& other){
    cout << "这是拷贝构造函数" << endl;
    char *str = other.m_data;
    if(str == NULL){
        m_data = new char[1];
        *m_data = '\0';
    }else{
        int len = (int)strlen(str);
        if(len > 0){
            m_data = new char[len+1];
            if (m_data != NULL) {
                strcpy(m_data, str);
            }
        }
    }
}

String::String(String&& other)//移动构造函数
{
    cout << "这是移动构造函数" << endl;
    if(other.m_data != NULL){
        m_data = other.m_data;
        other.m_data = NULL;
    }
}

String::~String(){
    cout << "这是析构函数" << endl;
    if(m_data){
        delete[] m_data;
    }
}

String& String::operator=(const String& other) {
    cout << "这是 = 运算符" << endl;
    if(this == &other){
        return *this;
    }else{
        delete[] m_data;
        char *str = other.m_data;
        if(str == NULL){
            m_data = new char[1];
            *m_data = '\0';
        }else{
            int len = (int)strlen(str);
            if(len > 0){
                m_data = new char[len+1];
                if (m_data != NULL) {
                    strcpy(m_data, str);
                }
            }
        }
    }
    return *this;
}

String& String::operator=(String&& rhs)noexcept   //移动赋值运算符 && 右值引用
{
    cout << "这是 Move 运算符" << endl;
    if(this != &rhs){
        delete[] m_data;
        if(rhs.m_data != NULL){
            m_data = rhs.m_data;
            rhs.m_data = NULL;
        }
    }
    return *this;
}
/*
 这个方法不属于 String 的内部方法，但是要访问 String 内部的成员变量，就要用 friend 
 */
ostream& operator<<(ostream& os, const String& s){
    os << s.m_data << endl;
    return os;
}
