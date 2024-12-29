//
//  Observer.hpp
//  C++_Observer
//
//  Created by sunjian on 2024/11/4.
//

#ifndef Observer_hpp
#define Observer_hpp

#include <stdio.h>

class Observer {
public:
    Observer(){}
    ~Observer(){}
    virtual void update(void* args) = 0;
};

#endif /* Observer_hpp */
