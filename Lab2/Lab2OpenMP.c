#include "stdio.h"
#include "omp.h"
#include "stdlib.h"
#include "omp.h"
#define NUM_THREADS 4

void printMatrix(int size , int *array);

int main()
{	
	int size = 0;
	printf("Enter size of matrix: ");
	scanf("%d",&size);

	int *mat;
	mat = (int *)malloc(sizeof(int)*size*size);
    if(mat == NULL) {
    	printf("malloc failed!\n");   
    	exit(1);}
	
	int i = 0;
	
	for(i = 0 ; i < size*size ; i++)
	{
		mat[i] = i;

	}
	printf("The initial matrix is: \n");
	printMatrix(size , mat);
	
	
	//Transpose the matrix using standard serial transpose method
	int d = 0, temp = 0 ;
	int diag = 0 ,xdimen = diag,ydimen = diag, f = size;
	int tempsize = size;
	/*
	double time1 = omp_get_wtime();
	for(d = 0 ; d < size ; d++)
	{	
		xdimen = diag;
		ydimen = diag;
		for(f = tempsize; f != 1 ; f--)
		{	++xdimen;
			ydimen = ydimen + size;
			temp = mat[xdimen];
			mat[xdimen]=mat[ydimen];
			mat[ydimen]=temp;
		}
		
		tempsize--;
		diag = diag + size +1;
	}
	double time2 = omp_get_wtime();
	double difftime = time2-time1;
	//printf("The traspose serial matrix is: \n");
	//printMatrix(size , mat);
	printf("The run time for the transpose(serial) is: %f\n",difftime);
*/
	
	///////////////////////////////////////////////////////////////////////////////////////////
	
	//Transpose the matrix using openMP parallel transpose method
	
	double time3 = omp_get_wtime();
	omp_set_num_threads(NUM_THREADS);
	
	for(d = 0 ; d < size ; d++)
	{	
		xdimen = diag;
		ydimen = diag;
		for(f = tempsize; f != 1 ; f--)
		{	++xdimen;
			ydimen = ydimen + size;
			#pragma omp parallel
			{	int ID = omp_get_thread_num();
				temp = mat[xdimen];
				mat[xdimen]=mat[ydimen];
				mat[ydimen]=temp;
				printf("Thread %d",ID);
				printf(" %d",xdimen);
				printf(" %d\n", ydimen);
			}
		}
		
		tempsize--;
		diag = diag + size +1;
	}
	
	
	double time4 = omp_get_wtime();
	double difftime2 = time4-time3;
	printf("The traspose openMP matrix is: \n");
	printMatrix(size , mat);
	printf("The run time for the transpose(OPenMP) is: %f\n",difftime2);
	
}

void printMatrix(int size , int *array)
{
	int j = 0;
	int counter = 0;
	for( j =0 ; j <size*size ; j++)
	{	
		printf("%d \t", array[j]);
		counter++;
		if(counter == size)
		{
		printf("\n");
		counter = 0;
		} 

	}
}
