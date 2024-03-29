#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

void display(int arr[100][100],int size)
{
for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            cout<<arr[i][j]<<"\t";
        }
        cout<<endl;
    }
}

int main()
{
    int size=100;
    int array1[100][100]={0};
    int array2[100][100]={0};
    int result[100][100]={0};
    

    #pragma omp parallel for
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
        array1[i][j]=rand()%10+1;
        array2[i][j]=rand()%10+1;
        }
    }

    cout<<"Array 1: \n";
    display(array1,size);

    cout<<"Array 2: \n";
    display(array1,size);


//serial execution
double start_time = omp_get_wtime();
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            for(int k=0;k<size;k++)
            {
                result[i][j]+=array1[i][k]*array2[k][j];
            }
        }
    }
double end_time = omp_get_wtime(); // Get the end time
cout<<"\nExecution time without threads: "<< end_time - start_time;


cout<<"\n\nCOURSE GRAINED:\n";


//parallel execution with default scheduling
start_time = omp_get_wtime();
#pragma omp parallel for
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            for(int k=0;k<size;k++)
            {
                result[i][j]+=array1[i][k]*array2[k][j];
            }
        }
    }
end_time = omp_get_wtime(); // Get the end time
cout<<"\nExecution time with default scheduling is: "<< end_time - start_time;




//parallel execution with static scheduling
start_time = omp_get_wtime();
#pragma omp parallel for schedule(static)
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            for(int k=0;k<size;k++)
            {
                result[i][j]+=array1[i][k]*array2[k][j];
            }
        }
    }
end_time = omp_get_wtime(); // Get the end time
cout<<"\nExecution time with static scheduling is: "<< end_time - start_time;



//parallel execution with dynamic scheduling
start_time = omp_get_wtime();
#pragma omp parallel for schedule(dynamic)
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            for(int k=0;k<size;k++)
            {
                result[i][j]+=array1[i][k]*array2[k][j];
            }
        }
    }
end_time = omp_get_wtime(); // Get the end time
cout<<"\nExecution time with dynamic scheduling is: "<< end_time - start_time;





cout<<"\n\nFINE GRAINED:\n";

//parallel execution with default scheduling
start_time = omp_get_wtime();
#pragma omp parallel for num_threads(size)
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            for(int k=0;k<size;k++)
            {
                result[i][j]+=array1[i][k]*array2[k][j];
            }
        }
    }
end_time = omp_get_wtime(); // Get the end time
cout<<"\nExecution time with default scheduling is: "<< end_time - start_time;



//parallel execution with static scheduling
start_time = omp_get_wtime();
#pragma omp parallel for schedule(static,1)
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            for(int k=0;k<size;k++)
            {
                result[i][j]+=array1[i][k]*array2[k][j];
            }
        }
    }
end_time = omp_get_wtime(); // Get the end time
cout<<"\nExecution time with static scheduling is: "<< end_time - start_time;



//parallel execution with dynamic scheduling
start_time = omp_get_wtime();
#pragma omp parallel for schedule(dynamic,1)
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            for(int k=0;k<size;k++)
            {
                result[i][j]+=array1[i][k]*array2[k][j];
            }
        }
    }
end_time = omp_get_wtime(); // Get the end time
cout<<"\nExecution time with dynamic scheduling is: "<< end_time - start_time;



    cout<<"\n\nOutput Array: \n";
    display(result,size);
   


}