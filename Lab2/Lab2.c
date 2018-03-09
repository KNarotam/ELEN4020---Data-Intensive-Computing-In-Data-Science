#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <omp.h>
#include <time.h>

/*************************
		PThread
*************************/

struct thread_data {
	int thread_id;
	int *arr_ptr;
	int *utArr_ptr;
	int sp;			//Starting point
	int Alpha; 		// alpha = delta / num. threads
	int arraySize;
};

void *transposeBlock(void *threadarg){
	struct thread_data *my_data;
	my_data = (struct thread_data *) threadarg;
	int temp;

	//Get 2D coordinate in array from upper triangle array
	for (int row=(my_data->sp);row<(my_data->sp+my_data->Alpha);row++){
		int r = my_data->utArr_ptr[row] / my_data->arraySize;
		int c = my_data->utArr_ptr[row] % my_data->arraySize;
		//printf("%d",my_data->utArr_ptr[row]);
		//printf(" ");

		//Now transpose in main array
		temp = my_data->arr_ptr[r*my_data->arraySize + c];
		my_data->arr_ptr[r*my_data->arraySize + c] = my_data->arr_ptr[c*my_data->arraySize + r];
		my_data->arr_ptr[c*my_data->arraySize + r] = temp;
	}
	pthread_exit(NULL);
}

/*************************
		Main
*************************/

int main() {

	int size;
	int temp;
	char option[20];
	double time_spent;

	printf("Enter the library you want to use (No, PThread, OpenMP): ");
	scanf("%s", option);

	printf("Enter matrix size: ");
	scanf("%d",&size);

	int num_elements = size*size;
	int delta = (num_elements - size) / 2;

	//Dynamically allocate array (assumed to be linear row major ordered)
	int *array;
	array = (int *)malloc(sizeof(int)*num_elements);
	// return an error to caller if memory cannot be allocated
	if(array == NULL) {
		printf("malloc failed!\n");
		exit(1);
	}

	//Initialize array
	for (int i=0;i<num_elements;i++){
		array[i] = i;
	}

	//Dynamically allocate upper triangle array (1D)
	int *utArray;
	utArray = (int *)malloc(sizeof(int)*delta);
    // return an error to caller if memory cannot be allocated
    if(array == NULL) {
	   	printf("malloc failed!\n");
    	exit(1);
	}

	//Initialize upper triangle array
	int utIndex = 0;

	for (int diag=0;diag<size-1;diag++){
		for (int col=diag+1;col<size;col++){
			utArray[utIndex] = size*diag + col;
			utIndex++;
		}
	}

/*************************
		No threading
*************************/

	if(!strcmp(option, "No")){
		clock_t begin = clock();
		for (int d=0;d<size-1;d++){
			for (int col=d+1;col<size;col++){
				temp = array[d*size + col];
				array[d*size + col] = array[col*size + d];
				array[col*size + d] = temp;
			}
		}
		clock_t end = clock();
		//Get execution time in ms
		time_spent = (double)(end - begin)*1000 / CLOCKS_PER_SEC;

	}

/*************************
		PThread
*************************/

	if(!strcmp(option, "PThread")){
		int Threads;			// Change the number of threads here
		printf("Enter number of threads: ");
		scanf("%d",&Threads);
		int alpha = delta / Threads;
		pthread_t threads[Threads];
		struct thread_data td[Threads];

		clock_t begin = clock();

		for (int i=0; i<delta; i+=alpha){
			printf("main() : creating thread, %d",i/alpha );
			printf("\n");
			//Update thread arguments
			td[i/alpha].thread_id = i / alpha;
			td[i/alpha].sp = i;
			td[i/alpha].Alpha = alpha;
			td[i/alpha].arr_ptr = array;
			td[i/alpha].utArr_ptr =utArray;
			td[i/alpha].arraySize = size;
			pthread_create(&threads[i/alpha], NULL, transposeBlock, (void *)&td[i/alpha]);
		}

		clock_t end = clock();
		//Get execution time in ms
		time_spent = (double)(end - begin)*1000 / CLOCKS_PER_SEC;
	}

/*************************
		OpenMP
*************************/

	if(!strcmp(option, "OpenMP")){
		int r,c;
		int threads;

		printf("Enter number of threads: ");
		scanf("%d",&threads);

		clock_t begin = clock();
		omp_set_dynamic(0);		// Explicitly disable dynamic teams
		omp_set_num_threads(threads);
		#pragma omp parallel
		{
			//printf("%d",omp_get_num_threads());
			#pragma omp for
			for (int i=0;i<delta;i++){
				r = utArray[i] / size;
				c = utArray[i] % size;

				temp = array[r*size + c];
				array[r*size + c] = array[c*size + r];
				array[c*size + r] = temp;
			}
		}

		clock_t end = clock();
		//Get execution time in ms
		time_spent = (double)(end - begin)*1000 / CLOCKS_PER_SEC;

	}

	printf("\n");
	printf("%lf",time_spent);
	printf(" ms\n");

}
