#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

// 修正后的Vector模板类定义（原Vector.h内容）
template <typename T>
class Vector {
private:
    T* data;       // 存储元素的动态数组
    int m_size;    // 修正：将size改为m_size，避免与size()函数冲突
    int capacity;  // 容量

public:
    // 构造函数
    Vector() : data(nullptr), m_size(0), capacity(0) {}

    // 析构函数
    ~Vector() {
        delete[] data;
    }

    // 拷贝构造函数
    Vector(const Vector& other) {
        m_size = other.m_size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < m_size; ++i) {
            data[i] = other.data[i];
        }
    }

    // 拷贝赋值运算符
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            m_size = other.m_size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < m_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // 获取当前元素数量（修正：与成员变量m_size不冲突）
    int size() const {
        return m_size;
    }

    // 向向量末尾添加元素
    void push_back(const T& elem) {
        if (m_size >= capacity) {
            // 扩容（翻倍策略）
            int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            T* new_data = new T[new_capacity];
            for (int i = 0; i < m_size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity = new_capacity;
        }
        data[m_size++] = elem;
    }

    // 重载[]运算符，用于访问元素
    T& operator[](int index) {
        return data[index];
    }

    // 重载[]运算符（const版本）
    const T& operator[](int index) const {
        return data[index];
    }
};

using namespace std;

// 复数类定义（保持不变）
class Complex {
private:
    double real;  // 实部
    double imag;  // 虚部

public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    double getReal() const { return real; }
    double getImag() const { return imag; }

    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }

    double modulus() const { return sqrt(real * real + imag * imag); }

    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }
};

// 生成随机复数向量（保持不变）
Vector<Complex> generateRandomComplexVector(int size, double minVal, double maxVal) {
    Vector<Complex> vec;
    srand(time(0)); // 初始化随机数种子
    for (int i = 0; i < size; ++i) {
        double real = minVal + (maxVal - minVal) * rand() / RAND_MAX;
        double imag = minVal + (maxVal - minVal) * rand() / RAND_MAX;
        vec.push_back(Complex(real, imag));
    }
    return vec;
}

// 向量置乱（保持不变）
void shuffleVector(Vector<Complex>& vec) {
    srand(time(0)); // 重置随机数种子
    for (int i = vec.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1); // 生成[0, i]的随机索引
        swap(vec[i], vec[j]);
    }
}

// 向量唯一化（保持不变）
void uniqueVector(Vector<Complex>& vec) {
    Vector<Complex> temp;
    for (int i = 0; i < vec.size(); ++i) {
        bool isUnique = true;
        for (int j = 0; j < temp.size(); ++j) {
            if (vec[i] == temp[j]) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            temp.push_back(vec[i]);
        }
    }
    vec = temp; // 用去重后的向量替换原向量
}

// 起泡排序（保持不变）
void bubbleSort(Vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            double modJ = vec[j].modulus();
            double modJ1 = vec[j + 1].modulus();
            if (modJ > modJ1 || (modJ == modJ1 && vec[j].getReal() > vec[j + 1].getReal())) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// 归并排序辅助函数（保持不变）
void merge(Vector<Complex>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Vector<Complex> L, R;
    for (int i = 0; i < n1; ++i)
        L.push_back(vec[left + i]);
    for (int j = 0; j < n2; ++j)
        R.push_back(vec[mid + 1 + j]);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        double modL = L[i].modulus();
        double modR = R[j].modulus();
        if (modL < modR || (modL == modR && L[i].getReal() <= R[j].getReal())) {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

// 归并排序主函数（保持不变）
void mergeSort(Vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// 区间查找（保持不变）
Vector<Complex> rangeSearch(const Vector<Complex>& sortedVec, double m1, double m2) {
    Vector<Complex> result;
    for (int i = 0; i < sortedVec.size(); ++i) {
        double mod = sortedVec[i].modulus();
        if (mod >= m1 && mod < m2) {
            result.push_back(sortedVec[i]);
        }
    }
    return result;
}

// 打印向量（保持不变）
void printVector(const Vector<Complex>& vec, const string& msg = "") {
    if (!msg.empty()) {
        cout << msg << endl;
    }
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl << "向量大小: " << vec.size() << endl << endl;
}

// 主函数（保持不变）
int main() {
    int size = 8;
    Vector<Complex> vec = generateRandomComplexVector(size, -5.0, 5.0);
    printVector(vec, "1. 初始随机向量：");

    shuffleVector(vec);
    printVector(vec, "2. 置乱后的向量：");

    uniqueVector(vec);
    printVector(vec, "3. 唯一化后的向量（移除重复元素）：");

    Vector<Complex> bubbleVec = vec;
    bubbleSort(bubbleVec);
    printVector(bubbleVec, "4. 起泡排序后的向量（按模和实部）：");

    Vector<Complex> mergeVec = vec;
    if (mergeVec.size() > 0) {
        mergeSort(mergeVec, 0, mergeVec.size() - 1);
        printVector(mergeVec, "5. 归并排序后的向量（按模和实部）：");
    }

    if (mergeVec.size() > 0) {
        Vector<Complex> rangeResult = rangeSearch(mergeVec, 1.0, 3.0);
        printVector(rangeResult, "6. 模介于[1.0, 3.0)的元素：");
    }

    return 0;
}