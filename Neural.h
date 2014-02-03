/**
* Joshua Pyle, Biological Inspired Computation.
*/ 

/**
* Holds a basic Neural network node.
*/
typedef struct node{

	/**
	* Holds the bias weight.
	*/
	float biasWeight;

	/**
	* Holds the h value.
	*/	
	float h;

	/**
	* Holds the sigma value.
	*/
	float sigma;

	/**
	* Holds the delta value.
	*/
	float delta;
	
} Neuron;

/**
* Holds a layer. 
*/
typedef struct nodeLayer{

	/**
	* Holds the number of neurons in the layer
	*/
	int numNeurons;

	/**
	* Holds an array of neurons.
	*/		
	Neuron** neurons;

	/**
	* Holds an the array of input weights. 
	*/	
	float** weights;

	/**
	* Holds the numer of input weights per node.
	*/
	int numWeightsPerNode;

	/**
	* Holds the previous layer.
	*/
	struct nodeLayer* prevLayer;

	/**
	* Holds the next layer.
	*/
	struct nodeLayer* nextLayer;

} Layer;

/**
* Responsible for initializing a layer.
*/
Layer* initializeLayer(int numNeurons,int numWeightsPerNode,
	Layer* prevLayer,Layer* nextLayer);

/**
* Responsible for displaying a layer.
*/ 
void displayLayer(Layer* layer);

/**
* Responsible for freeing a layer.
*/ 
void freeLayer(Layer* layer);

/**
* responsible for initializing a neuron.
*/
Neuron* initializeNeuron();

/**
* responsible for displaying a neuron.
*/
void displayNeuron(Neuron* neuron);

/**
* responsible for freeing a neuron.
*/
void freeNeuron(Neuron* neuron);
