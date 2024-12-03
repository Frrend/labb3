#include <stdio.h>

void asd(int *age, int *place) {
    scanf("%d", &age[*place]);
    *place += 1;
}

int main(void) {
    int input = -1;
    int place = 0;
    int age[10];
    while (input != 0) {
        printf("Input: ");
        scanf("%d", &input);

        asd(&input, &place);

        printf("%d", age[0]);

    }
    return 0;
}
