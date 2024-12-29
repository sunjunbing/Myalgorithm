//
//  main.cpp
//  C++_Algorithm_List
//
//  Created by sunjian on 2024/11/8.
//

#include <iostream>
#include <string>
#include <stack>
#include <memory>
#include <queue>

using namespace std;

class ListNode {
public:
    shared_ptr<ListNode> next;
    int num;
    
    ListNode(int num):num(num), next(nullptr){
    }
    
    ~ListNode(){
    }
    
    friend ostream& operator<<(ostream& os, const ListNode& node){
        return os << node.num;
    }
    
    static shared_ptr<ListNode> ConstructList(int count){
        shared_ptr<ListNode> head, current;
        for (int i = 0; i < count; ++i) {
            auto newNode = make_shared<ListNode>(i); // 创建新节点
            if (!head) {
                head = newNode;
            } else {
                current->next = newNode;
            }
            current = newNode; // 更新当前节点
        }
        return head;
    }
    
    static void PrintList(shared_ptr<ListNode> head){
        shared_ptr<ListNode> cur = head;
        while (cur != nullptr) {
            cout << cur->num << ' ';
            cur = cur->next;
        }
        cout << endl;
    }
};

/*
 逆序打印列表
 解法一：利用 stack
 解法二：利用递归
 */
void List1(){
    shared_ptr<ListNode> head = ListNode::ConstructList(5);
    auto reversePrint = [](shared_ptr<ListNode> node){
        if(node == nullptr) return;
        stack<shared_ptr<ListNode>> stack;
        while (node != nullptr) {
            stack.push(node);
            node = node->next;
        }
        while (!stack.empty()) {
            cout << stack.top()->num << " ";
            stack.pop();
        }
    };
    reversePrint(head);
    cout << endl;
}

/*
 删除列表中节点：要求时间复杂度为O(1)
 解法一：遍历List，找到待删除的节点，然后删除O(n)，不符合要求
 解法二：找到待删除节点的下一个节点，复制内容到待删除节点，然后删除
 */
void List2(){
    shared_ptr<ListNode> head = ListNode::ConstructList(5);
    shared_ptr<ListNode> pDelNode = head->next->next;
    auto DeleteNode = [](shared_ptr<ListNode> head, shared_ptr<ListNode> pDelNode){
        if(head == nullptr || pDelNode == nullptr) return;
        shared_ptr<ListNode>next = pDelNode->next;
        if(next == nullptr){//尾节点
            pDelNode = NULL;
        }else{//非尾部节点
            pDelNode->num = next->num;
            pDelNode->next = next->next;
            next = NULL;
        }
    };
    DeleteNode(head, pDelNode);
    ListNode::PrintList(head);
}

/*
 删除列表中的重复节点：
 解法：如果当前节点和下一个节点相同那么就要被删除
 */
void List3(){
    shared_ptr<ListNode> head = ListNode::ConstructList(10);
    head->next->next->next->num = 5;
    head->next->next->next->next->num = 5;
    ListNode::PrintList(head);
    auto dummy = make_shared<ListNode>(-1);
    dummy->next = head;
    auto newHhead = head;
    while (newHhead->next != nullptr) {
        if (newHhead->num == newHhead->next->num) {
            newHhead->next = newHhead->next->next;
        }else{
            newHhead = newHhead->next;
        }
    }
    ListNode::PrintList(dummy->next);
}

/*
 C++简单：列表中倒数第k个节点
 解法一：最简单的方法就是列表全部入栈，然后popK次，
 解法二：快慢指针，第一个指针先走k-1步后，第一、第二个同时开始走，当第一个指针到底尾部，第二个正好指向倒数第K个节点，原理是：p1和p2 之间正好相差k-1 个节点，一共包含的是k个节点
 快慢指针在列表中应用广泛：
 1.列表中倒数第k个节点
 2.获取列表的中间节点
 列表通过设置一个 dummy 头节点，能提高效率
 */
void List4(){
    shared_ptr<ListNode> head = ListNode::ConstructList(6);
    ListNode::PrintList(head);
    auto getKthFromEnd = [](shared_ptr<ListNode> head, int k){
        if(k < 1) return;
        auto p1 = make_shared<ListNode>(-1); p1->next = head;
        auto p2 = make_shared<ListNode>(-1); p2->next = head;
        int count = -1;
        while (p1->next != nullptr) {
            p1 = p1->next;
            if (++count == k - 1) {
                --count;
                p2 = p2->next;
            }
        }
        cout << p2->num << endl;
    };
    for(int i = 0; i <= 6; i++){
        cout << "倒数第" << i << "节点是 : ";
        getKthFromEnd(head, i);
    }
}

