#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player {  /*玩家結構資料型態，包含string類型的玩家名稱以及int類型的玩家分數*/
    string name;
    int score;
};
/*如果抽到兩張 1 點，最多只能選擇一張當作 11 點，所以讓第一次抽到的當作 11 點*/
int drawCard(Player* player) {/*傳入Player結構，用來判斷目前score以及誰抽牌*/
    int score = rand() % 10 + 1; /*發牌功能，呼叫一次發一張數值在1-10之間的牌*/
    if (score == 1) {/*如果抽到 1 點*/
        cout << player->name << " 抽到 1 點，";
        if (player->score == 0) {/*如果是第一張牌，則選擇當作 11 點*/
            score = 11;
            cout << "第一張牌選擇當作 11 點 " << endl;
        }
        else if (player->score + 11 <= 21) {/*判斷會不會爆*/
            score = 11;/*如果不會爆，則選擇當作 11 點*/
            cout << "少於 21 點選擇當作 11 點 " << endl;
        }
        else {/*如果會爆，就當作 1 點*/
            cout << "多於 21 點選擇當作 1 點 " << endl;
        }
    }
    return score;
}

// 初始化玩家
void initializePlayer(Player* player, string name) {
    /*利用上面的結構變數，達到完成初始化玩家並且同時發兩張初始手牌*/
    player->name = name;/*傳入的name賦值給傳入的Player結構的name */
    player->score = 0;/*初始化score為0，否則初始值是亂數不會正確判斷是否會爆*/
    player->score = drawCard(player);/*先抽一次牌回傳，更新目前score*/
    player->score += drawCard(player);/*再抽第二次牌，避免連續抽到 1 點*/
}
// 顯示玩家分數
void displayScore(Player* player) {
    /*顯示玩家當前的手牌點數*/
    cout << player->name << " 的分數: " << player->score << endl;/*使用傳入函式Player結構的name和score，輸出點數*/
}
// 玩家回合
void playerTurn(Player* player) {
    char choice;/*初始化一個字元*/
    while (player->score < 21) {/*如果小於21點*/
        cout << "要抽牌嗎？(h = 抽, s = 停) : ";
        cin >> choice;/*讀取輸入字元*/
        if (choice == 'h') {
            //抽牌提示；宣告一個變數再呼叫抽牌函數
            /*將新抽到的手牌點數加上原本玩家擁有的手牌點數，並打印出來當前玩家手牌總點數*/
            int newCard = drawCard(player);/*初始化抽到的卡*/
            player->score += newCard;/*原本的score加上抽到的*/
            cout << "抽到 " << newCard << " 點，目前總分: " << player->score << endl;/*輸出抽完後的狀態*/
            if (player->score > 21) {/*爆掉直接結束*/
                cout << player->name << " 爆掉了！遊戲結束。\n";
                return;
            }
        }
        else if (choice == 's') {/*停止抽牌*/
            break;
        }
    }
}
// 莊家回合
void dealerTurn(Player* dealer) {
    while (dealer->score < 17) { // 莊家至少要到 17 點
        //抽牌提示；宣告一個變數再呼叫抽牌函數
        /*如果莊家點數小於17，則至少持續增加手牌值到莊家手牌點數大於等於17，並將莊家手牌點數打印出來*/
        int newCard = drawCard(dealer);/*初始化抽到的卡*/
        dealer->score += newCard;/*原本的score加上抽到的*/
        cout << "莊家 抽到 " << newCard << " 點，目前總分: " << dealer->score << endl;/*輸出抽完後的狀態*/
        if (dealer->score > 21) { // 如果莊家超過 21 點
            cout << "莊家爆了！玩家獲勝！" << endl;
            return; // 遊戲結束
        }
    }
}
// 判斷勝負
void determineWinner(Player* player, Player* dealer) {/*傳入指向玩家和莊家的address*/
    if (player->score > 21) {/*如果玩家爆了*/
        cout << "你爆了！莊家獲勝！\n";
    }
    else if (dealer->score > 21 || player->score > dealer->score) {/*如果莊家爆了或者玩家點數大於莊家*/
        cout << "你贏了！!\n";
    }
    else if (player->score == dealer->score) {/*如果score一樣*/
        cout << "平手！\n";
    }
    else {
        cout << "莊家贏了！\n";/*其他情況莊家獲勝*/
    }
}

// 主程式
int main() {
    srand(time(0));/*初始化亂數種子*/

    Player player, dealer;/*初始化玩家和莊家*/
    initializePlayer(&player, "玩家");/*初始化玩家*/
    initializePlayer(&dealer, "莊家");/*初始化莊家*/

    displayScore(&player);/*顯示玩家分數*/
    playerTurn(&player);/*玩家回合*/

    if (player.score <= 21) { // 如果沒爆才讓莊家回合
        cout << "\n莊家回合...\n";
        displayScore(&dealer);/*顯示莊家分數*/
        dealerTurn(&dealer);/*莊家回合*/
        determineWinner(&player, &dealer);/*判斷勝負*/
    }

    return 0;
}