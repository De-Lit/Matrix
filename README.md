# Matrix

В данном проекте в виде отдельного класса реализована библиотека matrix.h для работы с матрицами. Над объектами класса определены операции, представленные как методами, так и стандартными операторами +, -, * и т.д.

## Описание библиотеки

- Библиотека разработана на языке C++ стандарта C++17 с использованием компилятора gcc
- Код программы находится в папке src
- Сборки и тестирование библиотеки настроено с помощию Makefile (с целями all, clean, test, matrix.a)
- Обеспечено покрытие unit-тестами функций библиотеки c помощью библиотеки GTest

### Описание конструкторов и методов

 `S21Matrix()` Базовый конструктор, инициализирующий матрицу размерностью 1х1 \
 `S21Matrix(int rows, int cols)` Параметризированный конструктор с количеством строк и столбцов \
 `S21Matrix(const S21Matrix& other)` Конструктор копирования \
 `S21Matrix(S21Matrix&& other)` Конструктор переноса \
 `~S21Matrix()` Деструктор 

 `bool EqMatrix(const S21Matrix& other)` Проверяет матрицы на равенство между собой \
 `void SumMatrix(const S21Matrix& other)` Прибавляет вторую матрицы к текущей (исключение: различная размерность матриц) \
 `void SubMatrix(const S21Matrix& other)` Вычитает из текущей матрицы другую (исключение: различная размерность матриц) \
 `void MulNumber(const double num)` Умножает текущую матрицу на число \
 `void MulMatrix(const S21Matrix& other)` Умножает текущую матрицу на вторую (исключение: число столбцов первой матрицы не равно числу строк второй матрицы) \
 `S21Matrix Transpose()` Создает новую транспонированную матрицу из текущей и возвращает ее \
 `S21Matrix CalcComplements()` Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее (исключение: матрица не является квадратной) \
 `double Determinant()` Вычисляет и возвращает определитель текущей матрицы (исключение: матрица не является квадратной) \
 `S21Matrix InverseMatrix()` Вычисляет и возвращает обратную матрицу (исключение: определитель матрицы равен 0) 

 `+` Сложение двух матриц (исключение: различная размерность матриц) \
 `-` Вычитание одной матрицы из другой (исключение: различная размерность матриц) \
 `*` Умножение матриц и умножение матрицы на число (исключение: число столбцов первой матрицы не равно числу строк второй матрицы) \
 `==` Проверка на равенство матриц (`EqMatrix`) \
 `=` Присвоение матрице значений другой матрицы \
 `+=` Присвоение сложения (`SumMatrix`) (исключение: различная размерность матриц) \
 `-=` Присвоение разности (`SubMatrix`) (исключение: различная размерность матриц) \
 `*=` Присвоение умножения (`MulMatrix`/`MulNumber`) (исключение: число столбцов первой матрицы не равно числу строк второй матрицы) \
 `(int i, int j)` Индексация по элементам матрицы (строка, колонка) (исключение: индекс за пределами матрицы) 
