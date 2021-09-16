#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Syntax: arglen <int> \n");
        return EXIT_SUCCESS;
    }
    else {
        int runs = atoi(argv[1]);
        
        if (runs <= 0) {
            printf("Input not accepted. Please pass a positive integer \n");
            return EXIT_SUCCESS;
        }

        for (int i = 1; i <= runs; i++) {
            int num = 7 * i;
            printf("%d \n", num);
        }
        return EXIT_SUCCESS;
    }

}