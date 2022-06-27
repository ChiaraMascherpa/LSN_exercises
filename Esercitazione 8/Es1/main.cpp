//
//  es8.cpp
//  
//
//  Created by Chiara Mascherpa on 12/05/22.
//

#include "../../Librerie/Integral.h"
#include "../../Random/random.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

const double sigma=0.666432, mu=0.876166;

const int n_punti=5000, n_eq=10;

const double x_0=0, dx=0.1;

double psi_squared(double x){
    
    double s1=pow((x+mu)/sigma,2);
    double s2=pow((x-mu)/sigma,2);
    
    double e1=exp(-s1/2);
    double e2=exp(-s2/2);
    
    return pow(e1+e2,2);
}

double V(double x){
    return pow(x,4)-5./2.*pow(x,2);
    //return pow(x,2)/2; //per provare a verificare se funziona con potenziale armonico
}

double E(double x){
    
    double s1=pow((x+mu)/sigma,2);
    double s2=pow((x-mu)/sigma,2);
    
    double e1=exp(-s1/2);
    double e2=exp(-s2/2);
    
    return -(s2*e2+s1*e1-e1-e2)/(e1+e2)/(2*sigma*sigma)+V(x);
}


int main(){
    
    Random rnd;
    rnd.Initialize();
    
    ofstream output;
    output.open("Integral.out");
    
    Integral integ(E);
    
   
    int M=10000;             // Total number of throws
    int N=20;                // Number of blocks
    int L=int(M/N);           // Number of throws in each block, please use for M a multiple of N
    
    double ave=0;
    double av2=0;
    
    for(int i=0; i<N; i++){
        
        double sum  = 0;
        double sum_inc = 0;
            
        for (int j=0; j<L; j++){
            double r=integ.Metropolis(n_punti,psi_squared,x_0,dx,n_eq);
            sum += r ;                  //saving the mean value in each block
            sum_inc += pow(r-0.5,2);    //saving the discrepancy in each block
        }
                
            ave += sum/L;                            // r_i
            output<<ave/(i+1)<<" ";                  // printing the mean until this block
            av2 += pow(sum/L,2);                     // (r_i)^2
            if(i==0) output<<0<<" ";
            else output<<sqrt((av2/(i+1) - pow(ave/(i+1),2))/(i))<<" ";
            
            output<<endl;

    }

    
    
    output.close();
    
    return 0;
    
}

