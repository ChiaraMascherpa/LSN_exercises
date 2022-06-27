//
//  main.cpp
//  
//
//  Created by Chiara Mascherpa on 11/03/22.
//

#include <iostream>
#include <cmath>
#include <fstream>
#include "../../Random/random.h"

using namespace std;

int main(){
    
    Random rnd;
    rnd.Initialize();

    
    double L=2;             // Lenght of the needle
    double d=3;             // Distance between each line
    int M=pow(10,5);        // Number of throws
    int N=100;              // Number of blocks
    int N_throws=M/N;       // Number of throws per block
    
    ofstream output;
    output.open("Pi.out");
    
    output<<M<<" "<<N<<" "<<L<<" "<<d<<endl; // printing the initial value of the system
    
    double ave=0;          //Saving the mean values of pi
    double ave2=0;         //Saving the squares of the main values

    
    for (int k=0; k<N; k++){
        
        int N_hit=0;
        
        for(int i=0; i<N_throws; i++){
            
            double x=rnd.Rannyu(0,d);
            double x1=0;
            double y1=0;
            double r=0;
            
            do{
                x1=rnd.Rannyu(-1,1);
                y1=rnd.Rannyu(-1,1);
                
                r=sqrt((x1)*(x1)+y1*y1);
                
            }while (r>1);
            
            
            if(x1/r*L+x<0 or x1/r*L+x>d) N_hit++;
            
        }
        
        ave+=2*L*N_throws/(N_hit*d);
        ave2+=pow(2*L*N_throws/(N_hit*d),2);
        
        
        
        output<<ave/(k+1)<<" ";
        if(k==0) output<<0<<endl;
        else output<<sqrt((ave2/(k+1) - pow(ave/(k+1),2))/k)<<endl;
    }
    
    
    return 0;
}
