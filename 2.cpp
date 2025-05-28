#include <iostream>
using namespace std;

/**
 * @brief - Функция для перевода граммов в унции 
 * @param grams - значение веса в граммах
 * @return - возвращает вес в унциях
 */
double gramsToOunces(const double grams);

/**
 * @brief - Функция для безопасного ввода вещественного числа
 * @return - возвращает введенное пользователем число
 */
double getDoubleInput();

/**
 * @brief - Точка входа в программу 
 * @return - возвращает 0, если программа выполнена корректно
 */
int main()
{
    cout << "Введите вес в граммах: ";
    double grams = getDoubleInput();
    
    cout << grams << " граммов = " << gramsToOunces(grams) << " унций" << endl;
    return 0;
}

double gramsToOunces(const double grams)
{
    const double ouncesPerGram = 1.0 / 28.3; // 1 унция = 28.3 г, поэтому 1 г = 1/28.3 унций
    return grams * ouncesPerGram;
}

double getDoubleInput()
{
    double value;
    while (true)
    {
        cin >> value;
        if (cin.fail() || value <= 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Пожалуйста, введите положительное число: ";
        }
        else
        {
            break;
        }
    }
    return value;
}
