#include <vector>
#include <iostream>
using namespace std;

class Solution {
    public:
        int findLucky(vector<int>& arr) {
            //宣告一個vector陣列count，題目說明最長為500，所以宣告500個元素
            vector<int> count(501);
            //宣告一個lucky變數，初始值為-1
            int lucky = -1;
            //跑一個for迴圈遍歷arr陣列，將count陣列中對應的索引值++
            for (int i = 0; i < arr.size(); i++) {
                count[arr[i] - 1]++;
            }
            //再跑一個for迴圈遍歷count陣列，判斷count陣列中的值是否等於索引值
            for (int i = 1; i < count.size(); i++) {
                if (count[i - 1] == i) {
                    lucky = i;
                }
            }
            //跑完迴圈一定是最大的lucky number，如果沒找到就是-1
            return lucky;
            //3 + 2n，時間複雜度O(n)
        }
    };

    int main() {
        Solution sol;
        vector<int> arr = {2, 2, 3, 4};
        cout << sol.findLucky(arr) << endl;
        return 0;
    }