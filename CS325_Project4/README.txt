README - Project4

Repository location:
https://github.com/hardesc/CS325_Project4

Project 4, Group 16
CS 325, Oregon State University
Fall, 2015

This is the README file for both graders and group members which includes the following:

For instructors/TA’s and group members:
- A list of necessary files
- Compiling instructions
- Running Instructions

For group members:
- Notes on the repo
- struct definitions
- notes on functions
- notes on writing/ running the algorithm

Necessary files:

project4.c
TSP.c
project4.h
TSP.h
makefile

Other files included in the repo, but not essential:

tsp_example_1.txt
tsp_example_1.txt.tour
tsp_example_2.txt
tsp_example_2.txt.tour
tsp_example_3.txt
tsp_example_3.txt.tour
tsp-verifier.py
TSPAllVisited.py
watch.py
README.txt

Compiling instructions:
Compile with the makefile command:

make

This will generate the executable file: “project4”


Running instructions:
project4 takes 1 argument: the input file.
Usage:

./project4 <INPUT_FILENAME>


Output:
The program, on successful run will print three lines of results information to the screen, and will output
the required data to a file in the current working directory called <INPUT_FILENAME>.tour

FOR GROUP MEMBERS:

Repo Notes:
- Never mind the first folder in the repo, “CS325_Project4.xcodeproj”, that’s just Xcode stuff for running
 the program on my mac. Don’t even open it.

Overview:
Okay, so what I did was try my best to completely abstract all I/O stuff from the program so all you need
to worry about is writing the algorithm itself. All of the data from the file is available to you in a struct set 
that contains n struct city’s. Here’s the definition of the sctructs as copied directly from project4.h:

struct city {
    
    int number;				  //the number as read in from input file (first column)
    int x_coord;			  //second column of input file
    int y_coord;			  //third column of input file
};

struct set {
    
    int n;                                //the number of struct cities read in from input file
    struct city **city;			  //the array of all struct city's in the order they were read from input file
    int totalDistance;			  //initialized to 0, can be set once the array cityOrder has been filled
    int *cityOrder;			  //this is where the actual ordering of the struct cities occurs
    int *distancesTable;		  //initialized to all zeroes, this is a 2d array of distances between cities
    char inputFilename[200];		  //input file read in from command line
    char outputFilename[200];		  //output file generated from input file + ".tour"
    char testFilename[200];		  //used in testing
    char path[200];			  //current working directory
};

Here are the helper functions to help you manipulate the struct set. You won’t need to manipulate
any struct city’s.

void theAlgorithm(set *s); 		//This will be the function to call your algorithm, once complete

void numericallyOrder(set *s);  //In the absence of the actual algorithm that’s yet to be
                                      //written, this function simply orders the struct
                                      //city’s in the cityOrder array from 0 to n.

int calculateDistance(set *s, int A, int B);    //Returns the distance between any two city’s as
                                                //referenced by their index in the array of struct
                                                //city’s or the number attribute of each city

int _getDistance(set *s, int A, int B);	 //gets the distance from the distance table of the struct set

void _setDistance(set *s, int A, int B, int distance);  //sets the distance from the distance table of
                                                            //the struct set (this is not automatically
                                                            //done with calculateDistance)

int calculateAllDistances(set *s);	  //This will calculate all distances and add up the total
                                            //distance once the entire cityOrder array has been
                                            //filled. Calling this on a struct set that does not have its
                                            //cityOrder array filled will give incorrect results

void setOrderByOutputFile(set *s);	 //Don’t use this, I created it solely for testing that the program
                                            //returned the same results as “tsp_example_1.txt.tour” from
                                            // the order the results were listed


Writing/ Running the algorithm:
- Feel free to write more helper functions, just remember to prototype them in the appropriate .h file.

- Once the struct set’s cityOrder attribute has been filled with the desired ordering, just call the
        calculateAllDistances() function to complete the algorithm and let it return on its own, no need to
        return any value. All printing is done externally.

- On the screen, you’ll get a message with the total distance calculated, running time of the algorithm,
        and total running time of the entire program.

- Don’t hesitate to ask, call, email, write if there’s something you don’t understand, or if it’s not
    running properly. If your algorithm is immensely complicated and hard to work with these structs,
    then I will try to help. But I think this is the best way to set up the problem, structurally.

