#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

// 复数类定义
class Complex {
private:
    double real;  // 实部
    double imag;  // 虚部

public:
    // 构造函数
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 获取实部
    double getReal() const { return real; }

    // 获取虚部
    double getImag() const { return imag; }

    // 设置实部
    void setReal(double r) { real = r; }

    // 设置虚部
    void setImag(double i) { imag = i; }

    // 计算复数的模
    double modulus() const { return sqrt(real * real + imag * imag); }

    // 重载相等运算符
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // 重载不等运算符
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // 重载输出运算符
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }
};

// 生成随机复数向量
vector<Complex> generateRandomComplexVector(int size, double minVal, double maxVal) {
    vector<Complex> vec;
    srand(time(0));  // 初始化随机数生成器

    for (int i = 0; i < size; ++i) {
        double real = minVal + (maxVal - minVal) * rand() / RAND_MAX;
        double imag = minVal + (maxVal - minVal) * rand() / RAND_MAX;
        vec.push_back(Complex(real, imag));
    }
    return vec;
}

// 向量置乱
void shuffleVector(vector<Complex>& vec) {
    srand(time(0));
    for (int i = vec.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(vec[i], vec[j]);
    }
}

// 查找元素（实部和虚部均相同）
int findElement(const vector<Complex>& vec, const Complex& target) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return i;
        }
    }
    return -1;  // 未找到
}

// 插入元素
void insertElement(vector<Complex>& vec, int index, const Complex& elem) {
    if (index >= 0 && index <= vec.size()) {
        vec.insert(vec.begin() + index, elem);
    }
}

// 删除元素
bool deleteElement(vector<Complex>& vec, const Complex& elem) {
    auto it = find(vec.begin(), vec.end(), elem);
    if (it != vec.end()) {
        vec.erase(it);
        return true;
    }
    return false;
}

// 向量唯一化
void uniqueVector(vector<Complex>& vec) {
    sort(vec.begin(), vec.end(), [](const Complex& a, const Complex& b) {
        if (a.modulus() != b.modulus()) {
            return a.modulus() < b.modulus();
        }
        return a.getReal() < b.getReal();
        });
    auto last = unique(vec.begin(), vec.end());
    vec.erase(last, vec.end());
}

// 起泡排序（以模为基准，模相同则以实部为基准）
void bubbleSort(vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j].modulus() > vec[j + 1].modulus() ||
                (vec[j].modulus() == vec[j + 1].modulus() &&
                    vec[j].getReal() > vec[j + 1].getReal())) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// 归并排序辅助函数
void merge(vector<Complex>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Complex> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = vec[left + i];
    for (int j = 0; j < n2; ++j) R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].modulus() < R[j].modulus() ||
            (L[i].modulus() == R[j].modulus() &&
                L[i].getReal() < R[j].getReal())) {
            vec[k++] = L[i++];
        }
        else {
            vec[k++] = R[j++];
        }
    }

    while (i < n1) vec[k++] = L[i++];
    while (j < n2) vec[k++] = R[j++];
}

