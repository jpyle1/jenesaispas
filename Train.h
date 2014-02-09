#include "Neural.h"

/**
* Joshua Pyle, Bioglocial Inspired Computation.
*/


/**
* Computes the sigma value for a specified node.
*/
float computeSigma(float h);

/**
* Responsible for updating the h and sigma values.
*/
void computeOutputs(NeuralNetwork* neuralNetwork,float* inputs);

/**
* Responsible for updating the delta values.
*/
void computeDeltas(NeuralNetwork* neuralNetwork,float* output);

/**
* Responsible for updating the weights.
*/
void updateWeights(NeuralNetwork* neuralNetwork,float* inputs,
	float learningRate);

/**
* Trains the network based on a filename.
*/
void trainNetwork(NeuralNetwork* neuralNetwork,float learningRate, 
	char* fileName);

/**
* Trains the network based on handwritten recognition.
*/
void trainNetworkHand(NeuralNetwork* neuralNetwork,float learningRate,
	char* digits,char* labels);

/**
* Tests the network based on a filename.
*/
void testNetwork(NeuralNetwork* neuralNetwork,int epochNumber,char* fileName,
	FILE* fileOutput);

/**
* Responsible for validating the network.
*/ 
void validateNetwork(NeuralNetwork* neuralNetwork,char* fileName,
	FILE* fileOutput);

/**
* Resets the values of the neurons.
*/
void resetValues(NeuralNetwork* neuralNetwork);
