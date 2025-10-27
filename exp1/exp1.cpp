#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

// �����ඨ��
class Complex {
private:
    double real;  // ʵ��
    double imag;  // �鲿

public:
    // ���캯��
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // ��ȡʵ��
    double getReal() const { return real; }

    // ��ȡ�鲿
    double getImag() const { return imag; }

    // ����ʵ��
    void setReal(double r) { real = r; }

    // �����鲿
    void setImag(double i) { imag = i; }

    // ���㸴����ģ
    double modulus() const { return sqrt(real * real + imag * imag); }

    // ������������
    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // ���ز��������
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // ������������
    friend ostream& operator<<(ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }
};

// ���������������
vector<Complex> generateRandomComplexVector(int size, double minVal, double maxVal) {
    vector<Complex> vec;
    srand(time(0));  // ��ʼ�������������

    for (int i = 0; i < size; ++i) {
        double real = minVal + (maxVal - minVal) * rand() / RAND_MAX;
        double imag = minVal + (maxVal - minVal) * rand() / RAND_MAX;
        vec.push_back(Complex(real, imag));
    }
    return vec;
}

// ��������
void shuffleVector(vector<Complex>& vec) {
    srand(time(0));
    for (int i = vec.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(vec[i], vec[j]);
    }
}

// ����Ԫ�أ�ʵ�����鲿����ͬ��
int findElement(const vector<Complex>& vec, const Complex& target) {
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) {
            return i;
        }
    }
    return -1;  // δ�ҵ�
}

// ����Ԫ��
void insertElement(vector<Complex>& vec, int index, const Complex& elem) {
    if (index >= 0 && index <= vec.size()) {
        vec.insert(vec.begin() + index, elem);
    }
}

// ɾ��Ԫ��
bool deleteElement(vector<Complex>& vec, const Complex& elem) {
    auto it = find(vec.begin(), vec.end(), elem);
    if (it != vec.end()) {
        vec.erase(it);
        return true;
    }
    return false;
}

// ����Ψһ��
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

// ����������ģΪ��׼��ģ��ͬ����ʵ��Ϊ��׼��
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

// �鲢����������
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

// �鲢����������
void mergeSort(vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// ������ң�����ģ����[m1, m2)������Ԫ��
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

// ������������
vector<Complex> generateReverseVector(const vector<Complex>& sortedVec) {
    return vector<Complex>(sortedVec.rbegin(), sortedVec.rend());
}

// ���Ժ���
void testComplexVectorOperations() {
    // ���������������
    int size = 10;
    vector<Complex> vec = generateRandomComplexVector(size, -10.0, 10.0);
    cout << "ԭʼ����: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl;

    // ��������
    shuffleVector(vec);
    cout << "���Һ�: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl;

    // ���Բ���
    if (!vec.empty()) {
        Complex target = vec[0];
        int index = findElement(vec, target);
        cout << "���� " << target << " ��λ��: " << index << endl;
    }

    // ���Բ���
    Complex insertElem(100, 200);
    insertElement(vec, 2, insertElem);
    cout << "���� " << insertElem << " ��: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl;

    // ����ɾ��
    bool deleted = deleteElement(vec, insertElem);
    cout << "ɾ�� " << insertElem << (deleted ? " �ɹ�" : " ʧ��") << endl;
    cout << "ɾ����: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl;

    // ����Ψһ��
    uniqueVector(vec);
    cout << "Ψһ����: ";
    for (const auto& c : vec) cout << c << " ";
    cout << endl << endl;

    // ���ܲ���
    int testSize = 5000;
    vector<Complex> testVec = generateRandomComplexVector(testSize, -100.0, 100.0);

    // ˳������
    vector<Complex> sortedVec = testVec;
    mergeSort(sortedVec, 0, sortedVec.size() - 1);

    // ��������
    vector<Complex> reverseVec = generateReverseVector(sortedVec);

    // ��������
    vector<Complex> randomVec = testVec;

    // ����������������
    clock_t start, end;

    // ˳�����
    vector<Complex> bubbleSorted = sortedVec;
    start = clock();
    bubbleSort(bubbleSorted);
    end = clock();
    double bubbleTimeSorted = (double)(end - start) / CLOCKS_PER_SEC;

    // �������
    bubbleSorted = randomVec;
    start = clock();
    bubbleSort(bubbleSorted);
    end = clock();
    double bubbleTimeRandom = (double)(end - start) / CLOCKS_PER_SEC;

    // �������
    bubbleSorted = reverseVec;
    start = clock();
    bubbleSort(bubbleSorted);
    end = clock();
    double bubbleTimeReverse = (double)(end - start) / CLOCKS_PER_SEC;

    // ���Թ鲢��������
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

    // ������ܲ��Խ��
    cout << "�������ܲ��� (������С: " << testSize << ")" << endl;
    cout << "�������� - ˳��: " << bubbleTimeSorted << " ��" << endl;
    cout << "�������� - ����: " << bubbleTimeRandom << " ��" << endl;
    cout << "�������� - ����: " << bubbleTimeReverse << " ��" << endl << endl;

    cout << "�鲢���� - ˳��: " << mergeTimeSorted << " ��" << endl;
    cout << "�鲢���� - ����: " << mergeTimeRandom << " ��" << endl;
    cout << "�鲢���� - ����: " << mergeTimeReverse << " ��" << endl << endl;

    // ������Ҳ���
    double m1 = 2.0, m2 = 5.0;
    vector<Complex> rangeResult = rangeSearch(sortedVec, m1, m2);
    cout << "������� [ " << m1 << ", " << m2 << ") ���: " << endl;
    for (const auto& c : rangeResult) {
        cout << c << " ģ: " << c.modulus() << endl;
    }
}

// ���������������
int main() {
    testComplexVectorOperations();  // ���ò��Ժ���
    return 0;
}

#endif // VECTOR_H