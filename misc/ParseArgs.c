#include "../ParseArgs.h"

/**
* Joshua Pyle, Biological Inspired Computation.
*/ 

/**
* Initializes the Setting's structure with the default values.
*/
void setDefault(Settings* settings){
	settings->numHiddenLayers=3;
	settings->numNeurons = (int*)calloc(sizeof(int)*3,sizeof(int));		
	settings->numNeurons[0] = 3;
	settings->numNeurons[1] = 4;
	settings->numNeurons[2] = 3;	
	settings->learningRate = .2;
	settings->trainingFile = (char*)"training1.txt";
	settings->testingFile = (char*)"testing2.txt";
	settings->validationFile = (char*)"validation1.txt";	
	settings->numEpochs = 10;
	settings->numInputs = 2;
	settings->numOutputs=1;
	settings->testOutputFile="out.txt";
	settings->validationOutputFile="val.txt";
}

/**
* Frees the specified settings(number of neurons).
*/
void freeNumNeurons(Settings* settings){
	free(settings->numNeurons);
}

/**
* Responsible for displaying the selectd settings.
*/
void displaySettings(Settings* settings){
	printf("=======\n Neural Network Options \n\n");
	printf("NumHiddenLayers:%i\n",settings->numHiddenLayers);
	int i = 0;
	for(;i<settings->numHiddenLayers;i++){
		printf("HiddenLayer %i: %i\n",i,settings->numNeurons[i]);
	}
	printf("LearningRate: %.3f\n",settings->learningRate);
	printf("NumEpochs: %i\n",settings->numEpochs);
	printf("NumInputs: %i\n",settings->numInputs);
	printf("NumOutputs: %i\n",settings->numOutputs);
	printf("Training File: %s \n",settings->trainingFile);
	printf("Testing File: %s \n",settings->testingFile);
	printf("Validation File: %s\n",settings->validationFile);
	printf("Testing Output File: %s\n",settings->testOutputFile);
	printf("Validation Output File: %s\n",
		settings->validationOutputFile);
	printf("=========\n");
}

/**
* Gets the value of an argument that was specified.
*/
char* getValueSpecified(char** arguments,int numArg,char* value){
	int i =0;
	//Returns the value specfied
	for(;i<numArg;i++){
		if(strcmp(arguments[i],value)==0 && i!=(numArg-1)){
			return arguments[i+1];
		}
	}
	//If the arg was not found...
	return 0;
}

/**
* Determines if an argument was specified.
*/
int wasArgSpecified(char** arguments,int numArg,char* value){
	int i =0;
	for(;i<numArg;i++){
		if(strcmp(arguments[i],value)==0){
			return 1;
		}	
	}	
	//Was not found.
	return 0;
}

/**
* Responsible for displaying help to the user's screen.
*/
void displayHelp(){
	printf("--hiddenLayers [num] The number of hidden layers \n");
	printf("--numNeurons [num,num,...] Neurons in a hidden layer\n");	
	printf("--learningRate [float] The learning rate\n");
	printf("--numEpochs [num] The number of epochs\n");	
	printf("--numInputs [num] The number of inputs \n");	
	printf("--numOutputs [num] The number of outputs \n ");
	printf("--trainingFile [file] The training file \n");
	printf("--testingFile [file] The testing file \n");
	printf("--validationFile [file] The validation file\n");
	printf("--testOutputFile [file] The output file \n");
	printf("--validationOutputFile [file] The val file \n");
}


/**
* Responsible for parsing the arguments into the settings.
*/
void parseArguments(Settings* settings,char** args,int numArg){

	char* value = getValueSpecified(args,numArg,(char*)"--validationFile");
	if(value!=0){
		settings->validationFile = value;
	}

	value = getValueSpecified(args,numArg,(char*)"--testOutputFile");
	if(value){
		settings->testOutputFile = value;
	}
	
	value = getValueSpecified(args,numArg,
		(char*)"--validationOutputFile");
	if(value){
		settings->validationOutputFile= value;
	}

	value = getValueSpecified(args,numArg,(char*)"--testingFile");
	if(value!=0){
		settings->testingFile = value;
	}
	
	value = getValueSpecified(args,numArg,(char*)"--trainingFile");
	if(value!=0){
		settings->trainingFile = value;
	}	

	value = getValueSpecified(args,numArg,(char*)"--numInputs");
	if(value!=0){
		settings->numInputs = atoi(value);
	}

	value = getValueSpecified(args,numArg,(char*)"--numEpochs");
	if(value!=0){
		settings->numEpochs = atoi(value);
	}

	value = getValueSpecified(args,numArg,(char*)"--learningRate");
	if(value!=0){
			settings->learningRate = atof(value);
	}

	value = getValueSpecified(args,numArg,(char*)"--numOutputs");
	if(value!=0){
			settings->numOutputs = atof(value);
	}

	
	//Assuming it has been allocated as the default.
	value = getValueSpecified(args,numArg,(char*)"--hiddenLayers");
	if(value!=0){
		settings->numHiddenLayers=atoi(value);
		realloc(settings->numNeurons,sizeof(int)*settings->numHiddenLayers);
		memset(settings->numNeurons,0,sizeof(int)*settings->numHiddenLayers);
	}

	value = getValueSpecified(args,numArg,(char*)"--numNeurons");
	if(value!=0){
		char* firstValue = strtok(value,",");
		if(!firstValue){
			printf("Invalid format \n");
			return;
		}
		int count = 0;
		while(firstValue){
			if(count>settings->numHiddenLayers){
				printf("Numbers of hidden layers do not match specification\n");
				return;
			}
			settings->numNeurons[count] = atoi(firstValue);	
			firstValue = strtok(0,",");
			count++; 
		}					
	}

}

