#include <vector>
#include <iostream>
using namespace std;

class Solution {
    public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
    int scount = 0; //步驟計數器
    scount++;//記數陣列初始化
    scount++;//陣列長度賦值
    scount++;//宣告動態陣列result
    int count[101]={0};//計數陣列,範圍 0-100
    int n=nums.size();//陣列長度
    vector<int> result(n);//vector<int>是動態陣列,在執行分配記憶體時,可以根據 num.size()自動調整大小

    //計算每個數字的出現次數,此迴圈遍歷 nums,並統計每個數字 num 出現的次數
    for(int num:nums){count[num]++;}
    scount++;//第一個for迴圈

    //計算比當前數字小的數量
    for(int i=1; i<101; i++){
    scount++;//第二個for迴圈
    count[i]+=count[i-1];
    }
    //計算 result 陣列
    for(int i=0; i<n; i++){
    scount++;//第三個for迴圈
    result[i]=(nums[i]==0)?0:count[nums[i]-1];
    //count[nums[i]-1]代表比 nums[i]小的數的數量,nums[i]==0 時則直接返回 0
    }
    scount++;//回傳值
    printf("scount = %d\n", scount);
    return result;
    //4+3n時間複雜度是O(n)
}
};

class Solution2 {
    public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        int scount = 0; //步驟計數器
        scount++;//result陣列初始化
        scount++;//計數器初始化
        vector<int> result; //存結果
        int count = 0; //計數器

        //外層迴圈遍歷nums陣列中的每個元素
        for(int i = 0; i < nums.size(); i++){
            scount++;//第一層for迴圈
            count = 0; //每次重新計算當前元素的較小數量
            // 內層迴圈再次遍歷nums陣列，統計比nums[i]小的元素數量
            for(int j = 0; j < nums.size(); j++){
                scount++;//第二層for迴圈
                if(nums[j] < nums[i]){count++;} //如果nums[j] < nums[i]，則count++
            }
            result.push_back(count); //將count存入result
        }
        scount++;//回傳值
        printf("scount = %d\n", scount);
        return result;
        //3+n(n)時間複雜度是O(n^2)
    }
};

int main() {
    vector<int> nums = {8,1,2,2,3};
    Solution sol;
    vector<int> result = sol.smallerNumbersThanCurrent(nums);
    Solution2 sol2;
    vector<int> result2 = sol2.smallerNumbersThanCurrent(nums);
    for(int i:result){cout<<i<<" ";}
    cout<<endl;
    for(int i:result2){cout<<i<<" ";}
    cout<<endl;
    return 0;
}