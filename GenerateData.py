import subprocess
import sys
import random

def main(argv):
	problemNumber = argv[0];
	problemNumberStr = str(problemNumber);
	numInputs = argv[1];	

	problemNumber = "problem"+problemNumberStr
	trainingFile = "problem"+problemNumberStr+"_training.txt"
	testingFile = "problem"+problemNumberStr+"_testing.txt"
	validationFile = "problem"+problemNumberStr+"_validation.txt" 
	
	#Repeat the experiment several times...			
	#With different learning rates...	
	for runNumber in range(1,10):
		learningRate = .05*runNumber
		#For each hidden layer...1-10 possible 
		for hiddenLayerCount in range(1,10):			
			currentNumNeurons = ""	
			#Set the values of the current hidden layer...
			for currentLayer in range(1,hiddenLayerCount+1):				
				if(currentLayer!=hiddenLayerCount):
					currentNumNeurons+=str(random.randint(1,6))+","
				else:
					currentNumNeurons+=str(random.randint(1,6))		
			#Regenerate the data...		
			subprocess.call(["bin/main.exe","--"+problemNumber])	
			#Perform the data..	
			subprocess.call(["bin/main.exe","--learningRate",str(learningRate),
				"--hiddenLayers",str(hiddenLayerCount),"--numNeurons",
					str(currentNumNeurons),"--numEpochs",str(50000),"--numInputs",
					str(numInputs),"--trainingFile",trainingFile,"--testingFile",
					testingFile,"--validationFile",validationFile,"--testOutputFile",
					"report/"+problemNumber+"/test/"+str(runNumber)+"_"+
					str(hiddenLayerCount)+".txt","--validationOutputFile",
					"report/"+problemNumber+"/val/"+str(runNumber)+"_"+
					str(hiddenLayerCount)+".txt"])

if __name__ == "__main__":
	main(sys.argv[1:len(sys.argv)])