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
#include "../travelling_salesman.hpp"
#include "../../Random/random.h"

using namespace std;

const int nstep=100;

const double mutation_prop=0.3, crossover_prop=0.6;

int main(){

    ifstream input;
    
    input.open("../American_capitals.dat");
    cout<<"Reading american capitals from file.dat"<<endl;
    
    vector <City> cities;
    
    int label=0;
    while(!input.eof()){
        string state, name;
        double x,y;
        input>>state>>name>>x>>y;
        City city(x,y, label, state, name);
        cities.push_back(city);
        label++;
        
    }
    
    cout<<"Finished reading data"<<endl;
    
    cout<<"Cities read: "<<cities.size()<<endl;
    
    input.close();
    
    Travelling_salesman salesman(cities.size(), cities);
    
    salesman.Starting_Population();
    
    salesman.Check();
    
    Random rnd;
    
    rnd.Initialize();

    
    ofstream output, output2, output1;
    
    output.open("ave_path.out");
    output2.open("best.out");
    
    Path best=salesman.BestPath();
    
    cout<<setw(10)<<"step"<<setw(15)<<"L(best path)"<<setw(15)<<"<L>"<<endl;
    
    int j=0;
    
    for(int i=0; i<nstep; i++){
        
        vector <double> fit_tot=salesman.Ave_Fit();
        
        output<<i+1<<" "<<fit_tot[0]<<" "<<fit_tot[1]<<endl;
        
        output2<<i+1<<" "<<salesman.BestPath().GetFit()<<endl;
        
        cout<<setw(10)<<i+1<<setw(15)<<salesman.BestPath().GetFit()<<setw(15)<<fit_tot[0]<<endl;
        
        if(salesman.BestPath().GetFit()<best.GetFit()) {
            
            output1.open("path"+to_string(j)+".out");
            
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
    
    output3.open("final.out");
    
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
