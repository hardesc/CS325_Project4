//
//  project4.c
//  CS325_Project4
//  CS 325 Project 4
//  Oregon State University
//  Fall, 2015
//
//  Created by Charles Hardes on 12/2/15.
//

#ifndef CS325_Project4_project4_h
#define CS325_Project4_project4_h

#include <stdio.h>

struct city {
    
    int number;
    int x_coord;
    int y_coord;
};

struct set {
    
    int n;
    struct city **city;
    int totalDistance;
    int *cityOrder;
    int *distancesTable;
};

typedef struct city city;
typedef struct set set;

int getCityCount(const char *inputFileName);
city *createCity(int number, int x, int y);
void freeCity(city *c);
set *createSet(int n);
void _initSet(set *s, int n);
void freeSet(set *s);
void fillSet(set *s, int n, char *fileIn);
void testPrintSet(set *s);
void filePrintSet(set *s, char *fileOut);
void _setDistance(set *s, int A, int B, int distance);
int _getDistance(set *s, int A, int B);

#endif
