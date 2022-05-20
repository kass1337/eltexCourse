#include "stdio.h" 
#include "stdlib.h"
#include <dlfcn.h>
int main(int argc, char* argv[]) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    extern int sum(int a, int b);
    extern int power2(int a);
    printf("Sum = %d\n", sum(a, b));
    printf("Power 2 = %d\n", power2(a));
    printf("Power 2 = %d\n", power2(b)); 
    void* lib;
    lib = dlopen("eltex_lib/libDL.so", RTLD_LAZY);
    if (!lib) {
        printf("Error!\n");
        return 1;
    }
    int (*sumd)() = dlsym(lib, "sum");
    int (*power2d)() = dlsym(lib, "power2");
    printf("Sum of dynamic2 = %d\n", (*sumd)(a,b));
    printf("Power 2 of dynamic2 = %d\n", (*power2d)(a));
    printf("Power 2 of dynamic2 = %d\n", (*power2d)(b));
    
    return 0;
}