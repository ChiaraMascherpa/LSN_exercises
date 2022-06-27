//
//  es8.cpp
//  
//
//  Created by Chiara Mascherpa on 12/05/22.
//

#include "../../Librerie/Integral_m.hpp"
#include "../../Random/random.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

const double sigma0= 2, mu0= 1;

const int n_punti=10000, n_eq=10;

const double x_0=0, dx=1, bmax=50;

double beta=0.5, dsigma=1, dmu=1;

const double nstep=100, dbeta=1;

double psi_squared(vector <double> v){
    
    double x=v[0];
    double sigma=v[1];
    double mu=v[2];
    
    double s1=pow((x+mu)/sigma,2);
    double s2=pow((x-mu)/sigma,2);
    
    double e1=exp(-s1/2);
    double e2=exp(-s2/2);
    
    return pow(e1+e2,2);
}

double V(double x){
    //return pow(x,4)-5./2.*pow(x,2);
    return pow(x,2)/2; //per provare a verificare se funziona con potenziale armonico
}

double E(vector <double> v){
    double x=v[0];
    double sigma=v[1];
    double mu=v[2];
    
    
    double s1=pow((x+mu)/sigma,2);
    double s2=pow((x-mu)/sigma,2);
    
    double e1=exp(-s1/2);
    double e2=exp(-s2/2);
    
    return -(s2*e2+s1*e1-e1-e2)/(e1+e2)/(2*sigma*sigma)+V(x);
}


int main(){
    
    Random rnd;
    rnd.Initialize();
    
    vector <double> dep(3);
    
    Integral integ(E);
    
    dep[0]=x_0;
    dep[1]=sigma0;
    dep[2]=mu0;
    
    double old_integral = integ.Metropolis(n_punti, psi_squared, dep,dx,n_eq);
    double sigma_old    = dep[1];
    double mu_old       = dep[2];
    
    cout<<"mu = "<<dep[2]<<" sigma = "<<dep[1]<<"  I ="<<old_integral<<endl;
    
    ofstream output1;
    
    output1.open("Integral(beta).out");
    
    double ds=dsigma;
    double dm=dmu;
    
    for(double b=beta; b<bmax; b+=dbeta){
        
        double sum=0;
        double sum2=0;
        
        for(int i=0; i<nstep; i++){
            
             double a=dep[1]-dsigma;
             double d=dep[1]+dsigma;
             if(a<0.2) dep[1] = rnd.Rannyu(0.2, dep[1]+dsigma);
             else{
                 if(d>10) dep[1] = rnd.Rannyu(a, 10);
                 else dep[1] = rnd.Rannyu(a, d);
             }

             dep[2]    = fabs(rnd.Rannyu(dep[2]-dmu, dep[2]+dmu));
            
            double r=integ.Metropolis(n_punti, psi_squared, dep, dx, n_eq);
                
            if(r<old_integral){
                old_integral = r;
                sigma_old    = dep[1];
                mu_old       = dep[2];
            }
                
            else{
                double p = exp(b*(old_integral-r));
                double a = rnd.Rannyu();
                    
                if(a<p){
                    old_integral = r;
                    sigma_old    = dep[1];
                    mu_old       = dep[2];
                }
                    
                else {
                    dep[1] = sigma_old;
                    dep[2] = mu_old;
                }
            }

                
            sum+=old_integral;
            sum2+=old_integral*old_integral;

        }
            
            output1<<setw(15)<<b<<setw(15)<<dep[1]<<setw(15)<<dep[2]<<setw(15)<<sum/nstep<<setw(15)<<sqrt(sum2/nstep-pow(sum/nstep,2))<<endl;
        
        cout<<endl<<"mu = "<<dep[2]<<" sigma = "<<dep[1]<<"  I ="<<old_integral<<endl;
        dsigma=ds/pow(b,1./4.);
        dmu=dm/pow(b,1./4.);
        
    }

               cout<<"Final values: "<<endl;
               cout<<"mu = "<<dep[2]<<endl;
               cout<<"sigma = "<<dep[1]<<endl;
    

   //once mu and sigma are found
    ofstream output;
    output.open("Block_ave.out");
    
    int M=1000;             // Total number of throws
    int N=20;                // Number of blocks
    int L=int(M/N);           // Number of throws in each block, please use for M a multiple of N
    
    double ave=0;
    double av2=0;
    
    for(int i=0; i<N; i++){
        
        double sum  = 0;
            
        for (int j=0; j<L; j++){
            double r=integ.Metropolis(n_punti,psi_squared,dep,dx,n_eq);
            //cout<<r<<endl;
            sum += r ;              //saving the mean value in each block
            
        }
        output<<setw(15)<<i+1;
        ave += sum/L;                            // r_i
        output<<setw(15)<<ave/(i+1);                  // printing the mean until this block
        av2 += pow(sum/L,2);                     // (r_i)^2
        if(i==0) output<<setw(15)<<0;
        else output<<setw(15)<<sqrt((av2/(i+1) - pow(ave/(i+1),2))/(i));
            
        output<<endl;

    }

    
    
    output.close();
    
    

    return 0;
    
}

