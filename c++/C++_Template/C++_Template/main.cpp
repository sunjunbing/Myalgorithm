//
//  main.cpp
//  C++_Template
//
//  Created by sunjian on 2024/11/4.
//

#include <iostream>


template<int n>
struct Sum {
    enum Value{N = Sum<n-1>::N+n};//编译期原理 Sum(n) = Sum(n-1) + n
};
template<>
struct Sum<1>{
    enum Value{N = 1};//n = 1
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    std::cout << Sum<100>::N << std::endl;
    return 0;
}
