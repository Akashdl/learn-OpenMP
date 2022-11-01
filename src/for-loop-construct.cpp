#include<iostream>
#include<omp.h>

#define NTHREADS 10

int main() {
    size_t array_size{1'00'000};
    int a[array_size] = {1}, b[array_size] = {2}, c[array_size] = {0};

    omp_set_num_threads(NTHREADS);
    double tdata = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for
            for (size_t i = 0; i < array_size; i++)
                c[i] = a[i] + b[i];
    }
    tdata = omp_get_wtime() - tdata;
    std::cout<<"Time took in sec: "<<tdata<<"\n";
}