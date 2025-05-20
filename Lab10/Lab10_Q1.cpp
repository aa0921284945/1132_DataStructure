#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int EMPTY = (int)NULL; // 用 NULL 代表沒有節點
class TreeNode {
public:
    int value;// 節點值
    TreeNode* left;// 左子節點
    TreeNode* right;// 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}//初始化節點
};

class BinaryTree {
public:
    TreeNode* root;// 樹根節點

    BinaryTree() : root(nullptr) {}

    TreeNode* buildTree(const vector<int>& arr) {// 建立樹
        if (arr.empty() || arr[0] == EMPTY) return nullptr;

        queue<TreeNode**> q;//建立queue儲存待處理的節點指標
        root = new TreeNode(arr[0]);// 建立根節點 (陣列第一個元素)
        q.push(&root);// 將根節點的指標加入queue

        size_t i = 1;// 陣列索引
        while (!q.empty() && i < arr.size()) {
            TreeNode** nodePtr = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除

            // 左子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->left = new TreeNode(arr[i]);// 添加左子節點
                    q.push(&((*nodePtr)->left));// 將左子節點的指標加入queue
                }
                i++;
            }
            // 右子節點
            if (i < arr.size()) {
                if (arr[i] != EMPTY) {
                    (*nodePtr)->right = new TreeNode(arr[i]);// 添加右子節點
                    q.push(&((*nodePtr)->right));// 將右子節點的指標加入queue
                }
                i++;
            }
        }
        return root;
    }

    void Depth_first_search(TreeNode* node) {//深度優先搜尋
        if (node == nullptr) return;
        cout << node->value << " ";// 訪問當前節點的值
        Depth_first_search(node->left);// 遞迴遍歷左子樹
        Depth_first_search(node->right);// 遞迴遍歷右子樹
    }

    void Breadth_first_search(TreeNode* root) {
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue

        while (!q.empty()) {
            TreeNode* current = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除
            cout << current->value << " ";
            if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
            if (current->right) q.push(current->right);// 將右子節點的指標加入queue
        }
    }
    void Level_sum(TreeNode* root, int layer) {// 計算指定層的總和
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue
        int level = 0;// 樹的層數
        int level_sum = 0;// 指定層的總和
        while (!q.empty()) {// 當queue不為空時
            int size = q.size();// 當前層的節點數量
            for (int i = 0; i < size; i++) {// 遍歷當前層的所有節點
                TreeNode* current = q.front();// 取出queue的第一個節點指標
                q.pop();// 將該節點從queue中刪除
                if (level == layer) {// 如果當前層等於指定層
                    level_sum += current->value;// 將當前節點的值加入總和
                }else if (level != layer) {// 如果當前層不等於指定層
                    if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
                    if (current->right) q.push(current->right);// 將右子節點的指標加入queue
                }
            }
            level++;// 增加層數
        }
        if (level_sum != 0) {// 如果指定層的總和不為0
            cout << level - 1 << "Level Sum: " << level_sum << endl;
        } else {// 如果指定層的總和為0
            cout << "Over tree high" << endl;
        }
    }
};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, NULL, NULL, 10, 11, NULL, NULL };
    tree.buildTree(arr);

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;
    
    cout << "Enter search level (from 0): ";
    int layer;
    cin >> layer;
    tree.Level_sum(tree.root, layer);
    return 0;
}