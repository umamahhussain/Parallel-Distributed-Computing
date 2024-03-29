#include <iostream>
#include <ctime>
#include <vector>
#include <unistd.h>
#include <omp.h>
#include <cmath>
using namespace std;

int main()
{

int P=0;
int N=0;
vector<int> odd;

cout<<"Enter Num of Proc: ";
cin>>P;
cout<<"Enter Num of Iterations: ";
cin>>N;

int ChunkSize=N/P;  // Number of iterations each thread will execute
cout<<"\nChunk Size is: "<<N<<"/"<<P<<" : " <<ChunkSize<<endl;

omp_set_num_threads(P);

int loop=ceil(sqrt(N));
cout<<"The loop will iterate upto: "<<loop;
int i=0;
int j=0;

#pragma omp parallel for private(i,j) schedule(static,ChunkSize)
for(int i=3;i<loop;i++) 
{
    bool prime=true;
    for(int j=2;j<i;j++)
    {
        if(i%j==0)
        {
          prime=false;
        } 
    }
    if (prime) 
    {
        #pragma omp critical
        odd.push_back(i);
    }
    
}

 cout << "\n\nThe array of odd prime numbers is as follows: ";
    for (auto it = odd.begin(); it != odd.end(); ++it) {
        cout << *it << " ,";
    }
}