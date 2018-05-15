#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

// upper case letter pool
static const char upper[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// lower case letter pool
static const char lower[] =
"abcdefghijklmnopqrstuvwxyz";

int upperPoolSize = sizeof(upper)  - 1;
int lowerPoolSize = sizeof(lower) - 1;

char getUpperChar(){
          return upper[rand() % upperPoolSize];
}

char getLowerChar(){
          return lower[rand() % lowerPoolSize];
}

int main(int argc, char const *argv[]) {

          ofstream table1;
          table1.open("F1.txt");
          ofstream table2;
          table2.open("F2.txt");

          int wordLength1 = 5;
          int wordLength2 = 8;
          int tableSize;
          srand(time(0));
          string word1;
          string word2;

          cout << "Enter the size of the table: ";
          cin >> tableSize;

          for (int i = 0; i < tableSize; i++) {

                    for (int j = 0; j < wordLength1; j++) {

                              word1 += getUpperChar();
                    }
                    for (int k = 0; k < wordLength2; k++) {
                              word2 += getLowerChar();
                    }

                    table1 << i + 1 << "\t" << word1 << endl;
                    table2 << i + 1 << "\t" << word2 << endl;
                    word1 = "";
                    word2 = "";
          }

          table1.close();
          table2.close();
          return 0;
}
