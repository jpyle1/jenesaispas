import sys

def main(argv):
	out = open(argv[0]+"consol"+".csv","w+")	
	for learningRate in range(1,10):	
		temp = ""	
		for hiddenLayer in range(1,10):
			f = open(argv[0]+str(learningRate)+"_"+str(hiddenLayer)+".csv","r+")
			if(hiddenLayer==1):
				temp+=f.read().split()[1]
			else:
				temp+=","+f.read().split()[1]
			
		out.write(temp+"\n")
	out.close()		

if __name__ == "__main__":
	main(sys.argv[1:len(sys.argv)])
