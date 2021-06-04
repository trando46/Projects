# Bao Tran Do
# May 10, 2021
# HW5 
# This algorithm is for building a max heap since we want the array to have 
# ascending order 
# Source of the algorithm https://en.wikipedia.org/wiki/Heapsort



# Sort the array of the given size 
def heapSort(arr):

	length = len(arr)
	index0 = 0

	
	# largest value located at the root 
	heapify(arr,length)
	
	end = length - 1

	while end > 0:

		# swap the first element and the last element. The first element will no longer be consider
		# in the array since it is located at the end of the array for the max heap
		swap(arr, end, index0) 
		# reduced the heap size by one 
		end = end - 1
		
		# restore the heap property to make sure it is still a heap 
		shiftDown(arr, index0 , end)
		
	return arr 

# Want to have the elements in heap order
def heapify(arr,count):
	# Find the parent of the last element 
	start = getParent(count - 1)

	# Shift the element until all the nodes below the start index are in heap order 
	while start >= 0:
		
		shiftDown(arr, start, count - 1)

		# get the next parent node
		start = start - 1
	

# This is to restore the heap 
def shiftDown(arr, start, end): 

	root = start

	# Assuming that the root has at least 1 child 
	while getLeftChild(root) <= end:
		child = getLeftChild(root)
		swapChild = root 
	
		# if the root value is smaller than the left child swap 
		if arr[swapChild] < arr[child]:
			swapChild = child
			
		# if the root value is smaller than the right child swap 
		if getRightChild(root) <= end and arr[swapChild] < arr[getRightChild(root)]:
			swapChild = getRightChild(root)
			
		# if the swap child is the same as the root return 
		if swapChild == root:
			return 
		else: 
			# swap the elements 
			swap(arr, root, swapChild)
			root = swapChild


# This function perform the swapping of the 2 elements 
def swap(arr, firstPosition, secondPosition):
	arr[firstPosition], arr[secondPosition] = arr[secondPosition], arr[firstPosition]
	return arr

# This is getting the index of the parent
def getParent(index):
	return (index - 1)/2

# This is getting the left child index 
def getLeftChild(index):
	return 2 * index + 1 

# This is getting the right child index 
def getRightChild(index):
	return 2 * index + 2



# Test case
test1 = []
test2 = [0]
test3 = [10,1]
test4 = [1,10]
test5 = [1,2,3,4,5,6]
test6 = [1,2,3,4,5,6,7]
test7 = [6,5,4,3,2,1]
test8 = [7,6,5,4,3,2,1]
test9 = [20,11,17,3,6,2]
test10 = [20,1,4,21,24]

print('{:>60}'.format('Test Cases for max heapSort algorithm'))
print('--------------------------------------------------------------------------')
print('{:>25}  {:>40}'.format('cases', 'sorted' + '\n')) 
print('{:>25}  {:>40}'.format(str(test1), str(heapSort(test1)) + '\n')) 
print('{:>25}  {:>40}'.format(str(test2), str(heapSort(test2)) + '\n')) 
print('{:>25}  {:>40}'.format(str(test3), str(heapSort(test3)) + '\n')) 
print('{:>25}  {:>40}'.format(str(test4), str(heapSort(test4)) + '\n')) 
print('{:>25}  {:>40}'.format(str(test5), str(heapSort(test5)) + '\n')) 
print('{:>25}  {:>40}'.format(str(test6), str(heapSort(test6)) + '\n')) 
print('{:>25}  {:>40}'.format(str(test7), str(heapSort(test7)) + '\n')) 
print('{:>25}  {:>40}'.format(str(test8), str(heapSort(test8)) + '\n')) 
print('{:>25}  {:>40}'.format(str(test9), str(heapSort(test9)) + '\n')) 
print('{:>25}  {:>40}'.format(str(test10), str(heapSort(test10)) + '\n')) 







