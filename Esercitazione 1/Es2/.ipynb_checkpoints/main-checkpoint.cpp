//
//  main.cpp
//  
//
//  Created by Chiara Mascherpa on 10/03/22.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include "../../Random/random.h"

using namespace std;

int main(){
    Random rnd;                     // Creating the Pseudo-Random number Generator
    rnd.Initialize();               // Giving him the seeds

    int M[] = {1,2,10,100};         // Number of points in each mean value Sm
    int N=pow(10,4);                // Number of times Sm is calculated
    ofstream output;
    output.open("Exp.out");
    
    ofstream output1;
    output1.open("Lor.out");
    
    ofstream output2;
    output2.open("Std.out");
    
    output<<N<<endl;
    output1<<N<<endl;
    output2<<N<<endl;
    
    for(int i=0; i<4; i++){        //printing in each column the number of points in each Sm
        output<<M[i]<<" ";
        output1<<M[i]<<" ";
        output2<<M[i]<<" ";
    }
    
    output<<endl;
    output1<<endl;
    output2<<endl;

    
    for (int k=0; k<N; k++){
        
        for(int i=0; i<4; i++){
            
            double sum=0;
            double sum1=0;
            double sum2=0;
            
            for(int j=0; j<M[i]; j++){
                
                //generating a random value
                double t=rnd.Rannyu();              //uniformly distributed between [0,1)
                double r=rnd.Exponential(1.);       //with an exponential distribution
                double s=rnd.Cauchy(0.,1.);         //with a lorenzian distribution
                
                //saving the mean value in each block
                sum+=r;                             //for the Exponential dice
                sum1+=s;                            //for the Lorenzian dice
                sum2+=t;                            //for the Standard dice
            }
            
            //diving for the number of points on which each Sm is computed
            sum/=M[i];
            sum1/=M[i];
            sum2/=M[i];
            
            //printing the values
            output<<sum<<" ";
            output1<<sum1<<" ";
            output2<<sum2<<" ";
        }
        
        output<<endl;
        output1<<endl;
        output2<<endl;
    }
    
    output.close();
    output1.close();
    output2.close();
    
    return 0;
}
