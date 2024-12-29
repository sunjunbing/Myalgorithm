//
//  main.cpp
//  C++_FileOperate
//
//  Created by sunjian on 2024/11/3.
//

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int a;
    int index = 0;
    fstream fout;
    fout.open("test.txt");
    
    while (cin >> a) {
        fout << "The number is " << a << endl;
        index++;
        if (index == 5) {
            break;
        }
    }
    

    fout.close();
    
    return 0;
}
