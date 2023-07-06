// Husain Abugosh/ حسين ابوغوش / 1210338 / sec:5

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define CITY_NUM 5     //<-- number of cities that our graph will handle

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


// function to add a cities to the graph; by taking the target grpah, index of the city & the name of the city as paremters:
void addCity(Graph* graph, int cityIndex, char* cityName){
    strcpy(graph->cities[cityIndex], cityName);   //<-- fill the cities array 
}


// function to add an edge; by taking the graph , sourc city , dest city & the weghit btween them:
void addEdge( Graph* graph, char* src, char* dest, int weight){


 /* While the Cities array and the matrixArray designed to be a Prallel array that meen 
    the common thing between these 2 array  is the index so:
     we need to know the src and dest lay in which index then we will go to the matrixArray with 
     the specifc location(index) and fill it with the weight :  */

    int srcIndex = -1;
    int desIndex = -1;

    for(int i=0;  i<CITY_NUM; i++){
        if(strcmp(graph->cities[i],src) == 0){
            srcIndex = i;
        }
        if(strcmp(graph->cities[i],dest) == 0){
            desIndex = i;
        }
    }
    // if the  value of srcIndex or destIndex does not chnaged that mean there is no cities with these names:
    if(srcIndex != -1 && desIndex != -1){
        graph->matrix[srcIndex][desIndex] = weight;

    }else{

        if(srcIndex == -1){
         printf("the source city not found\n");
        }
        if(desIndex == -1){
        printf("the destination city not found\n");
        }
    }
}

// function to print the graph(in a matrix view):
void printGraph(Graph* graph){

    printf("    ");
   // print the cities in horizontal view:
    for (int i = 0; i < CITY_NUM; i++) {
        printf("%s ", graph->cities[i]);
    }

     printf("\n");
    // print each city with it weight with all the other cities in vertical way:
    for (int i = 0; i < CITY_NUM; i++) {
        printf("%s ", graph->cities[i]);
        for (int j = 0; j < CITY_NUM; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}



int main() {
    struct Graph* graph = createGraph();

    addCity(graph, 0, "City1");
    addCity(graph, 1, "City2");
    addCity(graph, 2, "City3");
    addCity(graph, 3, "City4");
    addCity(graph, 4, "City5");

    addEdge(graph, "City1", "City2", 10);
    addEdge(graph, "City1", "City5", 20);
    addEdge(graph, "City2", "City3", 30);
    addEdge(graph, "City2", "City4", 40);
    addEdge(graph, "City2", "City5", 50);
    addEdge(graph, "City3", "City4", 60);
    addEdge(graph, "City4", "City5", 70);

    printGraph(graph);

    return 0;
}