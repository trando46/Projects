#Bao Tran Do
#April 18, 2021
#HW3 Question 1 


# This function search the full string for the first occurence of the substring 
# If the substring is found, return the character index where the substring start
# If the substring is not found, return -1 
# @param fullstr 	Takes in the full string 
# @param substr 	Takes in the sub string 
def findSub(fullstr, substr):

	index = fullstr.find(substr)

	if(index < 0):
		index = -1

	return index 

# This display all the test cases 
def testCase(): 
	
	print('{:>43}'.format('Test Cases'))
	print('--------------------------------------------------------------------------')
	word = ['Full string', 'Substring', 'Result']
	print('{:>20}  {:>20}  {:>20}'.format(word[0], word[1], word[2]) + '\n'))

	test1 = ['Happy happy joy joy','happy', findSub('Happy happy joy joy','happy')]
	print('{:>19}  {:>20}  {:>19}'.format(test1[0], test1[1], test1[2]))

	test2 = ['Where is the dog?', 'cat', findSub('Where is the dog?','cat') ]
	print('{:20} {:>20} {:>20}'.format(test2[0], test2[1], test2[2]))

	test3 = ['fun fun fun', 'fun', findSub('fun fun fun','fun')]
	print('{:20} {:>20} {:>20}'.format(test3[0], test3[1], test3[2]))

	test4 = ['I love coding!','Me too!' , findSub('I love coding!','Me too!' )]
	print('{:20} {:>20} {:>20}'.format(test4[0], test4[1], test4[2]))

	print('\n--------------------------------------------------------------------------')

# This function asks for the users input and pass it into the finSub function
def userInput(): 
	fullstr = input("Enter your string: ")
	substr = input("Enter the substring: ")
	print("Result: " + str(findSub(fullstr,substr)))

# This prompt the user to enter their own strings and substring to test
def prompt():
	again = True
	while again:
		go = input("Would you like to enter your own strings? (y/n): ")

		while go != 'y' and go != 'n':
			print("Error: Please enter y or n!")
			go = input("Would you like to enter your own strings? (y/n): ")

		if go == 'n':
			again = False
		else:
			userInput()
	

def welcome():
	print("Welcome to the substring search!\nThis program searches a string S for the"
		+ " first occurence of substring U.\nIf the substring is found, return the" 
		+ " character index where Ustarts.\nIf the substring is not found, return -1.\n")

def goodBye():
	print('Thank you for using the substring search!')

#Calling the function 
welcome()
testCase() 
prompt()
goodBye()
