#include <iostream>
using namespace std;

/**
 * @brief - Функция для перевода граммов в унции 
 * @param grams - значение веса в граммах
 * @return - возвращает вес в унциях
 */
double gramsToOunces(const double grams);

/**
 * @brief - Точка входа в программу 
 * @return - возвращает 0, если программа выполнена корректно
 */
int main()
{
    double grams;
    cout << "Введите вес в граммах: ";
    cin >> grams;
    
    cout << grams << " граммов = " << gramsToOunces(grams) << " унций" << endl;
    return 0;
}

double gramsToOunces(const double grams)
{
    const double ouncesPerGram = 1.0 / 28.3; // 1 унция = 28.3 г, поэтому 1 г = 1/28.3 унций
    return grams * ouncesPerGram;
}
