//
//  main.cpp
//  
//
//  Created by Chiara Mascherpa on 17/03/22.
//

#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include "../../Random/random.h"

using namespace std;

int main (){
    
    Random rnd;
    rnd.Initialize();
    
    double a=1;
    int N=100;                                   // Number of blocks
    int M=100;                                   // Number of rw per block
    int L=100;                                   // Number of step per rw
    
    
    double *d   = new double [L];                // Saving the distance from the origin in each block at any given step
    double *ave = new double [L];                // Saving the distance of all blocks at any given step
    double *ave2= new double [L];                // Saving the square distance of all blocks at any given step
    
    //Discrete RW
    ofstream output;
    output.open("Discrete_RW.out");
    
    output<<M<<" "<<N<<" "<<L<<endl;
    output<<0<<" "<<0<<endl;                     // Printing the initial point
    
    
    for(int i=0; i<N; i++){
        
        for(int k=0; k<L; k++) d[k]=0;           // Reinitializing the distance array at the beginning of each block
        
        for(int k=0; k<M; k++){
            
            double x=0;                          // Coordinates
            double y=0;
            double z=0;
            
            for(int j=0; j<L; j++) {
                int t=rnd.Standard_Dice(2);      // Choosing if the step is forward of backwards
                int add=0;
                if(t==1) add=-a;
                if(t==2) add=a;
                t=rnd.Standard_Dice(3);          // Choosing the axis of the step
                if(t==1) x+=add;
                if(t==2) y+=add;
                if(t==3) z+=add;
                
                d[j]+=x*x+y*y+z*z;
            }
        }
                
        for(int j=0; j<L; j++) {
                
            ave[j]+=d[j];
            ave2[j]+=d[j]*d[j];
        }

    }
            
    for(int j=0; j<L; j++) {
                    
            output<<sqrt(ave[j]/N/M)<<" ";
            double err = sqrt((ave2[j]/N/M-ave[j]*ave[j]/(N*N*M*M))/(N-1));
                              
            output<<0.5/sqrt(ave[j])*err<<endl;
            }
    
    //Rw in the continuum
    output.close();
    output.open("Continuos_RW.out");
    
    output<<M<<" "<<N<<" "<<L<<endl;
    output<<0<<" "<<0<<endl;                     // Printing the initial point
   
    for(int k=0; k<L; k++) {
        ave[k]=0;
        ave2[k]=0;
    }
    
    for(int i=0; i<N; i++){
        
        for(int k=0; k<L; k++) d[k]=0;           // Reinitializing the distance array at the beginning of each block
        
        for(int k=0; k<M; k++){
            
            double x=0;                          // Coordinates
            double y=0;
            double z=0;
            
            for(int j=0; j<L; j++) {
                double cos_t=rnd.Rannyu(-1,1);      //Generating the cosene uniformly to keep memory of the Jacobian sin(theta) of the polar coordinates
                double sin_t=sqrt(1-pow(cos_t,2));  //The sine has to be positive for theta is in [0, pi]
                double p=rnd.Rannyu(0,2*M_PI);      //Phi is simply uniformly distributed
                
                x+=sin_t*cos(p)*a;
                y+=sin_t*sin(p)*a;
                z+=cos_t*a;
                
                d[j]+=x*x+y*y+z*z;
            }
        }
                
        for(int j=0; j<L; j++) {
                
            ave[j]+=d[j];
            ave2[j]+=d[j]*d[j];
        }

    }
            
    for(int j=0; j<L; j++) {
                    
            output<<sqrt(ave[j]/N/M)<<" ";
            double err = sqrt((ave2[j]/N/M-ave[j]*ave[j]/(N*N*M*M))/(N-1));
                              
            output<<0.5/sqrt(ave[j])*err<<endl;
            }

    output.close();
    
    return 0;
}
