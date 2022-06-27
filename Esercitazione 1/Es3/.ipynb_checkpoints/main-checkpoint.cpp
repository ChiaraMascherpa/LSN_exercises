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
    int seed[4];
    int p1, p2;
    
    ifstream Primes("../../Random/Primes");
    if (Primes.is_open()){
       Primes >> p1 >> p2 ;
    } else cerr << "PROBLEM: Unable to open Primes" << endl;
    Primes.close();

    ifstream input("../../Random/seed.in");
    string property;
    if (input.is_open()){
       while ( !input.eof() ){
          input >> property;
          if( property == "RANDOMSEED" ){
             input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
             rnd.SetRandom(seed,p1,p2);
          }
       }
        input.close();
     } else cerr << "PROBLEM: Unable to open seed.in" << endl;

    
    double L=2;
    double d=3;
    int M=pow(10,4);        //numero throws totale
    int N=100;              //numero blocchi
    int N_throws=M/N; //numero throws per blocco
    
    ofstream output;
    output.open("Pi.out");
    
    double ave=0;
    double ave2=0;
    
    for (int k=0; k<N; k++){
        
        int N_hit=0;
        
        for(int i=0; i<N_throws; i++){
            
            double x=rnd.Rannyu(0,d);
            double x1=0;
            double y1=0;
            double r=0;
            
            do{
                x1=rnd.Rannyu(-L,L);
                y1=rnd.Rannyu(-L,L);
                
                r=sqrt((x1)*(x1)+y1*y1);
                
            }while (r>L);
            
            
            if(x1/r*L+x<0 or x1/r*L+x>d) N_hit++;
            
        }
        
        ave+=2*L*N_throws/(N_hit*d);
        ave2+=pow(2*L*N_throws/(N_hit*d),2);
        
        
        
        output<<ave/(k+1)<<" ";
        if(k==0) output<<0<<endl;
        else output<<((ave2/(k+1) - pow(ave/(k+1),2))/(k))<<endl;
    }
    
    
    return 0;
}
