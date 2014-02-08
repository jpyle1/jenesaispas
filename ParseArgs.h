/**
* Joshua Pyle, Biological Inpsired Computation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* Structure responsible for holding the input parameters as specified
* by the user of the program.
*/
typedef struct argStruct{
	/**
	* Holds the number of hidden layers.
	*/
	int numHiddenLayers;

	/**
	* Holds the number of neurons in each hidden layer.
	*/
	int* numNeurons;

	/**
	*	Holds the learning rate of the network.
	*/	
	float learningRate;

	/**
	* Holds the file used for training file.
	*/
	char* trainingFile;

	/**
	* Holds the file used for testing.
	*/
	char* testingFile;

	/**
	* Holds the file used for validation.
	*/
	char* validationFile;

	/**
	* Holds the number of training epochs.
	*/
	int numEpochs;

	/**
	* Holds the number of inputs to the network.
	*/	
	int numInputs;

	/**
	* Holds the number of output nodes.
	*/		
	int numOutputs;

	/**
	* Where to store the test output.
	*/
	char* testOutputFile;

	/**
	* Where to store the validation output.
	*/
	char* validationOutputFile;

} Settings;

/**
* Initializes the Setting's structure with the default values.
*/
void setDefault(Settings* settings);

/**
* Responsible for parsing the arguments into the settings.
*/
void parseArguments(Settings* settings,char** args,int numArg);

/**
* Frees the specified settings(number of neurons).
*/
void freeNumNeurons(Settings* settings);

/**
* Responsible for displaying help to the user's screen.
*/
void displayHelp();

/**
* Responsible for displaying the selectd settings.
*/
void displaySettings(Settings* settings);

/**
* Gets the value of an argument that was specified.
*/
char* getValueSpecified(char** arguments,int numArg,char* value);

/**
* Determines if an argument was specified.
*/
int wasArgSpecified(char** arguments,int numArg, char* value);


