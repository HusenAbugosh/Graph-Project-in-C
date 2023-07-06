// Husain Abugosh/ حسين ابوغوش / 1210338 / sec:5

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <limits.h> 


#define CITY_NUM 30    //<-- number of cities that our graph will handle
#define INF INT_MAX   //<-- a relly big number that will act line infinity-> thats will help us with Di

//// Graph Structure Using adjacency matrix  ////

typedef struct Graph{

    char cities[CITY_NUM][50];        //<-- 2D array to store the name of the cities.
    int  matrix[CITY_NUM][CITY_NUM];  //<-- 2D array to represent the edges between the cities.
    // *they will work like 2D parallel array each row and each column of the matrix corresponds to a city*
    
}Graph;

// funtion to create a grpah:
Graph* createGraph() {
    
    // to find a space in memo to create a graph:
    Graph* graph = (Graph*)malloc(sizeof(Graph)); 

    // if there is no space in the memo:
    if (graph == NULL){
        printf("Out of memory!\n");
    }
    // fill the matrix 2D array with zeros -> thats mean no edges in the graph in the begining:
    for (int i = 0; i < CITY_NUM; i++) {

        for (int j = 0; j < CITY_NUM; j++) {
            graph->matrix[i][j] = 0;
        }
    }
    return graph;
}


//// Queue Structure  ////

typedef struct Node {

    int data;
    struct Node* next;

}Node;


typedef struct Queue {
     Node *front;  //<-- it will point to the first node(head) of the linkedList.
     Node *rear;  //<-- it will point to the last node(tail) of the linkedList.
}Queue;

// this function will create a new linked lidt node and store the dat in it :
 Node* newNode(int k) {

    Node* temp = (struct Node*)malloc(sizeof(struct Node)); //<-- will search for empty space in memo.

    // handle if there any issue in the  allocating memory:
    if (temp == NULL) {
        printf("Memory overflow. Could not allocate memory.\n");
        exit(0);
    }
    temp->data = k;       //<-- insert the data in the node.
    temp->next = NULL;   //<-- set the pointer.
    return temp;
}

//this function will create a  Queue Node:
 Queue* createQueue() {

    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    // handle if there any issue in the  allocating memory:
    if (q == NULL) {
        printf("Memory overflow. Could not allocate memory.\n");
        exit(0);
    }
    q->front = q->rear = NULL;
    return q;
}

/* this function will Insert element at the end (Called Rear) (insert at the end of the list)
by taking the q we need to insert the elemnet in and the value of the element as parameters:*/
void enQueue(Queue* q, int k) {

    // create a new linkedlist node with the inserted element(K):
     Node* temp = newNode(k);

    // if queue is empty then -> new node will be the front & rear both(the only emelent in the queue):
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    // if the queue is NOT empty then -> add the new node at the end of queue and change the rear:
    q->rear->next = temp;
    q->rear = temp;  //<-- make the last inserted  element  the rear.
}

// this function will remove a key from the front of the given queue:
void deQueue(Queue* q) {

    // if queue is empty -> return NULL(nothing to remove)
    if (q->front == NULL){
       return;
    }
        
    // store previous front and move front one node ahead.
     Node* temp = q->front;
     q->front = q->front->next;

    // if front becomes NULL then -> change rear also to NULL.
    if (q->front == NULL){
       q->rear = NULL;
    }

    free(temp); //<-- free the node.
}

//// functions //// 

