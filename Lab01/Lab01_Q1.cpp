#include <vector>
#include <iostream>
using namespace std;

void printPairs(const vector<int>& arr) {
    int count = 0;//for step counting
    count++;//(i = 0)loop initialization |count 1
    for (int i = 0; i < arr.size(); i++) {
    count++;//(i < arr.size())loop comparison |count n
    count++;//(j = i + 1)second loop initialization |count n
    count++;//(j = i + 1)second loop initialization |count n
    for (int j = i + 1; j < arr.size(); j++) {
    count++;//(j < arr.size())loop comparison |count n(n-1)/2
    count++;//(arr[i])loop array access |n(n-1)/2
    count++;//(arr[j])loop array access |n(n-1)/2
    cout << arr[i] << "," << arr[j] << endl;
    count++;//(j++)loop increment |count n(n-1)/2
    }
    count++;//(i++)loop increment |count n
    }
    cout << "Total operations: " << count << endl;
}
//Total operations:
//outer loop: 1
//inner loop: 4n
//printing operations: 4(n(n-1)/2)
//Time complexity: O(n^2)

int findMax(const vector<int>& arr) {
    int count = 0;//for step counting
    int max = arr[0];
    count++;//(max = )initialization |count 1
    count++;//(arr[0])initialization |count 1
    count++;//(i = 1)loop initialization |count 1
    for (int i = 1; i < arr.size(); i++) {
    count++;//(i < arr.size())loop comparison |count n-1
    count++;//(arr[i])loop array access |count n-1
    count++;//(> max)loop comparison |count n-1
    if (arr[i] > max) {
        count++;//(arr[i])array access |count n-1
        count++;//(max = )comparison |count n-1
        max = arr[i];
    }
    count++;//(i++)increment |count n-1
    }
    count++;//(return)return |count 1
    cout << "Total operations: " << count << endl;
    return max;
}
//Total operations(worst case):
//3 (initial) + 6(n-1) (loop) + 1 (return)=  6n - 2
//Time complexity: O(n)


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
    //printPairs(arr);
    //cout << findMax(arr) << endl;
    return 0;
}