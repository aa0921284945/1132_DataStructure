#include <vector>
#include <iostream>
using namespace std;

class Solution{
public:
    vector<int> runningSum(vector<int>& nums) {
        int n = nums.size();//宣告一個n來記錄nums陣列的長度
        vector<int> result(n);//使用vector動態宣告result陣列長度跟nums一樣
        result[0] = nums[0];//nums陣列的第一個value固定不變
        //跑一個for迴圈依序加起來，第一個元素不變，索引i從1開始
        for (int i = 1; i < n; i++) {
            //第i個位置等於前一個位置的值加上目前位置的值
            result[i] = result[i - 1] + nums[i];
        }
        return result;//回傳一個vector陣列
        //n + 4，時間複雜度O(n)
    }
};
int main() {
    Solution sol;
    vector<int> nums = {1, 2, 3, 4};
    vector<int> result = sol.runningSum(nums);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    return 0;
}