#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int input = 1;
    int vehiclelist[10];

    struct owner {
        char name[10];
        char age[3];
    };

    struct vehicle {
        char vehicleType[10];
        char brand[10];
        char plateNumber[6];
        struct owner owner;
    };

    printf("1. Add Vehicle\n2. Remove Vehicle\n3. Sort\n4. Show Vehicle\n5. Show Registry\n0. Quit\n>");

    while (input != 0) {
        char _input[2];
        fgets(_input, 2, stdin);
        input = atoi(_input);

        if (input > 5 || input < 0) {
            continue;
        }

        switch (input) {
            case 1:
                struct vehicle new;
                printf("Vehicle type: ");
                fgets(new.vehicleType, 10, stdin);

                printf("Vehicle brand: ");
                fgets(new.brand, 10, stdin);

                printf("Vehicle plate number: ");
                fgets(new.plateNumber, 6, stdin);

                printf("Owner name: ");
                fgets(new.owner.name, 10, stdin);

                printf("Owner age: ");
                fgets(new.owner.age, 3, stdin);
                break;


            case 2: printf("2");
                break;
            case 3: printf("3");
                break;
            case 4: printf("4");
                break;
            case 5: printf("5");
                break;
            case 0: return 0;
        }
    }
}
