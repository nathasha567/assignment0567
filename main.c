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
void displayDistanceTable();
void calculateCosts();
void deliveryRequest();
void deliveryEstimate();
void displayReport();
int findShortestPath();
void findLeastCostRoute();

int main(){
    int choice;
    while (1){
        displayMenu();
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice){
        case 1:
            addCity();
            break;

        case 2:
            renameCity();
            break;

        case 3:
            removeCity();
            break;

        case 4:
            displayCities();
            break;

        case 5:
            inputDistance();
            break;

        case 6:
            displayDistanceTable();
            break;

        case 7:
            deliveryRequest();
            break;

        case 8:
            findLeastCostRoute();
            break;

        case 9:
            displayReport();
            break;

        case 10:
            printf("Exiting...\n");
            return 0;

        default:
            printf("Invalid choice...\n");
        }
    }
    return 0;
}

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
    getchar();
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
    printf("\nCity '%s' added successfully...\n\n",newCity);
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
    printf("\n");
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
    printf("\nCity '%s' renamed to '%s'\n\n",cities[index],newName);
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
    printf("\nCity '%s' removed.\n\n", cities[index]);

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
    printf("\n");
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

void deliveryRequest(){
    displayCities();
    if(cityCount<2){
        printf("Need at least teo cities...\n");
        return;
    }

    int source, destination, weight, typeOfVehicle;

    printf("Enter the source city index : ");
    scanf("%d", &source);
    printf("Enter the destination city index : ");
    scanf("%d", &destination);

    if(source<0 || source>=cityCount || destination<0 || destination>=cityCount){
        printf("Invalide city index...\n");
        return;
    }

    if(source == destination){
        printf("Source city and destination city cannot be same..\n");
        return;
    }

    printf("Enter weight (kg) : ");
    scanf("%d", &weight);

    printf("\nVehicle Types\n");
    for(int i=0; i<3; i++){
        printf("%d. %s (Capacity : %d kg , Rate : %d LKR/km)\n",i+1, vehicleTypes[i], vehicleCapacity[i], vehicleRate[i]);

    }
    printf("Select vehicle type (1-3) : ");
    scanf("%d", &typeOfVehicle);

    if(typeOfVehicle<1 || typeOfVehicle>3){
        printf("Invalid vehicle type...\n");
        return;
    }
    typeOfVehicle--; //convert back to index starting from 0

    if(weight > vehicleCapacity[typeOfVehicle]){
        printf("Weight exceeds vehicle capacity...\n");
        return;
    }

    int dist = distance[source][destination];
    if(dist == 0){
        printf("Distance haave not entered between these cities...\n");
        return;
    }

    //using a temporary index for calculations
    int tempIndex = deliveryCount;

    strcpy(deliverySource[tempIndex], cities[source]);
    strcpy(deliveryDestination[tempIndex], cities[destination]);
    deliveryDistance[tempIndex] = dist;
    deliveryWeight[tempIndex] = weight;
    deliveryVehicleType[tempIndex] = typeOfVehicle;

    calculateCosts(dist, weight, typeOfVehicle, tempIndex);
    deliveryEstimate(tempIndex);

    int confirm;
    printf("\nConfirm delivery ? (1=yes, 0=no) : ");
    scanf("%d", &confirm);

    if(confirm == 1){
        deliveryCount++;
        printf("Delivery Confirmed...\n");
    }
    printf("\n");
}

