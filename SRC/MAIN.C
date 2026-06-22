#include <stdio.h>

int main(void){
    #ifdef DEBUG
        printf("Hello world DEBUG!\n");
    #else
        printf("Hello world RELEASE!\n");
    #endif
    return 0;
}