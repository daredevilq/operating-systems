#include <stdio.h>

#ifndef DYNAMIC
    #include "collatz.h"
#endif //DYNAMIC

#ifdef DYNAMIC
    #include "dlfcn.h"
    int (*collatz_conjecture)(int input);
    int (*test_collatz_convergence)(int input, int max_iter);
#endif //DYNAMIC



int main(){
    #ifdef DYNAMIC
        void *handle = dlopen("./libdynamic.so", RTLD_LAZY);
        if(!handle){
            printf("Error: %s\n", dlerror());
        }

        test_collatz_convergence = dlsym(handle, "test_collatz_convergence");

        printf("(dynamic) Answer for %d is: %d\n", 15,test_collatz_convergence(15,1000));
        printf("(dynamic) Answer for %d is: %d\n", 31,test_collatz_convergence(31,1000));
        printf("(dynamic) Answer for %d is: %d\n", 27,test_collatz_convergence(27,1000));
        printf("(dynamic) Answer for %d is: %d\n", 43,test_collatz_convergence(43,1000));
        dlclose(handle);
    #endif //DYNAMIC

    #ifndef DYNAMIC
        printf("Answer for %d is: %d\n",21,test_collatz_convergence(21,1000));
        printf("Answer for %d is: %d\n",87,test_collatz_convergence(87,1000));
        printf("Answer for %d is: %d\n",63,test_collatz_convergence(63,1000));
        printf("Answer for %d is: %d\n",4,test_collatz_convergence(4,1000));
    #endif
    return 0;
}

