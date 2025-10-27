#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// 计算柱状图最大矩形面积
int largestRectangleArea(vector<int>& heights) {
    stack<int> stk; // 单调递增栈，存储索引
    heights.push_back(0); // 末尾添加哨兵，确保所有元素出栈
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i < n; ++i) {
        // 当前高度小于栈顶高度时，弹出栈顶并计算面积
        while (!stk.empty() && heights[i] < heights[stk.top()]) {
            int h = heights[stk.top()]; // 栈顶元素高度
            stk.pop();
            // 宽度 = 当前索引 - 新栈顶索引 - 1（栈空时宽度为i）
            int w = stk.empty() ? i : i - stk.top() - 1;
            maxArea = max(maxArea, h * w);
        }
        stk.push(i);
    }
    return maxArea;
}

// 生成随机测试数据
vector<int> generateRandomHeights(int length) {
    vector<int> heights(length);
    for (int i = 0; i < length; ++i) {
        heights[i] = rand() % 10001; // 0~104随机值
    }
    return heights;
}

// 打印测试数据和结果
void printTestResult(int idx, const vector<int>& heights, int area) {
    cout << "测试组 " << idx << ":" << endl;
    cout << "柱状图高度: ";
    // 只打印前10个和后10个（避免大数据量刷屏）
    if (heights.size() <= 20) {
        for (int h : heights) cout << h << " ";
    }
    else {
        for (int i = 0; i < 10; ++i) cout << heights[i] << " ";
        cout << "... ";
        for (int i = heights.size() - 10; i < heights.size(); ++i) cout << heights[i] << " ";
    }
    cout << endl;
    cout << "最大矩形面积: " << area << endl << endl;
}

int main() {
    srand(time(0)); // 初始化随机数种子

    // 生成10组测试数据（长度1~10^5）
    for (int i = 0; i < 10; ++i) {
        int length = rand() % 100000 + 1; // 1~10^5
        vector<int> heights = generateRandomHeights(length);
        int maxArea = largestRectangleArea(heights);
        printTestResult(i + 1, heights, maxArea);
    }

    return 0;
}