#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <cmath>
using namespace std;

// 定義 Stack 的節點結構
template <typename T>
struct Node {
    T data;  // 存儲資料(可以是任何類型)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
template <typename T>
class Stack {
    private:
        Node<T>* top; // 指向堆疊頂端
    public:
        Stack() { top = nullptr; } // 初始化堆疊
        ~Stack() {
            while (!isEmpty()) {
                pop();
            }
        }// 釋放Stack記憶體
    
        // Push 操作：將元素放入堆疊
        void push(T ch) {
            Node<T>* newNode = new Node<T>;// 建立新節點
            newNode->data = ch;// 設定節點的數值
            newNode->next = top;// 將新節點的next指向Top指的節點(從Top放入)
            top = newNode;// 更新Top指向新節點
        }
    
        // Pop 操作：移除並回傳頂端元素
        T pop() {
            if (isEmpty()) {// 判斷Stack是否為空
                cout << "Stack is empty!" << endl;
                return T();
            }
            T charValue = top->data;// 取得Top元素的數值
            Node<T>* temp = top;// 複製Top指向的節點
            top = top->next;// 更新Top指向下一個節點
            delete temp;// 釋放原Top指向的節點記憶體
            return charValue;// 回傳Top元素的數值
        }
    
        // Peek 操作：取得頂端元素但不移除
        T peek() {
            if (isEmpty()) {// 判斷Stack是否為空
                cout << "Stack is empty!" << endl;
                return T();
            }
            T charValue = top->data;// 取得Top元素的數值
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

// 判斷是否為運算子
bool isOperator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%') {
        return true;
    }
    return false;
}

// 判斷運算子的優先順序
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(string& infix, string& postfix) {
    Stack<string> stack;// 建立一個存放string的Stack
    int i = 0;// 記錄當前字元位置
    while (i < infix.length()) {// 迴圈直到string結束
        // 判斷是否為負號若出現在開頭、 ( 後面、運算子後面，則視為負號
        // isOperator(infix[i-2]) 跳過空白字元往後檢查
        if (infix[i] == '-' && (i == 0 || infix[i-1] == '(' || isOperator(infix[i-1]))) {
            string number = "-";// 先放入負號
            bool hasDecimal = false;// 判斷是否有小數點
            i++;// 索引往後移動 
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {// 處理小數點和多位數的情況
                if (infix[i] == '.') {// 判斷小數點格式是否正確
                    if (hasDecimal) {
                        // 發現第二個小數點，錯誤處理
                        cout << "Error: Invalid number format (multiple decimal points) " << endl;
                        return;
                    }
                    hasDecimal = true;
                }
                number += infix[i++];// 將一個一個字元放入number中
            }
            postfix += number + " ";// 如果是數字直接放入postfix中(已經是處理過的string)
        }else if (isdigit(infix[i]) || infix[i] == '.') {// 判斷是否為數字或小數點
            string number = "";// 先放入空string
            bool hasDecimal = false;// 判斷是否有小數點
            while (i < infix.length() && (isdigit(infix[i]) || infix[i] == '.')) {// 處理小數點和多位數的情況
                if (infix[i] == '.') {// 判斷小數點格式是否正確
                    if (hasDecimal) {
                        // 發現第二個小數點，錯誤處理
                        cout << "Error: Invalid number format (multiple decimal points)" << endl;
                        return;
                    }
                    hasDecimal = true;
                }
                number += infix[i++];// 將一個一個字元放入number中
            }
            postfix += number + " ";// 如果是數字直接放入postfix中(已經是處理過的string)
        }else if (infix[i] == '(') { // 判斷是否為左括號
            stack.push("(");// 將左括號放入Stack中
            i++;
        } else if (infix[i] == ')') {// 判斷是否為右括號
            while (!stack.isEmpty() && stack.peek() != "(") {// 直到Stack為空或遇到左括號
                postfix += stack.pop() + " ";// 將Stack中的運算子放入postfix中
            }
            stack.pop();  // 移除 '('
            i++;
        } else if (isOperator(infix[i])) {// 判斷是否為運算子
            string op(1, infix[i]); // 將字元轉換為string
            while (!stack.isEmpty() && precedence(stack.peek()[0]) >= precedence(infix[i])) {// 判斷Stack中的運算子優先順序
                postfix += stack.pop() + " ";// 先pop出來順序高的運算子
            }
            stack.push(op);// 再將當前運算子放入Stack中
            i++;
        } else if (infix[i] == ' ') {// 判斷是否為空白字元
            i++;// 跳過空白字元
        } else {
            cout << "invalid characters: " << infix[i] << endl; // 無效字元提示
            return;
        }
    }
    while (!stack.isEmpty()) {// 將Stack剩餘運算子放入postfix中
        postfix += stack.pop() + " ";
    }
    cout << "Postfix expression: " << postfix << endl;// 顯示後序表達式
}   

// 計算後序表達式的值
double EvaluatePostfix(const string& postfix) {
    Stack<double> stack;// 建立一個存放double的Stack
    istringstream iss(postfix); // 依據空白字元分割string
    string token; // 存放每個token

    while (iss >> token) {// 分割後的string傳到token依序處理
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {// 判斷是否為數字或負數
            stack.push(stod(token));// 將string轉換為double並放入Stack中
        } else if (token.length() == 1 && isOperator(token[0])) {// 判斷是否為運算子
            if (stack.isEmpty()) {// 判斷Stack是否為空
                cout << "Error: insufficient operands" << endl;
                return 0;
            }
            double b = stack.pop();// 取出Stack中的第二個數字
            if (stack.isEmpty()) {// 判斷Stack是否為空
                cout << "Error: insufficient operands" << endl;
                return 0;
            }
            double a = stack.pop();// 取出Stack中的第一個數字
            double result = 0;// 存放計算結果

            switch (token[0]) {// 根據運算子進行計算
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                case '%': result = fmod(a, b); break;
                case '^': result = pow(a, b); break;
            }
            stack.push(result);// 將計算結果放入Stack中
        } else {
            cout << "Invalid token: " << token << endl;// 無效字元提示
            return 0;
        }
    }
    // 正常情況下，Stack中應該只剩下最後的結果，如果是空的則報錯
    if (stack.isEmpty()) {// 判斷Stack是否為空
        cout << "Error: invalid postfix expression" << endl;// 無效後序表達式提示
        return 0;
    }

    double finalResult = stack.pop();// 取出Stack最後剩下的的結果

    // 如果Stack中還有其他元素，表示有多餘數字則報錯
    if (!stack.isEmpty()) {
        cout << "Error: too many operands" << endl;
        return 0;
    }

    return finalResult;// 回傳計算結果
}

int main() {
    string infix, postfix;
    postfix = "";// 初始化postfix為空
    cout << "Enter an Infix expression: ";// 提示使用者輸入中序表達式
    getline(cin, infix);// 讀取整行輸入(可處理空白字元)
    //infix = "2.5 + 3.5 * 2"; // 測試用的中序表達式
    InfixToPostfix(infix, postfix);// 將中序表達式轉換為後序表達式
    double result = EvaluatePostfix(postfix);// 計算後序表達式的值
    cout << "Result = " << result << endl;// 顯示計算結果
    return 0;
}