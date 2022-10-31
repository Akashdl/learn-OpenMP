#include<iostream>
#include<omp.h>

int main() {
    #pragma omp parallel
    {
        int rank = omp_get_thread_num();
        std::cout<<"Hello World: "<<rank<<"\n";
    }
}