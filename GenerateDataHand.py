import subprocess

def main():
	directory = "report/problem3/"
	for numNeurons in range(1,6):
		numNeurons = numNeurons*25
		for learningRate in range(1,4):
			learningRateValue = .1*learningRate
			subprocess.call(["./bin/main.exe","--hiddenLayers","1","--numNeurons",
				str(numNeurons),"--learningRate",str(learningRateValue),"--numEpochs",
				"100","--validationOutputFile",directory+"confusion.csv",
				"--testOutputFile",directory+str(numNeurons)+"_"+str(learningRate)+
				".csv","--problem3"])		


if __name__ == "__main__":
	main()
