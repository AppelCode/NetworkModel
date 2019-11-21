#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include "uniform.h"
#include "exp.h"
#include "poisson.h"
#include "MM1.h"
#include "MEk1.h"
#include "erlang.h"
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

    Uniform u(5);
    vector<double> numbers1;
    double temp1;
    for(int i =0; i <10000; i++){
        temp1 = u.generate();
        numbers1.push_back(temp1);
    }
    sort(numbers1.begin(),numbers1.end());

    double x_1 = 0;
    double x_max_1 = 0;
    int index_1 =0;
    int size_1 = numbers1.size();
    vector<double>x_val_1;
    vector<double>y_val_1;
    for(auto i : numbers1) {
        x_val_1.push_back(i);
        y_val_1.push_back((double(size_1)-index_1)/size_1);
        x_max_1 = i;
        index_1++;
    }

    plt::figure(1);

    plt::title("Uniform P(X>x)");
    plt::xlabel("x");
    plt::ylabel("P(X>x)");
    plt::plot(x_val_1,y_val_1);

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
    vector<double>x_val;
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
    vector<double>x_val_exp;
    vector<double>y_val_exp;
    double current_p=0;
    for(int j = x-1; j >= 0; j--){
        current_p = current_p + pow(double(2),j)*exp(-2)/fact(j);
        x_val_exp.push_back(j);
        y_val_exp.push_back(current_p);
    }

    //compare expected to actual plot
    plt::figure(2);

    plt::title("Poisson P(X>x)");
    plt::xlabel("x");
    plt::ylabel("P(X>x)");
    plt::named_plot("simulated",x_val,y_val);
    plt::named_plot("theory",x_val_exp,y_val_exp);
    plt::legend();

    //test exponential
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

    //expected Exponential P(X>x)
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
    plt::title("Exponential P(X>x)");
    plt::xlabel("x");
    plt::ylabel("P(X>x)");
    plt::named_plot("simulated",x_val_e,y_val_e);
    plt::named_plot("theory",x_val_exp_e,y_val_exp_e);
    plt::legend();

