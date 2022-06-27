//
//  main.cpp
//  
//
//  Created by Chiara Mascherpa on 17/03/22.
//

#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>
#include "../../Random/random.h"
#include "../../Librerie/Integral.h"

using namespace std;

double my_func(double x) {
    return M_PI/2.*cos(M_PI/2.*x);                 // Integral needing computing
}

double my_distr(double x){
    return 1-sqrt(1-x);                            // Distribution for the importance sampling
}

double my_val (double x){
    return my_func(x)/2/(1-x);                     // Dividing the integral by the comulative function
}

int main(){
    
    int M=pow(10,8);                               // Number of throws
    int N=pow(10,2);                               // Number of blocks
    int L=(int) M/N;                               // Number of throws per block
    
    Integral integral (0, 1, my_func);             // To integrate the function of the exercise
    Integral integral2 (0,1, my_val);              // To integrate using importance sampling
    
    double ave=0;                                  // Saving all sum without importance sampling
    double av2=0;
    
    double aveb=0;                                 // Saving all sum with importance sampling
    double av2b=0;
    
    ofstream output;
    output.open ("File.out");
    
    output<<M<<" "<<N<<endl;
    
    for(int i=0; i<N; i++){
        
        double a=integral.MediaInt(L);              // Generating points using the two probability distribution
        double b=integral2.Distr(L, my_distr);
        
        ave+=a;
        av2+=pow(a,2);
        
        aveb+=b;
        av2b+=pow(b,2);
        
        output<<ave/(i+1)<<" ";
        output<<aveb/(i+1)<<" ";
        
        if(i==0){
            output<<0<<" ";
            output<<0<<endl;
        }
        else{
            output<<sqrt((av2/(i+1) - pow(ave/(i+1),2))/(i))<<" ";
            output<<sqrt((av2b/(i+1) - pow(aveb/(i+1),2))/(i))<<endl;
        }
    }
    
    return 0;
    
}
