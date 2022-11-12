#include <iostream>
#include <fstream>
#include <omp.h>

using namespace std;

void generate_matrix_1(int row, int col) {
    int** a;
    int i, j;
    a = new int* [row];
#pragma omp parallel for private(i, j) shared(a)
    for (i = 0; i < row; i++)
    {
        a[i] = new int[col];
        for (j = 0; j < col; j++)
        {
            a[i][j] = rand() % 10;
        }
    }
    ofstream fout("matrix_1_1.txt");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            fout << a[i][j] << " ";
        fout << endl;
    }
    fout.close();
}

void generate_matrix_2(int row, int col) {
    int** a;
    int i, j;
    a = new int* [row];
#pragma omp parallel for private(i, j) shared(a)
    for (i = 0; i < row; i++)
    {
        a[i] = new int[col];
        for (j = 0; j < col; j++)
        {
            a[i][j] = rand() % 10;
        }
    }
    ofstream fout("matrix_2_1.txt");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
            fout << a[i][j] << " ";
        fout << endl;
    }
    fout.close();
}

int** get_matrix_1(int row, int col) {
    ifstream fin("matrix_1_1.txt");
    int** a;
    int i, j;
    a = new int* [row];
#pragma omp parallel for private(i, j) shared(a)
    for (i = 0; i < row; i++) {
        a[i] = new int[col];
        for (j = 0; j < col; j++) {
            fin >> a[i][j];
        }
    }
    fin.close();
    return a;
}

int** get_matrix_2(int row, int col) {
    ifstream fin("matrix_2_1.txt");
    int** a;
    int i, j;
    a = new int* [row];
#pragma omp parallel for private(i, j) shared(a)
    for (i = 0; i < row; i++) {
        a[i] = new int[col];
        for (j = 0; j < col; j++) {
            fin >> a[i][j];
        }
    }
    fin.close();
    return a;
}

void multiplication(int** a, int** b, int row1, int row2, int col1, int col2) {
    clock_t tStart = clock();
    int** c;
    int i, j, k;
    c = new int* [row1];
#pragma omp parallel for private(i, j, k) shared(a, b, c)
    for (i = 0; i < row1; i++)
    {
        c[i] = new int[col2];
        for (j = 0; j < col2; j++)
        {
            c[i][j] = 0;
            for (k = 0; k < col1; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
    ofstream fout("result_1.txt");
    for (i = 0; i < row1; i++)
    {
        for (j = 0; j < col2; j++)
            fout << c[i][j] << " ";
        fout << endl;
    }
    fout.close();
    ofstream f1out("time_1.txt");
    f1out << "Time: " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "\n";
    cout << row1 << ": " << (double)(clock() - tStart) / CLOCKS_PER_SEC << "\n";
    f1out.close();
}

int main() {
    srand(time(NULL));
    int n = 250;
#pragma omp parallel for private(n) shared(a, b)
    while (n < 2001) {
        int row = n, col = n;
        generate_matrix_1(row, col);
        generate_matrix_2(row, col);
        int** a, ** b;
        a = get_matrix_1(row, col);
        b = get_matrix_2(row, col);
        multiplication(a, b, row, col, row, col);
        n += 250;
    }
    return 0;
}