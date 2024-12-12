#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <_mingw_mac.h>

// TODO magic variables.
struct Owner {
    char name[32];
    int age;
};

struct Vehicle {
    char vehicleType[32];
    char brand[32];
    char plateNumber[32];
    struct Owner owner;
};

void add_vehicle(FILE *registrationFile) {
    struct Vehicle newVehicle;

    fseek(registrationFile, 0, SEEK_END);
    if (ftell(registrationFile) / sizeof(struct Vehicle) >= 10) {
        printf("you have reached the max car amount\n");
        return;
    }

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
    int age = 0;
    char _age[32];
    int looper = 1;
    while (looper) {
        fgets(_age, sizeof(newVehicle.owner.age), stdin);
        if (isdigit(*_age) == 0) {
            printf("Input must be a digit\n> ");
            continue;
        }
        age = atoi(_age);
        looper = 0;
    }
    newVehicle.owner.age = age;

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

void vehicle_search(FILE *registrationFile) {
    rewind(registrationFile);
    struct Vehicle newVehicle;
    char _vehicleIndex[32];

    fgets(_vehicleIndex, sizeof(_vehicleIndex) - 1, stdin);
    const int vehicleIndex = atoi(_vehicleIndex) - 1;

    fseek(registrationFile, sizeof(struct Vehicle) * vehicleIndex, SEEK_SET);
    if (fread(&newVehicle, sizeof(struct Vehicle), 1, registrationFile) != 1) {
        printf("No vehicle found at the given number.\n");
        return;
    }

    printf(
        "\n___________________________\nPlate number: %s\nVehicle brand: %s\nVehicle type: %s \nVehicle owner: %s\nOwner age: %d\n___________________________\n"
        , newVehicle.plateNumber, newVehicle.brand, newVehicle.vehicleType, newVehicle.owner.name,
        newVehicle.owner.age);
}

int main(void) {
    FILE *registrationFile = fopen("registry.bin", "ab+");
    if (registrationFile == NULL) {
        printf("Failed to open file");
        exit(1);
    }

    char _input[32] = "";

    while (1) {
        printf("1. Add Vehicle\n2. Remove Vehicle\n3. Sort\n4. Show Vehicle\n5. Show Registry\n0. Quit\n>");
        if (fgets(_input, sizeof(_input) - 1, stdin) != NULL) {
            // Can you use this?
            if (isdigit(*_input) == 0) {
                puts("Invalid input, please try again.\n");
                continue;
            }
            int input = atoi(_input);

            switch (input) {
                case 1: add_vehicle(registrationFile);
                    break;
                case 2:
                    printf("Remove Vehicle functionality not implemented yet.\n");
                    break;
                case 3:
                    printf("Sort functionality not implemented yet.\n");
                    break;
                case 4: vehicle_search(registrationFile);
                    break;
                case 5: vehicle_register(registrationFile);
                    break;
                case 0: fclose(registrationFile);
                    return 0;
                default: printf("Invalid input, please try again.\n\n");
            }
        }
    }
}
