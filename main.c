#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// TODO magic variables.
struct Owner {
    char name[10];
    char age[4];
};

struct Vehicle {
    char vehicleType[10];
    char brand[10];
    char plateNumber[6];
    struct Owner owner;
};

// TODO fix inputting numbers for age (int needed). The program should not crash.
// TODO adding a Vehicle when the amount is full.
void add_vehicle(FILE *registrationFile) {
    struct Vehicle newVehicle;

    printf("Vehicle type: ");
    fgets(newVehicle.vehicleType, sizeof(newVehicle.vehicleType), stdin);
    newVehicle.vehicleType[strcspn(newVehicle.vehicleType, "\n")] = '\0';

    printf("Vehicle brand: ");
    fgets(newVehicle.brand, sizeof(newVehicle.brand), stdin);
    newVehicle.brand[strcspn(newVehicle.brand, "\n")] = '\0';

    printf("Vehicle plate number: ");
    fgets(newVehicle.plateNumber, sizeof(newVehicle.plateNumber), stdin);
    newVehicle.plateNumber[strcspn(newVehicle.plateNumber, "\n")] = '\0';

    printf("Owner name: ");
    fgets(newVehicle.owner.name, sizeof(newVehicle.owner.name), stdin);
    newVehicle.owner.name[strcspn(newVehicle.owner.name, "\n")] = '\0';

    printf("Owner age: ");
    fgets(newVehicle.owner.age, sizeof(newVehicle.owner.age), stdin);
    newVehicle.owner.age[strcspn(newVehicle.owner.age, "\n")] = '\0';

    fwrite(&newVehicle, sizeof(struct Vehicle), 1, registrationFile);
}

void vehicle_register(FILE *registrationFile) {
    rewind(registrationFile);
    struct Vehicle newVehicle;
    int i = 1;
    printf("___________________________\n");

    while (fread(&newVehicle, sizeof(struct Vehicle), 1, registrationFile) == 1) {
        printf(
            "%d.\n\tPlate number: %s\n\tVehicle brand: %s\n\tVehicle type: %s\n___________________________\n",
            i, newVehicle.plateNumber, newVehicle.brand, newVehicle.vehicleType);
        i++;
    }
}

// TODO trying to search after car number -1 and 13.
// TODO fix searching after unsigned car.
void vehicle_search(FILE *registrationFile, char *_input, int *input) {
    rewind(registrationFile);
    struct Vehicle newVehicle;

    fgets(_input, 3, stdin);
    *input = atoi(_input) - 1;

    for (int j = 0; sizeof(struct Vehicle) > j; j++) {
        fseek(registrationFile, sizeof(struct Vehicle) * *input, SEEK_SET);
        fread(&newVehicle, sizeof(struct Vehicle), 1, registrationFile);
    }
    printf(
        "\n___________________________\nPlate number: %s\nVehicle brand: %s\nVehicle type: %s \nVehicle owner: %s\nOwner age: %s\n___________________________\n"
        , newVehicle.plateNumber, newVehicle.brand, newVehicle.vehicleType, newVehicle.owner.name,
        newVehicle.owner.age);
    *input = 1;
}

// TODO fix string input crashes the program.
int main(void) {
    FILE *registrationFile = fopen("registry.bin", "ab+");
    if (registrationFile == NULL) {
        printf("Failed to open file");
        exit(1);
    }

    int input = 1;

    while (input != 0) {
        printf("1. Add Vehicle\n2. Remove Vehicle\n3. Sort\n4. Show Vehicle\n5. Show Registry\n0. Quit\n>");

        char _input[3] = "";
        if (fgets(_input, 3, stdin) != NULL) {
            input = atoi(_input);

            switch (input) {
                case 1: add_vehicle(registrationFile);
                    break;
                case 2:
                    printf("Remove Vehicle functionality not implemented yet.\n");
                    break;
                case 3:
                    printf("Sort functionality not implemented yet.\n");
                    break;
                case 4: vehicle_search(registrationFile, _input, &input);
                    break;
                case 5: vehicle_register(registrationFile);
                    break;
                default: printf("Invalid input, please try again.\n\n");
            }
        }
    }
    fclose(registrationFile);
    return 0;
}
