//
//  main.cpp
//  C++_STL
//
//  Created by sunjian on 2024/11/4.
//

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>

using namespace std;

struct Display{
    void operator()(int i){
        cout << i << " ";
    }
};

struct MapDisplay{
    void operator()(pair<string, double> info){
        cout << info.first << " " << info.second << endl;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    int array[] = {1,2,3,4};

    vector<int> iVec(array, array+4);
    list<int> iList(array, array+4);
    deque<int> iDeque(array, array+4);
    queue<int> iQueue(iDeque);
    stack<int> iStack(iDeque);
    priority_queue<int> iPQ(array, array+4);
    
    for_each(iVec.begin(), iVec.end(), Display());
    cout << endl;
    for_each(iList.begin(), iList.end(), Display());
    cout << endl;
    for_each(iDeque.begin(), iDeque.end(), Display());
    cout << endl;
    
    while (!iQueue.empty()) {
        cout << iQueue.front() << " ";
        iQueue.pop();
    }
    cout << endl;
    while (!iStack.empty()) {
        cout << iStack.top() << " ";
        iStack.pop();
    }
    cout << endl;
    while (!iPQ.empty()) {
        cout << iPQ.top() << " ";
        iPQ.pop();
    }
    cout << endl;
    
    map<string, double> studentScore;
    studentScore["hehe"] = 90.0;
    studentScore["haha"] = 91.0;
    studentScore.insert(pair<string, double>("enen", 100));
    studentScore.insert(pair<string, double>("data", 92.4));
    studentScore.insert(map<string, double>::value_type("wangwu", 55));
    for_each(studentScore.begin(), studentScore.end(), MapDisplay());

    map<string, double>::iterator iter;
    iter = studentScore.find("enen");
    if(iter != studentScore.end()){
        cout << "Find the scroe is " << (*iter).second << endl;
    }else{
        cout << "Con't find score" << endl;
    }
    
    iter = studentScore.begin();
    while (iter != studentScore.end()) {
        if (iter->second < 98.0) {
            studentScore.erase(iter++);//这里要注意迭代器失效的问题
        }else{
            iter++;
        }
    }
    for_each(studentScore.begin(), studentScore.end(), MapDisplay());
    
    for(iter = studentScore.begin(); iter != studentScore.end(); iter++){
        if (iter->second < 90.0) {
            iter = studentScore.erase(iter);//返回下一个迭代器
        }
    }
    for_each(studentScore.begin(), studentScore.end(), MapDisplay());
    studentScore.clear();
    cout << (studentScore.empty() ? "0" : "1") << endl;
    
    return 0;
}
