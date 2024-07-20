#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

// Функция для вычисления значения выражения, используя стек
double evaluate(const char* expr);

// Функция для определения приоритета операций
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Функция для применения операции к двум операндам
double applyOp(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            cout << "Ошибка: деление на ноль." << endl;
            exit(1);
        }
        return a / b;
    }
    return 0;
}

// Основная функция вычисления выражения
double evaluate(const char* expr) {
    double values[100];
    char ops[100];
    int valueTop = -1, opTop = -1;

    for (int i = 0; i < strlen(expr); i++) {
        // Игнорируем пробелы
        if (isspace(expr[i])) continue;

        // Если текущий символ - число, добавляем его в стек значений
        if (isdigit(expr[i])) {
            double value = 0;
            while (i < strlen(expr) && isdigit(expr[i])) {
                value = (value * 10) + (expr[i] - '0');
                i++;
            }
            values[++valueTop] = value;
            i--; // Уменьшаем индекс, чтобы не пропустить символ
        }
        // Если текущий символ - '(', добавляем в стек операций
        else if (expr[i] == '(') {
            ops[++opTop] = expr[i];
        }
        // Если текущий символ - ')', выполняем операции до '('
        else if (expr[i] == ')') {
            while (opTop != -1 && ops[opTop] != '(') {
                double b = values[valueTop--];
                double a = values[valueTop--];
                char op = ops[opTop--];
                values[++valueTop] = applyOp(a, b, op);
            }
            opTop--; // Убираем '(' из стека
        }
        // Если текущий символ - оператор
        else {
            while (opTop != -1 && precedence(ops[opTop]) >= precedence(expr[i])) {
                double b = values[valueTop--];
                double a = values[valueTop--];
                char op = ops[opTop--];
                values[++valueTop] = applyOp(a, b, op);
            }
            ops[++opTop] = expr[i];
        }
    }

    // Выполняем оставшиеся операции
    while (opTop != -1) {
        double b = values[valueTop--];
        double a = values[valueTop--];
        char op = ops[opTop--];
        values[++valueTop] = applyOp(a, b, op);
    }

    // Возвращаем окончательное значение
    return values[valueTop];
}

int main() {
    setlocale(LC_ALL, "rus");
    char expression[100];
    cout << "Введите арифметическое выражение: ";
    cin.getline(expression, 100);

    double result = evaluate(expression);
    cout << "Результат: " << result << endl;

    return 0;
}