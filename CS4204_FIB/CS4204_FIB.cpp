// gcc example.c -o example


#include<omp.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include "fibonacci.h"
#include <vector>


int main()
{
    clock_t t1 = clock();
    int res, res2;
    omp_set_num_threads(8);
    printf("Begin\n");

#pragma omp parallel for num_threads(10) default(shared) linear(i)  schedule(dynamic,5) 
    for (int i = 0; i < 100; i++) {
        res = payload1(i);
        res2 = payload2(res);

    

//#pragma omp parallel for private(res, res2) //将 res 和 res2 声明为私有变量，以防止潜在的竞争条件
//    for (int i = 0; i < 100; i++) {
//         res = payload1(i);
//         res2 = payload2(res);
//
#pragma omp critical//critical 指令确保在同一时刻只有一个线程执行被保护的代码段。
        {
            printf("%d\n", i);
        }
    }

    clock_t t2 = clock();
    printf("End");
    std::cout << "time: " << t2 - t1 << std::endl;
}
