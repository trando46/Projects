#Bao Tran Do
#April 4, 2021


#Write a program in the language of your choice that implements Fibonacci in each of the 
#first three techniques and counts the number of addition operations when called.

#Classic recursive 

CLASSIC = 0
ITERATIVE = 0
ACCUMULATORS = 0 

def classicRecursive(num): 

	global CLASSIC

	if num == 0:
		return 0
	elif num == 1: 
		return 1
	else: 
		CLASSIC = CLASSIC + 1

		return classicRecursive(num - 1) + classicRecursive(num - 2)


def iterativeSolution(num):

	global ITERATIVE

	if num == 0:
		return num
	elif num == 1: 
		return num

	a = 0
	b = 1
	c = 1

	for i in range(2,num + 1):

		c = a + b
		a = b 	#sliding this variable over 1 space 
		b = c 	#sliding this variable over 1 space 

		ITERATIVE = ITERATIVE + 1

	return c

def recursiveAccumulators(num, a = 0, b = 1):

	global ACCUMULATORS

	if num == 0:
		return a
	elif num == 1: 
		return b
	else: 
		ACCUMULATORS = ACCUMULATORS + 1
		return recursiveAccumulators(num - 1, b, a + b)
	

def printing(num):


	print("Number of times the addition occurred: \n")

	print("n = " + str(num) + "\n")

	print("Fib(n): " + str(classicRecursive(num)))
	print("Classic Recursive: " + str(CLASSIC) + "\n")

	print("Fib(n): " + str(iterativeSolution(num)))
	print("Iterative: " + str(ITERATIVE) + "\n")

	print("Fib(n): " + str(recursiveAccumulators(num)))
	print("Recursive w/ Accum: " + str(ACCUMULATORS))
	print("\n-------------------------------")

	



printing(3)
CLASSIC = 0
ITERATIVE = 0
ACCUMULATORS = 0 

printing(10)
CLASSIC = 0
ITERATIVE = 0
ACCUMULATORS = 0 

printing(20)

