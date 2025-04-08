#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// 定義 Stack 的節點結構
struct Node {
    char data;  // 存儲字符 (運算子或括號)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top; // 指向堆疊頂端
public:
    Stack() { top = nullptr; } // 初始化堆疊
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }// 釋放Stack記憶體

    // Push 操作：將元素放入堆疊
    void push(char ch) {
        Node* newNode = new Node();// 建立新節點
        newNode->data = ch;// 設定節點的數值
        newNode->next = top;// 將新節點的next指向Top指的節點(從Top放入)
        top = newNode;// 更新Top指向新節點
    }

    // Pop 操作：移除並回傳頂端元素
    char pop() {
        if (isEmpty()) {// 判斷Stack是否為空
            cout << "Stack is empty!" << endl;
            return 0;
        }
        char charValue = top->data;// 取得Top元素的數值
        Node* temp = top;// 複製Top指向的節點
        top = top->next;// 更新Top指向下一個節點
        delete temp;// 釋放原Top指向的節點記憶體
        return charValue;// 回傳Top元素的數值
    }

    // Peek 操作：取得頂端元素但不移除
    char peek() {
        if (isEmpty()) {// 判斷Stack是否為空
            cout << "Stack is empty!" << endl;
            return 0;
        }
        char charValue = top->data;// 取得Top元素的數值
        return charValue;// 回傳Top元素的數值
    }

    // 判斷堆疊是否為空
    bool isEmpty() {
        if (top == nullptr) {// 判斷Top是否初始化狀態
            return true;
        }
        return false;
    }
};

// 判斷運算子(加減乘除) 的優先順序
int precedence(char op) {
    // 回傳數值越大，代表優先順序越高
    switch (op) {
        case '+':
        case '-':
            return 1; 
        case '*':
        case '/':
            return 2;
        default:
            return 0;  // 非運算子或未定義
    }
}


// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
    Stack stack;// 用來存運算子和括號的Stack
    int j = 0;// postfix 字串的索引
    int length = strlen(infix);// 取得infix的長度

    for (int i = 0; i < length; i++) {
        char c = infix[i];
        // 如果是數字或字母，直接加到postfix
        if (isalnum(c)) {
            postfix[j++] = c;
        }
        // 如果是左括號，push進Stack
        else if (c == '(') {
            stack.push(c);
        }
        // 如果是右括號，pop直到遇到左括號
        else if (c == ')') {
            while (stack.peek() != '(') {
                postfix[j++] = stack.pop();
            }
            stack.pop();// 將左括號pop出Stack，但不放入postfix
        }
        // 如果是運算子 (+, -, *, /)
        else {
            // 當Stack不為空、且頂端運算子優先權 >= 當前運算子時
            // 將Stack頂端運算子pop出來放入postfix
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c)) {
                postfix[j++] = stack.pop();
            }
            // 再push當前的運算子
            stack.push(c);
        }
    }
    // 將Stack中剩餘的運算子全部pop到postfix
    while (!stack.isEmpty()) {
        postfix[j++] = stack.pop();
    }
    // 添加最後字串結尾
    postfix[j] = '\0';
}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin >> infix; // 輸入中序表達式
    
    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式

    return 0;
}