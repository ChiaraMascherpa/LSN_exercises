//
//  Integral_m.cpp
//  
//
//  Created by Chiara Mascherpa on 16/05/22.
//

#include "Integral_m.hpp"

using namespace std;

Integral::Integral(const function <double(vector<double>)> f){

   m_f = f;
   m_prec=1.E-6;
   m_myrand = new Random();
   m_myrand->Initialize();
}


Integral::Integral(double a, double b, const function <double(vector<double>)> f){

   m_f = f;
   m_a = min(a,b);
   m_b = max(a,b);
   if ( a > b) m_sign = -1;
   else m_sign = 1;
   m_prec=1.E-6;
   m_myrand = new Random();
   m_myrand->Initialize();
}

Integral::Integral(double a, double b, double prec, const function <double(vector<double>)> f){

   m_f = f;
   m_a = min(a,b);
   m_b = max(a,b);
   if ( a > b) m_sign = -1;
   else m_sign = 1;
   m_prec=prec;
    m_myrand = new Random();
    m_myrand->Initialize();
}


double Integral::Metropolis (int punti,const function <double(vector<double>)> rho, vector <double> dep, double dx, int neq){
    
    m_sum=0;
    attempted=0;
    accepted=0;

    for (int i=0; i<neq; i++){
        
        double x1=m_myrand->Rannyu(dep[0]-dx, dep[0]+dx);
        vector<double> dep1(dep);
        dep1[0]=x1;
        
        if(rho(dep)<rho(dep1)) dep[0]=x1;
        
        else{
            double a=m_myrand->Rannyu();
            double p=(rho(dep1)/rho(dep));
            if (a<p) dep[0]=x1;
        }
    }
    
    for(int i=0; i<punti; i++){
        
        m_sum+=m_f(dep);
        
        double x1=m_myrand->Rannyu(dep[0]-dx, dep[0]+dx);
        vector <double> dep1(dep);
        dep1[0]=x1;

        attempted+=1;
        
        if(rho(dep)<rho(dep1)) {
            dep[0]=x1;
            accepted+=1;
        }
        
        else{
            double a=m_myrand->Rannyu();
            double p=(rho(dep1)/rho(dep));
            
            if (a<p) {
                dep[0]=x1;
                accepted+=1;
            }
        }

    }
        
    m_integral=m_sum/punti;
    
    //cout<<"Acceptance rate: "<<(double)accepted/(double)attempted<<endl;

    return m_integral;

}
