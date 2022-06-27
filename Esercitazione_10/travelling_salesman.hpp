//
//  travelling_salesman.hpp provaaaa
//  
//
//  Created by Chiara Mascherpa on 19/05/22.
//

#ifndef travelling_salesman_hpp
#define travelling_salesman_hpp

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include "../Random/random.h"

using namespace std;

class Coordinates{
    public:
    
        Coordinates(double x, double y){
            m_x=x;
            m_y=y;
        }
        double getX() const {return m_x;};                  // Coordinate cartesiane
        double getY() const {return m_y;};
        double getT() const {return atan(m_y/m_x);};         //Coordinate polari
        double gerR() const {return sqrt(m_x*m_x+m_y*m_y);};
    
        void Setx(double x) {m_x=x;};
        void Sety(double y) {m_y=y;};
    
        ~Coordinates() {};
    
    private:
        double m_x, m_y;
};

double Distance(Coordinates c1, Coordinates c2);


class City{
    public:
        City(double x, double y, int label, string state, string name) : m_coordinates(x,y){
            m_label=label;
            m_state=state;
            m_name=name;
        };
        City(int label, double x, double y) : m_coordinates(x,y){
            m_label=label;
        };
    
        unsigned int GetLabel() {return m_label;};
        Coordinates GetCoordinates() {return m_coordinates;};
        
        void SetLabel(unsigned int label) {m_label=label;};
    
        ~City() {};
    
    private:
        Coordinates m_coordinates;
        unsigned int m_label;
        string m_state;
        string m_name;
};

double Distance(City c1, City c2);

class Path{
    
    public:
    
        Path(vector <City> path){
            m_path=path;
            /*m_fit=0;
            for(int i=0; i<m_path.size()-1; i++) m_fit+=Distance(m_path[i], m_path[i+1]);
            m_fit+=Distance(m_path[0], m_path[m_path.size()-1]);*/
        };
        
        Path(){};
    
        vector <City> GetPath() {return m_path;};
        unsigned int GetDim() {return m_path.size();};
    
        void SetPath(vector <City> path){m_path=path;};
        
        void Fit();
        double GetFit();
        void Shorten(unsigned int i);
        void Insert(vector <City> a, unsigned int i);
        void Insert(unsigned int i, unsigned int j, unsigned int k);
        void Swap(unsigned int i1, unsigned int i2);
        void Shift(unsigned int shift, unsigned int first, unsigned int last);
        void Reverse(unsigned int first, unsigned int last);
        void Rotate(unsigned int first, unsigned int last, unsigned int r);
    
        ~Path() {};
    
    private:
        vector <City> m_path;
        double m_fit;
        
};

class Travelling_salesman {
    
    public:
        Travelling_salesman(unsigned int N, vector <City> c, vector <Path> population){
            m_N=N;
            m_cities=c;
            m_population=population;
            rnd.Initialize();
        };
        
        Travelling_salesman(unsigned int N, vector <City> c, vector <Path> population, int line){
            m_N=N;
            m_cities=c;
            m_population=population;
            rnd.Initialize(line);
        };
    
        Travelling_salesman(unsigned int N, vector <City> c){
            m_N=N;
            m_cities=c;
            rnd.Initialize();
        };
        
        Travelling_salesman(unsigned int N, vector <City> c, int line){
            m_N=N;
            m_cities=c;
            rnd.Initialize(line);
        };
        
        void Check();
    
        void Starting_Population();
    
        vector <Path> Crossover( double crossover_prob, unsigned int i, unsigned int j);
        
        void New_Generation(double crossover_prob, double mutation_prob);
        
        void Mutation1(double mutation_prob, unsigned int k);
        void Mutation2(double mutation_prob, unsigned int k);
        void Mutation3(double mutation_prob, unsigned int k);
        void Mutation4(double mutation_prob, unsigned int k);
    
        unsigned int GetN() {return m_N;};
    
        vector <City> GetCities() {return m_cities;};
        vector <Path> GetPopulation() {return m_population;};
    
        Path BestPath();
        void ChangeBest(int *labels);
        void ChangeWorst(int *labels);
        vector <double> Ave_Fit();
    
        ~Travelling_salesman() {};
    
    private:
        unsigned int m_N;                     //total number of cities
        vector <Path> m_population;           //vector of possible genetic codes
        vector <City> m_cities;               //keeping track of all the cities
        Random rnd;
    
};

//add find

#endif /* travelling_salesman_hpp */
