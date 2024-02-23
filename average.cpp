#include<iostream>
#include<cstdlib>

using namespace std;

int main(int agrc , char *agrv[]){

    if(agrc-1 == 0){
        cout << "Please input numbers to find average.";
        return 0;
    }

    cout << "---------------------------------" << endl;

    double average;
    double sum = 0;

    for(int i = 0 ; i < agrc ; i++){

        sum += atoi(agrv[i]);

    }

    average = sum/(agrc-1);

    cout << "Average of " << agrc-1 << " numbers = " << average << endl;

    cout << "---------------------------------" << endl;

}