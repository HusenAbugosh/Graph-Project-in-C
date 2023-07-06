// Function to find the index of a city in the graph
int findCityIndex(Graph* graph, const char* city) {
    for (int i = 0; i < CITY_NUM; i++) {
        if (strcmp(graph->cities[i], city) == 0) {
            return i;
        }
    }
    return -1;  // City not found
}