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
		generateFileProb1("problem1_training.csv",200,-2,2);
		generateFileProb1("problem1_testing.csv",100,-2,2);
		generateFileProb1("problem1_validation.csv",50,-2,2);
		return 0;
	}

	if(wasArgSpecified(argv,argc,"--problem2")){
		generateFileProb2("problem2_training.csv",200,-2,2);
		generateFileProb2("problem2_testing.csv",100,-2,2);
		generateFileProb2("problem2_validation.csv",50,-2,2);
		return 0;
	}

	if(wasArgSpecified(argv,argc,"--problem3")){
		settings.numInputs = 400;
		settings.numOutputs = 10;
		settings.learningRate =0.2f;
		settings.numEpochs=100;
		settings.numHiddenLayers=1;	
		settings.testOutputFile="report/problem3/test.csv";
		settings.validationOutputFile="report/problem3/confusion.csv";
		int numNeurons[1];
		numNeurons[0] = 50;
		settings.numNeurons = numNeurons;	
		//Show the user what was selected.
		displaySettings(&settings);
		NeuralNetwork* neuralNetwork = initializeNeuralNetwork(&settings);
		int x  = 0;
		for(;x<settings.numEpochs;x++){	
		trainNetworkHand(neuralNetwork,settings.learningRate,
			(char*)"handwritten/digits.csv",(char*)"handwritten/digit_labels.csv");
		}
		FILE* file = fopen(settings.testOutputFile,"w+");
		FILE* confusion = fopen(settings.validationOutputFile,"w+");
		fprintf(file,"Digit,RMSE\n");
		testNetworkHand(neuralNetwork,0,
			(char*)"handwritten/digits.csv",(char*)"handwritten/digit_labels.csv",
			file,confusion);		
		fclose(file);	
		fclose(confusion);
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
