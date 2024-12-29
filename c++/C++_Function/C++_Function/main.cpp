//
//  main.cpp
//  C++_Function
//
//  Created by sunjian on 2024/11/2.
//

#include <iostream>
//方法 1： 递归，不推荐
int Fib(int n){
    if(n == 0) return  0;
    if(n == 1) return 1;
    return Fib(n-1)+Fib(n-2);
}
//方法 2：使用循环替代递归
int Fib1(int n){
    if(n < 2) return n;
    int n0 = 0, n1 = 1, temp;
    for(int i = 2; i <= n; i++){
        temp = n0;
        n0 = n1;
        n1 = temp + n1;
    }
    return n1;
}
//方法 3： 尾递归，编译器帮我们处理，原理是啥？
/*
 尾递归的特点：
 1.递归调用发生在函数体的最后一个操作
 2.返回值直接被当前函数返回
 优点：
 1.可以被编译器优化为循环模式
 2.不需要开辟新的栈空间，避免堆栈的溢出
 */
int Fib2(int n, int ret0, int ret1){
    if(n == 0) return ret0;
    if(n == 1) return ret1;
    return Fib2(n - 1, ret1, ret0 + ret1);
}

int g_list[1000];
//方法 4：动态规划，空间换时间
int Fib3(int n){
    g_list[0] = 0;
    g_list[1] = 1;
    for(int i = 2; i <= n; i++){
        if(g_list[i] == 0){
            g_list[i] = g_list[i- 1] + g_list[i - 2];
        }
    }
    return g_list[n];
}
int main(int argc, const char * argv[]) {
    // insert code here...
    int n = 30;
    std::cout <<Fib(n) <<  std::endl;
    std::cout <<Fib1(n) <<  std::endl;
    std::cout <<Fib2(n, 0, 1) <<  std::endl;
    std::cout << Fib3(n) <<  std::endl;
    return 0;
}
