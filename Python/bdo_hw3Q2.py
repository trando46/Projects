# Bao Tran Do
# April 20, 2021
# HW3 Question 2

# Note to professor: I know you hate python but I really need to refresh my skills for python for work so I am using this class
# as a good opportunity to do that. I applogize in advance! 

# Contain information about the weights and the values 
items = { 7: 42,
		  3: 12,
		  4: 40,
		  5: 25}
# This contain the weights 
keys = list(items.keys())
# Total number of items 
length = len(items)
# Capacity weight the knapsack can hold 
WEIGHT = 10 

# I wrote this in c++ and transfer that logic to python because I was struggling with writing this
# in python at first. 
print('-----------------------\nMy way of doing things since I know what sets can be eliminated')
print('Note: This doesnt applied if all the given weights summation is less than the capacity')

# I envisioned this as a 2D matrix, since the subset values can only be 2 items. 3 or more items
# are not feasible 
def bag():
	maxValue = 0 
	#Start at the beginning of the array 
	for i in range(length):
		for j in range(length):
			#This check ensure that we dont add the same item twice 
			if(i != j):
				addWeight = keys[i] + keys[j] 
				#This check ensure that the 2 items does not exceed that of the capacity WEIGHT 
				if(addWeight <= WEIGHT): 
					addValues = items[keys[i]] + items[keys[j]]
					# This check to ensure that we get the optimal value 
					if(addValues > maxValue):
						maxValue = addValues
						#Store the weight of the 2 items 
						global item1, item2
						item1 = keys[i]
						item2 = keys[j]
	return maxValue

# Printing the result 
print("\nOptimal value: " + str(bag()))
print("item weight: " + str(item1))
print("item weight: " + str(item2))








print('\n-----------------------\nRecursion by using Brute-Force Algorithm(Exhaustive Search)\n')

# This is the recursive solution starting at the end of the list and moving to the left.
# This is considering for all subsets of items. 
# @param n total items 
# @param Cap is the capacity of the knapsack that it can hold 
def bag1(n, Cap):

	# Base case: when the items are out or when the capacity is max out there is nothing to add so return 0
	if n == 0 or Cap == 0:
		return 0

    # if the weight are less than that of the capacity weight then do magic 
	if keys[n - 1] <= Cap:
		# Case1: not putting the item into the knapsack but move the pointer to the left 
		temp1 = bag1(n-1,Cap)
		# Case2: if putting the item into the knapsack add the current item and any items  
		# pointing to the left(recursively happening) until the capacity of the weight is max out(recursively the cap
		# will reach 0 when it will stop)
		temp2 = items[keys[n-1]] + bag1(n-1, Cap - keys[n-1])
		# Take the max of the two cases to get the optimal value 
		return max(temp1, temp2)
	else:
		# If the current item weight is greater than capacity call the function and move to the 
		# left at the next element. 
		return bag1(n-1,Cap)

# Store the elements value that added up to the equivalent optimal value 		
resultVal = []

# This function find the elements that added up to the equivalent optimal value 
# @param optValue the optimal value for the knapsack 
def findElementsWithGivenSum(optValue):
	for x in range(length):
		resultVal.append(items[keys[x]])
		# If the total is greater than the optimal value remove the first element 
		while(sum(resultVal) > optValue):
			resultVal.pop(0)
		# If the total is equivalent optimal value return the arr
		if(sum(resultVal) == optValue):
			return resultVal
	
findElementsWithGivenSum(bag1(length,WEIGHT))

# Store the weights value where the values of the weight are found 
resultWt = []
for x in range(length):
	for i in range(len(resultVal)):
		if items[keys[x]] == resultVal[i]:
			resultWt.append(keys[x])
			#print(keys[x])

#Printing the result 
print("Optimal value: " + str(bag1(length,WEIGHT))) 		
for x in range(len(resultWt)):
	print("item weight: " + str(resultWt[x]))













