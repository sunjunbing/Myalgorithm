//
//  main.cpp
//  C++_Observer
//
//  Created by sunjian on 2024/11/4.
//

#include <iostream>
#include "Observer.hpp"
#include "Observerable.hpp"
#include <iostream>

class News : public Observerable{
public:
    virtual void getSomeNews(std::string news) override{
        setChange("I have private " + news);
    }
};

class User1 : public Observer{
    void update(void *args) {
        std::cout << "User1 update " + std::string(reinterpret_cast<char*>(args)) << std::endl;
    }
};

class User2 : public Observer{
    void update(void *args) {
        std::cout << "User2 update " + std::string(reinterpret_cast<char*>(args)) << std::endl;
    }
};

void func(void *){
    std::cout << "func(void *)" << std::endl;
}

void func(int){
    std::cout << "func(int)" << std::endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    User1 u1;
    User2 u2;
    
    News news;
    news.Attach(&u1);
    news.Attach(&u2);
    
    news.getSomeNews("I'm fired");
    
    return 0;
}