/*
 列表中环的入口节点
 1.判断列表是否有环：快慢指针
 2.计算环中节点的数量
 3.确认入口节点
 */
void List5(){
    shared_ptr<ListNode> head = make_shared<ListNode>(0);
    shared_ptr<ListNode> node1 = make_shared<ListNode>(1);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(2);
    shared_ptr<ListNode> node3 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node5 = make_shared<ListNode>(5);
    shared_ptr<ListNode> node6 = make_shared<ListNode>(6);
    head->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    node6->next = node5;
    
    auto thereIsLoop = [](shared_ptr<ListNode> head) -> shared_ptr<ListNode> {
        auto fast = head;
        auto slow = head;
        while (fast->next != nullptr) {
            fast = fast->next;
            if (fast == slow) {
                return slow;
            }
            slow = slow->next;
            if (fast->next != nullptr) {
                fast = fast->next;
            }
        }
        return nullptr;
    };
    auto nodeInLoop = thereIsLoop(head);
    if(nodeInLoop == nullptr) {
        cout << "There is no Loop" << endl;
        return;
    }
    
    auto countOfLoop = [nodeInLoop](shared_ptr<ListNode> head) -> int {
        auto guard = nodeInLoop->next;
        int ret = 1;
        while (guard != nodeInLoop) {
            ret++;
            guard = guard->next;
        }
        return ret;
    };

    auto count = countOfLoop(head);
    
    auto EntryNodeOfLoop = [&count](shared_ptr<ListNode> head) -> shared_ptr<ListNode> {
        auto fast = head;
        auto slow = head;
        while (count-- > 0) {
            fast = fast->next;
        }
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    };
    cout << "EntryPort is " << EntryNodeOfLoop(head)->num << endl;
}

/*
 反转列表
 */
