#include <stdio.h>
#include <string.h>

int main() {
    char word[] = "hello";
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            printf(" ");
        }
        for (int k = 0; k <= i; k++) {
            printf("%c ", word[k]);
        }
        printf("\n");
    }

    return 0;
}

//save
/////save 2
