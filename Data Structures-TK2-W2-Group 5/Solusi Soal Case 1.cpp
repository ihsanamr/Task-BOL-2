#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct stack {
    char data;
    struct stack* next;
};

struct stack* top = NULL;

struct stack* push(struct stack* top, char val) {
    struct stack* ptr = (struct stack*)malloc(sizeof(struct stack));
    ptr->data = val;
    ptr->next = top;
    top = ptr;
    return top;
}

char pop(struct stack** top) {
    if (*top == NULL) {
        return '\0';
    }
    struct stack* temp = *top;
    *top = (*top)->next;
    char popped = temp->data;
    free(temp);
    return popped;
}

void reverse(char str[]) {
    int n = strlen(str);
    struct stack* top = NULL;
    for (int i = 0; i < n; i++) {
        top = push(top, str[i]);
    }
    for (int i = 0; i < n; i++) {
        str[i] = pop(&top);
    }
}

int countWords(char str[]) {
    int count = 0;
    int i = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ' && str[i + 1] != ' ') {
            count++;
        }
    }
    return count + 1;
}

int main() {
    char input[1000];
    char choice[100];

    printf("=======================\n");
    printf("Program Reverse Kalimat\n");
    printf("=======================\n");

    do {
        do {
            printf("\nMasukkan kalimat yang ingin dibalik (minimal 5 kata): ");
            scanf(" %[^\n]", input); getchar();
            printf("\n-----------------------------------------------\n");
            int wordCount = countWords(input);
            if (wordCount < 5) {
                printf("Invalid. Silakan coba lagi sesuai ketentuan.\n");
                printf("-----------------------------------------------\n");
            } else {
                break;
            }
        } while (1);

        reverse(input);
        printf("Kalimat yang dibalik: %s\n", input);
        printf("-----------------------------------------------\n\n");

        do {
            printf("Apakah Anda ingin mencoba lagi? (yes/no): ");
            scanf(" %[^\n]", choice); getchar();
            printf("\n-----------------------------------------------\n");
            
            for (int i = 0; choice[i]; i++) {
                choice[i] = tolower(choice[i]);
            }

            if (strcmp(choice, "yes") != 0 && strcmp(choice, "no") != 0) {
                printf("Invalid. Masukkan 'yes' atau 'no'.\n");
                printf("-----------------------------------------------\n\n");
            } else {
                break;
            }
        } while (1);

    } while (strcmp(choice, "yes") == 0);

    return 0;
}

