//
//  TSP.c
//  CS325_Project4
//
//  Created by Oregon State University Fall 2015 CS325 Group 16 on 12/2/15.
//

#ifndef CS325_Project4_project4_h
#define CS325_Project4_project4_h

#include <stdio.h>

struct city {
    
    int number;//the number as read in from input file (first column)
    int x_coord;//second column of input file
    int y_coord;//third column of input file
};

struct set {
    
    int n;//the number of struct cities read in from input file
    struct city **city;//the array of all struct city's in the order they were read from input file
    int totalDistance;//initialized to 0, can be set once the array cityOrder has been filled
    int *cityOrder;//this is where the actual ordering of the struct cities occurs
    int *distancesTable;//initialized to all zeroes, this is a 2d array of distances between cities
    char inputFilename[200];//input file read in from command line
    char outputFilename[200];//output file generated from input file + ".tour"
    char testFilename[200];//used in testing
    char path[200];//current working directory
};

typedef struct city city;
typedef struct set set;

void getFilenames(set *s, char *argv1, int args);
int getCityCount(char *inputFileName);
city *createCity(int number, int x, int y);
void freeCity(city *c);
set *createSet(int n);
void _initSet(set *s, int n);
void freeSet(set *s);
void fillSet(set *s);
void testPrintSet(set *s);
void filePrintSet(set *s);
void testPrintResults(set *s);
void filePrintResults(set *s);

#endif