/// function to add a cities to the graph and to add the distance between them:
void addPath(struct Graph* graph, char source[], char destination[], int distance) {
    /* While the Cities array and the matrixArray designed to be a parallel array, the common thing between these 2 arrays is the index.
    We need to know the source and destination cities' indices, then we will go to the matrixArray with the specific location(index)
    and fill it with the weight: */
    
    // To track the operation:
    int sourceIndex = -1;
    int destinationIndex = -1;

    // Check if cities already exist
    for (int i = 0; i < CITY_NUM; i++) {
        // Source city
        if (strcmp(graph->cities[i], source) == 0) {
            sourceIndex = i; 
        }
        // Destination city
        if (strcmp(graph->cities[i], destination) == 0) {
            destinationIndex = i;
        }
    }

    // If the source city does not exist (sourceIndex did not change), add it to the cities
    if (sourceIndex == -1) {
        for (int i = 0; i < CITY_NUM; i++) {
            if (strcmp(graph->cities[i], "") == 0) {  // Find the first empty spot ("") and fill it with the new city
                strcpy(graph->cities[i], source);
                sourceIndex = i;
                break;
            }
        }
    }

    // If the destination city does not exist (destinationIndex did not change), add it to the cities
    if (destinationIndex == -1) {
        for (int i = 0; i < CITY_NUM; i++) {
            if (strcmp(graph->cities[i], "") == 0) {  // Find the first empty spot ("") and fill it with the new city
                strcpy(graph->cities[i], destination);
                destinationIndex = i;
                break;
            }
        }
    }

    // Add edge (directed edge from source to destination):
    graph->matrix[sourceIndex][destinationIndex] = distance;
}



void loadCities(Graph** graph){

         // read data from the file:
        FILE *file = fopen("cities.txt", "r"); //<-- will open the wanted file & put it on the reading mode.

        // this if-statment used to check if there any error with openning the file:
        if (file == NULL){
            printf("*ERROR: File couldn't be opened*\n");
        }

        printf("\nReading the File\n ");
        // varibales will hold the data in it:
        char srcCity[20];
        char disCity[20];
        char distance[10];

        /* the loop continues as long as fscanf successfully reads and assigns
           values to all 3 variables (which is when it returns 3): */
        while (fscanf(file, "%s %s %s\n", srcCity, disCity, distance) == 3) {

            int iDistance;
            sscanf(distance, "%d", &iDistance); //<-- will take just the number from the string(KM will nt be scrap)
            addPath(*graph,srcCity,disCity,iDistance);
        }

        printf("Done\n ");
        fclose(file); //<-- close the file.
}



/* suporter function to get the minDistance; by taking  as parameters: 
~int dist[] array that contain the current shortest distance from the source to each city.
~sptSet[] which indicates whether a city is included in the shortest path Set or not(1:included / 0:not)
* so basically minDistance "know" which paths are marked
 (or rather, which vertices are included in the shortest path tree) and only choose among the remaining ones.
*/

int minDistance(int dist[], int sptSet[]) {

    int min = INF;  //<-- set to infinity to compare with the distance value.
    int min_index; //<-- will store the city the smallest distance value.


// we will go through all the cities and chaeck each city if a city is
// not yet included in the shortest path tree (sptSet[v] == 0):
    for (int v = 0; v < CITY_NUM; v++){
         if (sptSet[v] == 0 && dist[v] <= min){
           min = dist[v];
           min_index = v;  
         }
    }

    return min_index;
}

// recursive suporter function thats print the shortest path from src to city represented index(j) :
void printPath(int parent[], int j, Graph* graph, int dist[], int* pj) {
    
    // base case: 
    //if the parent of the current city (j) is -1, it means we have reached the source city 
    if (parent[j] == -1){
        *pj = j;  //<-- pointer to keeps track of the index of the previous city in the path.
        return;
    }
        
    printPath(parent, parent[j], graph, dist, pj);  //<-- call the function again till the disCity index
    printf(" -> %s (%dkm)", graph->cities[j], dist[j] - dist[*pj]);
    *pj = j;
}


/* 
function thats print all the road details by taking as a parmeter:
~dist[]: array that contain the current shortest distance from the source to each city.
~ parent[]: this array holds the immediate parent of a node in the path from the source to that node.
*/
void printResult(int dist[], int parent[], Graph* graph, int src, int dest) {

    printf("\nShortest Path from %s to %s \t Distance: %d", graph->cities[src], graph->cities[dest], dist[dest]);
    printf("\nPath: %s", graph->cities[src]);
    int j = src;
    printPath(parent, dest, graph, dist ,&j);
    printf("\n");
}

