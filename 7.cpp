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
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на созданный массив
 */
int** createArray(const size_t rows, const size_t cols);

/**
 * @brief Выводит массив на экран
 * @param array Массив для вывода
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void printArray(int** array, const size_t rows, const size_t cols);

/**
 * @brief Заполняет массив вручную с клавиатуры
 * @param array Массив для заполнения
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void fillArray(int** array, const size_t rows, const size_t cols);

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
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void invertMaxInRows(int** array, const size_t rows, const size_t cols);

/**
 * @brief Находит максимальный элемент во всем массиве
 * @param array Массив для поиска
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Максимальный элемент
 */
int findMaxElement(int** array, const size_t rows, const size_t cols);

/**
 * @brief Проверяет наличие максимального элемента в указанном столбце
 * @param array Массив для проверки
 * @param rows Количество строк
 * @param col Индекс столбца для проверки
 * @param maxElement Искомый максимальный элемент
 * @return true если элемент найден, иначе false
 */
bool hasMaxElement(int** array, const size_t rows, size_t col, int maxElement);

/**
 * @brief Подсчитывает количество столбцов, содержащих максимальный элемент
 * @param array Массив для проверки
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Количество столбцов с максимальным элементом
 */
size_t getNumberColumns(int** array, const size_t rows, const size_t cols);

/**
 * @brief Вставляет столбцы с нулями после столбцов, содержащих максимальный элемент
 * @param newArray Новый массив для заполнения
 * @param rows Количество строк
 * @param newCols Количество столбцов в новом массиве
 * @param cols Количество столбцов в исходном массиве
 * @param originalArray Исходный массив
 */
void insertZeroColumns(int** newArray, const size_t rows, const size_t newCols, const size_t cols, int** originalArray);

/**
 * @brief Освобождает память, занятую массивом
 * @param array Массив для удаления
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void deleteArray(int** array, const size_t rows, const size_t cols);

/**
 * @brief Создает копию массива
 * @param array Массив для копирования
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на копию массива
 */
int** copyArray(int** array, const size_t rows, const size_t cols);

/**
@brief Главная функция программы, выполняющая основную логику работы
@return int Возвращает 0 при успешном выполнении программы
*/
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
    
    cout << "/nИсходный массив:" << endl;
    printArray(originalArray, m, n);
    
    // Задание 1: Инвертировать максимальные элементы в строках
    invertMaxInRows(workingArray, m, n);
    cout << "\nПосле инверсии максимальных элементов в строках:" << endl;
    printArray(workingArray, m, n);
    
    // Задание 2: Вставить нулевые столбцы после столбцов с максимальным элементом
    size_t newColumns = getNumberColumns(workingArray, m, n);
    int** newArray = createArray(m, n + newColumns);
    insertZeroColumns(newArray, m, n + newColumns, n, workingArray);
    cout << "\nПосле вставки нулевых столбцов:" << endl;
    printArray(newArray, m, n + newColumns);
    
    // Освобождаем память
    deleteArray(originalArray, m, n);
    deleteArray(workingArray, m, n);
    deleteArray(newArray, m, n + newColumns);
    
    return 0;
}

int getValue()
{
    int value = 0;
    if (!(cin >> value)) {
        cerr << "Ошибка ввода! Программа завершена." << endl;
        abort();
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
        abort();
    }
}

int** createArray(const size_t rows, const size_t cols)
{
    int** array = new int*[rows];
    for (size_t i = 0; i < rows; i++) {
        array[i] = new int[cols]();
    }
    return array;
}

void printArray(int** array, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << setw(6) << array[i][j];
        }
        cout << endl;
    }
}

void fillArray(int** array, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
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

void invertMaxInRows(int** array, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++) {
        size_t maxIndex = getMaxIndexInRow(array[i], cols);
        array[i][maxIndex] = -array[i][maxIndex];
    }
}

int findMaxElement(int** array, const size_t rows, const size_t cols)
{
    int maxElement = array[0][0];
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (array[i][j] > maxElement) {
                maxElement = array[i][j];
            }
        }
    }
    return maxElement;
}

bool hasMaxElement(int** array, const size_t rows, size_t col, int maxElement)
{
    for (size_t i = 0; i < rows; i++) {
        if (array[i][col] == maxElement) {
            return true;
        }
    }
    return false;
}

size_t getNumberColumns(int** array, const size_t rows, const size_t cols)
{
    int maxElement = findMaxElement(array, rows, cols);
    size_t count = 0;
    
    for (size_t j = 0; j < cols; j++) {
        if (hasMaxElement(array, rows, j, maxElement)) {
            count++;
        }
    }
    return count;
}

void insertZeroColumns(int** newArray, const size_t rows, const size_t newCols, const size_t cols, int** originalArray)
{
    int maxElement = findMaxElement(originalArray, rows, cols);
    size_t newCol = 0;
    
    for (size_t j = 0; j < cols; j++) {
        // Копируем оригинальный столбец
        for (size_t i = 0; i < rows; i++) {
            newArray[i][newCol] = originalArray[i][j];
        }
        newCol++;
        
        // Добавляем нулевой столбец если нужно
        if (hasMaxElement(originalArray, rows, j, maxElement)) {
            for (size_t i = 0; i < rows; i++) {
                newArray[i][newCol] = 0;
            }
            newCol++;
        }
    }
}

void deleteArray(int** array, const size_t rows, const size_t cols)
{
    for (size_t i = 0; i < rows; i++) {
        delete[] array[i];
    }
    delete[] array;
}

int** copyArray(int** array, const size_t rows, const size_t cols)
{
    int** newArray = createArray(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            newArray[i][j] = array[i][j];
        }
    }
    return newArray;
}
