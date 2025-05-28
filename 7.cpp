/**
 * @brief Находит максимальный элемент в строке
 * @param row - вектор-строка
 * @return значение максимального элемента
 */
int findMaxInRow(const vector<int>& row) {
    int max = row[0];
    for (int num : row) {
        if (num > max) max = num;
    }
    return max;
}

/**
 * @brief Заменяет максимальный элемент каждой строки на противоположный
 * @param matrix - ссылка на двумерный вектор
 */
void invertMaxInRows(vector<vector<int>>& matrix) {
    for (auto& row : matrix) {
        int max = findMaxInRow(row);
        for (int& num : row) {
            if (num == max) num = -num;
        }
    }
}

/**
 * @brief Проверяет, содержит ли столбец максимальный элемент матрицы
 * @param matrix - двумерный вектор
 * @param col - индекс столбца
 * @return true, если содержит, иначе false
 */
bool containsMaxElement(const vector<vector<int>>& matrix, int col) {
    int global_max = matrix[0][0];
    // Находим глобальный максимум
    for (const auto& row : matrix) {
        for (int num : row) {
            if (num > global_max) global_max = num;
        }
    }
    // Проверяем столбец
    for (const auto& row : matrix) {
        if (row[col] == global_max) return true;
    }
    return false;
}

/**
 * @brief Вставляет столбец из нулей после столбцов с максимальным элементом
 * @param matrix - ссылка на двумерный вектор
 */
void insertZeroAfterMaxColumns(vector<vector<int>>& matrix) {
    if (matrix.empty()) return;
    
    vector<bool> cols_to_insert(matrix[0].size(), false);
    // Определяем, какие столбцы нужно вставить
    for (size_t j = 0; j < matrix[0].size(); ++j) {
        cols_to_insert[j] = containsMaxElement(matrix, j);
    }
    
    // Вставляем столбцы
    for (size_t j = 0; j < cols_to_insert.size(); ++j) {
        if (cols_to_insert[j]) {
            for (auto& row : matrix) {
                row.insert(row.begin() + j + 1, 0);
            }
            // Пропускаем только что вставленный столбец
            j++;
        }
    }
}

int main() {
    // ... (предыдущий код)

    // Реализация для варианта 5
    cout << "1. Замена максимальных элементов строк на противоположные:" << endl;
    invertMaxInRows(matrix);
    printMatrix(matrix);

    cout << "2. Вставка столбцов из нулей после столбцов с максимальным элементом:" << endl;
    insertZeroAfterMaxColumns(matrix);
    printMatrix(matrix);

    return 0;
}