void dijkstra(Graph* graph, char source[], char destination[]) {


    int dist[CITY_NUM];      //<-- will store the shortest distance from the source to evrey other city.
    int sptSet[CITY_NUM];   //<-- acting like bool array to hold 1(true) if the shortest path from the source to the i-th city has been finalized.
    int parent[CITY_NUM];  //<--  will store the immediate predecessor of a city in the shortest path from the source.
   
   // will store the index that reflect the city in it:
    int srcIndex = -1;
    int destIndex = -1;
    
    // check the cities the same as in the addPath function:
    for (int i = 0; i < CITY_NUM; i++) {
        if (strcmp(graph->cities[i], source) == 0) {
            srcIndex = i;
        }

        if (strcmp(graph->cities[i], destination) == 0) {
            destIndex = i;
        }

        parent[i] = -1;
        dist[i] = INF;
        sptSet[i] = 0;
    }

    if (srcIndex == -1){
        printf("Source City not found\n");
    }
    if (destIndex == -1){
        printf("Destnation City not found\n");
    }

    dist[srcIndex] = 0;  //<--  distancefrom the source to itself is 0.

    for (int count = 0; count < CITY_NUM - 1; count++) {

        int u = minDistance(dist, sptSet); //<-- store the city with the minimum distance value from the set of cities not yet included in the shortest path set
        sptSet[u] = 1; //<--the selected city will be now markes as included in the shortest path list
       
        // cheack if the selected city is the dest -> then we will stop:
        if (u == destIndex) {
            break;
        }

        for (int v = 0; v < CITY_NUM; v++) {
            if (sptSet[v] == 0 && graph->matrix[u][v] && dist[u] != INF && dist[u] + graph->matrix[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph->matrix[u][v];
            }
        }
    }

    printResult(dist, parent, graph, srcIndex, destIndex);

}



// Function: to perform Breadth-First Search (BFS) on the graph:
void bfs(Graph* graph, char source[], char destination[], int op) {

    int srcIndex = -1;
    int destIndex = -1;

    int dist[CITY_NUM];     //<-- willl to store the distance from source to each city
    int prev[CITY_NUM];     //<-- willl to store the previous city in the shortest path
    int sptSet[CITY_NUM];   //<-- willl to track visited cities

    Queue* queue = createQueue(); //<-- declear a queue

    // initialize distance, previous city, and visited arrays
    for (int i = 0; i < CITY_NUM; i++) {
        dist[i] = INF;
        prev[i] = -1;
        sptSet[i] = 0;
    }

    // find the inesxes that reflect the source and destination cities:
    for (int i = 0; i < CITY_NUM; i++) {
        if (strcmp(graph->cities[i], source) == 0) {
            srcIndex = i;
        }
        if (strcmp(graph->cities[i], destination) == 0) {
            destIndex = i;
        }
    }

    // t0 check source or destination city not found, return
    if (srcIndex == -1){
        printf("Source City not found\n");
    }
    if (destIndex == -1){
        printf("Destnation City not found\n");
    }


    
    dist[srcIndex] = 0;       //<--  distancefrom the source to itself is 0.
    enQueue(queue, srcIndex);  //<-- the src city index will enqueued in the q
   
    //the loop continues until the queue becomes empty or we reached destination :
    while (queue->front != NULL) {

        int currIndex = queue->front->data;
        deQueue(queue);
        sptSet[currIndex] = 1;

        // stop BFS if destination city is reached:
        if (currIndex == destIndex) {
            break;
        }

        // Traverse all neighboring cities
        for (int i = 0; i < CITY_NUM; i++) {
            if (graph->matrix[currIndex][i] != 0 && sptSet[i] == 0) {
                // Update distance and previous city
                if (dist[currIndex] + graph->matrix[currIndex][i] < dist[i]) {
                    dist[i] = dist[currIndex] + graph->matrix[currIndex][i];
                    prev[i] = currIndex;
                }
                enQueue(queue, i);
            }
        }
    }

    // if destination city was not reached:
    if (prev[destIndex] == -1) {
        printf("There is no path from %s to %s.\n", source, destination);
        return;
    }

    switch (op){
    case 1: {

        // print the shortest path and distance to terminal
        printf("\nShortest Path from %s to %s\n", source, destination);
        printf("Distance: %d\n", dist[destIndex]);
        printf("Path: ");
        int path[CITY_NUM];
        int pathLength = 0;
        int currIndex = destIndex;

        while (currIndex != -1) {
            path[pathLength++] = currIndex;
            currIndex = prev[currIndex];
        }

        for (int i = pathLength - 1; i >= 0; i--) {
            printf("%s", graph->cities[path[i]]);
            if (i > 0) {
                int distance = graph->matrix[path[i]][path[i-1]];
                printf(" (%dkm) -> ", distance);
            }
        }
        printf("\n");
        break;



    }

    case 2 :{

        FILE* outputFile = fopen("output.txt", "w");
        if (outputFile == NULL) {
            printf("Failed to open output file.\n");

        }


        fprintf(outputFile, "\n\nBFS Result:\nShortest Path from %s to %s\n", source, destination);
        fprintf(outputFile, "Distance: %d\n", dist[destIndex]);
        fprintf(outputFile, "Path: ");

        int path[CITY_NUM];
        int pathLength = 0;
        int currIndex = destIndex;

        while (currIndex != -1) {
            path[pathLength++] = currIndex;
            currIndex = prev[currIndex];
        }
  
        for (int i = pathLength - 1; i >= 0; i--) {
            fprintf(outputFile, "%s", graph->cities[path[i]]);
            if (i > 0) {
                int distance = graph->matrix[path[i]][path[i-1]];
                fprintf(outputFile, " (%dkm) -> ", distance);
            }
        }

        // Close the output file
        fclose(outputFile);
        break;


    }
        
       
    default:
        break;
    }


}









int main() {

    // the graph that will contain evrething:
     Graph* graph = createGraph();

    int choice;              //<-- will store the choice of the user.
    int exitFlag = 0;        //<-- if the user rise the flag(exitFlag = 1) th loop will stop and close the programe.
    int loadFalg = 0;   

    // will hold the source and dest cities:
    char srcCity[20];
    char desCity[20];

   //  this loop use for showing the menu:
    while (!exitFlag){

        printf("\n_______Menu_______\n\n");
        printf("1. Load cities.\n");
        printf("2. Enter source.\n");
        printf("3. Enter destination.\n");
        printf("4 .Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n");
                //loads the file and construct the graph:
                loadCities(&graph);
                loadFalg = 1;
                break;
            case 2:
                printf("\n");
                if(!loadFalg){
                    loadCities(&graph);
                    loadFalg = 1;
                }

                //read the source city:
                printf("Please enter source city:\n ");
                scanf("%s", srcCity); 
                break;
            case 3:
                printf("\n");

                if(strcmp(srcCity,"") == 0){
                    printf("Please enter source city first:(option1)\n ");
                    break;
                }

                //print the full route of the shortest path including the distance between each 
                //two cities and the total shortest cost for both algorithms (Dijkstra and BFS):

                printf("Please enter the source city:\n ");
                scanf("%s", desCity);

                printf("Dijkstra Results:\n:");
                dijkstra(graph, srcCity, desCity);
                printf("\n-----------------------------------------\n");
                //BFS:
                printf("BFS Results:\n:");
                bfs(graph, srcCity, desCity,1);

                break;
            case 4:
                 // exit and print the short path to a output file.
                 bfs(graph, srcCity, desCity,2);

                 break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
            }
            printf("\n");
    }

    return 0;
}