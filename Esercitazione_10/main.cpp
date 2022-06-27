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
#include "mpi.h"

using namespace std;

const int nstep=100;

const double mutation_prop=0.1, crossover_prop=0.5;

int main(){
    
    MPI_Init(NULL,NULL);
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status stat1, stat2;
    MPI_Request req;
    
    ifstream input;
    
    input.open("American_capitals.dat");
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

    input.close();
    
    Travelling_salesman salesman(cities.size(), cities, rank);
    
    salesman.Starting_Population();
    
    salesman.Check();
    
    Random rnd;
    
    rnd.Initialize();
    
    //vector <Path> all_best(size);
    
    //all_best[rank]=salesman.BestPath();

    for(int i=0; i<nstep; i++){
        
        salesman.New_Generation(crossover_prop,mutation_prop);

    cout<<"Fatta la generazione "<<i<<endl;
        
        vector <int> couples;
        
        if(i%5==0 and i!=0){
            
            for(int j=0; j<size; j++) couples.push_back(j);
    
            random_shuffle(couples.begin(), couples.end());
            
            int *b_couples= new int(size);

            for(int j=0; j<size; j++) b_couples[j]=couples[j];
            
            MPI_Barrier(MPI_COMM_WORLD);

            MPI_Bcast(b_couples,size, MPI_INTEGER ,0, MPI_COMM_WORLD);
                
            int *labels=new int [salesman.GetN()];
            MPI_Barrier(MPI_COMM_WORLD);
        
            for(int j=0; j<size; j+=2){
                
                if(rank==b_couples[j]){
                    
                    Path best=salesman.BestPath();
                    for(int k=0; k<salesman.GetN(); k++) labels[k]=best.GetPath()[k].GetLabel();
                    


                    MPI_Isend(labels,salesman.GetN(),MPI_INTEGER,b_couples[j+1],0, MPI_COMM_WORLD,&req);
                    MPI_Recv(labels,salesman.GetN(),MPI_INTEGER,b_couples[j+1],1, MPI_COMM_WORLD,&stat2);
                }
                
                if(rank==b_couples[j+1]){
                    
                    Path best=salesman.BestPath();
                    for(int k=0; k<salesman.GetN(); k++) labels[k]=best.GetPath()[k].GetLabel();
                    
                    MPI_Send(labels,salesman.GetN(),MPI_INTEGER,b_couples[j],1, MPI_COMM_WORLD);
                    MPI_Recv(labels,salesman.GetN(),MPI_INTEGER,b_couples[j],0, MPI_COMM_WORLD,&stat1);
                }
            }
            
            salesman.ChangeBest(labels);

            delete []labels;
            delete []b_couples;
            
        }
        
    }
    
    /*cout<<"qua";
    
    int *recv=new int [salesman.GetN()*size];
    cout<<"qua";
    
    int *isend=new int [salesman.GetN()];
    
    for(int j=0; j<salesman.GetN(); j++) isend[j]=salesman.BestPath().GetPath()[j].GetLabel();
    cout<<"qua1";
    
    MPI_Barrier(MPI_COMM_WORLD);
    cout<<"qua2";
    
    //MPI_Gather(&isend,salesman.GetN(),MPI_INTEGER,recv,salesman.GetN()*size,MPI_INTEGER,0, MPI_COMM_WORLD);
 
    cout<<"qua3";
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    cout<<"qua4";

    Path all_best;
    
    if(rank==0){
		
        int t=0;
        double fit=0;
        for(int j=0; j<size; j++){
            Path prova;
            
            cout<<"qua5";
            
            for(int k=0; k<salesman.GetN(); k++){
                
                for(int l=0; l<salesman.GetN(); l++){
                    if(recv[t]==cities[l].GetLabel()) prova.GetPath().push_back(cities[l]);
                }
                t++;
                
            }
            
            if(j==0) {
                fit=prova.GetFit();
                all_best=prova;
            }
            
            else{
                if(fit>prova.GetFit()){
                    fit=prova.GetFit();
                    all_best=prova;
                }
            }
        }
        
        cout<<"Best Path: ";
        
        ofstream output3;
        
        output3.open("final.out");
        
        output3<<all_best.GetFit()<<endl;
        
        for(int i=0; i<salesman.GetN(); i++) {
            output3<<all_best.GetPath()[i].GetLabel()<<" "<<all_best.GetPath()[i].GetCoordinates().getX()<<" "<<all_best.GetPath()[i].GetCoordinates().getY()<<endl;
            cout<<all_best.GetPath()[i].GetLabel();
        }
        output3<<all_best.GetPath()[0].GetLabel()<<" "<<all_best.GetPath()[0].GetCoordinates().getX()<<" "<<all_best.GetPath()[0].GetCoordinates().getY()<<endl;
        cout<<endl;
	
	cout<<"lenght of the best path: "<<all_best.GetFit();        

        output3.close();
    }*/
    
    ofstream output3;

	Path all_best=salesman.BestPath().GetPath();
        
    output3.open("final"+to_string(rank)+".out");
        
    output3<<all_best.GetFit()<<endl;
        
    for(int i=0; i<salesman.GetN(); i++) {
            output3<<all_best.GetPath()[i].GetLabel()<<" "<<all_best.GetPath()[i].GetCoordinates().getX()<<" "<<all_best.GetPath()[i].GetCoordinates().getY()<<endl;
        }
        output3<<all_best.GetPath()[0].GetLabel()<<" "<<all_best.GetPath()[0].GetCoordinates().getX()<<" "<<all_best.GetPath()[0].GetCoordinates().getY()<<endl;
        
        output3.close();
    
    MPI_Finalize();
    
    return 0;
}
