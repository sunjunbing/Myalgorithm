//
//  Observerable.hpp
//  C++_Observer
//
//  Created by sunjian on 2024/11/4.
//

#ifndef Observerable_hpp
#define Observerable_hpp

#include <stdio.h>
#include <list>
#include "Observer.hpp"
#include <string>

class Observerable {
public:
    Observerable();
    ~Observerable();
    
    virtual void getSomeNews(std::string news){
        setChange(news);
    }
    
    void Attach(Observer *observer);//const的作用成员变量是无法被改变的
    
    void Detach(Observer *observer);
    
protected:
    void setChange(std::string news){
        m_bChanged = true;
        Notify((void*)(news.c_str()));
    }
    
    void Notify(void *args){
        if(m_bChanged){
            auto it = m_observers.begin();
            for(; it != m_observers.end(); it++){
                (*it)->update(args);
            }
        }
        m_bChanged = false;
    }

private:
    std::list<Observer*> m_observers;
    bool m_bChanged = {0};
};

#endif /* Observerable_hpp */
