#include <stdio.h>
#include <dlfcn.h>

void printMessage();

int main(){

    void *handle = dlopen("./libstringlibrary.so", RTLD_LAZY);
    if(!handle){
        printf("Error: %s\n", dlerror());
    }

    void (*lib_fun)();
    lib_fun = (void (*)())dlsym(handle,"printMessage");

    if(dlerror() != NULL){
        printf("Error: %s\n", dlerror());
    }

    (*lib_fun)();

    dlclose(handle);

    return 0;

}


