#include <iostream>
#include <iomanip>
#include <ctime>

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

using namespace std;

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
            cout << "Error" << endl;
            deleteArray(array, m, n);
            return 1;
    }
    
    cout << "Original array:" << endl;
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

void fillRandom(int** array, const size_t m, const size_t n, const int start, const int end)
{
    srand(time(0));
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            array[i][j] = rand() % (end - start + 1) + start;
        }
    }
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Error" << endl;
        abort();
    }
    return value;
}

size_t getSize()
{
    int n = getValue();
    checkN(n);
    return (size_t)n;
}

void checkN(const int n)
{
    if (n <= 0)
    {
        cout << "Error" << endl;
        abort();
    }
}

int** getNewArray(const size_t m, const size_t n)
{
    int** array = new int*[m];
    for (size_t i = 0; i < m; i++)
    {
        array[i] = new int[n];
    }
    return array;
}

void printArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << setw(6) << array[i][j];
        }
        cout << endl;
    }
}

void fillArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << "Enter array[" << i << "," << j << "] = ";
            array[i][j] = getValue();
        }
    }
}

size_t getMaxIndexInLine(int* array, const size_t n)
{
    size_t maxIndex = 0; 
    for (size_t i = 0; i < n; i++)
    {
        if (array[i] > array[maxIndex])
        {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void invertMaxInRows(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        size_t maxIndex = getMaxIndexInLine(array[i], n);
        array[i][maxIndex] = -array[i][maxIndex];
    }
}

int** copyArray(int** array, const size_t m, const size_t n)
{
    int** result = getNewArray(m, n);
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            result[i][j] = array[i][j];
        }
    }
    return result;
}

void deleteArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        delete[] array[i];
    }
    delete[] array;
}

int findMaxElement(int** array, const size_t m, const size_t n)
{
    int max = array[0][0];
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (array[i][j] > max)
            {
                max = array[i][j];
            }
        }
    }
    return max;
}

bool containsMaxElement(int** array, const size_t m, const size_t n, size_t col)
{
    int max = findMaxElement(array, m, n);
    for (size_t i = 0; i < m; i++)
    {
        if (array[i][col] == max)
        {
            return true;
        }
    }
    return false;
}

void insertZeroAfterMaxColumns(int**& array, size_t& m, size_t& n)
{
    // First, find which columns need zero columns after them
    bool* columnsToInsertAfter = new bool[n];
    for (size_t j = 0; j < n; j++)
    {
        columnsToInsertAfter[j] = containsMaxElement(array, m, n, j);
    }
    
    // Count how many new columns we need
    size_t newColumns = 0;
    for (size_t j = 0; j < n; j++)
    {
        if (columnsToInsertAfter[j]) newColumns++;
    }
    
    if (newColumns == 0)
    {
        delete[] columnsToInsertAfter;
        return;
    }
    
    size_t newN = n + newColumns;
    int** newArray = getNewArray(m, newN);
    
    // Copy old data and insert zero columns
    size_t newJ = 0;
    for (size_t j = 0; j < n; j++)
    {
        // Copy current column
        for (size_t i = 0; i < m; i++)
        {
            newArray[i][newJ] = array[i][j];
        }
        newJ++;
        
        // Insert zero column if needed
        if (columnsToInsertAfter[j])
        {
            for (size_t i = 0; i < m; i++)
            {
                newArray[i][newJ] = 0;
            }
            newJ++;
        }
    }
    
    // Clean up old array
    deleteArray(array, m, n);
    
    // Update array and dimensions
    array = newArray;
    n = newN;
    
    delete[] columnsToInsertAfter;
}
