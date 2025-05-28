#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

/**
 * @brief Функция для заполнения массива случайными числами
 * @param arr - ссылка на вектор для заполнения
 * @param n - размер массива
 * @param min - минимальное значение
 * @param max - максимальное значение
 */
void fillRandom(vector<int>& arr, int n, int min, int max) {
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % (max - min + 1) + min;
    }
}

/**
 * @brief Функция для заполнения массива с клавиатуры
 * @param arr - ссылка на вектор для заполнения
 * @param n - размер массива
 */
void fillManual(vector<int>& arr, int n) {
    arr.resize(n);
    cout << "Введите " << n << " целых чисел:" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        while (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Пожалуйста, введите целое число: ";
            cin >> arr[i];
        }
    }
}

/**
 * @brief Функция для замены последних k элементов на противоположные
 * @param arr - ссылка на вектор
 * @param k - количество элементов для замены
 */
void invertLastKElements(vector<int>& arr, int k) {
    if (k <= 0 || k > arr.size()) return;
    
    for (size_t i = arr.size() - k; i < arr.size(); ++i) {
        arr[i] = -arr[i];
    }
}

/**
 * @brief Функция для вывода индексов элементов, кратных 3
 * @param arr - вектор для поиска
 */
void printIndicesDivisibleBy3(const vector<int>& arr) {
    cout << "Индексы элементов, кратных 3: ";
    bool found = false;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] % 3 == 0) {
            cout << i << " ";
            found = true;
        }
    }
    if (!found) cout << "таких элементов нет";
    cout << endl;
}

/**
 * @brief Функция для проверки наличия пары соседних элементов с заданной суммой
 * @param arr - вектор для поиска
 * @param target - целевая сумма
 * @return true, если такая пара найдена, иначе false
 */
bool hasPairWithSum(const vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        if (arr[i] + arr[i + 1] == target) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Функция для безопасного ввода целого числа с проверкой диапазона
 * @param prompt - приглашение для ввода
 * @param min - минимальное допустимое значение
 * @param max - максимальное допустимое значение
 * @return введенное пользователем число
 */
int getIntInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Пожалуйста, введите целое число от " 
                 << min << " до " << max << ": ";
        } else {
            break;
        }
    }
    return value;
}

/**
 * @brief Точка входа в программу
 * @return 0 при успешном выполнении
 */
int main() {
    srand(time(0)); // Инициализация генератора случайных чисел

    cout << "=== Вариант 5 ===" << endl;
    cout << "1. Заменить последние k элементов массива на противоположные по знаку" << endl;
    cout << "2. Вывести индексы элементов, кратных 3" << endl;
    cout << "3. Проверить наличие пары соседних элементов с заданной суммой" << endl << endl;

    // Ввод размера массива
    int n = getIntInput("Введите размер массива (1-100): ", 1, 100);

    // Выбор способа заполнения массива
    vector<int> arr;
    cout << "Выберите способ заполнения массива:" << endl;
    cout << "1 - случайные числа [-100; 100]" << endl;
    cout << "2 - ввод с клавиатуры" << endl;
    
    int choice = getIntInput("Ваш выбор: ", 1, 2);
    if (choice == 1) {
        fillRandom(arr, n, -100, 100);
    } else {
        fillManual(arr, n);
    }

    // Вывод массива
    cout << "Массив: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl << endl;

    // Задача 1: Замена последних k элементов
    int k = getIntInput("Введите k для замены последних элементов (1-" + to_string(n) + "): ", 1, n);
    invertLastKElements(arr, k);
    cout << "Массив после замены: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl << endl;

    // Задача 2: Индексы элементов, кратных 3
    printIndicesDivisibleBy3(arr);
    cout << endl;

    // Задача 3: Проверка пары с заданной суммой
    int target = getIntInput("Введите число для проверки суммы соседних элементов: ", -200, 200);
    if (hasPairWithSum(arr, target)) {
        cout << "В массиве есть соседние элементы с суммой " << target << endl;
    } else {
        cout << "В массиве нет соседних элементов с суммой " << target << endl;
    }

    return 0;
}
