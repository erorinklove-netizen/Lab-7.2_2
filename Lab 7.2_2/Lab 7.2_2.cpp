// Lab 7.2_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
// <Якимів Наталія>
// Лабораторна робота №7.1
// Опрацювання матриці рекурсивним способом
// Варіант 7

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void CreateRow(int** a, int row, int col, const int n, const int Low, const int High);
void CreateRows(int** a, int row, const int k, const int n, const int Low, const int High);

void PrintRow(int** a, int row, int col, const int n);
void PrintRows(int** a, int row, const int k, const int n);

int RowMin(int** a, int row, int col, const int n);
int MaxOfRowMins(int** a, int row, const int k, const int n, int currentMax);

int main()
{
    srand((unsigned)time(NULL));

    int k, n;
    cout << "k = "; cin >> k;
    cout << "n = "; cin >> n;

    int Low = -20, High = 50;

    int** a = new int* [k];
    for (int i = 0; i < k; i++)
        a[i] = new int[n];

    CreateRows(a, 0, k, n, Low, High);
    PrintRows(a, 0, k, n);

    int firstMin = RowMin(a, 0, 0, n);
    int result = MaxOfRowMins(a, 1, k, n, firstMin);

    cout << "Max of row minimums = " << result << endl;

    for (int i = 0; i < k; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// ---------- Формування ----------
void CreateRow(int** a, int row, int col, const int n, const int Low, const int High)
{
    a[row][col] = Low + rand() % (High - Low + 1);
    if (col < n - 1)
        CreateRow(a, row, col + 1, n, Low, High);
}

void CreateRows(int** a, int row, const int k, const int n, const int Low, const int High)
{
    CreateRow(a, row, 0, n, Low, High);
    if (row < k - 1)
        CreateRows(a, row + 1, k, n, Low, High);
}

// ---------- Виведення ----------
void PrintRow(int** a, int row, int col, const int n)
{
    cout << setw(5) << a[row][col];
    if (col < n - 1)
        PrintRow(a, row, col + 1, n);
    else
        cout << endl;
}

void PrintRows(int** a, int row, const int k, const int n)
{
    PrintRow(a, row, 0, n);
    if (row < k - 1)
        PrintRows(a, row + 1, k, n);
    else
        cout << endl;
}

// ---------- Обчислення ----------
int RowMin(int** a, int row, int col, const int n)
{
    if (col == n - 1)
        return a[row][col];

    int nextMin = RowMin(a, row, col + 1, n);
    return (a[row][col] < nextMin) ? a[row][col] : nextMin;
}

int MaxOfRowMins(int** a, int row, const int k, const int n, int currentMax)
{
    if (row >= k)
        return currentMax;

    int rowMin = RowMin(a, row, 0, n);
    if (rowMin > currentMax)
        currentMax = rowMin;

    return MaxOfRowMins(a, row + 1, k, n, currentMax);
}
