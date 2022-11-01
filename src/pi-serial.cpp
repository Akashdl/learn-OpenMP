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

int main() {
    const int start{0}, end{1};
    const int num_steps = 10'00'00'000;
    const double step_size = (end - start) / (double)num_steps;
    double x, pi{0}, sum{0};
    double start_time, run_time;
    
    start_time = omp_get_wtime();
    for (int i = 0; i < num_steps; ++i) {
        x = (i + 0.5) * step_size; // center of the step
        sum += 4.0 / ( 1.0 + x*x);
    }
    pi += sum * step_size;

    run_time = omp_get_wtime() - start_time;
    std::cout<<"Pi is: "<<pi<<"\nStep size is: "<<step_size<<"\nRun time in seconds is: "<<run_time<<"\n";
}