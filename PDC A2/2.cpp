#include <iostream>
#include <pthread.h>

using namespace std;

int **ResultMatrix;
int **Matrix1;
int **Matrix2;
int r1, c1, r2, c2;

int **MemoryAllocation(int r, int c)
{
    int **Matrix = new int *[r];
    for (int i = 0; i < r; i++)
    {
        Matrix[i] = new int[c];
    }
    return Matrix;
}

void InputMatrix(int **Matrix, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> Matrix[i][j];
        }
    }
}

void DisplayMatrix(int **Matrix, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << Matrix[i][j] << "      ";
        }
        cout << endl;
    }
}

void *MultiplyMatrices(void *arg)
{
    int row = *((int *)arg);
    cout << "Thread " << row << " has entered.\n";

    for (int i = 0; i < c2; i++)
    {
        ResultMatrix[row][i] = 0;
        for (int j = 0; j < r2; j++)
        {
            ResultMatrix[row][i] += Matrix1[row][j] * Matrix2[j][i];
        }
    }
    
    cout << "Thread " << row << " has finished.\n";
    return(NULL);
}


int main()
{
    // input size
    cout << "Please enter the row size of Matrix 1: ";
    cin >> r1;
    cout << "Please enter the column size of Matrix 1: ";
    cin >> c1;

    cout << "\nPlease enter the row size of Matrix 2: ";
    cin >> r2;
    cout << "Please enter the column size of Matrix 2: ";
    cin >> c2;

    if (c1 != r2)
    {
        cout << "\nMultiplication can not be performed sorry!!!";
        return 0;
    }

    pthread_t threads[r1];
    Matrix1 = MemoryAllocation(r1, c1);
    Matrix2 = MemoryAllocation(r2, c2);
    ResultMatrix = MemoryAllocation(r1, c2);

    // input the elements
    cout << "\nPlease enter the elements of Matrix 1: \n";
    InputMatrix(Matrix1, r1, c1);

    cout << "\nPlease enter the elements of Matrix 2: \n";
    InputMatrix(Matrix2, r2, c2);

    cout << "\nMatrix 1: \n";
    DisplayMatrix(Matrix1, r1, c1);
    cout << "\nMatrix 2: \n";
    DisplayMatrix(Matrix2, r2, c2);

    for (int i = 0; i < r1; i++)
    {
        int *arg = new int;
        *arg = i;
        pthread_create(&threads[i], NULL, MultiplyMatrices, (void *)arg);
    }

    for (int i = 0; i < r1; i++)
    {
        pthread_join(threads[i], NULL);
    }

    cout << "\nResult Matrix: \n";
    DisplayMatrix(ResultMatrix, r1, c2);

    return 0;
}
