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
			currentNeuron->sigma = computeSigma(currentNeuron->sigma);
		}
		currentLayer=currentLayer->nextLayer;
	}		
}
