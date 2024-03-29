#include <iostream>
#include <cstdlib>
#include <omp.h>
using namespace std;

int main()
{
    int size=0;
    cout<<"Please enter the size of the array: ";
    cin>>size;
    int key=0;
    cout<<"\nEnter the key: ";
    cin>>key;

    int*arr=new int[size];
    for(int i=0;i<size;i++)
    {
        arr[i]=rand()%size+1;
        cout<<arr[i]<<" ";
    }

    int found=0;

    #pragma omp parallel for reduction(+:found)
    for(int i=0;i<size;i++)
    {
        // cout<<"\nHello from thread ID: "<<omp_get_thread_num();
        if(arr[i]==key)
        {
            found++;
        }
    }

    cout<<"\nThe number of times key was found is: "<<found;

}