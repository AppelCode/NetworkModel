#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "uniform.h"
#include "exp.h"
#include "poisson.h"
#include "MM1.h"

using namespace std;

int main(){
    MM1 m;
    m.tick();
    m.tick();
    m.tick();
    /*
    Poisson p(5);
    Exp e(3.4);
    vector<double> numbers;
    double temp;
    for(int i =0; i <100; i++){
        temp = p.generate();
        numbers.push_back(temp);
    }
    sort(numbers.begin(),numbers.end());

    int j = 0;
    int found = 0;
    for(auto i : numbers) {
        cout << i << " ";
        if(i >= 0.5 && !found){
            //cout << j << "\n";
            found =1;
        }
        j++;
    }
    return 0;
    */
}