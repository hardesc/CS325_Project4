//
//  TSP.c
//  CS325_Project4
//
//  Created by Oregon State University Fall 2015 CS325 Group 16 on 12/2/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "project4.h"
#include "TSP.h"


/*This is where the work of solving the TSP algorithm is done. A struct set of n struct cities has
    been created, read in from the designated input file. See the README file for instructions on
    how to manipulate the struct set and see "project4.h" for the definition of struct set and
    struct city.
*/
void theAlgorithm(set *s) {
    
    //Below is a default ordering function for testing. It simply orders the cities from 0 to n.
        //Our real algorithm must set the order of the struct cities in the struct set, then call
        //setAllDistances(s) to make the final distance calculations.
    numericallyOrder(s);//comment this out when you have a working TSP solution

    /*
    
    *****************************************************************************
    
    ------------------------TSP ALGORITHM GOES HERE------------------------------
    
    *****************************************************************************
     
     
     */
    
    //this gets called once the order is completely set and we want to get the total distance
    calculateAllDistances(s);
    

    
}

/************************************************************************************

                            HELPER FUNCTIONS

 ************************************************************************************
*/

//default ordering, fills the order attribute from 0 to n, in that exact order;
    //primarily used for testing
void numericallyOrder(set *s) {
    
    int i;
    for (i = 0; i < s->n; i++) {
        s->cityOrder[i] = i;
    }
}

//Main post-condition: the cityOrder attribute is set according to the ordering of the output file
    //Only used to check calculations in the case of the output test file: tsp_example_1.txt.tour
    //in which the order was set by some unkown program and only way to check that we get the same
    //total distance caluclation is to take in the ordering by the output file ordering.
    //the output has reordered the cities by some unknown method. This function can be
    //called to verify that this program outputs the same results as that file.
    //if this function is called on an output file other than example_1, the order
    //should be the exact same as the default numeriallyOrder() function.
void setOrderByOutputFile(set *s) {
    
    FILE *ofp;
    if ((ofp = fopen(s->testFilename, "r")) == NULL) {perror("input file");}
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

//calculates the distance between any two points (cities), A and B
    //ints A and B  are used as indexes to access the array of cities in set s
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

//simplify the process of setting the distance of a pair of cities A and B
    //sets a distance in the distancesTable 2d array
void _setDistance(set *s, int A, int B, int distance) {
    
    if (s->distancesTable[(A * s->n) + B] == distance){return;}
    else s->distancesTable[(A * s->n) + B] = distance;
    
    //set reciprocal value (A to B = B to A)
    _setDistance(s, B, A, distance);
}

//simplify the process of getting the distance that's already been calculated between two points
    //returns 0 if not yet calculated/ set, or if the two ints passed are equal (same city)
int _getDistance(set *s, int A, int B) {
    
    return s->distancesTable[(A * s->n) + B];
}

/*Given that the order array is completely filled and set, this function will calculate each
    distance in the order given, filling the distances table with each result, and returns
    the total distance as well as fills the toatlDistance attribute of the struct set

    Preconditions:
        -struct set s has been created and appropriately filled
        -Order must first be set with every element in the cityOrder array filled
    compute and set all distances according to order set.
 */
int calculateAllDistances(set *s) {
    
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

