//
//  main.cpp
//  C++_CodeDesign
//
//  Created by sunjian on 2024/11/4.
//

#include <iostream>

class LegacyRectangle {
public:
    LegacyRectangle(double x1, double y1, double x2, double y2){
        m_x1 = x1;
        m_x2 = x2;
        m_y1 = y1;
        m_y2 = y2;
    }
    void LegacyDraw(){
        std::cout << "LegacyRectangle(double x1, double y1, double x2, double y2)" << std::endl;
    }
private:
    double m_x1;
    double m_y1;
    double m_x2;
    double m_y2;
};

class Rectangle {
public:
    virtual void Draw() = 0;
};

class Adapter : public Rectangle, public LegacyRectangle {//多重继承的方式
public:
    Adapter(double x, double y, double w, double h) : LegacyRectangle(x,y,x+w,y+h){
        
    }
    void Draw() override{
        LegacyDraw();
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";

    double x = 20.0, y = 10.0, w = 1.0, h = 2.0;
    Adapter ad(x,y,w,h);
    Rectangle *rc = &ad;
    rc->Draw();
    
    return 0;
}
