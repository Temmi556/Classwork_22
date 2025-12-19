#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define M_PI 3.14159265358979323846
#define NUM_FUNCS 3

typedef double (*Func)(double);

void tabulirovat(Func f, double a, double b, double h) {
    printf("--------------------------------------\n");
    printf("|     x     |   Результат функции   |\n");
    printf("--------------------------------------\n");
    for (double x = a; x <= b; x += h)
        printf("|  %7.3lf  |  %18.6lf  |\n", x, f(x));
    printf("--------------------------------------\n");
}
// Вариант 9 - Функции
double func1(double x) {
    return (exp(-x) * tan(x)) / (2 * x);
}

double func2(double x) {
    if (x > 2 * M_PI)
        return cbrt(fabs(x));
    else if (x >= 0 && x <= 2 * M_PI)
        return exp(-0.3 * x);
    else
        return -pow(cos(x * M_PI), 2);
}

double func3(double x) {
    double t = (x - 1) / (x + 1);
    return t + pow(t, 3) / 3 + pow(t, 5) / 5 + pow(t, 7) / 7;
}

// Массив указателей на функции
Func funcs[NUM_FUNCS] = {func1, func2, func3};


const char *func_names[NUM_FUNCS] = {
    "1. f(x) = (e^(-x) * tan(x)) / (2x)",
    "2. f(x) = cbrt(|x|) при x > 2pi; e^(-0.3x) при 0 <= x <= 2pi; -cos^2(pi*x) иначе",
    "3. f(x) = t + t^3/3 + t^5/5 + t^7/7, где t = (x-1)/(x+1)"
};

void print_func_menu() {
    printf("Выберите функцию:\n");
    for (int i = 0; i < NUM_FUNCS; i++)
        printf("%s\n", func_names[i]);
    printf("Ваш выбор: ");
}

// Получение функции по выбору пользователя
Func get_func(int choice) {
    if (choice >= 1 && choice <= NUM_FUNCS)
        return funcs[choice - 1];
    return NULL;
}
// Главная функция
int main() {
    int choice, func_choice;
    double x, a, b, h;
    Func f;
    FILE *file;

    while (true) {
        printf("\nМеню:\n");
        printf("1 - Вычислить значение\n");
        printf("2 - Табулировать функцию\n");
        printf("3 - Выполнить операцию (запись в файл)\n");
        printf("4 - Выход\n");
        printf("Ваш выбор: ");
        scanf("%d", &choice);

        if (choice == 4) exit(0);
        
        print_func_menu();
        scanf("%d", &func_choice);
        
        f = get_func(func_choice);
        if (!f) {
            printf("Неверный выбор функции!\n");
            continue;
        }
        
        switch (choice) {
            case 1:  // Вычислить значение
                printf("Введите значение x: ");
                scanf("%lf", &x);
                printf("Результат: f(%.4lf) = %.6lf\n", x, f(x));
                break;

            case 2:  // Табулировать
                printf("Введите a, b, h: ");
                scanf("%lf %lf %lf", &a, &b, &h);
                tabulirovat(f, a, b, h);
                break;

            case 3:  // Запись в файл
                printf("Введите a, b, h для сохранения результата в файл:\n");
                scanf("%lf %lf %lf", &a, &b, &h);
                file = fopen("dat.txt", "w");
                for (x = a; x <= b; x += h)
                    fprintf(file, "%.4lf,%.6lf\n", x, f(x));
                fclose(file);
                printf("Данные успешно записаны в файл dat.txt\n");
                break;
        }
    }
    return 0;
}