#include "../Neural.h"
#include "../Generate.h"
#include <stdio.h>

/**
* Joshua Pyle, Biological Inspired computation.
*/

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

	float** weights = (float**)malloc(sizeof(float*)*numWeightsPerNode);
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
			currentWeights[x] = generateRandomFloat(-1,1,1000000,10000000.0f); 
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
	neuron->biasWeight = generateRandomFloat(-1,1,1000000,10000000.0f); 
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
