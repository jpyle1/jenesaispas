import sys

def main(argv):
	for learningRate in range(1,10):		
		out = open(argv[0]+str(learningRate)+".csv","w+")	
		out.write("HiddenLayer,RMSE\n");
		for hiddenLayer in range(1,10):
			f = open(argv[0]+str(learningRate)+"_"+str(hiddenLayer)+".csv","r+")
			out.write(str(hiddenLayer)+","+f.read().split()[1]+"\n")
		

if __name__ == "__main__":
	main(sys.argv[1:len(sys.argv)])
