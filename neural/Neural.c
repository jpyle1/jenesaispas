#include "../Neural.h"

/**
* Joshua Pyle, Biological Inspired computation.
*/

/**
* Creates a neural network based on the settings.
*/
NeuralNetwork* initializeNeuralNetwork(Settings* settings){

	NeuralNetwork* neuralNetwork = (NeuralNetwork*)malloc(sizeof(NeuralNetwork));
	Layer** layers = (Layer**)malloc(sizeof(Layer*)*settings->numHiddenLayers+1);	
	
	neuralNetwork->numInputs = settings->numInputs;
	neuralNetwork->numOutputs = settings->numOutputs; 
	neuralNetwork->numLayers = settings->numHiddenLayers+1;
	
	Layer* prevLayer = 0;
	Layer* currentLayer = 0;
	int i = 0;
	for(;i<neuralNetwork->numLayers;i++){
		if(i == 0){
			//If there is one or more hidden layers.
			if(neuralNetwork->numLayers-1!=0){	
				prevLayer = initializeLayer(settings->numNeurons[i],
					settings->numInputs,0,0);
			}
			//if there are no hidden layers.
			else{
				prevLayer = initializeLayer(settings->numOutputs,
					settings->numInputs,0,0); 
			}	
			layers[i] = prevLayer;
		}else if(i==neuralNetwork->numLayers-1){
			currentLayer = initializeLayer(settings->numOutputs,
				prevLayer->numNeurons,prevLayer,0);
			layers[i] = currentLayer;
		}else{
			currentLayer = initializeLayer(settings->numNeurons[i],
				prevLayer->numNeurons,prevLayer,0);	
			layers[i] = currentLayer;	
			prevLayer->nextLayer = currentLayer;
			prevLayer = currentLayer;
		}		
	}

	neuralNetwork->layers= layers;

	return neuralNetwork;
}

/**
* Displays a neural network.
*/
void displayNeuralNetwork(NeuralNetwork* neuralNetwork){
	printf("Displaying neural network\n\n");	
	printf("Num Inputs:%i\n",neuralNetwork->numInputs);
	printf("Num Outputs%i\n",neuralNetwork->numOutputs);
	printf("Num Layers%i\n",neuralNetwork->numLayers);
	int i = 0;
	for(;i<neuralNetwork->numLayers;i++){
		printf("\n======\n");
		displayLayer(neuralNetwork->layers[i]);
		printf("\n======\n");
	}				
	printf("Done displaying neuralnetwork \n\n");
}

/**
* Frees a neural network.
*/
void freeNeuralNetwork(NeuralNetwork* neuralNetwork){
	int i = 0;	
	for(;i<neuralNetwork->numLayers;i++){
		freeLayer(neuralNetwork->layers[i]);
	}	
}



/**
* Responsible for initializing a layer.
*/
Layer* initializeLayer(int numNeurons,int numWeightsPerNode,
	Layer* prevLayer,Layer* nextLayer){

	Layer* layer = (Layer*)malloc(sizeof(Layer));
	
	layer->numNeurons = numNeurons;
	layer->numWeightsPerNode = numWeightsPerNode;
	layer->prevLayer = prevLayer;
	layer->nextLayer = nextLayer;

	float** weights = (float**)malloc(sizeof(float*)*numNeurons);
	Neuron** neurons = (Neuron**)malloc(sizeof(Neuron*)*numNeurons);
	
	int i = 0;
	for(;i<numNeurons;i++){
		neurons[i] = initializeNeuron();
	}					

	layer->neurons = neurons;
	
	for(i=0;i<numNeurons;i++){
		int x = 0;
		float* currentWeights = (float*)malloc(sizeof(float)*numWeightsPerNode);	
		for(;x<numWeightsPerNode;x++){
			currentWeights[x] = generateRandomFloat(-.1f,.1f); 
		}
		weights[i] = currentWeights;
	}
	layer->weights = weights;

	return layer;

}

/**
* Responsible for displaying a layer.
*/ 
void displayLayer(Layer* layer){
	int i = 0;
	printf("NumNeurons: %i\n",layer->numNeurons);
	printf("NumInputWeights %i\n",layer->numWeightsPerNode);
	for(;i<layer->numNeurons;i++){
		displayNeuron(layer->neurons[i]);
		
		int x = 0;	
		for(;x<layer->numWeightsPerNode;x++){
			printf("%.6f,",layer->weights[i][x]);
		}
		
		printf("\n\n");
	}
}

/**
* Responsible for freeing a layer.
*/ 
void freeLayer(Layer* layer){
	int i = 0;
	for(;i<layer->numNeurons;i++){
		free(layer->neurons[i]);
	}
	free(layer->neurons);
		
	i = 0;

	for(;i<layer->numNeurons;i++){
		free(layer->weights[i]);
	}	
	free(layer->weights);
	free(layer);		
}



/**
* responsible for initializing a neuron.
*/
Neuron* initializeNeuron(){
	Neuron* neuron = (Neuron*)malloc(sizeof(Neuron));
	neuron->sigma = 0.0f;
	neuron->delta = 0.0f;
	neuron->h = 0.0f;
	neuron->biasWeight = generateRandomFloat(-.1,.1); 
	return neuron;	
}

/**
* responsible for displaying a neuron.
*/
void displayNeuron(Neuron* neuron){
	printf("Sigma:%.6f\n",neuron->sigma);
	printf("Delta:%.6f\n",neuron->delta);
	printf("h:%.6f\n",neuron->h);
	printf("weightBias:%.6f\n",neuron->biasWeight);
}

/**
* responsible for freeing a neuron.
*/
void freeNeuron(Neuron* neuron){
	free(neuron);
}