/*
    //test erlang
    int k_er=4;
    double lambda_er = 1;
    Erlang er(lambda_er,k_er,6);
    vector<double> numbers_er;
    double temp_er;
    for(int i =0; i <10000; i++){
        temp_er = er.generate();
        numbers_er.push_back(temp_er);
    }
    sort(numbers_er.begin(),numbers_er.end());

    //find P(X>x)
    double x_er = 0;
    double x_max_er = 0;
    int index_er =0;
    int size_er = numbers_er.size();
    vector<double>x_val_er;
    vector<double>y_val_er;
    for(auto i : numbers_er) {
        x_val_er.push_back(i);
        y_val_er.push_back((double(size_er)-index_er)/size_er);
        x_max_er = i;
        index_er++;
    }

    //expected Erlang P(X>x)
    vector<double>x_val_exp_er;
    vector<double>y_val_exp_er;
    double current_p_er=0;
    double l=0;
    while(l < x_max_er){
        double sum = 0;
        for (int i = 0; i <= k_er-1; i++){
            sum = sum + ((1/fact(i))*(exp(-1*lambda_er*l))*pow((lambda_er*l),i));
        }
        x_val_exp_er.push_back(l);
        y_val_exp_er.push_back(sum);
        l = l + 0.1;
    }

    //plot erlang result
    plt::figure(4);
    plt::plot(x_val_er,y_val_er);
    plt::plot(x_val_exp_er,y_val_exp_er);
*/

    //test mm1
    double lambda = 5;
    double mu = 6;
    double rho = lambda/mu;
    MM1 m(lambda,mu);
    int run_time = 10800; //1 day
    for(int i =0; i < run_time ; i++){
        m.tick();
    }
    cout << "\n\n";
    map<int,double>::iterator it;
    vector<double>x_mm1;
    vector<double>y_mml;
    vector<double>y_mm1_exp;
    double expected_n_mm1 = 0;
    double expected_n_mm1_act = 0;
    for (it = m.customer_state.begin(); it != m.customer_state.end(); it++){
        //cout << it->first << " expected: " << pow(rho,(it->first))*(1-rho) << " actual: " << it->second/run_time << "\n";
        x_mm1.push_back(it->first);
        y_mml.push_back(it->second/run_time);
        y_mm1_exp.push_back(pow(rho,(it->first))*(1-rho));

        expected_n_mm1_act = expected_n_mm1_act + (it->first*(it->second/run_time));
        expected_n_mm1 = expected_n_mm1 + (it->first*(pow(rho,(it->first))*(1-rho)));
    }

    //plot mm1 result
    plt::figure(5);
    plt::title("MM1 Pn vs n for lambda = 5 and mu = 6");
    plt::xlabel("n");
    plt::ylabel("Pn");
    plt::named_plot("simulated",x_mm1,y_mml);
    plt::named_plot("theory",x_mm1,y_mm1_exp);
    plt::legend();

    cout <<"MM1 Queue Simulation Resuls" << "\n";
    cout << "Expected number in Queue (Theory): " << expected_n_mm1 << "\n";
    cout << "Expected number in Queue (Simulated): " << expected_n_mm1_act << "\n";
    cout << "Expected wait time (Theory): " << expected_n_mm1/lambda << "\n";
    cout << "Expected wait time (Simulated): " << m.expected_wait() << "\n";
    cout << "\n\n";

    //test mmek1
    int k_mek1 = 4;
    lambda = 5;
    mu = 6*k_mek1;
    rho = lambda/mu;
    MEk1 mek(lambda,mu,k_mek1);
    run_time = 10800; //1 day
    for(int i =0; i < run_time ; i++){
        mek.tick();
    }
    cout << "\n\n";
    map<int,double>::iterator it_ek;
    vector<int>x_mm1_ek;
    vector<double>y_mml_ek;
    expected_n_mm1_act = 0;
    for (it_ek = mek.customer_state.begin(); it_ek != mek.customer_state.end(); it_ek++){
        //cout << it->first << " expected: " << pow(rho,(it->first))*(1-rho) << " actual: " << it->second/run_time << "\n";
        x_mm1_ek.push_back(it_ek->first);
        y_mml_ek.push_back(it_ek->second/run_time);

        expected_n_mm1_act = expected_n_mm1_act + (it_ek->first*(it_ek->second/run_time));
    }

    cout << "MEk1 Queue Simulation Resuls" << "\n";
    cout << "Expected number in Queue (Simulated): " << expected_n_mm1_act << "\n";
    cout << "Expected wait time (Simulated): " << mek.expected_wait() << "\n";
    cout << "\n\n";

    plt::figure(6);
    plt::plot(x_mm1_ek,y_mml_ek);
    plt::title("MEk1 with lambda =4 mu =6 and k=4");
    plt::xlabel("n");
    plt::ylabel("Pn");

    plt::figure(7);
    double counter = 0;

    vector<double>rho_states;
    vector<double>En;
    vector<double>DEn;

    while (counter < 4.9){

        //plt::plot(x_mm1_ek,y_mml_ek);
        //test mmek1
        k_mek1 = 40;
        lambda = 1 + counter;
        mu = 6*k_mek1;
        rho = lambda/6;

        rho_states.push_back(rho);

        MEk1 mek1(lambda,mu,k_mek1);
        run_time = 10800; //1 hour
        for(int i =0; i < run_time ; i++){
            mek1.tick();
        }

        expected_n_mm1_act = 0;
        for (it_ek = mek1.customer_state.begin(); it_ek != mek1.customer_state.end(); it_ek++){

            expected_n_mm1_act = expected_n_mm1_act + (it_ek->first*(it_ek->second/run_time));
        }

        counter = counter + 1;

        double d_en = rho/(1-rho)*(1-(rho/2));
        En.push_back(expected_n_mm1_act);
        DEn.push_back(d_en);

    }

    plt::title("MEk1 for lambda = 1 to 5.9, rho vs En");
    plt::xlabel("rho");
    plt::ylabel("En");
    plt::named_plot("MEk1",rho_states,En);
    plt::named_plot("MD1",rho_states,DEn);
    plt::legend();
    plt::show();

}