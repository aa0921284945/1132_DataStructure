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
    int sum(TreeNode* node) {// 計算子樹的總和
        if (node == nullptr) return 0;// 如果節點為空，返回0
        return node->value + sum(node->left) + sum(node->right);// 遞迴計算左子樹和右子樹的總和
    }
    void Search_node(int node_value){// 搜尋節點
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root);// 將根節點的指標加入queue
        while (!q.empty()) {// 當queue不為空時，繼續搜尋
            TreeNode* current = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除
            if (current->value == node_value) {// 如果找到節點
                if (current->left == nullptr && current->right == nullptr) {// 如果該節點是葉子節點
                    cout << "Node with value " << node_value << " found, but it is a leaf node." << endl;
                } else {// 如果該節點不是葉子節點
                    cout << "left subtree sum: " << sum(current->left) << endl;// 計算左子樹的總和
                    cout << "right subtree sum: " << sum(current->right) << endl;// 計算右子樹的總和
                    max(sum(current->left), sum(current->right)) == sum(current->left) ? cout << "left subtree is larger" : cout << "right subtree is larger";
                    cout << endl;// 輸出較大的子樹
                }
                return;// 找到節點，返回
            }
            if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
            if (current->right) q.push(current->right);// 將右子節點的指標加入queue
        }
        cout << "Node with value " << node_value << " not found." << endl;// 如果沒有找到節點
    }
};

int main() {
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, NULL, NULL, 10, 11, NULL, NULL };
    tree.buildTree(arr);

    cout << "BFS Result: ";
    tree.Breadth_first_search(tree.root);
    cout << endl;
    
    cout << "Enter search node value: ";
    int node_value;
    cin >> node_value;
    tree.Search_node(node_value);
    return 0;
}