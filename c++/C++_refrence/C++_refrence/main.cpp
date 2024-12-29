//
//  main.cpp
//  C++_refrence
//
//  Created by sunjian on 2024/11/1.
//

#include <iostream>

using namespace std;

/*
 有了指针为啥还要有引用
    为了函数运算符重载？？
 有了引用为啥还要指针？
    为了兼容 c 语言
 */

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//
//    int x = 1, x2 = 3;
//    int& rx = x;//引用会永远指向初始化他的对象 rx 永远指向 x
//    cout << x << endl;//1
//    cout << rx << endl;//1
//    rx = x2;//相当于 x = x2
//    cout << x << endl;
//    cout << rx << endl;
//    int a = 3, b = 4;
//    swap(a, b);
//    assert(a == 4 && b == 3);
    
    
    //指针的数组和数组的指针
    unsigned int c[4] = {0x80000000, 0xffffffff, 0x000000000, 0x7fffffff};
    unsigned int* a[4];//
    unsigned int(*b)[4];
    b = &c;
    for(int i = 0; i < 4; i++){
        a[i] = &(c[i]);
    }
    
    cout << *(a[0]) << endl;
    cout << (*b)[3] << endl;
    
    
    //const 的使用
    char str[] = {"helloWorld"};
    char const* pStr = "helloWorld";//pstr只能指向内存地址只能放 char
    char* const pStr1 = str;//pStr 指向的地址不能改变，但是内容可以改变
    char const * const pStr2 = "helloWorld";//pStr2 不能变/内容也不能变
    
    char intArray[] = {"C++helloWo"};

    pStr = intArray;
    
    int intArray1[] = {1};
    
    unsigned int len = strlen(pStr1);
    for(int i = 0; i < len; i++){
        pStr1[i] += 1;
    }
    
    return 0;
}
