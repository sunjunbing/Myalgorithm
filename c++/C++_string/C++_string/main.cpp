//
//  main.cpp
//  C++_string
//
//  Created by sunjian on 2024/11/1.
//

#include <iostream>
#include <string.h>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    char strArray[] = "HelloWorld";
    char strArray2[16] = {0};
    char* pStr = "elloddrl";
    //1.计算字符串的长度
    cout << strlen(strArray) << " " << sizeof(strArray) << endl;
    cout << strlen(pStr) << endl;
    //2.比较字符串
//    if(strcmp(strArray, pStr)){
//        cout << "strArray > pStr" << endl;
//    }
    //3.字符串的拷贝
//    strcpy(strArray, pStr);
//    cout << strArray << endl;
    //4.复制指定长度的字符串
//    strncpy(strArray, pStr, 5);//将字符串 pStr 前5 个字符拷贝到 strArray 中
//    cout << strArray << endl;
    //5.字符串的拼接
//    strcat(strArray, pStr);
//    cout << strArray << endl;
    //6.字符串查找
//    cout << strchr(strArray, 'H') << endl;
//    cout << strstr(strArray, "Hell") << endl;
    //编译器很重要
    
    string s = "feing";
    string s1("helloWorld");
    string s2 = string("hellold");
    cout << s << " " << s1 << " " << s2.c_str() << endl;
    cout << s.size() << " " << s1.length() << " " << s2.capacity() << endl;
    //C++中字符串可以直接比较
    string s3 = s + s2;
    cout << s3 << endl;
    for(int i = 0; i < s3.length(); i++){
        s3[i] += 1;
    }
    cout << s3 << endl;
    
    int* a = NULL;
    
    return 0;
}
