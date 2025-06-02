#include <iostream>

using namespace std;

/**
 * @brief Получает целое число от пользователя с проверкой ввода
 * @return Введенное целое число
 */
int getValue();

/**
 * @brief Получает размер массива от пользователя с проверкой ввода
 * @return Размер массива
 */
size_t getSize();

/**
 * @brief Проверяет корректность размера массива (n > 0)
 * @param n Размер массива для проверки
 */
void checkN(const int n);

/**
 * @brief Заполняет массив значениями, введенными пользователем
 * @param arr Указатель на массив
 * @param n Размер массива
 */
void fillArray(int* arr, const int n);

/**
 * @brief Выводит элементы массива на экран
 * @param arr Указатель на массив
 * @param n Размер массива
 */
void printArray(int* arr, const int n);

/**
 * @brief Заменяет последние k элементов массива на противоположные
 * @param arr Указатель на массив
 * @param n Размер массива
 * @param k Количество элементов для замены
 */
void replaceLastK(int* arr, const int n, int k);

/**
 * @brief Выводит индексы элементов массива, кратных 3
 * @param arr Указатель на массив
 * @param n Размер массива
 */
void printIndicesMultiplesOf3(int* arr, const int n);

/**
 * @brief Проверяет наличие пары соседних элементов с заданной суммой
 * @param arr Указатель на массив
 * @param n Размер массива
 * @param targetSum Целевая сумма для проверки
 * @return true если найдена пара, иначе false
 */
bool hasPairWithSum(int* arr, const int n, int targetSum);

/**
 * @brief Создает копию массива
 * @param arr Указатель на исходный массив
 * @param n Размер массива
 * @return Указатель на новый массив-копию
 */
int* copyArray(int* arr, const int n);

int main() {
    // Получаем размер массива от пользователя
    size_t n = getSize();
    int* arr = new int[n];
    
    // Заполняем массив вручную
    fillArray(arr, n);
    
    cout << "Исходный массив: ";
    printArray(arr, n);
    
    // Задание 1: Замена последних k элементов на противоположные
    cout << "Введите k для замены последних элементов: ";
    int k = getValue();
    int* copy1 = copyArray(arr, n);
    replaceLastK(copy1, n, k);
    cout << "После замены последних " << k << " элементов: ";
    printArray(copy1, n);
    delete[] copy1;
    
    // Задание 2: Вывод индексов элементов, кратных 3
    cout << "Индексы элементов, кратных 3: ";
    printIndicesMultiplesOf3(arr, n);
    
    // Задание 3: Проверка наличия пары соседних элементов с заданной суммой
    cout << "Введите целевую сумму для проверки: ";
    int targetSum = getValue();
    if (hasPairWithSum(arr, n, targetSum)) {
        cout << "Есть пара соседних элементов с суммой " << targetSum << endl;
    } else {
        cout << "Нет пар соседних элементов с суммой " << targetSum << endl;
    }
    
    delete[] arr;
    return 0;
}

// Функция для получения целого числа от пользователя
int getValue() {
    int value = 0;
    cin >> value;
    if (cin.fail()) {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

// Функция для получения размера массива
size_t getSize() {
    cout << "Введите размер массива n: ";
    int n = getValue();
    checkN(n);
    return static_cast<size_t>(n);
}

// Функция для проверки корректности размера массива
void checkN(const int n) {
    if (n <= 0) {
        cout << "Ошибка: размер массива должен быть положительным" << endl;
        abort();
    }
}

// Функция для заполнения массива
void fillArray(int* arr, const int n) {
    for (size_t i = 0; i < n; i++) {
        cout << "Введите arr[" << i + 1 << "] = ";
        arr[i] = getValue();
    }
}

// Функция для вывода массива
void printArray(int* arr, const int n) {
    for (size_t i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Задание 1: Замена последних k элементов на противоположные
void replaceLastK(int* arr, const int n, int k) {
    if (k <= 0 || k > n) {
        cout << "Некорректное значение k" << endl;
        return;
    }
    
    for (size_t i = n - 1 - k; i < n; i++) {
        arr[i] = -arr[i];
    }
}

// Задание 2: Вывод индексов элементов, кратных 3
void printIndicesMultiplesOf3(int* arr, const int n) {
    bool found = false;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] % 3 == 0) {
            cout << i << " ";
            found = true;
        }
    }
    if (!found) {
        cout << "Нет элементов, кратных 3";
    }
    cout << endl;
}

// Задание 3: Проверка наличия пары соседних элементов с заданной суммой
bool hasPairWithSum(int* arr, const int n, int targetSum) {
    if (n < 2) return false;
    
    for (size_t i = 0; i < n - 1; i++) {
        if (arr[i] + arr[i + 1] == targetSum) {
            return true;
        }
    }
    return false;
}

// Функция для создания копии массива
int* copyArray(int* arr, const int n) {
    int* copyArr = new int[n];
    for (size_t i = 0; i < n; i++) {
        copyArr[i] = arr[i];
    }
    return copyArr;
}
