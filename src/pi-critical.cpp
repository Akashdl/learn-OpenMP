/*

This program will numerically compute the integral of

                  4/(1+x*x) 
				  
from 0 to 1.  The value of this integral is pi -- which 
is great since it gives us an easy way to check the answer.
             N
             __
            \    F(x_i) * delta_x
            /__           
             0

*/

#include<iostream>
#include<omp.h>

#define NTHREADS 10

int main() {
    const int start{0}, end{1};
    const int num_steps = 10'00'00'000;
    const double step_size = (end - start) / (double)num_steps;
    int actual_nthreads;
    double pi{0}, sum{0};
    double start_time, run_time;

    omp_set_num_threads(NTHREADS);
    
    start_time = omp_get_wtime();
    #pragma omp parallel
    {
        int rank = omp_get_thread_num();
        int numthreads = omp_get_num_threads();
        double x{0}, partial_sum{0};

        if(rank == 0) actual_nthreads = numthreads; // rank 0 is writing to avoid data race

        for (int i = rank; i < num_steps; i += numthreads) {
            x = (i + 0.5) * step_size;
            partial_sum += 4.0 / ( 1.0 + x*x);
        }
        #pragma omp critical
        {
            sum += partial_sum;
        }
    }
    
    pi += sum * step_size;

    run_time = omp_get_wtime() - start_time;
    std::cout<<"Pi is: "<<pi<<"\nStep size is: "<<step_size<<"\nRun time in seconds is: "<<run_time<<"\n";
}