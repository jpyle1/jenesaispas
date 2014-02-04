#include "../Neural.h"

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
