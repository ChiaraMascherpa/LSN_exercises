#include "Integral.h"

using namespace std;

Integral::Integral(const function <double(double)> f){

   m_f = f;
   m_prec=1.E-6;
   m_myrand = new Random();
   m_myrand->Initialize();
}


Integral::Integral(double a, double b, const function <double(double)> f){

   m_f = f;
   m_a = min(a,b);
   m_b = max(a,b);
   if ( a > b) m_sign = -1;
   else m_sign = 1;
   m_prec=1.E-6;
   m_myrand = new Random();
   m_myrand->Initialize();
}

Integral::Integral(double a, double b, double prec, const function <double(double)> f){

   m_f = f;
   m_a = min(a,b);
   m_b = max(a,b);
   if ( a > b) m_sign = -1;
   else m_sign = 1;
   m_prec=prec;
    m_myrand = new Random();
    m_myrand->Initialize();
}


double Integral::MediaInt (int punti){

    m_sum=0;

    for (int i=0; i<punti; i++){
        double x=m_myrand->Rannyu(m_a, m_b);
        m_sum=(static_cast<double>(i))/(static_cast<double>(i+1))*m_sum+1./(static_cast<double>(i+1))*(m_f(x));
    }
    
    m_integral=m_sign*(m_b-m_a)*m_sum;

    return m_integral;

};

double Integral::Distr (int punti, const function <double(double)> f){
    
    m_sum=0;

    for (int i=0; i<punti; i++){
        double x=m_myrand->Param1(f);
        m_sum=(static_cast<double>(i))/(static_cast<double>(i+1))*m_sum+1./(static_cast<double>(i+1))*(m_f(x));
        //m_sum+=m_f(x);
    }
    
    //m_sum/=punti;
    
    m_integral=m_sign*(m_b-m_a)*m_sum;

    return m_integral;

}

double Integral::Metropolis (int punti,const function <double(double)> rho, double x0, double dx, int neq){
    
    m_sum=0;
    attempted=0;
    accepted=0;

    for (int i=0; i<neq; i++){
        
        double x1=m_myrand->Rannyu(x0-dx, x0+dx);
        
        if(rho(x0)<rho(x1)) x0=x1;
        
        else if (m_myrand->Rannyu()<(rho(x1)/rho(x0))) x0=x1;

    }
    
    for(int i=0; i<punti; i++){
        
        m_sum+=m_f(x0);
        
        double x1=m_myrand->Rannyu(x0-dx, x0+dx);
        
        attempted+=1;
        
        if(rho(x0)<rho(x1)) {
            x0=x1;
            accepted+=1;
        }
        
        else if (m_myrand->Rannyu()<(rho(x1)/rho(x0))) {
            x0=x1;
            attempted+=1;
        }

    }
        
    m_integral=m_sum/punti;
    
    //cout<<"Acceptance rate: "<<(double)accepted/(double)attempted<<endl;

    return m_integral;

}
