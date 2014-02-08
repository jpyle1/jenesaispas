#include "../Train.h"

/**
* Computes the sigma value for a specified node.
*/
float computeSigma(float h){
	return 1.0f/(1.0f+exp(-1*h));
}

/**
* Responsible for updating the h and sigma values.
*/
void computeOutputs(NeuralNetwork* neuralNetwork,float* inputs){
	//Get the first hidden input layer.
	Layer* firstLayer = neuralNetwork->layers[0];
	
	//Iterate through each node of the first layer.
	int i = 0;	
	for(;i<firstLayer->numNeurons;i++){
		//Get the current neuron being processed.
		Neuron* currentNeuron = firstLayer->neurons[i];	
		//Iterate through the number of inputs.
		int x = 0;
		for(;x<neuralNetwork->numInputs;x++){
			currentNeuron->h+=inputs[x]*firstLayer->weights[i][x];					
		}
		//Add the bias weight.
		currentNeuron->h+=currentNeuron->biasWeight;
		//Compute the sigma for each input node.
		currentNeuron->sigma = computeSigma(currentNeuron->h);	
	}

	//Iterate through each of the hidden layers
	//And each of the output layers.
	Layer* currentLayer = firstLayer->nextLayer;
	while(currentLayer){
		//Iterate through each neuron in the currnet Layer.
		int i = 0;		
		for(;i<currentLayer->numNeurons;i++){
			Neuron* currentNeuron = currentLayer->neurons[i];
			//For each hidden weight...					
			int x = 0;
			for(;x<currentLayer->numWeightsPerNode;x++){
				currentNeuron->h+=currentLayer->weights[i][x]*
					currentLayer->prevLayer->neurons[x]->sigma;
			}	
			//Add the bias weight.
			currentNeuron->h+=currentNeuron->biasWeight;
			//Compute the sigma for this node.	
			currentNeuron->sigma = computeSigma(currentNeuron->h);
		}
		currentLayer=currentLayer->nextLayer;
	}		
}

/**
* Responsible for updating the delta values.
*/
void computeDeltas(NeuralNetwork* neuralNetwork,float output){
	//Retrieve the output layer.
	Layer* outputLayer = neuralNetwork->layers[neuralNetwork->numLayers-1];
	
	//For each node in the output layer.
	int i = 0;
	for(;i<outputLayer->numNeurons;i++){
		Neuron* currentNeuron = outputLayer->neurons[i];
		currentNeuron->delta = currentNeuron->sigma*(1-currentNeuron->sigma)*
			(output-currentNeuron->sigma); 
	}
	//Get the previous layer.
	Layer* currentLayer = outputLayer->prevLayer;
	while(currentLayer){
		Layer* nextLayer = currentLayer->nextLayer;	
		int x = 0;
		//Iterate through the number of nodes in this layer.	
		for(;x<currentLayer->numNeurons;x++){
			//Get the current neuron.
			Neuron* currentNeuron = currentLayer->neurons[x];
			//Iterate through all the nodes in the next layer.
			int y = 0;
			for(;y<nextLayer->numNeurons;y++){
				currentNeuron->delta += currentNeuron->sigma*(1-currentNeuron->sigma)*
					nextLayer->neurons[y]->delta*nextLayer->weights[y][x];	
			}		
		}
		currentLayer = currentLayer->prevLayer;
	}
		

}

/**
* Responsible for updating the weights.
*/
void updateWeights(NeuralNetwork* neuralNetwork,float* inputs,
	float learningRate){
	//Get the first layer
	Layer* inputLayer = neuralNetwork->layers[0];

	//Update the weights of the first layer.
	int i = 0;
	for(;i<inputLayer->numNeurons;i++){
		Neuron* currentNeuron = inputLayer->neurons[i];
		int x = 0;	
		for(;x<neuralNetwork->numInputs;x++){	
			inputLayer->weights[i][x]+=learningRate*currentNeuron->delta*inputs[x];	
		}
		currentNeuron->biasWeight += learningRate*currentNeuron->delta;
	}	

	//For each other layer...
	Layer* currentLayer = inputLayer->nextLayer;
	while(currentLayer){
		Layer* prevLayer = currentLayer->prevLayer;
		//For each node in the current layer..
		for(i=0;i<currentLayer->numNeurons;i++){		
			Neuron* currentNeuron = currentLayer->neurons[i];
			int x = 0;	
			for(;x<currentLayer->numWeightsPerNode;x++){
				currentLayer->weights[i][x]+=learningRate*
					prevLayer->neurons[x]->sigma*currentNeuron->delta;
			}
			currentNeuron->biasWeight+= learningRate*currentNeuron->delta;
		}	
		currentLayer=currentLayer->nextLayer;
	}		
}

/**
* Returns the file loaded into a buffer.
*/
char* getFile(char* fileName){
	//Firstly, fetch the contents of the file.
	FILE* currentFile = fopen(fileName,"r");
	//Get the file size...
	fseek(currentFile,0L,SEEK_END);
	int size = ftell(currentFile);
	fseek(currentFile,0L,SEEK_SET);
	char* file = (char*)malloc(sizeof(char)*size);
	fread(file,size*sizeof(char),size,currentFile);
	fclose(currentFile);
	return file;			
}

