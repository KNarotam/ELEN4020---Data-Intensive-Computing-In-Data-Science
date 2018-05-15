#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <mpi.h>
#include <ctime>
using namespace std;
//mpiCC -std=c++11 -o m mp.cpp
//export PATH=$PATH:$HOME/openmpi/bin
//export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$HOME/openmpi/lib

struct Record {
    int ID;
    string val;
};

int main(void) {

ifstream table1;
table1.open("F1.txt");

ifstream table2;
table2.open("F2.txt");

vector<Record> tableA;
vector<Record> tableB;
vector<int> tableAKey;
vector<int> tableBKey;
vector<string> tableAVal;
vector<string> tableBVal;

int key;
string value;
int numberOfEntry=0;

while(!table1.eof()){
	table1 >> key >> value;
	tableA.push_back({key,value});
	table2 >> key >> value;
	tableB.push_back({key,value});
	tableBKey.push_back(key);
	numberOfEntry++;	//Assumes both files have same amount of entries
	}

          cout << "Size of table:";
          cin >> numberOfEntry;
    int numberOfEntries = numberOfEntry - 1;
    int numProcs, rank;
    int chunkSize = numberOfEntries / numProcs;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double duration;
    clock_t start = clock();
/* Pseudocode

1) Scatter entries of tableB onto each process : chunk size = number of entries / number of processes;
Note number of entries must be divisible by number of processes.

2) For each entry in tableA
	Broadcast entry
	for all entries in each scattered chunk
		if entry.ID is equal to chunk.ID
			Join tableA entry and chunk entry

*/

//Broadcast each key in A
for (int keyA=0;keyA<numberOfEntries;keyA++){
	int currentKey = tableA[keyA].ID;
	string currentVal = tableA[keyA].val;
	MPI_Bcast(&currentKey, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//MPI_Bcast(&currentVal, 1, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
	//cout << rank << " proc has  "<< currentKey <<endl;

//Determine each ranks' search region,ie a lower and upper bound, for each key in A searched.

	int lower = rank*chunkSize;
	int upper = ((rank+1)*chunkSize)-1;
	for (int i=lower;i<=upper;i++){
		if (currentKey == tableB[i].ID){
			cout << currentKey << " " << tableA[keyA].val << " " << tableB[i].val <<endl;}



/*	Correct implementation would use a send and recv of the value in table B

	MPI_Isend(&i,1,MPI_INT,0,0,MPI_COMM_WORLD);}
}
	if (rank == 0){
		MPI_Status status;
		int rcv;
		MPI_Irecv(&rcv,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
		cout << rcv ;
		cout << currentKey << " " << tableA[keyA].val << " " << tableB[rcv].val << endl;}
		cout << "herer";
*/

}}

MPI_Finalize();
duration = (clock() - start) / (double) CLOCKS_PER_SEC;
cout << "Time Taken: " << duration << " seconds" << endl;

}
