//
//  TSP.c
//  CS325_Project4
//
//  Created by Oregon State University Fall 2015 CS325 Group 16 on 12/2/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "TSP.h"
#include "project4.h"

//FOR XCODE
#define PATH "/Users/charleshardes/Documents/XCode Workspace/CS325_Project4/CS325_Project4/"
#define INPUT_FILENAME "tsp_example_2.txt"
#define OUTPUT_FILENAME "tsp_example_3.txt.tour(3)"
#define TEST_FILENAME "tsp_example_1.txt.tour"
//END XCODE

int main(int argc, const char * argv[]) {
    
    int count, totalDistance;
    set *startSet;
    clock_t T1, T2, T3, T4;
    float time, time2;    
    
    T1 = clock();//start timer

    if (_POSIX_VERSION ==  200112) {//XCODE
        count = getCityCount(INPUT_FILENAME);
    }
    else {//flip server
        count = getCityCount((char *)argv[1]);
    }
    
    startSet = createSet(count);
    getFilenames(startSet, (char *)argv[1], argc);
    
    fillSet(startSet);
    //testPrintSet(startSet);//uncomment this to print

    T3 = clock();//start timer
    
    theAlgorithm(startSet);
    
    T4 = clock();//end timer
    
    filePrintResults(startSet);
    //testPrintResults(startSet);
    
    totalDistance = startSet->totalDistance;
    
    freeSet(startSet);
    T2 = clock();//end timer
    time = ((float)(T2 - T1)) / CLOCKS_PER_SEC;//get total time
    time2 = ((float)(T4 - T3)) / CLOCKS_PER_SEC;//get total time

    printf("Total calculated distance: %d\nTotal time to execute entire program: %fs\nTime to execute TSP algorithm only: %fs\n", totalDistance, time, time2);

    return 0;
    
}//END MAIN




/**************************************************
 *                                                *
 *  MAIN PROGRAM HELPER FUNCTIONS                 *
 *                                                *
 **************************************************
 */

void getFilenames(set *s, char *argv1, int args) {
    
    char path[200];
    int pathLength;
    
    
    //For XCode writing/testing
    if (_POSIX_VERSION ==  200112) {
        
        
        pathLength = (int)strlen(strcpy(s->path, strcpy(path, PATH)));
        strcpy(s->inputFilename, INPUT_FILENAME);
        strcpy(s->inputFilename, strcat(path, s->inputFilename));
        path[pathLength] = '\0';
        strcpy(s->outputFilename, OUTPUT_FILENAME);
        strcpy(s->outputFilename, strcat(path, s->outputFilename));
        path[pathLength] = '\0';
        strcpy(s->testFilename, TEST_FILENAME);
        strcpy(s->testFilename, strcat(path, s->testFilename));
    }
    //For UNIX
    else {
        if (args != 2) {
            perror("Usage: ./project4 <INPUT_FILE>\n");
            exit(1);
        }
        strcpy(path, getcwd(path, 200));
        strcpy(s->inputFilename, argv1);
        strcpy(s->outputFilename, strcat(argv1, ".tour"));
        strcpy(s->testFilename, TEST_FILENAME);
    }
}

//get the number of cities to process
int getCityCount(char *inputFileName) {
    
    char string[25], FileName[200], path[200];
    int count = 0;
    FILE *ifp;
    
    //For XCode
    if (_POSIX_VERSION ==  200112) {
        
        inputFileName = "";
        strcpy(path, PATH);
        strcpy(FileName, INPUT_FILENAME);
        //strcpy(inputFileName, strcat(path, FileName));
        inputFileName = strcat(path, FileName);
    }
    
    if ((ifp = fopen(inputFileName, "r")) == NULL) {
        perror("input file");
        exit(1);
    }
    
    while (fgets(string, 25, ifp) != NULL) {count++;}
    if (!feof(ifp)) {perror("fgets");}
    
    fclose(ifp);
    
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
        s->cityOrder[i] = -1;
        
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
void fillSet(set *s) {
    
    int i, j;
    char c, xCoords[6], yCoords[6];
    FILE *input;
    
    //s = createSet(n);
    
    input = fopen(s->inputFilename, "r");
    
    for (i = 0; i < s->n; i++) {
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

//Same as testPrintSet, but prints to file. Can't remember why I created this function.
void filePrintSet(set *s) {
    
    int i;
    FILE *ofp;
    
    if ((ofp = fopen(s->outputFilename, "w")) == NULL) {perror("output file");}
    
    for (i = 0; i < s->n; i++) {
        fprintf(ofp, "%d %d %d\n", s->city[i]->number, s->city[i]->x_coord, s->city[i]->y_coord);
    }
    fclose(ofp);
}



//Prints the results to screen, for testing purposes
void testPrintResults(set *s) {
    
    int i;
    
    printf("%d\n", s->totalDistance);
    for (i = 0; i < s->n; i++) {
        printf("%d\n", s->cityOrder[i]);
    }
}

//Prints the results to file
void filePrintResults(set *s) {
    
    int i;
    FILE *ofp;
    
    if ((ofp = fopen(s->outputFilename, "w")) == NULL) {perror("output file");}
    
    fprintf(ofp, "%d\n", s->totalDistance);
    for (i = 0; i < s->n; i++) {
        fprintf(ofp, "%d\n", s->cityOrder[i]);
    }
    fclose(ofp);
}

