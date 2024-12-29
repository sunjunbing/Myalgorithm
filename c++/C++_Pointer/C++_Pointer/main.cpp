//
//  main.cpp
//  C++_Pointer
//
//  Created by sunjian on 2024/11/1.
//

#include <iostream>

int a = 0;//GVAR 全局变量区
int *p1;//bss 段， 为初始化的全局区

void test(){
    char ch = 'a';//临时变量放在栈区
    char *cp = &ch;//cp是栈区的地址，放的是 ch 的地址值
    
    char* cp2 = ++cp;//cp2 = cp + 1;    cp += 1
    char* cp3 = cp++;//cp3 = cp2;       cp += 1
    char* cp4 = --cp;//cp4 = cp3;       cp -= 1
    char* cp5 = cp--;//cp5 = cp4;       cp -= 1
    
    
    *++cp2 = 98;
    char ch3 = *++cp2;
    *cp2++ = 98;
    char ch4 = *cp2++;
    
    
    int a = 1, b = 2, c, d;
    
    c = a+++b;
    
    char ch5 = ++*++cp;
    
    //cp 的地址是：0x00007ffeefbff3c0
    //cp ：0x00007ffeefbff3cf
    //cp + 1 : 0x00007ffeefbff3d0，cp 中的内容+1
    //*(cp+1)放的是0x00007ffeef626240
    //++*++cp = 0x00007ffeef626240 + 1 = 0x00007ffeef626241 char是一个字节
    //0x41 = 0d65 = A
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    int b = 1;
    char s[] = "123";
    int *p2 = NULL;
    char *p3 = "456";//p3 中存放的是 常量 “456”在常量区的地址，常量区的地址中存放的才是 “456”
    static int c = 0;// GVAR 全局（静态）初始化区
    p2 = new int(10);
    p1 = new int(20);
    
    
    sizeof(p1);
    
    
    
    char ch = 'a';//ch 就是内存地址的一个别名，在内存中有一个叫 ch 的地址，里面放的是字符 a
//    &ch = 98;
    char *chP = &ch;//ch 具体的地址是啥呢，需要通过&获取
    char **chPp = &chP;
    
    *chP = 'b';//更新 ch 的数据，也就是通过直接通过地址修改

    char ch2 = *chP;
    
    ch2 = *chP + 1;
    
    *(chP + 1) ='a';
    
    
    char *cp = ++chP;
    
    char *cp1 = chP++;
    
    test();
    
    return 0;
}
