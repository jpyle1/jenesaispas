#include "../ParseArgs.h"

/**
* Joshua Pyle, Biological Inspired Computation.
*/

/**
* Entry point for the neural network program.
*/ 
int main(int argc,char** argv){

	//Determine if the user needs help.
	if(wasArgSpecified(argv,argc,"--help")){
		displayHelp();	
		return 0;	
	}	
	
	//Get the appropriate settings from the user.
	Settings settings;
	setDefault(&settings);
	parseArguments(&settings,argv,argc);
	displaySettings(&settings);


	freeNumNeurons(&settings);
	return 0;	
}
