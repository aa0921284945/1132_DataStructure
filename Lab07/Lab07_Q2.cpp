#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
using namespace std;

// 樹的節點
class TreeNode {
public:
    int value;             // 節點的值
    TreeNode* left;        // 左子節點
    TreeNode* right;       // 右子節點

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {} // 初始化節點
};

// 樹結構
class BinaryTree {
public:
    TreeNode* root;

    BinaryTree() : root(nullptr) {} // 初始化樹

    // 用陣列構建二元樹
    TreeNode* buildTree(vector<int>& arr) {
        if (arr.empty()) return nullptr;

        queue<TreeNode*> q; // 建立queue儲存待處理的節點
        root = new TreeNode(arr[0]); // 建立根節點 (陣列第一個元素)
        q.push(root); // 將根節點加入queue

        size_t i = 1; // 陣列索引
        while (!q.empty() ) {//&& i < arr.size()
            TreeNode* current = q.front(); // 取出queue中的節點
            q.pop();

            // 添加左子節點
            if (i < arr.size()) {
                current->left = new TreeNode(arr[i]);
                q.push(current->left); // 將左子節點加入queue
                i++;
            }

            // 添加右子節點
            if (i < arr.size()) {
                current->right = new TreeNode(arr[i]);
                q.push(current->right); // 將右子節點加入queue
                i++;
            }
            
        }

        return root;
    }

    // 中序遍歷
    void inorderTraversal(TreeNode* node) {
        if (node == nullptr) return; // 如果節點為空，忽略

        inorderTraversal(node->left);  // 遍歷左子樹
        cout << node->value << " ";    // 訪問當前節點
        inorderTraversal(node->right); // 遍歷右子樹
    }
    // 查找最大值
    int findMax(TreeNode* node) {
        if (node == nullptr) return INT_MIN;  // 如果是空節點，回傳最小整數
    
        int leftMax = findMax(node->left);// 遍歷左子樹找到最左節點的值
        int rightMax = findMax(node->right);// 遍歷右子樹找到最右節點的值

        // 比較左節點和右節點大小，再跟當前節點比，最後回傳最大值
        return max(node->value, max(leftMax, rightMax));
    }
};


int main() {
    BinaryTree tree; // 宣告二元樹

    // 輸入陣列用於構建樹，NULL 表示空子節點
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };

    tree.buildTree(arr); // 建立樹

    // 中序遍歷輸出
    cout << "Inorder Traversal: ";
    tree.inorderTraversal(tree.root);
    cout << endl;

    // 查找最大值輸出
    int leftmaxValue = tree.findMax(tree.root->left); // 查找左子樹的最大值
    int rightmaxValue = tree.findMax(tree.root->right); // 查找右子樹的最大值
    cout << "Maximum left subtree value : " << leftmaxValue << endl;
    cout << "Maximum right subtree value: " << rightmaxValue << endl;

    return 0;
} 