void deliveryEstimate(int deliveryIndex){
    printf("\n\n======================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("From : %s\n", deliverySource[deliveryIndex]);
    printf("To : %s\n", deliveryDestination[deliveryIndex]);
    printf("Distance : %d km\n", deliveryDistance[deliveryIndex]);
    printf("Vehicle : %s\n", vehicleTypes[deliveryVehicleType[deliveryIndex]]);
    printf("Weight : %d kg\n", deliveryWeight[deliveryIndex]);
    printf("------------------------------------------------------\n");
    printf("Base Cost : %.2f LKR\n", deliveryCost[deliveryIndex]);
    printf("Fuel Cost : %.2f LKR\n", deliveryFuelCost[deliveryIndex]);
    printf("Operational Cost : %.2f LKR\n", deliveryTotalCost[deliveryIndex]);
    printf("Profit (25%%) : %.2f LKR\n", deliveryProfit[deliveryIndex]);
    printf("Customer Charge : %.2f LKR\n", deliveryCustomerCharge[deliveryIndex]);
    printf("Estimate Time : %.2f hours\n", deliveryTime[deliveryIndex]);
    printf("======================================================\n\n");
}

void displayReport(){
    if(deliveryCount == 0){
        printf("No deliveries recorded yet...\n");
        return;
    }

    int totalDistance = 0;
    double totalTime = 0;
    double totalRevenue = 0;
    double totalProfit = 0;
    int longestDistance = deliveryDistance[0];
    int shortestDistance = deliveryDistance[0];

    for(int i=0; i<deliveryCount; i++){
        totalDistance += deliveryDistance[i];
        totalTime += deliveryTime[i];
        totalRevenue += deliveryCustomerCharge[i];
        totalProfit += deliveryProfit[i];

        if(deliveryDistance[i] > longestDistance){
            longestDistance = deliveryDistance[i];
        }
        if(deliveryDistance[i] < shortestDistance){
            shortestDistance = deliveryDistance[i];
        }
    }

    printf("\n\n======================================================\n");
    printf("PERFOMANCE REPORT\n");
    printf("======================================================\n");
    printf("Total Deliveries : %d\n", deliveryCount);
    printf("Total Distance Covered : %d km\n", totalDistance);
    printf("Average Delivery Time : %.2f hours\n", totalTime/deliveryCount);
    printf("Total Revenue : %.2f LKR\n", totalRevenue);
    printf("Total Profit : %.2f LKR \n", totalProfit);
    printf("Longest Route : %d km\n", longestDistance);
    printf("Shortest Route : %d km\n", shortestDistance);
    printf("======================================================\n\n");
}

int findShortestPath(int source, int destination, int *path){
    int shortestDistance[MAX_CITIES];
    int processed[MAX_CITIES];
    int previous[MAX_CITIES];

    for(int i=0; i<cityCount; i++){
        shortestDistance[i] = -1; //-1 means not yet calculated
        processed[i] = 0;
        previous[i] = -1;
    }
    shortestDistance[source] = 0;

    for(int count=0; count<cityCount-1; count++){
        int min = -1, minIndex = -1;

        //find unvisited with minimum distance
        for(int a=0; a<cityCount; a++){
            if(!processed[a] && shortestDistance[a] != -1){
                if(min == -1 || shortestDistance[a] < min){
                    min = shortestDistance[a];
                    minIndex = a;
                }
            }
        }
        if(minIndex == -1)
            break;
        processed[minIndex] = 1;

        //update distance
        for(int a=0; a<cityCount; a++){
            if(!processed[a] && distance[minIndex][a] && shortestDistance[minIndex] != -1){
                int newDistance = shortestDistance[minIndex] + distance[minIndex][a];
                if(shortestDistance[a] == -1 || newDistance < shortestDistance[a]){
                    shortestDistance[a] = newDistance;
                    previous[a] = minIndex;
                }
            }
        }
    }

    //check if destination is reachable
    if(shortestDistance[destination] == -1){
        return -1;
    }

    //construct path
    int pathIndex = 0;
    int current = destination;
    int tempPath[MAX_CITIES];
    int tempIndex = 0;

    while(current != -1){
        tempPath[tempIndex++] = current;
        current = previous[current];
    }

    //reverse path
    for(int i=tempIndex-1; i>=0; i--){
        path[pathIndex++] = tempPath[i];
    }
    path[pathIndex++] = -1;

    return shortestDistance[destination];
}

void findLeastCostRoute(){
    displayCities();
    if(cityCount<2){
        printf("Need at least two cities...\n");
        return;
    }

    int source, destination;
    printf("Enter the source city index : ");
    scanf("%d", &source);
    printf("Enter the destination city index : ");
    scanf("%d", &destination);

    if(source<0 || source>=cityCount || destination<0 || destination>=cityCount){
        printf("Invalid city index...\n");
        return;
    }

    if(source == destination){
        printf("Source city and destination city cannot be same...\n");
        return;
    }

    int path[MAX_CITIES];
    int minDistance = findShortestPath(source, destination, path);

    if(minDistance == -1){
        printf("No route found...\n");
        return;
    }

    printf("\nShortest route from %s to %s : \n", cities[source], cities[destination]);
    printf("Path : ");
    for(int i=0; path[i] != -1; i++){
        printf("%s", cities[path[i]]);
        if(path[i+1] != -1)
            printf(" -> ");
    }
    printf("\nTotal Distance : %d km\n", minDistance);
}

