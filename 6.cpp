#include <iostream>
#include <cstdlib>

using namespace std;

// Объявления функций (прототипы)
int getValue();

size_t getSize();

void checkN(const int n);

void fillArray(int* arr, const int n);

void printArray(const int* arr, const int n);

int sumOfElementsDivisibleBy3(const int* arr, const int n);

void sortArray(int* arr, const int n);

size_t getIndexOfFirstNegative(const int* arr, const int n);

int* copyArray(const int* arr, const int n);


int main()
{
    size_t n = getSize();
    int* arr = new int[n];
    
    fillArray(arr, n);
    printArray(arr, n);
    
    cout << "Sum of elements divisible by 3: " << sumOfElementsDivisibleBy3(arr, n) << endl;
    
    size_t index = getIndexOfFirstNegative(arr, n);
    if (index == n) {
        cout << "No negative elements" << endl;
    }
    else {
        cout << "Index of first negative element: " << index + 1 << endl;
    }
    
    int* sortedArr = copyArray(arr, n);
    sortArray(sortedArr, n);
    cout << "Sorted array: ";
    printArray(sortedArr, n);
    cout << "Original array: ";
    printArray(arr, n);
    
    delete[] sortedArr;
    delete[] arr;
    return 0;
}

// Реализации функций (определения)

int getValue()
{
    double value;
    cin >> value;
    if (cin.fail()) {
        cerr << "Input error!" << endl;
        exit(EXIT_FAILURE);
    }
    return value;
}

size_t getSize()
{
    cout << "Enter array size (n > 0): ";
    double n = getValue();
    checkN(n);
    return static_cast<size_t>(n);
}

void checkN(const int n)
{
    if (n <= 0) {
        cerr << "Array size must be positive!" << endl;
        exit(EXIT_FAILURE);
    }
}

void fillArray(int* arr, const int n)
{
    for (size_t i = 0; i < n; i++) {
        cout << "Enter arr[" << i + 1 << "]: ";
        arr[i] = getValue();
    }
}

void printArray(const int* arr, const int n)
{
    for (size_t i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int sumOfElementsDivisibleBy3(const int* arr, const int n)
{
    int sum = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] % 3 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

size_t getIndexOfFirstNegative(const int* arr, const int n)
{
    for (size_t i = 0; i < n; i++) {
        if (arr[i] < 0) {
            return i;
        }
    }
    return n;
}

void sortArray(int* arr, const int n)
{
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int* copyArray(const int* arr, const int n)
{
    int* newArr = new int[n];
    for (size_t i = 0; i < n; i++) {
        newArr[i] = arr[i];
    }
    return newArr;
}
