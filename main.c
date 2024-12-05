#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Owner {
    char name[10];
    char age[3];
};

struct Vehicle {
    char vehicleType[10];
    char brand[10];
    char plateNumber[6];
    struct Owner owner;
};

int main(void) {
    int input = 1;

    while (input != 0) {
        printf("1. Add Vehicle\n2. Remove Vehicle\n3. Sort\n4. Show Vehicle\n5. Show Registry\n0. Quit\n>");

        char _input[3] = "";
        if (fgets(_input, 3, stdin) != NULL) {
            input = atoi(_input);

            if (input > 5 || input < 0) {
                printf("Invalid input, please try again.\n");
                continue;
            }

            switch (input) {
                case 1: {
                    struct Vehicle newVehicle;

                    printf("Vehicle type: ");
                    fgets(newVehicle.vehicleType, 10, stdin);
                    newVehicle.vehicleType[strcspn(newVehicle.vehicleType, "\n")] = '\0';

                    printf("Vehicle brand: ");
                    fgets(newVehicle.brand, 10, stdin);
                    newVehicle.brand[strcspn(newVehicle.brand, "\n")] = '\0';

                    printf("Vehicle plate number: ");
                    fgets(newVehicle.plateNumber, 6, stdin);
                    newVehicle.plateNumber[strcspn(newVehicle.plateNumber, "\n")] = '\0';

                    printf("Owner name: ");
                    fgets(newVehicle.owner.name, 10, stdin);
                    newVehicle.owner.name[strcspn(newVehicle.owner.name, "\n")] = '\0';

                    printf("Owner age: ");
                    fgets(newVehicle.owner.age, 3, stdin);
                    newVehicle.owner.age[strcspn(newVehicle.owner.age, "\n")] = '\0';

                    break;
                }

                case 2:
                    printf("Remove Vehicle functionality not implemented yet.\n");
                    break;
                case 3:
                    printf("Sort functionality not implemented yet.\n");
                    break;
                case 4:
                    printf("Show Vehicle functionality not implemented yet.\n");
                    break;
                case 5:
                    printf("Show Registry functionality not implemented yet.\n");
                    break;
            }
        }
    }
    return 0;
}
