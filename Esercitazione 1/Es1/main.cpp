//
//  Es01.cpp
//  
//
//  Created by Chiara Mascherpa on 10/03/22.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "../../Random/random.h"

using namespace std;

int main(){
    
        Random rnd;               // Creating the Pseudo-Random number Generator
        rnd.Initialize();         // Giving him the seeds
        int M=100000;             // Total number of throws
        int N=100;                // Number of blocks
        int L=int(M/N);           // Number of throws in each block, please use for M a multiple of N
    
        double ave=0;             //Saving the mean values
        double av2=0;             //Saving the squares of the main values
        double ave_inc=0;         //Saving the discrepancies from the expected value
        double av2_inc=0;         //Saving the squares of the discrepancies

        
        ofstream output;          //Opening the channels for the output
        output.open("mean.out");
    
        ofstream output2;
        output2.open("var.out");
    
        output<<M<<" "<<N<<endl;
    
        output2<<M<<" "<<N<<endl;
            
        for (int i=0; i<N; i++){
            double sum  = 0;
            double sum_inc = 0;
            
            for (int j=0; j<L; j++){
                double r=rnd.Rannyu();      //uniform number between [0,1)
                sum += r ;                  //saving the mean value in each block
                sum_inc += pow(r-0.5,2);    //saving the discrepancy in each block
            }
                
            ave += sum/L;                            // r_i
            output<<ave/(i+1)<<" ";                  // printing the mean until this block
            av2 += pow(sum/L,2);                     // (r_i)^2
            if(i==0) output<<0<<" ";
            else output<<sqrt((av2/(i+1) - pow(ave/(i+1),2))/(i))<<" ";
            
            output<<endl;
            
            ave_inc += sum_inc/L;        // r_i
            output2<<ave_inc/(i+1)<<" ";
            av2_inc += pow(sum_inc/L,2); // (r_i)^2
            if(i==0) output2<<0<<" ";
            else output2<<sqrt((av2_inc/(i+1) - pow(ave_inc/(i+1),2))/(i))<<" ";
            
            output2<<endl;
            
        }
    
        output.close();
        output2.close();
    
        //chi squared test
        N=10000;            // Number of throws
        int T=100;          // Number of times I'll compute the chi squared
        M=100;              // Number of subintervals
    
        double *distr=new double [M];  //it gives me the number of points in each subintervals
        double d=(double) 1./M;        //width of a single subinterval
    
        ofstream output3;
        output3.open("chi.out");
        output3<<T<<endl;
    
    for (int i=0; i<T; i++){
        
        double chi=0;
        
        for(int j=0; j<M; j++) distr[j]=0; //initializing the array
        for(int j=0; j<N; j++){
            double r=rnd.Rannyu();         //Generating a Random Value between [0,1)
            int x=int(r/d);                //Computing in which subinterval is found
            distr[x]++;                    //Adding 1 in the right subinterval
        }
        
        for (int j=0; j<M; j++) chi+=pow((distr[j]-N/M),2)/(N/M);   //computing the chi square
       
        output3<<chi<<endl;
    }
    
        delete [] distr;
    
        return 0;
}
