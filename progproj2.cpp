#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <ctime>

int main() {
    srand ( time(NULL) );
    int arr[20];
    for(int i = 0; i <= 20; i++){

        arr[i] =  (rand() % 100);
        
     }
 for(int i = 0 ; i < 20 ; i++){
     printf("%d\n" ,arr[i]);
 }
    int start, end;
    int arrsize = sizeof(arr) / sizeof(int);
    printf("array size: %d\n", 20);
    int fd[2];

    if (pipe(fd) == -1) {
        return 1;
    }

    int id = fork();
    if (id == -1) {
        return 2;
    }

    if (id == 0) {
        // Child process
        start = arrsize / 2;
        end = arrsize;
        printf("child loop from 0 to 10\n");
    } else {
        // Parent process
        start = 0;
        end = arrsize / 2;
        printf("parent loop from 11 to 20\n");
    }

    int min = INT_MAX;
    for (int i = start; i < end; i++) {
        if (arr[i] < min && arr[i] >= 0 && arr[i] <= 10) {
            min = arr[i];
        }
    }

    printf("calculated min: %d\n", min);

    if (id == 0) {
        // Child process
        printf("child's process id is %d\n", getpid());
        write(fd[1], &min, sizeof(min));
        close(fd[1]);
    } else {
        // Parent process
        printf("parent's process id is %d\n", getpid());
        close(fd[1]);
        int childMin;
        read(fd[0], &childMin, sizeof(int));
        close(fd[0]);
        int overallMin;
        if (min > childMin){
            overallMin = childMin;
        } else {
            overallMin = min;
        }
        printf("Overall minimum is: %d\n", overallMin);
    }

    return 0;
}