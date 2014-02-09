#include <time.h>
#include <stdlib.h>
#include <math.h>

/**
* Joshua Pyle, Biological Inspired Computation.
*/

/**
* Seed the random with the current time.
*/
void seedRandom();

/**
* Generate a random float.
* Assume 6 decimal spots.
*/
float generateRandomFloat(float min,float max);

/**
* Generates a random integer.
*/
int generateRandomInteger(int min,int max);

/**
* Generate a file for problem 1..
*/
void generateFileProb1(char* fileName,int numRecords,float min,float max);

/**
* Generate a file for problem 2..
*/
void generateFileProb2(char* fileName,int numRecords,float min,float max);

