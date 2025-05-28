#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

/**
 * @brief Функция для безопасного ввода числового значения
 * @return Введенное пользователем значение
 */
double getValue();

/**
 * @brief Функция для проверки корректности шага
 * @param step - значение шага для проверки
 */
void checkStep(const double step);

/**
 * @brief Функция для вычисления значения y по заданному уравнению
 * @param x - значение переменной x
 * @return вычисленное значение y
 */
double getY(const double x);

/**
 * @brief Функция для проверки принадлежности x области определения функции
 * @param x - значение переменной x для проверки
 * @return true, если x принадлежит области определения, иначе false
 */
bool isDomain(const double x);

/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программа выполнена корректно
 */
int main()
{
    cout << "Enter xn: ";
    double xstart = getValue();
    cout << "Enter xk: ";
    double xend = getValue();
    cout << "Enter step: ";
    double step = getValue();
    
    checkStep(step);
    
    for (double x = xstart; x < xend + step; x += step)
    {
        cout << "x = " << x;
        if (isDomain(x))
        {
            cout << " y = " << getY(x) << endl;
        }
        else
        {
            cout << " not in domain" << endl;
        }
    }
    return 0;
}

double getValue()
{
    double value;
    cin >> value;
    if (cin.fail())
    {
        cout << "Incorrect value" << endl;
        abort();
    }
    return value;
}

void checkStep(const double step)
{
    if (step <= 0)
    {
        cout << "Error value" << endl;
        abort();
    }
}

double getY(const double x)
{
    return cos(2.0 / x) - 2 * sin(1.0 / x) + 1.0 / x;
}

bool isDomain(const double x)
{
    return !(abs(x) < std::numeric_limits<double>::epsilon());
}
