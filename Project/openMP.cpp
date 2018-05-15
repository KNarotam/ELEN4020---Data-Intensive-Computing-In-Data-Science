#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <omp.h>
#include <vector>
#include <ctime>

using namespace std;


void funcA(){
          cout << "In funcA: his section is executed by thread", omp_get_thread_num();
}

void funcB(){
          cout << "In funcB: this section is executed by thread", omp_get_thread_num();
}

int main(int argc, char const *argv[]) {


          ifstream table1;
          table1.open("F1.txt");

          ifstream table2;
          table2.open("F2.txt");

          vector<int> keyA;
          vector<string> A;
          vector<int> keyB;
          vector<string> B;
          vector<int> keyC;
          vector<string> C;
          int count = 0;
          int key;
          string temp;

          while(!table1.eof()){
                    table1 >> key>> temp;
                    keyA.push_back(key);
                    A.push_back(temp);
                    table2 >> key >> temp;
                    keyB.push_back(key);
                    B.push_back(temp);
                    count ++;
          }

          keyA.pop_back();
          A.pop_back();
          keyB.pop_back();
          B.pop_back();

/*          for (size_t i = 0; i < A.size(); i++) {
                    cout << keyA[i] << " " << A[i] << endl;
                    cout << keyB[i] << " " << B[i] << endl;
          }
*/

          int sizeOfA = A.size();
          int sizeOfB = B.size();
          int NUM_THREADS;

          cout << "How many threads must be used: ";
          cin >> NUM_THREADS;

          double duration;
          clock_t start = clock();

          omp_lock_t lck;
          omp_set_num_threads(NUM_THREADS);

          int counter = 0;
          int tempKeyA;
          int i;
          int j;

          omp_init_lock(&lck);
          #pragma omp parallel for shared(lck,B,C,count,sizeOfA,sizeOfB) private(tempKeyA,i,j)

          for (int i = 0; i < A.size(); i++) {
              int tempKeyA = keyA[i];

                    for (int j = 0; j < B.size(); j++) {
                            int tempKeyB = keyB[j];
                              if(tempKeyA == tempKeyB){
                                        omp_set_lock(&lck);
                                        string entry =  A[i] + "\t" + B[i];
                                        keyC.push_back(counter+1);
                                        C.push_back(entry);
                                        counter ++;
                                        omp_unset_lock(&lck);
                              }
                    }
          }
          omp_destroy_lock(&lck);

          ofstream table3;
          table3.open("F3.txt");
          for (int i = 0; i < C.size(); i++) {
                    table3 << keyC[i] << "\t" << C[i] << endl;
          }

          table1.close();
          table2.close();
          table3.close();

          duration = (clock() - start) / (double) CLOCKS_PER_SEC;
          cout << "Time Taken: " << duration << " seconds" << endl;
          return 0;
}
