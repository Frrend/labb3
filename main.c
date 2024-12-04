#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void carRegister(char vehicleType[10], char brand[10], char plateNumber[6], char name[10], char age_[3]) {
    printf("Vehicle owners name: ");
    fgets(name, 10, stdin);

    printf("Owners age: ");
    fgets(age_, 3, stdin);

    printf("Vehicle type: ");
    fgets(vehicleType, 10, stdin);

    printf("Car brand: ");
    fgets(brand, 10, stdin);

    printf("Vehicle plate number: ");
    fgets(plateNumber, 6, stdin);
}

int main(void) {
    char name[10];
    char age_[4];
    char vehicleType[10];
    char brand[10];
    char plateNumber[6];

    carRegister(vehicleType, brand, plateNumber, name, age_);
    int age = atoi(age_);

    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
    printf("Vehicle Type: %s\n", vehicleType);
    printf("Car Brand: %s\n", brand);
    printf("Plate Number: %s\n", plateNumber);
    return 0;
}
