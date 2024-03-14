#include "collatz.h"
#include <stdio.h>

int collatz_conjecture(int input){
    if (input % 2 == 0) return input / 2;
    else return 3 * input + 1;
    
}

int test_collatz_convergence(int input, int max_iter){
    for (int i = 0; i < max_iter; i++){
        if (input == 1) return i;
        input = collatz_conjecture(input);
    }
    return -1;
}

