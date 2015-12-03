//
//  TSP.h
//  CS325_Project4
//
//  Created by Charles Hardes on 12/2/15.
//  Copyright (c) 2015 Charles Hardes. All rights reserved.
//

#ifndef __CS325_Project4__TSP__
#define __CS325_Project4__TSP__

#include <stdio.h>
#include "project4.h"

void numericallyOrder(set *s);
int calculateDistance(set *s, int A, int B);
int setAllDistances(set *s);
void testPrintResults(set *s);
void filePrintResults(set *s, char *fileOut);
void setOrderByOutputFile(set *s, const char *testFileName);

#endif /* defined(__CS325_Project4__TSP__) */
