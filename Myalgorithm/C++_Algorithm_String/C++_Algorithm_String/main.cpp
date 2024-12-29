//
//  main.cpp
//  C++_Algorithm_String
//
//  Created by sunjian on 2024/11/14.
//

#include <iostream>
#include <string>

using namespace std;

/*
 替换空格
 解法一：从前到后遍历整个字符串，碰到空格，就将后面的字符向后移动
 解法二：从后到前的遍历，使用快慢指针，有的时候从前向后复杂可以考虑从后向前
 基础：数据结构与算法、操作系统、网络协议
 语言：C/C++、OC、Swift、C#、Shell、Vim、TypeScript
 */
void String(){
    string str = "How are you";
    cout << str << endl;
    auto replaceSpace = [](string& str){
        string replaceStr  = "%20";
        if (str.length() <= 0 ) return;
        int spaceCount = 0;
        for (auto it = str.begin(); it != str.end(); it++) {
            if (*it == ' ') {
                spaceCount++;
            }
        }
        int totalLen = ((int)str.length() - spaceCount) + spaceCount * 3;
        auto retStr = string(totalLen,' ');
        
        int oldIndex = (int)str.length();
        int newIndex = (int)retStr.length();
        int replaceIndex = (int)replaceStr.length();
        
        while (--oldIndex >= 0 && --newIndex >= 0) {
            if (str[oldIndex] == ' ') {
                while (--replaceIndex >= 0) {
                    retStr[newIndex--] = replaceStr[replaceIndex];
                }
                replaceIndex = (int)replaceStr.length();
                newIndex++;
            }else{
                retStr[newIndex] = str[oldIndex];
            }
        }
        
        cout << retStr << endl;
    };
    replaceSpace(str);
}

/*
 第一个只出现一次的字符串
 解法一：使用位图，可 Mach 中 hash[128] 用官方提供map 有点大才小用，考虑到字符的特性 char = 1Byte = 8bits = 265，
 */
void String2(){
//    char[] str = "abaccdef";
    const char* str = "abaccdef";
    auto firstUniqChar = [](const char* str) -> char{
        const int Len = 256;
        unsigned int hashTable[Len];
        for (int  i = 0; i < Len; i++) {
            hashTable[i] = 0;
        }
        int i = 0;
        while (str[i++] != '\0') {
            hashTable[str[i]]++;
        }
        i = 0;
        while (str[i++] != '\0') {
            if (hashTable[str[i]] == 1) {
                return str[i];
            }
        }
        return '\0';
    };
    cout << firstUniqChar(str) << endl;
}

/*
 反转字符串：
 解法一：分两步，1.全句反转 2.单词反转
 */
void Reverse(string& str){
    string ret(str);
    int index = 0;
    for (auto it = str.rbegin(); it != str.rend(); it++) {
        ret[index++] = *it;
    }
    str = ret;
}

void String3(){
    string str = "I am a student.";
    Reverse(str);
    cout << str << endl;
    int begin = 0;
    string ret;
    str += ' ';
    for (int end = 0; end < (int)str.length(); ++end) {
        if (str[end] == ' ') {
            string temp(str.begin()+begin, str.begin() + end);
            Reverse(temp);
            if (ret.length() == 0) {
                ret += temp;
            }else{
                ret += ' ';
                ret += temp;
            }
            begin = end+1;
        }
    }
    cout << ret << endl;
}

/*
 左旋转字符串:
 参考上面那道题的思路解决问题
 */
void myReverse(string& str, int begin, int end){
    while (begin <= end) {
        auto temp = str[begin];
        str[begin] = str[end];
        str[end] = temp;
        begin++;end--;
    }
}
void reverseLeftWords(string& str, int n){
    if(str.length() == 0 || n <= 0 || n >= str.length()) return;
    int len = (int)str.length()-1;
    int leftEnd = len - n;
    myReverse(str, 0, (int)str.length()-1);
    myReverse(str, 0, leftEnd);
    myReverse(str, leftEnd+1, (int)str.length()-1);
}
void String4(){
    string str = "abcdefg";
    cout << str << endl;
    reverseLeftWords(str, 2);
    cout << str << endl;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    String();
    
    String2();
    
    String3();
    
    String4();
    
    return 0;
}