shared_ptr<ListNode> reverseList1(shared_ptr<ListNode> head){
    if(head == nullptr || head->next == nullptr){
        return head;
    }else{
        auto p = reverseList1(head->next);
        head->next->next = head;
        head->next = nullptr;
        return p;
    }
}
void List6(){
    shared_ptr<ListNode> head = ListNode::ConstructList(4);
    ListNode::PrintList(head);
    //原地反转效率更高
    auto reverseList = [](shared_ptr<ListNode> head) ->shared_ptr<ListNode> {
        shared_ptr<ListNode> pre = nullptr;
        auto cur = head;
        while (cur != nullptr) {;
            auto next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    };
    //ListNode::PrintList(reverseList(head));
    //递归反转
    //ListNode::PrintList(reverseList1(head));
    //堆栈反转
    auto reverseList3 = [](shared_ptr<ListNode> head){
        auto ret = head;
        stack<shared_ptr<ListNode>> stacks;
        while (ret->next != nullptr) {;
            stacks.push(ret);
            ret = ret->next;
        }
        while (!stacks.empty()) {
            auto cur = stacks.top();
            stacks.pop();
            cur->next->next = cur;
            cur->next = nullptr;
        }
        return ret;
    };
    ListNode::PrintList(reverseList3(head));
}

/*
 合并两个有序列表，
 解法一：mergeSort
 解法二：递归
 */
shared_ptr<ListNode> mergeTwoSortedList1(shared_ptr<ListNode>& head1, shared_ptr<ListNode>& head2){
    if(head1 == nullptr){
        return head2;
    }else if(head2 == nullptr){
        return head1;
    }
    shared_ptr<ListNode> root;
    if (head1->num < head2->num) {
        root = head1;
        root->next = mergeTwoSortedList1(head1->next, head2);
    }else{
        root = head2;
        root->next = mergeTwoSortedList1(head1, head2->next);
    }
    return root;
}

void List7(){
    shared_ptr<ListNode> head1 = make_shared<ListNode>(2);
    shared_ptr<ListNode> node1 = make_shared<ListNode>(5);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(7);
    shared_ptr<ListNode> head2 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node5 = make_shared<ListNode>(6);
    
    head1->next = node1;
    node1->next = node2;
    
    head2->next = node4;
    node4->next = node5;
    
    auto mergetTwoSortList2 = [](shared_ptr<ListNode> head1,  shared_ptr<ListNode> head2) -> shared_ptr<ListNode> {
        //双队列
        queue<shared_ptr<ListNode>> q1;
        queue<shared_ptr<ListNode>> q2;
        
        while (head1 != nullptr) {
            q1.push(head1);
            head1 = head1->next;
        }
        
        while (head2 != nullptr) {
            q2.push(head2);
            head2 = head2->next;
        }
        
        shared_ptr<ListNode> newHead = make_shared<ListNode>(-1);
        auto ret = newHead;
        return ret->next;
    };
//    ListNode::PrintList(mergetTwoSortList2(head1, head2));
    //递归
    ListNode::PrintList(mergeTwoSortedList1(head1, head2));
    
}

/*
 两个列表的第一个公共节点
 */
shared_ptr<ListNode> getInteractionNode(shared_ptr<ListNode> node1, shared_ptr<ListNode> node2){
    if(node1 == nullptr || node2 == nullptr) return nullptr;
    auto A = node1; auto B = node2;
    while (A != B) {
        A = A == nullptr ? node2 : A->next;
        B = B == nullptr ? node1 : B->next;
    }
    return A;
}
void List8(){
    shared_ptr<ListNode> node1 = make_shared<ListNode>(1);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(2);
    shared_ptr<ListNode> node3 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node5 = make_shared<ListNode>(5);
    shared_ptr<ListNode> node6 = make_shared<ListNode>(6);
    shared_ptr<ListNode> node7 = make_shared<ListNode>(7);
    node1->next = node2;node2->next = node3;node3->next = node6;node6->next = node7;
    node4->next = node5;node5->next = node6;node6->next = node7;
    auto middle = getInteractionNode(node1, node4);
    cout << middle->num << endl;
    
}

/*
 分割列表：
 给定一个列表和一个特定值，使得小于 x 都在左边，大于 x 在右边
 解法一：双指针就能搞定吧
 解法二：创建两个列表A，B，小于x的, 放A，否则放B
 */
shared_ptr<ListNode> partition(shared_ptr<ListNode> node, int x){
    if (node == nullptr) return nullptr;
    auto small = make_shared<ListNode>(-1);
    auto small2 = small;
    auto big = make_shared<ListNode>(-1);
    auto big2 = big;
    while (node != nullptr) {
        if (node->num < x) {
            small->next = node;
            small = small->next;
        }else{
            big->next = node;
            big = big->next;
        }
        node = node->next;
    }
    small->next = nullptr;
    big->next = nullptr;
    while (big2->next != nullptr) {
        small->next = big2->next;
        big2->next = big2->next->next;
        small = small->next;
    }
    return small2->next;
}
void List9(){
    shared_ptr<ListNode> node1 = make_shared<ListNode>(1);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node3 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(2);
    shared_ptr<ListNode> node5 = make_shared<ListNode>(5);
    shared_ptr<ListNode> node6 = make_shared<ListNode>(2);
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    ListNode::PrintList(node1);
    auto ret = partition(node1, 3) ;
    ListNode::PrintList(ret);
}

/*
 判断一个一个列表是否是回文列表
 找到中间节点，然后反转右边的列表
 遍历判断是否相等
 */
/*
 中间节点的获取方式，快慢指针
 */
shared_ptr<ListNode> middleNode(shared_ptr<ListNode>& node){
    if (node == nullptr) return nullptr;
    auto slow = node;
    auto fast = node;
    while (slow != nullptr && fast != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
/*
 过去、现在、将来
 链表反转：过去、现在、将来
 */
shared_ptr<ListNode> reverseNode(shared_ptr<ListNode> node){
    shared_ptr<ListNode> pre = nullptr;//过去
    auto cur = node;//现在
    while (cur != nullptr) {
        auto next = cur->next;//将来
        cur->next = pre; pre = cur; cur = next;
    }
    return pre;
}
bool isPalindrom(shared_ptr<ListNode>& node){
    if (node == nullptr) return false;
    auto middle = middleNode(node);
    if (middle == nullptr) {
        return false;
    }
    auto newMiddle = reverseNode(middle);
    while (newMiddle != nullptr) {
        if (node->num != newMiddle->num) {
            return false;
        }
        node = node->next;
        newMiddle = newMiddle->next;
    }
    return true;
}
void List10(){
    shared_ptr<ListNode> node1 = make_shared<ListNode>(1);
    shared_ptr<ListNode> node2 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node3 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node4 = make_shared<ListNode>(3);
    shared_ptr<ListNode> node5 = make_shared<ListNode>(4);
    shared_ptr<ListNode> node6 = make_shared<ListNode>(1);
    
    node1->next = node2;
    node2->next = node3;
    node3->next = node4;
    node4->next = node5;
    node5->next = node6;
    ListNode::PrintList(node1);
    cout << isPalindrom(node1) << endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    List1();
    
    List2();
    
    List3();
    
    List4();
    
    List5();
    
    List6();
    
    List7();
    
    List8();
    
    List9();
    
    List10();
    
    return 0;
}
