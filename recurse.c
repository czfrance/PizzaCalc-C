#include <stdio.h>
#include <stdlib.h>

int calc_f(int n) {
    if (n == 0) {
        return 2;
    }

    int eqn = 3*(n-1)+1;

    int result = eqn + calc_f(n-1);

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Syntax: arglen <int> \n");
        return EXIT_SUCCESS;
    }
    else {
        int n;
        int check = sscanf(argv[1], "%d", &n);
        
        if (check == 0) {
            printf("Input not accepted. Please pass a positive integer \n");
            return EXIT_SUCCESS;
        }

        printf("%d \n", calc_f(n));
        
        return EXIT_SUCCESS;
    }
}

