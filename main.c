#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <_mingw_mac.h>

#define MAX_INPUT_SIZE 32
#define MAX_VEHICLE_AMOUNT 10

struct Owner {
    char name[MAX_INPUT_SIZE];
    int age;
};

struct Vehicle {
    char vehicleType[MAX_INPUT_SIZE];
    char brand[MAX_INPUT_SIZE];
    char plateNumber[MAX_INPUT_SIZE];
    struct Owner owner;
};

void add_vehicle(FILE *registrationFile) {
    struct Vehicle newVehicle;

    if (ftell(registrationFile) / sizeof(struct Vehicle) >= MAX_VEHICLE_AMOUNT) {
        printf("You have reached the max car amount\n");
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
    int looper = 1;
    while (looper) {
        char _age[MAX_INPUT_SIZE];
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

void vehicle_delete(FILE *registrationFile) {
    printf("Vehicle position to delete: ");
    int delete = 0;
    int looper = 1;
    while (looper) {
        char _delete[MAX_INPUT_SIZE];
        fgets(_delete, sizeof(_delete), stdin);
        if (isdigit(*_delete) == 0) {
            printf("Input must be a digit\n> ");
            continue;
        }
        delete = atoi(_delete) - 1;
        looper = 0;
    }

    struct Vehicle newVehicle;
    struct Vehicle carList[MAX_VEHICLE_AMOUNT];
    int vehicleCount = 0;

    while (fread(&newVehicle, sizeof(struct Vehicle), 1, registrationFile) == 1) {
        carList[vehicleCount] = newVehicle;
        vehicleCount++;
    }

    for (int i = delete; i < vehicleCount - 1; i++) {
        carList[i] = carList[i + 1];
    }

    FILE *deleteFromFile = fopen("registry.bin", "wa");

    for (int i = 0; i < vehicleCount - 1; i++) {
        fwrite(&carList[i], sizeof(struct Vehicle), 1, deleteFromFile);
    }
    fclose(deleteFromFile);
}

void vehicle_sorter(FILE *registrationFile) {
    struct Vehicle newVehicle;
    struct Vehicle carList[MAX_VEHICLE_AMOUNT];
    int vehicleCount = 0;

    while (fread(&newVehicle, sizeof(struct Vehicle), 1, registrationFile) == 1) {
        carList[vehicleCount] = newVehicle;
        vehicleCount++;
    }

    for (int i = 0; 10 > i; i++) {
        for (int j = 0; j < strlen(carList[j].brand); j++) {
            carList[i].brand[j] = tolower(carList[i].brand[j]);
        }
    }

    for (int i = 0; i < vehicleCount - 1; i++) {
        for (int j = 0; j < vehicleCount - 1 - i; j++) {
            if (strcmp(carList[j].brand, carList[j + 1].brand) > 0) {
                struct Vehicle holder = carList[j];
                carList[j] = carList[j + 1];
                carList[j + 1] = holder;
            }
        }
    }

    printf("\n___________________________\n");
    for (int i = 0; i < vehicleCount; i++) {
        printf(
            "Plate number: %s\nVehicle brand: %s\nVehicle type: %s \nVehicle owner: %s\nOwner age: %d\n___________________________\n"
            , carList[i].plateNumber, carList[i].brand, carList[i].vehicleType, carList[i].owner.name,
            carList[i].owner.age);
    }
}

void vehicle_search(FILE *registrationFile) {
    struct Vehicle newVehicle;
    char _vehicleIndex[MAX_INPUT_SIZE];

    fgets(_vehicleIndex, sizeof(_vehicleIndex) - 1, stdin);
    int vehicleIndex = atoi(_vehicleIndex) - 1;

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

void vehicle_register(FILE *registrationFile) {
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


int main(void) {
    FILE *registrationFile = fopen("registry.bin", "ab+");
    if (registrationFile == NULL) {
        printf("Failed to open file");
        exit(1);
    }

    char _input[MAX_INPUT_SIZE] = "";

    while (1) {
        rewind(registrationFile);
        printf("1. Add Vehicle\n2. Remove Vehicle\n3. Sort\n4. Show Vehicle\n5. Show Registry\n0. Quit\n>");
        if (fgets(_input, sizeof(_input) - 1, stdin) == NULL) continue;

        // Can you use this?
        if (isdigit(*_input) == 0) {
            puts("Invalid input, please try again.\n");
            continue;
        }

        int input = atoi(_input);

        switch (input) {
            case 1: add_vehicle(registrationFile);
                break;
            case 2: vehicle_delete(registrationFile);
                break;
            case 3: vehicle_sorter(registrationFile);
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
