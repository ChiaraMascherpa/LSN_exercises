//
//  main.cpp
//  
//
//  Created by Chiara Mascherpa on 31/03/22.
//

#include <iostream>
#include <fstream>
#include "../Random/random.h"
#include <cmath>
#include <algorithm>

using namespace std;

int main () {
    
    int N=100;          // # blocks
    int M=pow(10,4);    // # throws
    int L=int(M/N);     // Number of throws in each block, please use for M a multiple of N
    
    
    
    int t=100;          // #sub intervals
    
    double S_0=100.;    //Starting price
    double T=1.;        //Final time
    double K=100.;      //Agreed price
    double r=0.1;       //Interest that a Bank would have given
    double sigma=0.25;  //Volatility
    
    Random rnd;
    rnd.Initialize();
    
    ofstream output;
    output.open("Direct.out");
    
    double ave_c=0;
    double ave2_c=0;
    
    double ave_p=0;
    double ave2_p=0;
    
    output<<N<<" "<<M<<endl;

    
    //computing evaluting only at the final time
    
    for(int k=0; k<N; k++){
        double sum_c=0;         //saving sum of call profits
        double sum_p=0;         //saving sum of put profits
        
        
        for(int j=0; j<L; j++){
            double w=rnd.Gauss(0,T);                            // normally distributed variable
            
            double S_T=S_0*exp((r-0.5*sigma*sigma)*T+sigma*w);  // final price
            
            sum_c+=exp(-r*T)*max(0., S_T-K);                    //saving profits
            sum_p+=exp(-r*T)*max(0., K-S_T);
            
        }
        
        
        ave_c+= sum_c/L;
        ave2_c+= pow(sum_c/L,2);
        ave_p+= sum_p/L;
        ave2_p+= pow(sum_p/L,2);
        
        
        output<<ave_c/(k+1)<<" "<<ave_p/(k+1)<<" ";
        if(k==0) output<<0<<" "<<0<<endl;
        
        else output<<sqrt((ave2_c/(k+1) - pow(ave_c/(k+1),2))/k)<<" "<<sqrt((ave2_p/(k+1) - pow(ave_p/(k+1),2))/k)<<endl;
       
    }
    
    output.close();
    output.open("Discretized.out");
    
    output<<t<<endl;
    
    // dividing in sub intervals
    
    ave_p=0;        //initializing the variables
    ave_c=0;
    ave2_p=0;
    ave2_c=0;
 
    for(int k=0; k<N; k++){
        
        double sum_c=0;
        double sum_p=0;
        
        for(int j=0; j<L; j++){
            double S_t=S_0;
            
            for(int i=0; i<t; i++){
                double z=rnd.Gauss(0,1);
                S_t=S_t*exp((r-0.5*sigma*sigma)*(T/t)+sigma*z*sqrt(T/t));
            }
            
            sum_c+=exp(-r*T)*max(0., S_t-K);
            sum_p+=exp(-r*T)*max(0., K-S_t);
            
            
        }
        
        
        ave_c+= sum_c/L;
        ave2_c+= pow(sum_c/L,2);
        ave_p+= sum_p/L;
        ave2_p+= pow(sum_p/L,2);
        
        output<<ave_c/(k+1)<<" "<<ave_p/(k+1)<<" ";
        if(k==0) output<<0<<" "<<0<<endl;
        else output<<sqrt((ave2_c/(k+1) - pow(ave_c/(k+1),2))/k)<<" "<<sqrt((ave2_p/(k+1) - pow(ave_p/(k+1),2))/k)<<endl;
    }
    
    
    output.close();
    
    return 0;

}
