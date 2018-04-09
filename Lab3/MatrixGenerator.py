from random import *

# Dimensions of the square matrix
N = input("The size of your square matrix: ")
matrices = ["File1ForLab3.txt", "File2ForLab3.txt"]

def create(matrix_file):
	matrix_file.write(str(N) + ' ' + str(N) + '\n')
	for x in range(0, N):
		for y in range(0, N):
			value = randint(1, 10)
			matrix_file.write(str(x) + ' ' + str(y) + ' ' + str(value)+ '\n')

matrix1 = open(matrices[0], 'wb')
create(matrix1)
matrix2 = open(matrices[1], 'wb')
create(matrix2)
