#include <iostream>
#include <pthread.h>
#include <algorithm>

using namespace std;

int **Matrix1;
int r1, c1;
int sum = 0;

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

int partition(int arr[], int start, int end)
{
    int pivot = arr[start];
    int i = start;
    for (int j = start + 1; j <= end; j++)
    {
        if (arr[j] >= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[start], arr[i]);
    return i;
}

void quickSort(int arr[], int start, int end)
{
    if (start < end)
    {
        int p = partition(arr, start, end);
        quickSort(arr, start, p - 1);
        quickSort(arr, p + 1, end);
    }
}

void *sortRow(void *arg)
{
    int row = *(int *)arg;
    cout << "Thread " << row << " has entered.\n";
    quickSort(Matrix1[row], 0, c1 - 1);

    // Calculate the sum of the sorted row
    int rowSum = 0;
    for (int i = 0; i < c1; i++)
    {
        rowSum += Matrix1[row][i];
    }

    // Add the sum of this row to the total sum
    sum += rowSum;
    cout << "Thread " << row << " has finished.\n";

    return NULL;
}

int main()
{
    // input size
    cout << "Please enter the row size of Matrix 1: ";
    cin >> r1;
    cout << "Please enter the column size of Matrix 1: ";
    cin >> c1;

    pthread_t threads[r1];
    Matrix1 = MemoryAllocation(r1, c1);

    // input the elements
    cout << "\nPlease enter the elements of Matrix 1: \n";
    InputMatrix(Matrix1, r1, c1);

    cout << "\nMatrix 1: \n";
    DisplayMatrix(Matrix1, r1, c1);

    // Sorting each row using pthreads
    for (int i = 0; i < r1; i++)
    {
        int *row = new int;
        *row = i;
        pthread_create(&threads[i], NULL, sortRow, (void *)row);
    }

    // Waiting for threads to finish
    for (int i = 0; i < r1; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Displaying sorted matrix
    cout << "\nResult Matrix: \n";
    DisplayMatrix(Matrix1, r1, c1);
    cout << "\nSum is: " << sum;


    return 0;
}
