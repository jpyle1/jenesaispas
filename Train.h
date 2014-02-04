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
void computeDeltas(NeuralNetwork* neuralNetwork,float output);
