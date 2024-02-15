#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>
int global = 234;
int global2;
int main(){
    int a;
    while(1){
        printf("%d\n", getpid());
        printf("%p\n", &a);
        sleep(1);
    }
    return 0;
}
