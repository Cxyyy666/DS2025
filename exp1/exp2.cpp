#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

// �������Vectorģ���ඨ�壨ԭVector.h���ݣ�
template <typename T>
class Vector {
private:
    T* data;       // �洢Ԫ�صĶ�̬����
    int m_size;    // ��������size��Ϊm_size��������size()������ͻ
    int capacity;  // ����

public:
    // ���캯��
    Vector() : data(nullptr), m_size(0), capacity(0) {}

    // ��������
    ~Vector() {
        delete[] data;
    }

    // �������캯��
    Vector(const Vector& other) {
        m_size = other.m_size;
        capacity = other.capacity;
        data = new T[capacity];
        for (int i = 0; i < m_size; ++i) {
            data[i] = other.data[i];
        }
    }

    // ������ֵ�����
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

    // ��ȡ��ǰԪ�����������������Ա����m_size����ͻ��
    int size() const {
        return m_size;
    }

    // ������ĩβ���Ԫ��
    void push_back(const T& elem) {
        if (m_size >= capacity) {
            // ���ݣ��������ԣ�
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

    // ����[]����������ڷ���Ԫ��
    T& operator[](int index) {
        return data[index];
    }

    // ����[]�������const�汾��
    const T& operator[](int index) const {
        return data[index];
    }
};

using namespace std;

// �����ඨ�壨���ֲ��䣩
class Complex {
private:
    double real;  // ʵ��
    double imag;  // �鲿

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

// ��������������������ֲ��䣩
Vector<Complex> generateRandomComplexVector(int size, double minVal, double maxVal) {
    Vector<Complex> vec;
    srand(time(0)); // ��ʼ�����������
    for (int i = 0; i < size; ++i) {
        double real = minVal + (maxVal - minVal) * rand() / RAND_MAX;
        double imag = minVal + (maxVal - minVal) * rand() / RAND_MAX;
        vec.push_back(Complex(real, imag));
    }
    return vec;
}

// �������ң����ֲ��䣩
void shuffleVector(Vector<Complex>& vec) {
    srand(time(0)); // �������������
    for (int i = vec.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1); // ����[0, i]���������
        swap(vec[i], vec[j]);
    }
}

// ����Ψһ�������ֲ��䣩
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
    vec = temp; // ��ȥ�غ�������滻ԭ����
}

// �������򣨱��ֲ��䣩
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

// �鲢���������������ֲ��䣩
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

// �鲢���������������ֲ��䣩
void mergeSort(Vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// ������ң����ֲ��䣩
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

// ��ӡ���������ֲ��䣩
void printVector(const Vector<Complex>& vec, const string& msg = "") {
    if (!msg.empty()) {
        cout << msg << endl;
    }
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl << "������С: " << vec.size() << endl << endl;
}

// �����������ֲ��䣩
int main() {
    int size = 8;
    Vector<Complex> vec = generateRandomComplexVector(size, -5.0, 5.0);
    printVector(vec, "1. ��ʼ���������");

    shuffleVector(vec);
    printVector(vec, "2. ���Һ��������");

    uniqueVector(vec);
    printVector(vec, "3. Ψһ������������Ƴ��ظ�Ԫ�أ���");

    Vector<Complex> bubbleVec = vec;
    bubbleSort(bubbleVec);
    printVector(bubbleVec, "4. ������������������ģ��ʵ������");

    Vector<Complex> mergeVec = vec;
    if (mergeVec.size() > 0) {
        mergeSort(mergeVec, 0, mergeVec.size() - 1);
        printVector(mergeVec, "5. �鲢��������������ģ��ʵ������");
    }

    if (mergeVec.size() > 0) {
        Vector<Complex> rangeResult = rangeSearch(mergeVec, 1.0, 3.0);
        printVector(rangeResult, "6. ģ����[1.0, 3.0)��Ԫ�أ�");
    }

    return 0;
}