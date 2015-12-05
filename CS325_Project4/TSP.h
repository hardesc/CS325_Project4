//
//  TSP.c
//  CS325_Project4
//
//  Created by Oregon State University Fall 2015 CS325 Group 16 on 12/2/15.
//

#ifndef __CS325_Project4__TSP__
#define __CS325_Project4__TSP__

#include <stdio.h>
#include "project4.h"

void theAlgorithm(set *s);
void numericallyOrder(set *s);
int calculateDistance(set *s, int A, int B);
int _getDistance(set *s, int A, int B);
void _setDistance(set *s, int A, int B, int distance);
int calculateAllDistances(set *s);
void setOrderByOutputFile(set *s);

#endif /* defined(__CS325_Project4__TSP__) */
