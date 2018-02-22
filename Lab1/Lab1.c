#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Function prototypes
void allocateArray(int *,int);
void procedureOne(int *,int );
void procedureTwo(int *,int );
void procedureThree(int *,int *,int ,int );

int main(){

	srand(time(NULL));  //Seeding for random number generator
	int Dimension;	
    int mode;

//////////////////////////////////////////////////////////////

	//Example array

	//This example uses a 2D (5x5) array
	// It is stored as a linear row major ordered array
	// 0   1   2   3   4
	// 5   6   7   8   9
	// 10  11  12  13  14
	// 15  16  17  18  19
	// 20  21  22  23  24

	/*
	int arrayInitializer[] = {5,5};	//Can enter any matrix,separate dimensions with commas
	Dimension = sizeof(arrayInitializer) / sizeof(int);	
	allocateArray(arrayInitializer,Dimension);
	*/

//////////////////////////////////////////////////////////////

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//To view the entire output,disable 'Limit Scrolling to' in terminal>edit>profiles>edit>scrolling tab
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    printf("Press 1 to run or 2 to input an array : ");
    scanf("%d",&mode);
    
    if (mode == 2){
    

    //Input array dimension
    printf("Enter array dimension : ");
    scanf("%d", &Dimension);
    int userArray[Dimension]; 
    
    //Input size of each dimension
    printf("Enter the size of each dimension : ");
    for (int i=0; i<Dimension; i++)
    {
        scanf("%d", &userArray[i]);
    }
    
    printf("\n");
    allocateArray(userArray,Dimension);
}
    
    if (mode == 1){
        
	int arrayInitializer1[] = {100,100};
	Dimension = sizeof(arrayInitializer1) / sizeof(int);
	allocateArray(arrayInitializer1,Dimension);

	int arrayInitializer2[] = {100,100,100};
	Dimension = sizeof(arrayInitializer2) / sizeof(int);
	allocateArray(arrayInitializer2,Dimension);

	int arrayInitializer3[] = {50,50,50,50};
	Dimension = sizeof(arrayInitializer3) / sizeof(int);
	allocateArray(arrayInitializer3,Dimension);

	int arrayInitializer4[] = {20,20,20,20,20};
	Dimension = sizeof(arrayInitializer4) / sizeof(int);
	allocateArray(arrayInitializer4,Dimension);}
    

}

//______________________________________________________________
// Implementation

void allocateArray(int iniArray[],int dimension){

    //Determine number of elements in array
    int num_elements = 1;
    for (int i=0;i<dimension;i++){
	num_elements*=iniArray[i];}

    //Dynamically allocate array (assumed to be linear row major ordered)
    int *array;
    array = (int *)malloc(sizeof(int)*num_elements);
 
    printf("%d Dimensions",dimension);printf(" , ");printf("%d Elements",num_elements);printf("\n\n\n");

    // return an error to caller if memory cannot be allocated
    if(array == NULL) {
    	printf("malloc failed!\n");   
    	exit(1);}   			   

    for(int i=0; i < num_elements; i++){
    	array[i] = i;	//Sets cell value to index - not required - but makes it easier to visualise
  	//printf("%d",array[i]);printf(" ");	//Uncomment this line to print the allocated array
					}

// Execute procedures on array

procedureOne(array,num_elements);

procedureTwo(array,num_elements);

procedureThree(array,iniArray,num_elements,dimension);

}

void procedureOne(int arr[],int numElements){ 
    printf("\n\n\n");
    printf("Procedure 1 : ");
    
	for (int i=0;i<numElements;i++){
		arr[i] = 0;	// Sets all elements to zero
        //printf("%d",arr[i]);printf(" ");	//Uncomment this line to print procedure 1 output
					}
        printf("\n...Executed procedure 1...\n");
}

void procedureTwo(int arr[],int numElements){ 
    printf("\n\n\n");
    printf("Procedure 2 : ");
    
	int tenPercentElements = numElements/10;  // Calculates 10% of number of total elements
    
	for (int i=0;i<numElements;i++){
		if (i < tenPercentElements)
			arr[i] = 1;		// Sets first 10% of elements to 1
        	//printf("%d",arr[i]);printf(" ");	//Uncomment this line to print procedure 2 output
			}
        printf("\n...Executed procedure 2...\n");
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
	coordinate_array[i] = rand()%arr2[i];   //Creates random co-ordinate, bounded by N0,N1,...Nd where d is the dimension
        printf("%d",coordinate_array[i]);
        if (i < dimension-1)    //Determines how many commas to print,depending on number of co-ordinates
            printf(" , ");
} 

printf(")");

//Co-ordinate mapping
//Uses row major indexing equation

int product = 1;    //Variable for inner product
int index = 0;      //Index is the linear row-major-ordered array index
int product2 = 1;   //Variable for outer product

//Row major indexing equation
for (int i=0;i<=dimension-1;i++){
    int product = 1;
	for (int j=i+1;j<=dimension-1;j++){
    product *= arr2[j];}
    
    product2 = product*coordinate_array[i];
	index+=product2;} 
    
    printf("  ;  Value = ");
    printf("%d",arr[index]);	//Prints array value at index mapped from co-ordinate
    printf("\n");}

    printf("\n...Executed procedure 3...\n_______________________________________\n_______________________________________\n");
}