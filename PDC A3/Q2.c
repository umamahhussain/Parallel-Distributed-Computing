#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>


int main() {
    int win = 0;
    int key = 111;
    int SIZE = 1000;
    double speedup=0;

    double start_time = omp_get_wtime(); // Get the start time

    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                int x = (i * i * 1000 / 35) % 1000;
                int y = (j * j * 1000 / 36) % 1000;
                int z = (k * k * 1000 / 37) % 1000;

                if (key == (x + y + z)) {
                    win++;
                }
            }
        }
    }
    double end_time = omp_get_wtime(); // Get the end time
    double seqTime=end_time-start_time;
    printf("\nExecution time without threads: %f seconds", end_time - start_time ) ;
    printf("\nTotal wins = %d\n", win);


win=0;
SIZE=1000;
key=111;


omp_set_num_threads(2);
start_time = omp_get_wtime(); // Get the start time

    #pragma omp parallel for reduction(+:win)
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                int x = (i * i * 1000 / 35) % 1000;
                int y = (j * j * 1000 / 36) % 1000;
                int z = (k * k * 1000 / 37) % 1000;

                if (key == (x + y + z)) {
                    win++;
                }
            }
        }
    }
    end_time = omp_get_wtime(); // Get the end time
    double parallelTime=end_time-start_time;
    printf("\n\nExecution time with 2 threads: %f seconds", parallelTime ) ;
    printf("\nTotal wins = %d\n", win);
    speedup=seqTime/parallelTime;
    printf("The speedup with 2 threads is: %f",speedup);


win=0;
SIZE=1000;
key=111;


    omp_set_num_threads(3);
    start_time = omp_get_wtime(); // Get the start time

    #pragma omp parallel for reduction(+:win)
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                int x = (i * i * 1000 / 35) % 1000;
                int y = (j * j * 1000 / 36) % 1000;
                int z = (k * k * 1000 / 37) % 1000;

                if (key == (x + y + z)) {
                    win++;
                }
            }
        }
    }

    end_time = omp_get_wtime(); // Get the end time
    parallelTime=end_time-start_time;
    printf("\n\nExecution time with 3 threads: %f seconds", parallelTime ) ;
    printf("\nTotal wins = %d\n", win);
    speedup=seqTime/parallelTime;
    printf("The speedup with 3 threads is: %f",speedup);


win=0;
SIZE=1000;
key=111;


    omp_set_num_threads(4);
    start_time = omp_get_wtime(); // Get the start time

    #pragma omp parallel for reduction(+:win)
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                int x = (i * i * 1000 / 35) % 1000;
                int y = (j * j * 1000 / 36) % 1000;
                int z = (k * k * 1000 / 37) % 1000;

                if (key == (x + y + z)) {
                    win++;
                }
            }
        }
    }

    end_time = omp_get_wtime(); // Get the end time
    parallelTime=end_time-start_time;
    printf("\n\nExecution time with 4 threads: %f seconds", parallelTime ) ;
    printf("\nTotal wins = %d\n", win);
    speedup=seqTime/parallelTime;
    printf("The speedup with 4 threads is: %f",speedup);

    return 0;
}
