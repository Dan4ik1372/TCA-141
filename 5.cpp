#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

/**
 * @brief Считывает целое число с клавиатуры с проверкой ввода
 * @return Считанное значение
 */
int getValue();

/**
 * @brief Считывает вещественное число с клавиатуры с проверкой ввода
 * @return Считанное значение
 */
double getDouble();

/**
 * @brief Проверяет, что введенное значение удовлетворяет условию n >= 1
 * @param n Считанное значение
 */
void checkN(const int n);

/**
 * @brief Проверяет, что введенное значение удовлетворяет условию e > 0
 * @param e Считанное значение
 */
void checkE(const double e);

/**
 * @brief Рассчитывает сумму n первых членов ряда с использованием рекуррентного выражения
 * @param n Заданное число членов
 * @return Сумма n первых членов ряда
 */
double sumN(const int n);

/**
 * @brief Рассчитывает следующий член ряда через рекуррентное выражение
 * @param current Текущий член ряда
 * @param k Текущий индекс (начинается с 1)
 * @return Следующий член ряда
 */
double getNext(const double current, const int k);

/**
 * @brief Рассчитывает сумму первых членов ряда, не меньших по модулю e
 * @param e Заданная точность
 * @return Сумма первых членов ряда, не меньших по модулю e
 */
double sumE(const double e);

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Вычисление суммы для ряда: (k=1 to n) [(-1)^k * k^4 / k!]" << endl << endl;
    
    cout << "Введите число членов ряда для рассчета последовательности: ";
    int n = getValue();
    checkN(n);
    cout << "Сумма первых " << n << " членов ряда равна " << sumN(n) << endl;
    
    cout << "Введите погрешность для рассчета последовательности: ";
    double e = getDouble();
    checkE(e);
    cout << "Сумма членов ряда с точностью e равна " << sumE(e) << endl;
    
    return 0;
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

double getDouble()
{
    double value = 0.0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

void checkN(const int n)
{
    if (n < 1)
    {
        cout << "Ошибка ввода: n должно быть >= 1" << endl;
        abort();
    }
}

void checkE(const double e)
{
    if (e <= 0)
    {
        cout << "Ошибка ввода: e должно быть > 0" << endl;
        abort();
    }
}

double sumN(const int n)
{
    double current = -1.0; // Первый член при k=1: (-1)^1 * 1^4 / 1! = -1
    double sum = current;
    
    for (int k = 1; k < n; k++)
    {
        current = getNext(current, k);
        sum += current;
    }
    
    return sum;
}

double getNext(const double current, const int k)
{
    // Рекуррентное соотношение: a_k = a_{k-1} * (-1) * k^4 / (k! / (k-1)!) = a_{k-1} * (-1) * k^3 / (k)
    // Упрощаем: a_k = a_{k-1} * (-1) * k^3 / k = a_{k-1} * (-1) * k^2
    // Но это неверно, правильное соотношение:
    // a_k = (-1)^k * k^4 / k!
    // a_{k-1} = (-1)^{k-1} * (k-1)^4 / (k-1)!
    // Тогда a_k = a_{k-1} * (-1) * k^4 / (k * (k-1)^4) = a_{k-1} * (-1) * k^3 / (k-1)^4
    
    return current * (-1.0) * pow(k, 4) / (k * pow(k-1, 3));
}

double sumE(const double e)
{
    double current = -1.0; // Первый член при k=1
    double sum = 0.0;
    int k = 1;
    
    while (fabs(current) >= e)
    {
        sum += current;
        current = getNext(current, k);
        k++;
    }
    
    return sum;
}
