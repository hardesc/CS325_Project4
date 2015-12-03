//
//  TSP.c
//  CS325_Project4
//
//  Created by Charles Hardes on 12/2/15.
//  Copyright (c) 2015 Charles Hardes. All rights reserved.
//

#include "project4.h"
#include "TSP.h"
#include <math.h>
#include <stdlib.h>

//default ordering, fills the order attribute from 0 to n, in that exact order;
    //primarily used for testing
void numericallyOrder(set *s) {
    
    int i;
    for (i = 0; i < s->n; i++) {
        s->cityOrder[i] = i;
    }
}

//used to check calculations, in the case of the output test file: tsp_example_1.txt.tour
    //the output has reordered the cities by some unknown method. This function can be
    //called to verify that the this program outputs the same results as that file.
    //if this function is called on an output file other than example_1, the results
    //should be the exact same as the default numeriallyOrder() function.
void setOrderByOutputFile(set *s, const char *testFileName) {
    
    FILE *ofp;
    if ((ofp = fopen(testFileName, "r")) == NULL) {perror("input file");}
    char c, index[6];
    int i, j;
    
    while ((c = fgetc(ofp)) != '\n') {}//skip first line
    
    //iterate through each line
    for (i = 0; i < s->n; i++) {
        j = 0;
        if (feof(ofp)) {break;}
        while ((c = fgetc(ofp)) != '\n') {
            index[j] = c;
            j++;
        }
        index[j] = '\0';
        s->cityOrder[i] = atoi(index);
    }
    
    //get each number and put it in the order array

    
    fclose(ofp);
}

//calculates the distance between any two points, A and B
int calculateDistance(set *s, int A, int B) {
    
    int Ax, Ay, Bx, By;
    double x, y;
    float root;
    
    Ax = s->city[A]->x_coord;
    Ay = s->city[A]->y_coord;
    Bx = s->city[B]->x_coord;
    By = s->city[B]->y_coord;
    

    x = pow((Ax - Bx), 2);
    y = pow((Ay - By), 2);
    
    root = sqrtf((float)(x + y));
    return (int)nearbyintf(root);
}

//Precondition: Order must first be set
//compute and set all distances according to order set.
int setAllDistances(set *s) {
    
    int i, total, distance, A, B, count;
    total = 0;
    count = 0;
    
    //set first distance to 0
    _setDistance(s, 0, 0, 0);
    
    for (i = 1; i <= s->n; i++) {
        
        //distance from previous city
        A = s->city[s->cityOrder[i - 1]]->number;
        
        //last city must route back to first
        if (i == s->n) {
            B = s->city[s->cityOrder[0]]->number;
        }
        //otherwise, finding distance from last city to current city in order list
        else B = s->city[s->cityOrder[i]]->number;

        distance = calculateDistance(s, A, B);
        _setDistance(s, A, B, distance);
        total += distance;
        count++;
    }
    
    s->totalDistance = total;
    //printf("total calculations: %d\n", count);//------TEST
    return total;
}

//Prints the results to screen, for testing purposes
void testPrintResults(set *s) {
    
    int i;
    
    printf("%d\n", s->totalDistance);
    for (i = 0; i < s->n; i++) {
        printf("%d\n", s->cityOrder[i]);
    }
}

//Prints final results to file
void filePrintResults(set *s, char *fileOut) {
    
    int i;
    FILE *ofp;
    
    if ((ofp = fopen(fileOut, "w")) == NULL) {perror("output file");}
    
    fprintf(ofp, "%d\n", s->totalDistance);
    for (i = 0; i < s->n; i++) {
        fprintf(ofp, "%d\n", s->cityOrder[i]);
    }
    fclose(ofp);
}