/**
* Trains the network based on a filename.
*/
void trainNetwork(NeuralNetwork* neuralNetwork,float learningRate, 
	char* fileName){
	//Get the current file.
	char* file = getFile(fileName);
	if(!file){
		printf("Could not load the file, could not train the network \n");
		return;
	}
	//Get the number of columns in the file.
	int numColumns = neuralNetwork->numInputs+1;
	
	float* currentRow = (float*)malloc(sizeof(float)*neuralNetwork->numInputs);
	int currentColumn = 0;	
	char* value = strtok(file,", \n");
	while(value!=NULL){
		if(currentColumn==numColumns-1){
			//Train the record now that all inputs have been received..
			computeOutputs(neuralNetwork,currentRow);
			computeDeltas(neuralNetwork,atof(value));
			updateWeights(neuralNetwork,currentRow,learningRate);
			resetValues(neuralNetwork);	
			currentColumn = 0;	
		}else{
			currentRow[currentColumn] = atof(value);
			currentColumn++;	
		}
		value=strtok(0,", \n");
	}
	free(currentRow);
	return;				
}

/**
* Tests the network based on a filename.
*/
void testNetwork(NeuralNetwork* neuralNetwork,int epochNumber, char* fileName,
	FILE* fileOutput){

	//Get the current file.
	char* file = getFile(fileName);
	if(!file){
		printf("Could not load the file, could not test the network \n");
		return;
	}
	//Get the number of columns in the file.
	int numColumns = neuralNetwork->numInputs+1;

	//Get the output layer
	Layer* outputLayer = neuralNetwork->layers[neuralNetwork->numLayers-1];	

	float sum = 0.0f;//Holds the sum value of the error.	
	float* currentRow = (float*)malloc(sizeof(float)*neuralNetwork->numInputs);
	int currentColumn = 0;
	int numTestingPatterns = 0; 	
	char* value = strtok(file,", \n");
	while(value!=NULL){
		if(currentColumn==numColumns-1){
			computeOutputs(neuralNetwork,currentRow);
			float outputSigma = outputLayer->neurons[0]->sigma;
			float outputValue = atof(value);
			sum+=(outputValue-outputSigma)*(outputValue-outputSigma);
			resetValues(neuralNetwork);
			numTestingPatterns++;	
			currentColumn = 0;	
		}else{
			currentRow[currentColumn] = atof(value);	
			currentColumn++;	
		}
		value=strtok(0,", \n");
	}
	float rms = sqrt((1.0f/(2.0f*numTestingPatterns))*sum);
	fprintf(fileOutput,"%i,%.6f\n",epochNumber,rms);
	free(currentRow);
	return;				
}


/**
* Responsible for validating the network.
*/ 
void validateNetwork(NeuralNetwork* neuralNetwork,char* fileName,
	FILE* fileOutput){
	//Get the current file.
	char* file = getFile(fileName);
	if(!file){
		printf("Could not load the file, could not test the network \n");
		return;
	}
	//Get the number of columns in the file.
	int numColumns = neuralNetwork->numInputs+1;

	//Get the output layer
	Layer* outputLayer = neuralNetwork->layers[neuralNetwork->numLayers-1];	

	float sum = 0.0f;//Holds the sum value of the error.	
	float* currentRow = (float*)malloc(sizeof(float)*neuralNetwork->numInputs);
	int currentColumn = 0;
	int numTestingPatterns = 0; 	
	char* value = strtok(file,", \n");
	while(value!=NULL){
		if(currentColumn==numColumns-1){
			computeOutputs(neuralNetwork,currentRow);
			float outputSigma = outputLayer->neurons[0]->sigma;
			float outputValue = atof(value);
			sum+=(outputValue-outputSigma)*(outputValue-outputSigma);
			resetValues(neuralNetwork);
			numTestingPatterns++;	
			currentColumn = 0;	
		}else{
			currentRow[currentColumn] = atof(value);	
			currentColumn++;	
		}
		value=strtok(0,", \n");
	}
	float rms = sqrt((1.0f/(2.0f*numTestingPatterns))*sum);
	fprintf(fileOutput,"%.6f \n",rms);
	free(currentRow);	
}

/**
* Resets the values of the neurons.
*/
void resetValues(NeuralNetwork* neuralNetwork){
	//Get the currentLayer.
	Layer* currentLayer = neuralNetwork->layers[0];
	while(currentLayer){
		int i = 0;
		for(;i<currentLayer->numNeurons;i++){
			Neuron* currentNeuron = currentLayer->neurons[i];
			currentNeuron->h = 0.0f;
			currentNeuron->sigma = 0.0f;
			currentNeuron->delta = 0.0f;	
		}	
		currentLayer=currentLayer->nextLayer;
	}	
}
