#include <omp.h>
#include <stdio.h>
#include <cstdio>
#include "simpson.cc"
#include <ctime>
#include <iostream>
#include <chrono>
#include <math.h>
#include "tqueue.h"
#include "q.h"
#include "product_record.h"
double add(double);
double f(double);

double bbp(double y)
{
    y=(16.0*y - 16.0) / (pow(y,4.0) - 2*pow(y,3.0) + 4.0*y - 4.0);
    return y;
}
double bbp2(double x)
{
    x = 4.0/(1.0+pow(x,2.0));
    return x;
}
int main()
{
    static double pi = 3.141592653589793238462643383279502884197169399375105820974944592307816406286;
    int a = 0, b=1;
    double n;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    n = simpson(&bbp2, a,b,100);
    /*#pragma omp parallel for shared(n)
    for (int i = 0; i <4 ; i++ )
    {
        if (omp_get_thread_num()==0)
        {
            printf( "thread 1 %i\n" ,omp_get_thread_num());
            #pragma omp atomic
            n += simpson(&bbp, 0.0,0.25,2500000);
        }
        else if(omp_get_thread_num()==1)
        {
            printf( "thread 2 %i\n" ,omp_get_thread_num());
            #pragma omp atomic
            n += simpson(&bbp, 0.25,0.5,2500000);
        }
        else if(omp_get_thread_num()==2)
        {
            printf( "thread 3 %i\n" ,omp_get_thread_num());
            #pragma omp atomic
            n += simpson(&bbp, 0.5,0.75,2500000);
        }
        else if(omp_get_thread_num()==3)
        {
            printf( "thread 4 %i\n" ,omp_get_thread_num());
            #pragma omp atomic
            n += simpson(&bbp, 0.75,1.0,2500000);
        }
    }*/

    end = std::chrono::system_clock::now();
    printf("\nintegral from %i to %i = %0.40f\n+                 pi = %0.40f\n",a,b,n,pi);

    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout  << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
double add(double a)
{
    #pragma omp atomic
    a = a + 1;
    return a;
}
double f(double x)
{
    return x = x*x;
}