// 归并排序主函数
void mergeSort(vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// 区间查找：查找模介于[m1, m2)的所有元素
vector<Complex> rangeSearch(const vector<Complex>& vec, double m1, double m2) {
    vector<Complex> result;
    for (const auto& c : vec) {
        double mod = c.modulus();
        if (mod >= m1 && mod < m2) {
            result.push_back(c);
        }
    }
    return result;
}

// 生成逆序向量
vector<Complex> generateReverseVector(const vector<Complex>& sortedVec) {
    return vector<Complex>(sortedVec.rbegin(), sortedVec.rend());
}

// 测试函数
void testComplexVectorOperations() {
    // 生成随机复数向量
    int size = 10;
    vector<Complex> vec = generateRandomComplexVector(size, -10.0, 10.0);
    cout << "原始向量: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl;

    // 测试置乱
    shuffleVector(vec);
    cout << "置乱后: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl;

    // 测试查找
    if (!vec.empty()) {
        Complex target = vec[0];
        int index = findElement(vec, target);
        cout << "查找 " << target << " 的位置: " << index << endl;
    }

    // 测试插入
    Complex insertElem(100, 200);
    insertElement(vec, 2, insertElem);
    cout << "插入 " << insertElem << " 后: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl;

    // 测试删除
    bool deleted = deleteElement(vec, insertElem);
    cout << "删除 " << insertElem << (deleted ? " 成功" : " 失败") << endl;
    cout << "删除后: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl;

    // 测试唯一化
    uniqueVector(vec);
    cout << "唯一化后: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl << endl;

    // 性能测试
    int testSize = 5000;
    vector<Complex> testVec = generateRandomComplexVector(testSize, -100.0, 100.0);

    // 顺序向量
    vector<Complex> sortedVec = testVec;
    mergeSort(sortedVec, 0, sortedVec.size() - 1);

    // 逆序向量
    vector<Complex> reverseVec = generateReverseVector(sortedVec);

    // 乱序向量
    vector<Complex> randomVec = testVec;

    // 测试起泡排序性能
    clock_t start, end;

    // 顺序情况
    vector<Complex> bubbleSorted = sortedVec;
    start = clock();
    bubbleSort(bubbleSorted);
    end = clock();
    double bubbleTimeSorted = (double)(end - start) / CLOCKS_PER_SEC;

    // 乱序情况
    bubbleSorted = randomVec;
    start = clock();
    bubbleSort(bubbleSorted);
    end = clock();
    double bubbleTimeRandom = (double)(end - start) / CLOCKS_PER_SEC;

    // 逆序情况
    bubbleSorted = reverseVec;
    start = clock();
    bubbleSort(bubbleSorted);
    end = clock();
    double bubbleTimeReverse = (double)(end - start) / CLOCKS_PER_SEC;

    // 测试归并排序性能
    vector<Complex> mergeSorted = sortedVec;
    start = clock();
    mergeSort(mergeSorted, 0, mergeSorted.size() - 1);
    end = clock();
    double mergeTimeSorted = (double)(end - start) / CLOCKS_PER_SEC;

    mergeSorted = randomVec;
    start = clock();
    mergeSort(mergeSorted, 0, mergeSorted.size() - 1);
    end = clock();
    double mergeTimeRandom = (double)(end - start) / CLOCKS_PER_SEC;

    mergeSorted = reverseVec;
    start = clock();
    mergeSort(mergeSorted, 0, mergeSorted.size() - 1);
    end = clock();
    double mergeTimeReverse = (double)(end - start) / CLOCKS_PER_SEC;

    // 输出性能测试结果
    cout << "排序性能测试 (向量大小: " << testSize << ")" << endl;
    cout << "起泡排序 - 顺序: " << bubbleTimeSorted << " 秒" << endl;
    cout << "起泡排序 - 乱序: " << bubbleTimeRandom << " 秒" << endl;
    cout << "起泡排序 - 逆序: " << bubbleTimeReverse << " 秒" << endl << endl;

    cout << "归并排序 - 顺序: " << mergeTimeSorted << " 秒" << endl;
    cout << "归并排序 - 乱序: " << mergeTimeRandom << " 秒" << endl;
    cout << "归并排序 - 逆序: " << mergeTimeReverse << " 秒" << endl << endl;

    // 区间查找测试
    double m1 = 2.0, m2 = 5.0;
    vector<Complex> rangeResult = rangeSearch(sortedVec, m1, m2);
    cout << "区间查找 [ " << m1 << ", " << m2 << ") 结果: " << endl;
    for (const auto& c : rangeResult) {
        cout << c << " 模: " << c.modulus() << endl;
    }
}

// 主函数，程序入口
int main() {
    testComplexVectorOperations();  // 调用测试函数
    return 0;
}

#endif // VECTOR_H