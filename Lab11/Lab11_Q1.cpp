#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Item {
public:
    string name; // 品名
    int    exp;  // 到期時間
    int    pop;  // 熱銷度
};

vector<Item> readItems(const string& filename)
{
    vector<Item> items;// 建立一個 Item 的 vector 來存放資料
    ifstream file(filename);// 開啟檔案
    if (!file) {// 檢查檔案是否成功開啟
        cerr << "Error opening file: " << filename << '\n';
        return items;
    }
    //讀第一行：有幾筆資料 
    string line;
    int n = 0;
    if (getline(file, line)) {
        try {
            n = static_cast<int>(stoi(line));// 將第一行轉換為整數並存入 n
        } catch (...) {
            cerr << "First line must be an integer (item count)\n";
            return items;
        }
    }
    //逐行讀取其餘資料
    while (getline(file, line) && items.size() < n) {
        istringstream ss(line);
        vector<string> tokens;
        string tok;
        while (ss >> tok) tokens.push_back(tok);

        //取最後兩個 token 當 exp 與 pop
        int pop = 0, exp = 0;
        try {
            pop = stoi(tokens.back());
            exp = stoi(tokens[tokens.size() - 2]);
        } catch (...) {
            cerr << "Invalid number format in line: " << line << '\n';
            continue;
        }
        // 剩餘的 tokens 組成品名
        string name;
        for (int i = 0; i + 2 < tokens.size(); ++i) {
            if (i) name += ' ';
            name += tokens[i];
        }

        items.push_back({name, exp, pop});// 將品名、到期時間和熱銷度存入 Item 並加入 vector
    }

    file.close();
    return items;
}

bool better(const Item& a, const Item& b)// 比較兩個 Item 的函式
{
    if (a.exp != b.exp)           return a.exp < b.exp; // exp 小者優先
    else                          return a.pop > b.pop; // exp 相同，pop 大者優先
}

void merge(vector<Item>& v, int l, int m, int r)// merge 函式
{
    vector<Item> tmp; tmp.reserve(r - l + 1);// 建立一個暫存 vector 來存放合併結果
    int i = l, j = m + 1;// i 指向左半邊的起始位置，j 指向右半邊的起始位置
    // 合併兩個已排序的子陣列
    while (i <= m && j <= r) {
        if (better(v[i], v[j]))
            tmp.push_back(v[i++]);
        else
            tmp.push_back(v[j++]);
    }
    while (i <= m) tmp.push_back(v[i++]);// 將左半邊剩餘的元素加入暫存 vector
    while (j <= r) tmp.push_back(v[j++]);// 將右半邊剩餘的元素加入暫存 vector
    // 將暫存 vector 的內容複製回原 vector
    for (int k = 0; k < tmp.size(); ++k)
        v[l + k] = std::move(tmp[k]);
}

void mergeSort(vector<Item>& v, int l, int r)// mergeSort 函式
{
    if (l >= r) return;// 如果左邊界大於或等於右邊界，則不需要排序
    int m = l + (r - l) / 2;// 計算中間位置
    mergeSort(v, l, m);// 遞迴排序左半邊
    mergeSort(v, m + 1, r); // 遞迴排序右半邊
    merge(v, l, m, r);// 合併已排序的兩個子陣列
}

int main()
{
    string filename = "C:/Data Structure/Lab11/input3.txt"; //修改成檔案路徑
    vector<Item> items = readItems(filename);
    if (items.empty()) {
        cerr << "No valid data found.\n";
        return -1;
    }

    //排序 
    mergeSort(items, 0, items.size() - 1);

    //列印排序後品名 
    for (const auto& it : items)
        cout << it.name << '\n';

    return 0;
}