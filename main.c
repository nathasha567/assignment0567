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

// global variables
char deliverySource[MAX_DELIVERIES][50];
char deliveryDestination[MAX_DELIVERIES][50];
int deliveryDistance[MAX_DELIVERIES];
int deliveryWeight[MAX_DELIVERIES];
int deliveryVehicleType[MAX_DELIVERIES];
double deliveryCost[MAX_DELIVERIES];
double deliveryFuelCost[MAX_DELIVERIES];
double deliveryTotalCost[MAX_DELIVERIES];
double deliveryProfit[MAX_DELIVERIES];
double deliveryCustomerCharge[MAX_DELIVERIES];
double deliveryTime[MAX_DELIVERIES];
int deliveryCount = 0;

//functions
void displayMenu();
void addCity();
void displayCities();
void renameCity();
void removeCity();
void inputDistance();

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

void addCity(){
    if(cityCount >= MAX_CITIES){
        printf("Maximum city limit reached...\n");
        return;
    }

    char newCity[50];
    printf("Enter city name : ");
    fgets(newCity, 50, stdin);
    newCity[strcspn(newCity, "\n")] = 0;

    for(int i=0; i<cityCount; i++){
        if(strcmp(cities[i], newCity) == 0){
            printf("City already exists...\n");
            return;
        }
    }
    strcpy(cities[cityCount], newCity);

    //distance
    for(int i=0; i<=cityCount; i++){
        distance[cityCount][i] = 0;
        distance[i][cityCount] = 0;
    }
    cityCount++;
    printf("City '%s' added successfully...\n",newCity);
}

void displayCities(){
    if(cityCount == 0){
        printf("No Cities Available...\n");
        return;
    }
    printf("\n___CITIES___\n");
    for(int i=0; i<cityCount; i++){
        printf("%d. %s\n",i,cities[i]);
    }
}

void renameCity(){
    displayCities();
    if(cityCount == 0)
        return;
    int index;
    printf("Enter city index to rename : ");
    scanf("%d",&index);
    getchar();

    if(index<0 || index>=cityCount){
        printf("Invalid index...\n");
        return;
    }
    char newName[50];
    printf("Enter New Name : ");
    fgets(newName, 50, stdin);
    newName[strcspn(newName, "\n")]=0;
    printf("City '%s' renamed to '%s'\n",cities[index],newName);
    strcpy(cities[index], newName);
}

void removeCity(){
    displayCities();
    if(cityCount == 0)
        return;

    int index;
    printf("Enter city index to remove : ");
    scanf("%d",&index);
    getchar();

    if(index<0 || index >= cityCount){
        printf("Invalid Index...\n");
        return;
    }
    printf("City '%s' removed.\n", cities[index]);

    //shifting cities
    for(int i=index; i<cityCount; i++){
        strcpy(cities[i], cities[i+1]);
    }

    //shifting distance
    for(int i=index; i<cityCount; i++){
        for(int j=0; j<cityCount; j++){
            distance[i][j] = distance[i+1][j];
        }
    }
    for(int i=0; i<cityCount; i++){
        for(int j=index; j<cityCount; j++){
            distance[i][j] = distance[i][j+1];
        }
    }
    cityCount--;
}

void inputDistance(){
    displayCities();
    if(cityCount<2){
        printf("Need at least 2 cities...\n");
        return;
    }

    int source, destination, dist; //dist is distance between source city and destination city
    printf("Enter source city index : ");
    scanf("%d",&source);
    printf("Enter destination city index : ");
    scanf("%d",&destination);

    if(source<0 || source>=cityCount || destination<0 || destination>=cityCount){
        printf("Invalid city index...\n");
        return;
    }
    if(source == destination){
        printf("Source city and destination city cannot be same...\n");
        return;
    }
    printf("Enter the distance (km) : ");
    scanf("%d",&dist);

    distance[source][destination] = dist;
    distance[destination][source] = dist;

    printf("Distance : %s <-> %s = %d km\n",cities[source], cities[destination], dist);
}

void displayDistanceTable(){
    if(cityCount == 0){
        printf("No cities available...\n");
        return;
    }
    printf("\n___DISTANCE TABLE___\n");
    printf("%-15s", "");
    for(int i=0; i<cityCount; i++){
        printf("%-10s", cities[i]);
    }
    printf("\n");

    for(int i=0; i<cityCount; i++){
        printf("%-15s", cities[i]);
        for(int j=0; j<cityCount; j++){
            printf("%-10d", distance[i][j]);
        }
        printf("\n");
    }
}

void calculateCosts(int dist, int weight, int typeOfVehicle, int deliveryIndex){
    // delivery cost
    deliveryCost[deliveryIndex] = dist * vehicleRate[typeOfVehicle] * (1.0 + weight/10000.0);

    //estimated delivery time
    deliveryTime[deliveryIndex] = (double)dist / vehicleSpeed[typeOfVehicle];

    //fuel consumption
    double fuelUsed = (double)dist / vehicleEfficiency[typeOfVehicle];

    //fuel cost
    deliveryFuelCost[deliveryIndex] = fuelUsed * FUEL_PRICE;

    //total operational cost
    deliveryTotalCost[deliveryIndex] = deliveryCost[deliveryIndex] + deliveryFuelCost[deliveryIndex];

    //profit
    deliveryProfit[deliveryIndex] = deliveryCost[deliveryIndex] * 0.25;

    //final charge to customer
    deliveryCustomerCharge[deliveryIndex] = deliveryTotalCost[deliveryIndex] + deliveryProfit[deliveryIndex];
}

int main()
{

    return 0;
}
