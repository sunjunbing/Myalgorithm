//
//  main.cpp
//  C++_TypeConversion
//
//  Created by sunjian on 2024/11/4.
//

#include <iostream>

void const_cast_test(){
    const int a  = 1;
//    int* pi = a;
    int* pi = const_cast<int*>(&a);
    *pi = 100;
}

void func(int value){
    printf("hehe \n");
}

void reinterpret_cast_test(){
    typedef void(*FuncPtr)();
    FuncPtr funcPtr;
    funcPtr = reinterpret_cast<FuncPtr>(&func);//不做类型检查
    funcPtr();
}

void static_cast_test(){//基本类型的转换
    int a = 5;
    double b = static_cast<double>(a);
    
}

class Base {
public:
    virtual void hehe(){
        std::cout << "Base" << std::endl;
    }
private:
    int a;
};

class Child : public Base{
public:
    virtual void hehe(){
        std::cout << "Child" << std::endl;
    }
    
private:
    int b;
};

void dynamic_cast_test(){//在继承体系中有虚函数才会做类型检查
    Base b;
    Child c;
    Base *pb;
    Child *pc;
    
    //父类 -> 子类
    pc = static_cast<Child*>(&b);
    if (pc == nullptr) {
        std::cout << "B -> C static cast error" << std::endl;
    }
    pc = dynamic_cast<Child*>(&b);
    if (pc == nullptr) {
        std::cout << "B -> C dynamic cast error" << std::endl;
    }
    
    //子类 -> 父类
    pb = static_cast<Base*>(&c);
    if (pb == nullptr) {
        std::cout << "C -> B static cast error" << std::endl;
    }
    pb = dynamic_cast<Base*>(&c);
    if (pb == nullptr) {
        std::cout << "C -> B dynamic cast error" << std::endl;
    }
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    const_cast_test();
    reinterpret_cast_test();
    static_cast_test();
    dynamic_cast_test();
    return 0;
}
