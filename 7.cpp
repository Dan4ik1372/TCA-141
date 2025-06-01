#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

/**
 * @brief Считывает целое число с клавиатуры с проверкой ввода
 * @return Считанное значение
 */
int getValue();

/**
 * @brief Считывает размер массива с проверкой ввода
 * @return Считанный размер
 */
size_t getSize();

/**
 * @brief Проверяет, что введенное значение удовлетворяет условию n > 0
 * @param n Считанное значение
 */
void checkN(const int n);

/**
 * @brief Создает двумерный массив заданного размера
 * @param m Количество строк
 * @param n Количество столбцов
 * @return Указатель на созданный массив
 */
int** createArray(const size_t m, const size_t n);

/**
 * @brief Выводит массив на экран
 * @param array Массив для вывода
 * @param m Количество строк
 * @param n Количество столбцов
 */
void printArray(int** array, const size_t m, const size_t n);

/**
 * @brief Заполняет массив вручную с клавиатуры
 * @param array Массив для заполнения
 * @param m Количество строк
 * @param n Количество столбцов
 */
void fillArray(int** array, const size_t m, const size_t n);

/**
 * @brief Находит индекс максимального элемента в строке
 * @param row Указатель на строку массива
 * @param n Количество элементов в строке
 * @return Индекс максимального элемента
 */
size_t getMaxIndexInRow(int* row, const size_t n);

/**
 * @brief Инвертирует знак максимального элемента в каждой строке
 * @param array Массив для обработки
 * @param m Количество строк
 * @param n Количество столбцов
 */
void invertMaxInRows(int** array, const size_t m, const size_t n);

/**
 * @brief Находит максимальный элемент во всем массиве
 * @param array Массив для поиска
 * @param m Количество строк
 * @param n Количество столбцов
 * @return Максимальный элемент
 */
int findMaxElement(int** array, const size_t m, const size_t n);

/**
 * @brief Проверяет наличие максимального элемента в указанном столбце
 * @param array Массив для проверки
 * @param m Количество строк
 * @param col Индекс столбца для проверки
 * @param maxElement Искомый максимальный элемент
 * @return true если элемент найден, иначе false
 */
bool hasMaxElement(int** array, const size_t m, size_t col, int maxElement);

/**
 * @brief Вставляет столбцы с нулями после столбцов, содержащих максимальный элемент
 * @param array Ссылка на указатель массива
 * @param m Ссылка на количество строк
 * @param n Ссылка на количество столбцов
 */
void insertZeroColumns(int**& array, size_t& m, size_t& n);

/**
 * @brief Освобождает память, занятую массивом
 * @param array Массив для удаления
 * @param m Количество строк
 * @param n Количество столбцов
 */
void deleteArray(int** array, const size_t m, const size_t n);

/**
 * @brief Создает копию массива
 * @param array Массив для копирования
 * @param m Количество строк
 * @param n Количество столбцов
 * @return Указатель на копию массива
 */
int** copyArray(int** array, const size_t m, const size_t n);

int main()
{
    cout << "Введите количество строк (m): ";
    size_t m = getSize();
    cout << "Введите количество столбцов (n): ";
    size_t n = getSize();
    
    int** originalArray = createArray(m, n);
    
    // Заполняем массив вручную
    fillArray(originalArray, m, n);
    
    // Создаем копию исходного массива
    int** workingArray = copyArray(originalArray, m, n);
    
    cout << "\nИсходный массив:" << endl;
    printArray(originalArray, m, n);
    
    // Задание 1: Инвертировать максимальные элементы в строках
    invertMaxInRows(workingArray, m, n);
    cout << "\nПосле инверсии максимальных элементов в строках:" << endl;
    printArray(workingArray, m, n);
    
    // Задание 2: Вставить нулевые столбцы после столбцов с максимальным элементом
    insertZeroColumns(workingArray, m, n);
    cout << "\nПосле вставки нулевых столбцов:" << endl;
    printArray(workingArray, m, n);
    
    // Освобождаем память
    deleteArray(originalArray, m, n);
    deleteArray(workingArray, m, n);
    
    return 0;
}

int getValue()
{
    int value;
    if (!(cin >> value)) {
        cerr << "Ошибка ввода! Программа завершена." << endl;
        exit(EXIT_FAILURE);
    }
    return value;
}

size_t getSize()
{
    int n = getValue();
    checkN(n);
    return static_cast<size_t>(n);
}

void checkN(const int n)
{
    if (n <= 0) {
        cerr << "Ошибка: Размер должен быть положительным!" << endl;
        exit(EXIT_FAILURE);
    }
}

int** createArray(const size_t m, const size_t n)
{
    int** array = new int*[m];
    for (size_t i = 0; i < m; i++) {
        array[i] = new int[n]();
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
            cout << "Введите элемент [" << i << "][" << j << "]: ";
            array[i][j] = getValue();
        }
    }
}

size_t getMaxIndexInRow(int* row, const size_t n)
{
    size_t maxIndex = 0;
    for (size_t i = 1; i < n; i++) {
        if (row[i] > row[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}

void invertMaxInRows(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++) {
        size_t maxIndex = getMaxIndexInRow(array[i], n);
        array[i][maxIndex] = -array[i][maxIndex];
    }
}

int findMaxElement(int** array, const size_t m, const size_t n)
{
    int maxElement = array[0][0];
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            if (array[i][j] > maxElement) {
                maxElement = array[i][j];
            }
        }
    }
    return maxElement;
}

bool hasMaxElement(int** array, const size_t m, size_t col, int maxElement)
{
    for (size_t i = 0; i < m; i++) {
        if (array[i][col] == maxElement) {
            return true;
        }
    }
    return false;
}

void insertZeroColumns(int**& array, size_t& m, size_t& n)
{
    int maxElement = findMaxElement(array, m, n);
    
    // Считаем столбцы с максимальным элементом
    size_t columnsToAdd = 0;
    for (size_t j = 0; j < n; j++) {
        if (hasMaxElement(array, m, j, maxElement)) {
            columnsToAdd++;
        }
    }
    
    if (columnsToAdd == 0) return;
    
    size_t newN = n + columnsToAdd;
    int** newArray = createArray(m, newN);
    
    size_t newCol = 0;
    for (size_t j = 0; j < n; j++) {
        // Копируем оригинальный столбец
        for (size_t i = 0; i < m; i++) {
            newArray[i][newCol] = array[i][j];
        }
        newCol++;
        
        // Добавляем нулевой столбец если нужно
        if (hasMaxElement(array, m, j, maxElement)) {
            for (size_t i = 0; i < m; i++) {
                newArray[i][newCol] = 0;
            }
            newCol++;
        }
    }
    
    // Заменяем старый массив новым
    deleteArray(array, m, n);
    array = newArray;
    n = newN;
}

void deleteArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++) {
        delete[] array[i];
    }
    delete[] array;
}

int** copyArray(int** array, const size_t m, const size_t n)
{
    int** newArray = createArray(m, n);
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            newArray[i][j] = array[i][j];
        }
    }
    return newArray;
}
