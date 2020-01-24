#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

using namespace std;

const int matrixSize = 10;
void printMatrix(bool array[matrixSize][matrixSize]);
void printMatrix(int array[matrixSize][matrixSize]);
int count_neighbors(bool matrix[matrixSize][matrixSize], int x, int y);
void next_generation(bool matrix[matrixSize][matrixSize], bool *changeInMatrix);

// g++ gameoflife.cpp -o gameoflife -fopenmp && "/home/petr/VScode/C++/"gameoflife
int main(int argc, char const *argv[])
{
    bool cellMatrix[matrixSize][matrixSize] = {};
    bool tmpCellMatrix[matrixSize][matrixSize] = {};
    //fill random matrix

    srand(time(NULL));
    for (int i = 0; i < matrixSize; i++)
    {
        for (int p = 0; p < matrixSize; p++)
        {
            int tmp_rand = rand() % 99;
            if (tmp_rand < 35)
            {
                cellMatrix[i][p] = true;
            }
            else
            {
                cellMatrix[i][p] = false;
            }
        }
    }
    int i = 0;
    while (true)
    {
        bool changeInMatrix = false;
        printMatrix(cellMatrix);
        cout << endl;
        next_generation(cellMatrix, &changeInMatrix);

        if ((!changeInMatrix) || (i == 1000000))
        {
            break;
        }
        i++;
    }
    return 0;
}

int matrixEqaul(bool metrixA[][matrixSize], bool matrixB[][matrixSize])
{
    for (int i = 0; i < matrixSize; i++)
        for (int j = 0; j < matrixSize; j++)
            if (metrixA[i][j] != matrixB[i][j])
                return 0;
    return 1;
}

void printMatrix(bool matrix[matrixSize][matrixSize])
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int p = 0; p < matrixSize; p++)
        {
            if (matrix[i][p] == true)
            {
                cout << " X ";
            }
            else
            {
                cout << " . ";
            }
            if (p == matrixSize - 1)
            {
                cout << endl;
            }
        }
    }
}

void printMatrix(int matrix[matrixSize][matrixSize])
{
    for (int i = 0; i < matrixSize; i++)
    {
        for (int p = 0; p < matrixSize; p++)
        {
            cout << matrix[i][p];
            if (p == matrixSize - 1)
            {
                cout << endl;
            }
        }
    }
}

int count_neighbors(bool matrix[matrixSize][matrixSize], int x, int y)
{
    int live_count = 0;

    if ((x - 1 >= 0) && (y - 1 >= 0) && (x - 1 < matrixSize) && (y - 1 < matrixSize) && (matrix[x - 1][y - 1] == true)) // x-1 | y-1
    {
        live_count++;
    }
    if ((x >= 0) && (y - 1 >= 0) && (x < matrixSize) && (y - 1 < matrixSize) && (matrix[x][y - 1] == true)) // x | y-1
    {
        live_count++;
    }
    if ((x + 1 >= 0) && (y - 1 >= 0) && (x + 1 < matrixSize) && (y - 1 < matrixSize) && (matrix[x + 1][y - 1] == true)) // x+1 | y-1
    {
        live_count++;
    }
    if ((x - 1 >= 0) && (y >= 0) && (x - 1 < matrixSize) && (y < matrixSize) && (matrix[x - 1][y] == true)) // x-1 | y
    {
        live_count++;
    }
    if ((x + 1 >= 0) && (y >= 0) && (x + 1 < matrixSize) && (y < matrixSize) && (matrix[x + 1][y] == true)) // x+1 | y
    {
        live_count++;
    }
    if ((x - 1 >= 0) && (y + 1 >= 0) && (x - 1 < matrixSize) && (y + 1 < matrixSize) && (matrix[x - 1][y + 1] == true)) // x-1 | y+1
    {
        live_count++;
    }
    if ((x >= 0) && (y + 1 >= 0) && (x < matrixSize) && (y + 1 < matrixSize) && (matrix[x][y + 1] == true)) // x | y+1
    {
        live_count++;
    }
    if ((x + 1 >= 0) && (y + 1 >= 0) && (x + 1 < matrixSize) && (y + 1 < matrixSize) && (matrix[x + 1][y + 1] == true)) // x+1 | y+1
    {
        live_count++;
    }

    return live_count;
}

void next_generation(bool matrix[matrixSize][matrixSize], bool *changeInMatrix)
{
    int evaluateMatrix[matrixSize][matrixSize] = {};
    int p, i = 0;
#pragma omp parallel for private(i, p)
    for (int i = 0; i < matrixSize; i++)
    {
        for (int p = 0; p < matrixSize; p++)
        {
            evaluateMatrix[i][p] = count_neighbors(matrix, i, p);
        }
    }
    // printMatrix(evaluateMatrix);
    // new generation
    *changeInMatrix = false;
#pragma omp parallel for private(i, p)
    for (int i = 0; i < matrixSize; i++)
    {
        for (int p = 0; p < matrixSize; p++)
        {
            if ((evaluateMatrix[i][p] < 2) && (matrix[i][p] == 1))
            {
                *changeInMatrix = true;
                matrix[i][p] = false;
            }
            else if (((evaluateMatrix[i][p] == 2) || (evaluateMatrix[i][p] == 3)) && (matrix[i][p] == 1))
            {
                matrix[i][p] = true;
            }
            else if ((evaluateMatrix[i][p] >= 3) && (matrix[i][p] == 1))
            {
                *changeInMatrix = true;
                matrix[i][p] = false;
            }
            else if ((evaluateMatrix[i][p] == 3) && (matrix[i][p] == 0))
            {
                *changeInMatrix = true;
                matrix[i][p] = true;
            }
        }
    }
}
