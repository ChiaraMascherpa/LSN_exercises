//
//  prova.cpp
//  
//
//  Created by Chiara Mascherpa on 20/05/22.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include "travelling_salesman.hpp"
#include "../Random/random.h"

using namespace std;

const int nstep=100;

const double mutation_prop=0.1, crossover_prop=0.6;

int main(){

    cout<<"To use cities on a circle type 0, to use cities on a square type 1"<<endl;
    
    int type;
    cin>>type;
    
    while(type!=0 and type!=1) {
        cout<<"Only 0 and 1 are accepted"<<endl<<"To use cities on a circle type 0, to use cities on a square type 1"<<endl;
        cin>>type;
    }
    
    ifstream input;
    
    if(type==0) {
        input.open("circle.dat");
        cout<<"Reading data from circle.dat"<<endl;
    }
    else {
        input.open("square.dat");
        cout<<"Reading data from square.dat"<<endl;
    }
    vector <City> cities;
    
   
    while(!input.eof()){
        int label=0;
        double x,y;
        input>>label>>x>>y;
        City city(label,x,y);
        cities.push_back(city);
    }
    
    cout<<"Finished reading data"<<endl;
    
    cout<<"Cities read: "<<cities.size()<<endl;
    
    input.close();
    
    Travelling_salesman salesman(cities.size(), cities);
    
    salesman.Starting_Population();
    
    Random rnd;
    
    rnd.Initialize();
    
    ofstream output, output2, output1;
    
    string dir;
    if(type==0) dir = "Circle/";
    else dir="Square/";
        
    output.open(dir+"ave_path.out");
    output2.open(dir+"best.out");
    
    Path best=salesman.BestPath();
    
    cout<<setw(10)<<"step"<<setw(15)<<"L(best path)"<<setw(15)<<"<L>"<<endl;
    
    int j=0;
    
    for(int i=0; i<nstep; i++){
        
        vector <double> fit_tot=salesman.Ave_Fit();
        
        output<<i+1<<" "<<fit_tot[0]<<" "<<fit_tot[1]<<endl;
        
        output2<<i+1<<" "<<salesman.BestPath().GetFit()<<endl;
        
        cout<<setw(10)<<i+1<<setw(15)<<salesman.BestPath().GetFit()<<setw(15)<<fit_tot[0]<<endl;
        
        if(salesman.BestPath().GetFit()<best.GetFit()) {
            
            output1.open(dir+"path"+to_string(j)+".out");
            
            best=salesman.BestPath();
            
            output1<<best.GetFit()<<endl;
            
            for(int k=0; k<salesman.GetN(); k++) output1<<best.GetPath()[k].GetLabel()<<" "<<best.GetPath()[k].GetCoordinates().getX()<<" "<<best.GetPath()[k].GetCoordinates().getY()<<endl;
            
            output1<<best.GetPath()[0].GetLabel()<<" "<<best.GetPath()[0].GetCoordinates().getX()<<" "<<best.GetPath()[0].GetCoordinates().getY()<<endl;
            
            j++;
        }

        
        salesman.New_Generation(crossover_prop,mutation_prop);
        
        output1.close();
        
    }
    
    output.close();
    output2.close();
    
    
    
    
    
    cout<<"Best Path: ";
    
    ofstream output3;
    
    output3.open(dir+"final.out");
    
    output3<<best.GetFit()<<endl;
    
    for(int i=0; i<salesman.GetN(); i++) {
        output3<<best.GetPath()[i].GetLabel()<<" "<<best.GetPath()[i].GetCoordinates().getX()<<" "<<best.GetPath()[i].GetCoordinates().getY()<<endl;
        cout<<best.GetPath()[i].GetLabel();
    }
    output3<<best.GetPath()[0].GetLabel()<<" "<<best.GetPath()[0].GetCoordinates().getX()<<" "<<best.GetPath()[0].GetCoordinates().getY()<<endl;
    cout<<endl;
    
    output3.close();
     
    return 0;
}
