#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0

//global variables
char cities[MAX_CITIES][50]; //  length of city name is 50 characters
int distance[MAX_CITIES][MAX_CITIES];
int cityCount = 0;

char vehicleTypes[3][20] = {"Van", "Truck", "Lorry"};
int vehicleCapacity[3] = {1000, 5000, 10000};
int vehicleRate[3] = {30, 40, 80};
int vehicleSpeed[3] = {60,50, 45};
int vehicleEfficiency[3] = {12, 6,4 };

void displayMenu(){
    printf("LOGISTIC MANAGEMENT SYSTEM\n\n");
    printf("1. Add City\n");
    printf("2. Rename City\n");
    printf("3. Remove City\n");
    printf("4. Display Cities\n");
    printf("5. Input Distance\n");
    printf("6. Display Distance Table\n");
    printf("7. Process Delivery Request\n");
    printf("8. Find Least-Cost Route\n");
    printf("9. View Reports\n");
    printf("10. Exit\n");
}

int main()
{

    return 0;
}
