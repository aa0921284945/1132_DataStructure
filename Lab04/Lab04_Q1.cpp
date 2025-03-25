#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>//根據時間來產生亂數
using namespace std;
// 表示單張撲克牌的類別
class Card {
public:
    string colors; //儲存撲克牌的花色
    string rank; //儲存撲克牌的數值
    Card(string s, string r) : colors(s), rank(r) {} //建立constructor來初始化物件，當Card物件建立時，它會自動執行這個函式，並把s和r的值存入colors和rank
    void display() const { //顯示撲克牌的資訊
        cout << rank << " of " << colors << endl;
    }
};

// 實作Stack
class Stack {
private:
    vector<Card> stack; //表示stack是一個能存放Card類別物件的vector
    int top = -1; //表示stack的頂端

public:
    //因為使用vector來實作stack，所以沒有特別限制容器上限
    void push(const Card& card) {
        stack.push_back(card);//將每張card加入stack
        top++;//top往上移動一層
    }

    Card pop() {
        if (isEmpty()) {//如果容器是空的
            cout << "Stack is empty!" << endl;//提示
            return Card("", "");//回傳空的Card
        }
        else {
            Card topCard = stack[top]; // 先取出目前top的card，附值給暫存的Card類別物件
            top--; // 然後再減少 top
            return topCard;//回傳取出的topCard
        }
    }

    bool isEmpty() const {
        return top == -1;//top為-1表示stack是空的
    }
};

// 代表一副撲克牌的類別
class Deck {
private:
    vector<Card> cards; // 存放未洗牌的撲克牌
    Stack shuffledDeck; // 存放洗過的牌，用實作的stack來管理
public:
    Deck() { //建立constructor來初始化物件
        string colors[] = { "Hearts", "Diamonds", "Clubs", "Spades" }; //儲存撲克牌的花色
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" }; //儲存撲克牌的數值

        //利用迴圈將52張牌加入cards這個vector裡面
        for (int i = 0; i < 4; i++) { // 四種花色
            for (int j = 0; j < 13; j++) { // 13 種點數
                cards.push_back(Card(colors[i], ranks[j]));
            }
        }
    }

    //洗牌(Hint:使用shuffle函數)
    void shuffleDeck() {
        mt19937 rng;//使用mt19937隨機引擎
        rng.seed(time(0));//根據系統時間設定亂數種子
        shuffle(cards.begin(), cards.end(), rng);//呼叫shuffle函數，將cards的元素打亂
        for (int i = 0; i < 52; i++) {//52張牌所以重複52次
            shuffledDeck.push(cards[i]);//遍歷cards物件，將洗牌後的每張牌加入shuffledDeck這個stack
        }
    }

    //發牌
    void drawAllCards() { 
        while (!shuffledDeck.isEmpty()) {
            shuffledDeck.pop().display();//當shuffledDeck不是空的，就取出一張牌並顯示 
        }
    }
};

int main() {
    Deck deck; //建立deck產生52張撲克牌
    deck.shuffleDeck(); //進行洗牌並放入堆疊
    cout << "Shuffled deck:" << endl;
    deck.drawAllCards(); //依序取出堆疊內的牌並顯示
    return 0;
}
