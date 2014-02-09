#include "../Train.h"

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

	if(wasArgSpecified(argv,argc,"--problem3")){
		settings.numInputs = 400;
		settings.numOutputs = 10;
		settings.learningRate =0.7f;
		settings.numEpochs=10000;
		settings.numHiddenLayers=1;	
		int numNeurons[1];
		numNeurons[0] = 75;
		settings.numNeurons = numNeurons;	
		//Show the user what was selected.
		displaySettings(&settings);
		NeuralNetwork* neuralNetwork = initializeNeuralNetwork(&settings);
		
		trainNetworkHand(neuralNetwork,settings.learningRate,
			(char*)"handwritten/digits.txt",(char*)"handwritten/digit_labels.txt");
		
		return 0;	
	}
	
	//Show the user what was selected.
	displaySettings(&settings);
	
	NeuralNetwork* neuralNetwork = initializeNeuralNetwork(&settings);
	int i = 0;
	FILE* currentFile = fopen(settings.testOutputFile,"w+");
	fprintf(currentFile,"epochNumber,RMSE\n");
	for(;i<settings.numEpochs;i++){
		trainNetwork(neuralNetwork,settings.learningRate,settings.trainingFile);
		testNetwork(neuralNetwork,i,settings.testingFile,currentFile);
	}
	fclose(currentFile);
	
	currentFile = fopen(settings.validationOutputFile,"w+");
	fprintf(currentFile,"RMSE_VALIDATED\n");
	validateNetwork(neuralNetwork,settings.validationFile,currentFile);
	fclose(currentFile);



	freeNeuralNetwork(neuralNetwork);
	freeNumNeurons(&settings);
	return 0;	
}
