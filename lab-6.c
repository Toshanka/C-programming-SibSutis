#include <stdio.h>
#include <windows.h>

// МАТРИЦЫ ЛАБА 6 

double det2(const double m[3][3]) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

double det3(const double m[3][3]) {
    return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
         - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
         + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

double det_n(int n, const double m[3][3]) {
    if (n == 2)
        return det2(m);
    if (n == 3)
        return det3(m);
    return 0.0;
}

//матрица, в которой столбец заменен 
void replace_column(int n, const double a[3][3], const double v[3], int col, double result[3][3]) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            result[r][c] = (c == col) ? v[r] : a[r][c];
        }
    }
}

// Определитель матрицы A с заменённым столбцом 
double det_replace(int n, const double a[3][3], const double v[3], int col) {
    double m[3][3] = {{0.0}};
    replace_column(n, a, v, col, m);
    return det_n(n, m);
}

void cramer(int n, const double a[3][3], const double b[3], double x[3]) {
    double det_a = det_n(n, a);
    // замена сталбца на столбец свободных членов 
    for (int k = 0; k < n; k++)
        x[k] = det_replace(n, a, b, k) / det_a;
}

void print_x(int n, const double x[3]) {
    for (int i = 0; i < n; i++) {
        printf("x%d = %.2f\n", i + 1, x[i]);
    }
}

int main(void) {
	SetConsoleOutputCP(CP_UTF8);

    int n;
    printf("n (2 или 3): ");
    scanf("%d", &n);

    if (n != 2 && n != 3) {
        printf("n должно быть 2 или 3\n");
    }

	else {
    double a[3][3] = {{0.0}}, b[3] = {0.0}, x[3] = {0.0};

    printf("Матрица:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &a[i][j]);

    printf("Вектор свободных членов b:\n");
    for (int i = 0; i < n; i++)
        scanf("%lf", &b[i]);

    double det_a = det_n(n, a);
    if (det_a == 0.0) {
        printf("det(A) = 0: решения нет\n");
        return 1;
    }

    cramer(n, a, b, x);
    printf("Решение:\n");
    print_x(n, x);
}
    return 0;
}