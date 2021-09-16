#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.14159265358979323846;

struct pizza {
    char *name;
    float ppd;
    struct pizza* next;
};

//void sort(struct pizza *head) {
//    int 
//}

float calc_ppd(float *d, float *cost) {
    if (*d == 0 || *cost == 0) {
        return 0;
    }
    float area = *d * *d * PI;
    area = area / 4;
    return area / *cost;
}

struct pizza* add_pizza(char *name, float *ppd) {
    struct pizza *newPizza = (struct pizza*)malloc(sizeof(struct pizza));
    newPizza->name = name;
    newPizza->ppd = *ppd;
}

void printList(struct pizza *head) {
    struct pizza *curr = head;
    while (curr != NULL) {
        printf("%s %f\n", curr->name, curr->ppd);
        curr = curr->next;
    }
}

void freePizzas(struct pizza *head) {
    struct pizza *curr = head;
    struct pizza *next = NULL;
    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Syntax: arglen <file> \n");
        return EXIT_SUCCESS;
    }
    else {
        FILE *file;
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Was not able to open the file\n");
            return EXIT_SUCCESS;
        }
        // int c = fgetc(file);
        // if (c == EOF) {
        //     printf("PIZZA FILE IS EMPTY\n");
        //     return EXIT_SUCCESS;
        // }
        // ungetc(c, file);

        char pName[255];
        float d;
        float cost;
        struct pizza *head = NULL;
        struct pizza *curr;

        while(true) {
            if (fscanf(file, "%s", pName) == EOF) {
                printf("PIZZA FILE IS EMPTY\n");
                return EXIT_SUCCESS;
            }
            else if (strcmp(pName, "DONE") == 0) {
                printf("breaking\n");
                break;
            }
            else {
                if (fscanf(file, "%f", &d) == 1 && fscanf(file, "%f", &cost) == 1) {
                    float ppd = calc_ppd(&d, &cost);
                    if (head == NULL) {
                        head = (struct pizza*)malloc(sizeof(struct pizza));
                        head->name = pName;
                        head->ppd = ppd;
                        curr = head;
                        printf("CREATE HEAD: %s %f\n", head->name, head->ppd);
                    }
                    else {
                        curr->next = add_pizza(pName, &ppd);
                        curr = curr->next;
                    }
                    printf("%s %f\n", curr->name, curr->ppd);
                }
            }
            printf("HEAD: %s %f\n", head->name, head->ppd);
            printf("CURR: %s %f\n", curr->name, curr->ppd);
        }

        // while (fscanf(file, "%s", name) == 1 && fscanf(file, "%f", &d) == 1 && 
        // fscanf(file, "%f", &cost) == 1) {
        //     float ppd = calc_ppd(&d, &cost);
        //     if (head == NULL) {
        //         head = (struct pizza*)malloc(sizeof(struct pizza));
        //         head->name = name;
        //         head->ppd = ppd;
        //         curr = head;
        //         printf("null");
        //     }
        //     else {
        //         curr->next = add_pizza(name, &ppd);
        //         curr = curr->next;
        //     }
        //     printf("%s %f\n", curr->name, curr->ppd);
        // }
        printf("HEAD: %s %f\n", head->name, head->ppd);

        printList(head);
        freePizzas(head);
        fclose(file);

        return EXIT_SUCCESS;
    }
}