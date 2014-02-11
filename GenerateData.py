import subprocess
import sys
import random

def main(argv):
	problemNumber = argv[0];
	problemNumberStr = str(problemNumber);
	numInputs = argv[1];	

	problemNumber = "problem"+problemNumberStr
	trainingFile = "problem"+problemNumberStr+"_training.csv"
	testingFile = "problem"+problemNumberStr+"_testing.csv"
	validationFile = "problem"+problemNumberStr+"_validation.csv" 
	
	indexFile = open("report/"+problemNumber+"/test/index.csv","w+")
	#Repeat the experiment several times...			
	#With different learning rates...	
	for runNumber in range(1,10):
		learningRate = .05*runNumber
		#For each hidden layer...1-10 possible 
		for hiddenLayerCount in range(1,10):			
			currentNumNeurons = ""	
			#Set the values of the current hidden layer...
			for currentLayer in range(1,hiddenLayerCount+1):			
				randNum = random.randint(1,6)	
				if(currentLayer!=hiddenLayerCount):
					currentNumNeurons+=str(randNum)+","
				else:
					currentNumNeurons+=str(randNum)	
			indexFile.write(str(runNumber)+"_"+str(hiddenLayerCount)+"_"
				+currentNumNeurons+"\n")	
			#Regenerate the data...		
			subprocess.call(["bin/main.exe","--"+problemNumber])	
			#Perform the data..	
			subprocess.call(["bin/main.exe","--learningRate",str(learningRate),
				"--hiddenLayers",str(hiddenLayerCount),"--numNeurons",
					str(currentNumNeurons),"--numEpochs",str(5000),"--numInputs",
					str(numInputs),"--trainingFile",trainingFile,"--testingFile",
					testingFile,"--validationFile",validationFile,"--testOutputFile",
					"report/"+problemNumber+"/test/"+str(runNumber)+"_"+
					str(hiddenLayerCount)+".csv","--validationOutputFile",
					"report/"+problemNumber+"/val/"+str(runNumber)+"_"+
					str(hiddenLayerCount)+".csv"])
	indexFile.close()	
if __name__ == "__main__":
	main(sys.argv[1:len(sys.argv)])
