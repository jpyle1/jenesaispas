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
float generateRandomFloat(int min,int max,int multFact,float divFact){
	//Add a delay, because on my macbookpro, it needed it.
	int randVal = rand()%((max-min)*multFact)+min*multFact;
	return ((float)randVal)/divFact; 
}

/**
* Generate a file for problem 1..
*/
void generateFileProb1(char* fileName,int numRecords,int min,int max){
	FILE* file = fopen(fileName,"w+");
	int i = 0;
	for(;i<numRecords;i++){
		float randomInput = generateRandomFloat(min,max,1000000,1000000.0f);
		float randomInput1 = generateRandomFloat(min,max,1000000,1000000.0f);
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
void generateFileProb2(char* fileName,int numRecords,int min,int max){
	FILE* file = fopen(fileName,"w+");
	int i = 0;
	for(;i<numRecords;i++){
		float x = generateRandomFloat(min,max,1000000,1000000.0f);
		float y = generateRandomFloat(min,max,1000000,1000000.0f);
		float z = generateRandomFloat(min,max,1000000,1000000.0f);
		float value = 3.0f*(x*x/2+y*y/3+z*z/4)/13.0f;
		fprintf(file,"%.6f,%.6f,%.6f,%.6f\n",x,y,z,value);
	}	
	fclose(file);		 		
}

