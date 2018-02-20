#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Functio prototypes
void procedureOne(int *,int );
void procedureTwo(int *,int );
void procedureThree(int *,int *,int ,int );

int main(){

	//This example uses a 2D (5x5) array
	// It is stored as a linear row major ordered array
	// 0   1   2   3   4
	// 5   6   7   8   9
	// 10  11  12  13  14
	// 15  16  17  18  19
	// 20  21  22  23  24

    srand(time(NULL));  //Seeding for random number generator
    
	int arrayInitializer[] = {5,5};
	//int arrayInitializer1[] = {100,100};
	//int arrayInitializer2[] = {100,100,100};
	//int arrayInitializer3[] = {50,50,50,50};
	//int arrayInitializer4[] = {20,20,20,20,20};
    
	int dimension = sizeof(arrayInitializer)/sizeof(int*);
	int num_elements = 1;
	for (int i=0;i<dimension;i++){
		num_elements*=arrayInitializer[i];}

	//Dynamically allocate array (assumed to be linear row major ordered)
	int *array;
	array = (int *)malloc(sizeof(int)*num_elements);

 
	printf("%d Dimensions",dimension);printf(" , ");printf("%d Elements",num_elements);printf("\n\n\n");


	if(array == NULL) {
  		printf("malloc failed!\n");   
  		exit(1);   // return an error to caller if memory cannot be allocated
			   }

for(int i=0; i < num_elements; i++){
  array[i] = i;
  printf("%d",array[i]);
  printf(" ");
}


procedureOne(array,num_elements);

procedureTwo(array,num_elements);

procedureThree(array,arrayInitializer,num_elements,dimension);

}

//______________________________________________________________
// Implementation

void procedureOne(int arr[],int numElements){ 
    printf("\n\n\n");
    printf("Procedure 1 : ");
    
	for (int i=0;i<numElements;i++){
		arr[i] = 0;
        printf("%d",arr[i]);
        printf(" ");}
        printf("\n");
}

void procedureTwo(int arr[],int numElements){ 
    printf("\n\n\n");
    printf("Procedure 2 : ");
    
	int tenPercentElements = numElements/10;  // Calculates 10% of number of total elements
    
	for (int i=0;i<tenPercentElements;i++){
		arr[i] = 1;}
	for (int i=0;i<numElements;i++){
        printf("%d",arr[i]);
        printf(" ");}
        printf("\n");
}

void procedureThree(int arr[],int arr2[],int numberElements,int dimension){
    printf("\n\n\n");
    printf("Procedure 3 : ");
    
	int fivePercentElements = numberElements*5/100; // Calculates 5% of number of total elements

	for (int a=0;a<fivePercentElements;a++){
        
//Allocate co-ordinate array
int *coordinate_array;
coordinate_array = (int *)malloc(sizeof(int)*dimension); 
printf("Co-ordinate = (");

//Random Co-ordinate Creation
for (int i=0;i<dimension;i++){
		coordinate_array[i] = rand()%arr2[i];   //Creates random co-ordinate, bounded by N0.N1,...Nd where d is the dimension
        printf("%d",coordinate_array[i]);
        if (i < dimension-1)    //Determines how many commas to print,depending on number of co-ordinates
            printf(" , ");
} 

printf(")");

//Co-ordinate mapping
//Uses row major indexing equation

int product = 1;    //Variable for inner product
int index = 0;      //Index is the linear row-major-ordered array index
int product2 = 1;   ////Variable for outer produc

//Row major indexing equation
for (int i=0;i<=dimension-1;i++){
    int product = 1;
	for (int j=i+1;j<=dimension-1;j++){
    product *= arr2[j];}
    
    product2 = product*coordinate_array[i];
	index+=product2;} 
    
    printf("  ;  Value = ");
    printf("%d",arr[index]);
    printf("\n\n\n");}
}



	



