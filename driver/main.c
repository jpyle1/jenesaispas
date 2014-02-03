#include "../ParseArgs.h"
#include "../Generate.h"
#include "../Neural.h"

/**
* Joshua Pyle, Biological Inspired Computation.
*/

/**
* Entry point for the neural network program.
*/ 
int main(int argc,char** argv){
	//Go ahead and seed the random.
	seedRandom();	

	//Determine if the user needs help.
	if(wasArgSpecified(argv,argc,"--help")){
		displayHelp();	
		return 0;	
	}	
	
	//Get the appropriate settings from the user.
	Settings settings;
	setDefault(&settings);
	parseArguments(&settings,argv,argc);
	
	//Does the user just want to generate test files?
	if(wasArgSpecified(argv,argc,"--problem1")){
		//Generate the different sets..
		generateFileProb1("problem1_training.txt",200,-2,2);
		generateFileProb1("problem1_testing.txt",100,-2,2);
		generateFileProb1("problem1_validation.txt",50,-2,2);
		return 0;
	}

	if(wasArgSpecified(argv,argc,"--problem2")){
		generateFileProb2("problem2_training.txt",200,-2,2);
		generateFileProb2("problem2_testing.txt",100,-2,2);
		generateFileProb2("problem2_validation.txt",50,-2,2);
		return 0;
	}
	
	//Show the user what was selected.
	displaySettings(&settings);

	Layer* layer = initializeLayer(10,10,0,0);
	displayLayer(layer);
	freeLayer(layer);
	//printf("%.6f\n",generateRandomFloat(-1,1,1000000,10000000.0f));
	//displayNeuron(initializeNeuron());
	

	freeNumNeurons(&settings);
	return 0;	
}
