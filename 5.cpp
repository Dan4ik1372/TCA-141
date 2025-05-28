#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

/**
 * @brief Функция для вычисления факториала (итеративная реализация)
 * @param n - число для вычисления факториала
 * @return вычисленный факториал
 */
unsigned long long factorial(int n) {
    if (n < 0) return 0;
    unsigned long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

/**
 * @brief Функция для вычисления суммы первых n членов последовательности
 * @param n - количество членов последовательности
 * @return сумма первых n членов
 */
double sumFirstN(int n) {
    double sum = 0.0;
    for (int k = 1; k <= n; ++k) {
        double term = pow(-1, k) * pow(k, 4) / factorial(k);
        sum += term;
    }
    return sum;
}

/**
 * @brief Функция для вычисления суммы членов последовательности, не меньших по модулю e
 * @param e - минимальное значение по модулю
 * @return сумма подходящих членов последовательности
 */
double sumGreaterThanE(double e) {
    double sum = 0.0;
    int k = 1;
    while (true) {
        double term = pow(-1, k) * pow(k, 4) / factorial(k);
        if (fabs(term) < e) break;
        sum += term;
        k++;
    }
    return sum;
}

/**
 * @brief Функция для безопасного ввода целого числа
 * @return введенное пользователем число
 */
int getIntInput() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Пожалуйста, введите положительное целое число: ";
        } else {
            break;
        }
    }
    return value;
}

/**
 * @brief Функция для безопасного ввода вещественного числа
 * @return введенное пользователем число
 */
double getDoubleInput() {
    double value;
    while (true) {
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Пожалуйста, введите положительное число: ";
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
    cout << "Вычисление суммы для ряда варианта 5:" << endl;
    cout << "∑(k=1 to n) [(-1)^k * k^4 / k!]" << endl << endl;

    // Часть a: сумма первых n членов
    cout << "Часть a: сумма первых n членов" << endl;
    cout << "Введите n: ";
    int n = getIntInput();
    cout << "Сумма первых " << n << " членов: " << sumFirstN(n) << endl << endl;

    // Часть b: сумма членов, не меньших по модулю e
    cout << "Часть b: сумма членов, не меньших по модулю e" << endl;
    cout << "Введите e: ";
    double e = getDoubleInput();
    cout << "Сумма членов, не меньших по модулю " << e << ": " << sumGreaterThanE(e) << endl;

    return 0;
}
