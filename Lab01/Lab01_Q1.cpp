#include <vector>
#include <iostream>
using namespace std;

//原本使用前後互減是否為0或1來作為區分標準，但是在隱藏測資會失敗
//於是使用兩個bool來分別判斷可能出現的遞增或遞減兩種情況，最後再用OR來選擇是否為其中一種，或是兩種都不是。
class Solution {
public:
    bool isMonotonic(vector<int>& nums) {
        int count = 0;
        bool increase = true;
        count++;//(increase = )initialization |count 1
        bool decrease = true;
        count++;//(decrease = )initialization |count 1
        count++;//(i = 0)loop initialization |count 1
        count++;//(nums.size() - 1)loop comparison |count 1
        for (int i = 0; i < nums.size() - 1; i++) {
        count++;//(i < nums.size())loop comparison |count n-1
        count++;//(nums[i])loop array access |count n-1
        count++;//(nums[i + 1])loop array access |count n-1
        count++;//([i + 1])loop  multiple |count n-1
        count++;//(nums[i] > nums[i + 1])loop comparison |count n-1
            if (nums[i] > nums[i + 1]) {
                count++;//(increase = )assignment |count n-1
                increase = false;
            }
            count++;//(nums[i])loop array access |count n-1
            count++;//(nums[i + 1])loop array access |count n-1
            count++;//([i + 1])loop multiple |count n-1
            count++;//(nums[i] < nums[i + 1])comparison |count n-1
            if (nums[i] < nums[i + 1]) {
                count++;//(decrease = )assignment |count n-1
                decrease = false;
            }
            count++;//(i++)loop increment |count n-1
        }
        count++;//(return)return |count 1
        count++;//(decrease || increase)OR |count 1
        cout << "Total operations: " << count << endl;
        return decrease || increase;
    }
};
//Total operations:
//4 (initial) + 11(n-1) (loop) + 2 (return) = 11n + 6
//Time complexity: O(n)

int main() {
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7};
    class Solution sol;
    cout << boolalpha << sol.isMonotonic(arr) << endl;
    return 0;
}