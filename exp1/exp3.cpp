#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// ������״ͼ���������
int largestRectangleArea(vector<int>& heights) {
    stack<int> stk; // ��������ջ���洢����
    heights.push_back(0); // ĩβ����ڱ���ȷ������Ԫ�س�ջ
    int maxArea = 0;
    int n = heights.size();

    for (int i = 0; i < n; ++i) {
        // ��ǰ�߶�С��ջ���߶�ʱ������ջ�����������
        while (!stk.empty() && heights[i] < heights[stk.top()]) {
            int h = heights[stk.top()]; // ջ��Ԫ�ظ߶�
            stk.pop();
            // ��� = ��ǰ���� - ��ջ������ - 1��ջ��ʱ���Ϊi��
            int w = stk.empty() ? i : i - stk.top() - 1;
            maxArea = max(maxArea, h * w);
        }
        stk.push(i);
    }
    return maxArea;
}

// ���������������
vector<int> generateRandomHeights(int length) {
    vector<int> heights(length);
    for (int i = 0; i < length; ++i) {
        heights[i] = rand() % 10001; // 0~104���ֵ
    }
    return heights;
}

// ��ӡ�������ݺͽ��
void printTestResult(int idx, const vector<int>& heights, int area) {
    cout << "������ " << idx << ":" << endl;
    cout << "��״ͼ�߶�: ";
    // ֻ��ӡǰ10���ͺ�10���������������ˢ����
    if (heights.size() <= 20) {
        for (int h : heights) cout << h << " ";
    }
    else {
        for (int i = 0; i < 10; ++i) cout << heights[i] << " ";
        cout << "... ";
        for (int i = heights.size() - 10; i < heights.size(); ++i) cout << heights[i] << " ";
    }
    cout << endl;
    cout << "���������: " << area << endl << endl;
}

int main() {
    srand(time(0)); // ��ʼ�����������

    // ����10��������ݣ�����1~10^5��
    for (int i = 0; i < 10; ++i) {
        int length = rand() % 100000 + 1; // 1~10^5
        vector<int> heights = generateRandomHeights(length);
        int maxArea = largestRectangleArea(heights);
        printTestResult(i + 1, heights, maxArea);
    }

    return 0;
}