//
//  project4.c
//  CS325_Project4
//  CS 325 Project 4
//  Oregon State University
//  Fall, 2015
//
//  Created by Charles Hardes on 12/2/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "TSP.h"

//FOR XCODE
#define PATH "/Users/charleshardes/Documents/XCode Workspace/CS325_Project4/CS325_Project4/TSP_Files-1/"
 #define INPUT_FILENAME "tsp_example_1.txt"
#define OUTPUT_FILENAME "tsp_example_3.txt.tour(1)"
#define TEST_FILENAME "tsp_example_1.txt.tour"
//END XCODE

int main(int argc, const char * argv[]) {
    
    int count;
    set *startSet;
    char inputFileName[200], path[200], outputFileName[200], testFileName[200];
    
    //For XCode writing/testing
    if (_POSIX_VERSION ==  200112) {
        strcpy(inputFileName, INPUT_FILENAME);
        strcpy(path, PATH);
        strcpy(inputFileName, strcat(path, inputFileName));
        
        strcpy(outputFileName, OUTPUT_FILENAME);
        strcpy(path, PATH);
        strcpy(outputFileName, strcat(path, outputFileName));
        
        strcpy(testFileName, TEST_FILENAME);
        strcpy(path, PATH);
        strcpy(testFileName, strcat(path, testFileName));
    }
    //For UNIX
    else {
        if (argc != 3) {
            perror("Usage: ./project4 <INPUT_FILE> <OUTPUT_FILE>\n");
        }
        strcpy(inputFileName, argv[1]);
        strcpy(inputFileName, argv[2]);
    }
    
    count = getCityCount(inputFileName);
    
    startSet = createSet(count);
    
    fillSet(startSet, count, inputFileName);
    //testPrintSet(startSet);

    //numericallyOrder(startSet);
    setOrderByOutputFile(startSet, testFileName);
    setAllDistances(startSet);
    filePrintResults(startSet, outputFileName);

    freeSet(startSet);
    return 0;
}//END MAIN


/**************************************************
 *                                                *
 *  MAIN PROGRAM HELPER FUNCTIONS                 *
 *                                                *
 **************************************************
 */
//get the number of cities to process
int getCityCount(const char *inputFileName) {
    
    char string[25];
    int count = 0;
    FILE *ifp;
    if ((ifp = fopen(inputFileName, "r")) == NULL) {perror("input file");}
    
    while (fgets(string, 25, ifp) != NULL) {count++;}
    if (!feof(ifp)) {perror("fgets");}
    
    return count;
}

//allocate memory for a struct city, initialize it to the arguments x and y
city *createCity(int number, int x, int y) {
    
    city *newCity;
    
    newCity = (city *)malloc(sizeof(city));
    newCity->number = number;
    newCity->x_coord = x;
    newCity->y_coord = y;
    
    return newCity;
}

//frees memory allocated by a struct city
void freeCity(city *c) {
    
    c->number = 0;
    c->x_coord = 0;
    c->y_coord = 0;
    free(c);
}

//creates an istance of a set, initializes it, and returns a pointer to it
set *createSet(int n) {
    
    set *newSet;
    
    newSet = (set *)malloc(sizeof(set));
    _initSet(newSet, n);

    return newSet;
}

//sets n to n, allocates n ints or pointers to every other attribute
void _initSet(set *s, int n) {
    
    int i, j;
    //city *city[n];
    
    s->n = n;
    s->totalDistance = 0;
    s->city = (city **)malloc(n * sizeof(city *));
    s->cityOrder = (int *)malloc(n * sizeof(int));
    s->distancesTable = (int *)malloc(n * n * sizeof(int));
    
    for (i = 0; i < n; i++) {
        
        s->city[i] = NULL;
        s->cityOrder[i] = 0;
        
        for (j = 0; j < n; j++) {
            _setDistance(s, i, j, 0);
        }
    }
}

//free the set and all its attributes
void freeSet(set *s) {
    
    int i;
    
    for (i = 0; i < s->n; i++) {
        freeCity(s->city[i]);
    }
    free(s->city);
    free(s->cityOrder);
    free(s->distancesTable);
    free(s);
}

//fills the attribute array of city pointers, creating each city and assigning each city attribute
void fillSet(set *s, int n, char *fileIn) {
    
    int i, j;
    char c, xCoords[6], yCoords[6];
    FILE *input;
    
    //s = createSet(n);
    
    input = fopen(fileIn, "r");
    
    for (i = 0; i < n; i++) {
        //skip the first string of numbers, it's just the index, which we already have as i
        while ((c = fgetc(input)) == ' ') {}//skips leading whitespace
        ungetc(c, input);//puts c back, we need it
        while ((c = fgetc(input)) != ' ') {}//skips first columns of numbers that's just the index
        ungetc(c, input);
        //get the x coordinates as a string of chars
        j = 0;
        while ((c = fgetc(input)) == ' ') {}//skips leading whitespace
        ungetc(c, input);
        while ((c = fgetc(input)) != ' ') {
            xCoords[j] = c;
            j++;
        }
        ungetc(c, input);
        xCoords[j] = '\0';//terminate the string
        j = 0;
        //get the y coordinates as a string of chars
        while ((c = fgetc(input)) == ' ') {}//skips leading whitespace
        ungetc(c, input);
        while ((c = fgetc(input)) != '\n') {
            yCoords[j] = c;
            j++;
        }
        yCoords[j] = '\0';//terminate the string
        
        s->city[i] = createCity(i, atoi(xCoords), atoi(yCoords));
        //s->city[i]->number = i;
    }
    fclose(input);
}

//FOR TESTING PURPOSES---- prints a struct set to screen to ensure struct has been filled correctly
void testPrintSet(set *s) {
    
    int i;
    
    for (i = 0; i < s->n; i++) {
        printf("%d %d %d\n", s->city[i]->number, s->city[i]->x_coord, s->city[i]->y_coord);
    }
}

void filePrintSet(set *s, char *fileOut) {
    
    int i;
    FILE *ofp;
    
    if ((ofp = fopen(fileOut, "w")) == NULL) {perror("output file");}
    
    for (i = 0; i < s->n; i++) {
        fprintf(ofp, "%d %d %d\n", s->city[i]->number, s->city[i]->x_coord, s->city[i]->y_coord);
    }
    fclose(ofp);
}

//simplify the process of setting the distance of a pair of cities A and B
void _setDistance(set *s, int A, int B, int distance) {
    
    s->distancesTable[(A * s->n) + B] = distance;
}

//simplify the process of getting the distance
int _getDistance(set *s, int A, int B) {
    
    return s->distancesTable[(A * s->n) + B];
}

