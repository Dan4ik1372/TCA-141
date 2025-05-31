#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// Объявления функций (прототипы)
int getValue();

size_t getSize();

void checkN(const int n);

int** getNewArray(const size_t m, const size_t n);

void printArray(int** array, const size_t m, const size_t n);

void fillArray(int** array, const size_t m, const size_t n);

void invertMaxInRows(int** array, const size_t m, const size_t n);

size_t getMaxIndexInLine(int* array, const size_t n);

void deleteArray(int** array, const size_t m, const size_t n);

int** copyArray(int** array, const size_t m, const size_t n);

bool containsMaxElement(int** array, const size_t m, const size_t n, size_t col);

void insertZeroAfterMaxColumns(int**& array, size_t& m, size_t& n);

void fillRandom(int** array, const size_t m, const size_t n, const int start, const int end);

int findMaxElement(int** array, const size_t m, const size_t n);

enum { RANDOM = 5, MANUAL = 6 };

int main()
{
    cout << "Enter m: ";
    size_t m = getSize();
    cout << "Enter n: ";
    size_t n = getSize();
    
    int** array = getNewArray(m, n);
    
    cout << "Enter the way to fill array: " << (int)MANUAL <<
        " to fill manually, " << (int)RANDOM << " to fill randomly: ";
    int choice = getValue();
    int start = 0;
    int end = 0;
    
    switch (choice)
    {    
        case RANDOM:    
            cout << "Enter start: ";
            start = getValue();
            cout << "Enter end: ";
            end = getValue();
            fillRandom(array, m, n, start, end);
            break;
        case MANUAL:    
            fillArray(array, m, n);
            break;
        default:
            cerr << "Error: Invalid choice!" << endl;
            deleteArray(array, m, n);
            return 1;
    }
    
    cout << "\nOriginal array:" << endl;
    printArray(array, m, n);
    
    // Task 1: Invert max elements in rows
    invertMaxInRows(array, m, n);
    cout << "\nAfter inverting max elements in rows:" << endl;
    printArray(array, m, n);
    
    // Task 2: Insert zero columns after columns with max element
    insertZeroAfterMaxColumns(array, m, n);
    cout << "\nAfter inserting zero columns:" << endl;
    printArray(array, m, n);
    
    deleteArray(array, m, n);
    return 0;
}

// Реализации функций (определения)

int getValue()
{
    double value;
    if (!(cin >> value)) {
        cerr << "Input error! Program terminated." << endl;
        exit(EXIT_FAILURE);
    }
    return value;
}

size_t getSize()
{
    double n = getValue();
    checkN(n);
    return static_cast<size_t>(n);
}

void checkN(const int n)
{
    if (n <= 0) {
        cerr << "Error: Size must be positive!" << endl;
        exit(EXIT_FAILURE);
    }
}

int** getNewArray(const size_t m, const size_t n)
{
    int** array = new int*[m];
    for (size_t i = 0; i < m; i++) {
        array[i] = new int[n]();  // Инициализация нулями
    }
    return array;
}

void printArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            cout << setw(6) << array[i][j];
        }
        cout << endl;
    }
}

void fillArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            cout << "Enter array[" << i << "][" << j << "]: ";
            array[i][j] = getValue();
        }
    }
}

void fillRandom(int** array, const size_t m, const size_t n, const int start, const int end)
{
    srand(static_cast<unsigned>(time(nullptr)));
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            array[i][j] = rand() % (end - start + 1) + start;
        }
    }
}

size_t getMaxIndexInLine(int* array, const size_t n)
{
    size_t maxIndex = 0;
    for (size_t i = 1; i < n; i++) {
        if (array[i] > array[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void invertMaxInRows(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++) {
        size_t maxIndex = getMaxIndexInLine(array[i], n);
        array[i][maxIndex] = -array[i][maxIndex];
    }
}

int** copyArray(int** array, const size_t m, const size_t n)
{
    int** newArray = getNewArray(m, n);
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            newArray[i][j] = array[i][j];
        }
    }
    return newArray;
}

void deleteArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++) {
        delete[] array[i];
    }
    delete[] array;
}

int findMaxElement(int** array, const size_t m, const size_t n)
{
    double maxElement = array[0][0];
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            if (array[i][j] > maxElement) {
                maxElement = array[i][j];
            }
        }
    }
    return maxElement;
}

bool containsMaxElement(int** array, const size_t m, const size_t n, size_t col)
{
    double maxElement = findMaxElement(array, m, n);
    for (size_t i = 0; i < m; i++) {
        if (array[i][col] == maxElement) {
            return true;
        }
    }
    return false;
}

void insertZeroAfterMaxColumns(int**& array, size_t& m, size_t& n)
{
    // Определяем, после каких столбцов нужно вставить нулевые
    vector<bool> insertAfter(n, false);
    double maxElement = findMaxElement(array, m, n);
    size_t newColumns = 0;

    for (size_t j = 0; j < n; j++) {
        for (size_t i = 0; i < m; i++) {
            if (array[i][j] == maxElement) {
                insertAfter[j] = true;
                newColumns++;
                break;
            }
        }
    }

    if (newColumns == 0) return;

    // Создаем новый массив с дополнительными столбцами
    size_t newN = n + newColumns;
    int** newArray = getNewArray(m, newN);

    // Копируем данные и вставляем нулевые столбцы
    size_t newCol = 0;
    for (size_t j = 0; j < n; j++) {
        // Копируем текущий столбец
        for (size_t i = 0; i < m; i++) {
            newArray[i][newCol] = array[i][j];
        }
        newCol++;

        // Вставляем нулевой столбец после столбцов с максимальным элементом
        if (insertAfter[j]) {
            for (size_t i = 0; i < m; i++) {
                newArray[i][newCol] = 0;
            }
            newCol++;
        }
    }

    // Удаляем старый массив и обновляем указатель и размер
    deleteArray(array, m, n);
    array = newArray;
    n = newN;
}
