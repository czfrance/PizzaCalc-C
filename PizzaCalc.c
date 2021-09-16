#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.14159265358979323846;

struct pizza {
    char name[65];
    float ppd;
    struct pizza* next;
};

float calc_ppd(float *d, float *cost) {
    if (*d == 0 || *cost == 0) {
        return 0;
    }
    float area = *d * *d * PI;
    area = area / 4;
    return area / *cost;
}

struct pizza* add_pizza(char *pName, float *ppd, struct pizza *head) {
    struct pizza *newPizza = (struct pizza*)malloc(sizeof(struct pizza));
    strcpy(newPizza->name, pName);
    newPizza->ppd = *ppd;
    newPizza-> next = head;
}

void printList(struct pizza *head) {
    struct pizza *curr = head;
    while (curr != NULL) {
        printf("%s %f\n", curr->name, curr->ppd);
        curr = curr->next;
    }
}

void swap(struct pizza *p1, struct pizza *p2) {
    char tempName[65]; 
    strcpy(tempName, p1->name);
    float tempPpd = p1->ppd;
    strcpy(p1->name, p2->name);
    p1->ppd = p2->ppd;
    strcpy(p2->name, tempName);
    p2->ppd = tempPpd;
}

void sort(struct pizza *head) {

    while (true) {
        struct pizza *curr = head;
        int count = 0;
        while (curr->next != NULL) {
            if (curr->ppd < curr->next->ppd) {
                swap(curr, curr->next);
                
                count++;
            }
            else if (curr->ppd == curr->next->ppd) {
                if (strcmp(curr->name, curr->next->name) > 0) {
                    swap(curr, curr->next);
                    count++;
                }
            }
            else {
                ;
            }
            curr = curr->next;
        }
        if (count == 0) {
            break;
        }
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

        struct pizza *head = NULL;
        char pName[65];
        float d;
        float cost;

        while(true) {
            if (fscanf(file, "%s", pName) == EOF) {
                printf("PIZZA FILE IS EMPTY\n");
                return EXIT_SUCCESS;
            }
            else if (strcmp(pName, "DONE") == 0) {
                break;
            }
            else {
                if (fscanf(file, "%f", &d) == 1 && fscanf(file, "%f", &cost) == 1) {
                    float ppd = calc_ppd(&d, &cost);
                    struct pizza *temp = add_pizza(pName, &ppd, head);
                    head = temp;
                }
            }
        }

        fclose(file);
        sort(head);
        printList(head);
        freePizzas(head);
        
        return EXIT_SUCCESS;
    }
}