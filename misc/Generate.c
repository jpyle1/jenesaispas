#include "../Generate.h"
#include <stdio.h>

/**
* Joshua Pyle, Biological Inspired Computation.
*/

/**
* Seed the random with the current time.
*/
void seedRandom(){
	srand(time(0));
}

/**
* Generate a random float.
* Assume 6 decimal spots.
*/
float generateRandomFloat(float min,float max){
	float random = ((float) rand())/((float)RAND_MAX);
	float diff = max - min;
	float r = random*diff;
	return min+r;
}

/**
* Generate a file for problem 1..
*/
void generateFileProb1(char* fileName,int numRecords,float min,float max){
	FILE* file = fopen(fileName,"w+");
	int i = 0;
	for(;i<numRecords;i++){
		float randomInput = generateRandomFloat(min,max);
		float randomInput1 = generateRandomFloat(min,max);
		float pi = atanf(1)*4;
		float output = (1.0f+sin(pi*randomInput/2.0f)*cos(pi*randomInput1/2.0f))
			/2.0f;
		fprintf(file,"%.6f,%.6f,%.6f\n",randomInput,randomInput1,output);			
	}
	fclose(file);		 		
}

/**
* Generate a file for problem 2..
*/
void generateFileProb2(char* fileName,int numRecords,float min,float max){
	FILE* file = fopen(fileName,"w+");
	int i = 0;
	for(;i<numRecords;i++){
		float x = generateRandomFloat(min,max);
		float y = generateRandomFloat(min,max);
		float z = generateRandomFloat(min,max);
		float value = 3.0f*(x*x/2+y*y/3+z*z/4)/13.0f;
		fprintf(file,"%.6f,%.6f,%.6f,%.6f\n",x,y,z,value);
	}	
	fclose(file);		 		
}

