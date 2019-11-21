#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "uniform.h"
#include "exp.h"
#include "poisson.h"
#include "MM1.h"
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

//for factorial
int fact(int n) { 
   if ((n==0)||(n==1))
      return 1;
   else
      return n*fact(n-1);
}

int main(){

    //test poisson
    Poisson p(2,1);
    vector<int> numbers;
    int temp;
    for(int i =0; i <10000; i++){
        temp = p.generate();
        numbers.push_back(temp);
    }
    sort(numbers.begin(),numbers.end());

    //plot P(X>x) for x 0 to max num in vector
    int x = 0;
    int index =0;
    int size = numbers.size();
    vector<int>x_val;
    vector<double>y_val;
    for(auto i : numbers) {
        if (i >= x){
            x_val.push_back(x);
            y_val.push_back((double(size)-index)/size);
            x++;
        }
        index++;
    }

    //expected poisson P(X>x)
    vector<int>x_val_exp;
    vector<double>y_val_exp;
    double current_p=0;
    for(int j = x-1; j >= 0; j--){
        current_p = current_p + pow(double(2),j)*exp(-2)/fact(j);
        x_val_exp.push_back(j);
        y_val_exp.push_back(current_p);
    }

    //compare expected to actual plot figure 1
    plt::figure(2);
    plt::plot(x_val,y_val);
    plt::plot(x_val_exp,y_val_exp);

    Exp e(0.5,6);
    vector<double> numbers_e;
    double temp_e;
    for(int i =0; i <10000; i++){
        temp_e = e.generate();
        numbers_e.push_back(temp_e);
    }
    sort(numbers_e.begin(),numbers_e.end());

    //plot E(X>x) 
    double x_e = 0;
    double x_max_e = 0;
    int index_e =0;
    int size_e = numbers.size();
    vector<double>x_val_e;
    vector<double>y_val_e;
    for(auto i : numbers_e) {
        x_val_e.push_back(i);
        y_val_e.push_back((double(size_e)-index_e)/size_e);
        x_max_e = i;
        index_e++;
    }
    
    //expected Exponential E(X>x)
    vector<double>x_val_exp_e;
    vector<double>y_val_exp_e;
    double current_p_e=0;
    double k=0;
    while(k < x_max_e){
        current_p_e = exp(-0.5*k);
        x_val_exp_e.push_back(k);
        y_val_exp_e.push_back(current_p_e);
        k = k + 0.1;
    }

    //plot exp result
    plt::figure(3);
    plt::plot(x_val_e,y_val_e);
    plt::plot(x_val_exp_e,y_val_exp_e);

    //test mm1
    MM1 m;
    int run_time = 10800; //1 day
    for(int i =0; i < run_time ; i++){
        m.tick();
    }
    double row = double(5)/6;
    cout << "\n\n";
    map<int,double>::iterator it;
    vector<int>x_mm1;
    vector<double>y_mml;
    vector<double>y_mm1_exp;
    for (it = m.customer_state.begin(); it != m.customer_state.end(); it++){
        //cout << it->first << " expected: " << pow(row,(it->first))*(1-row) << " actual: " << it->second/run_time << "\n";
        x_mm1.push_back(it->first);
        y_mml.push_back(it->second/run_time);
        y_mm1_exp.push_back(pow(row,(it->first))*(1-row));
    }

    //plot mm1 result
    plt::figure(4);
    plt::plot(x_mm1,y_mml);
    plt::plot(x_mm1,y_mm1_exp);
    plt::show();

}