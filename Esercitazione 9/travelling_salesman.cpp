//
//  travelling_salesman.cpp provaaa
//  
//
//  Created by Chiara Mascherpa on 19/05/22.
//

#include "travelling_salesman.hpp"

double Distance(Coordinates c1, Coordinates c2) {
    //return pow((c1.getX()-c2.getX()),2)+pow((c1.getY()-c2.getY()),2);
    return sqrt(pow((c1.getX()-c2.getX()),2)+pow((c1.getY()-c2.getY()),2));
}

double Distance(City c1, City c2){
    return Distance(c1.GetCoordinates(), c2.GetCoordinates());
}

void Path::Fit(){
    m_fit=0;
    for(int i=0; i<m_path.size()-1; i++) m_fit+=Distance(m_path[i], m_path[i+1]);
    m_fit+=Distance(m_path[0], m_path[m_path.size()-1]);
};

double Path::GetFit(){
    Fit();
    return m_fit;
};

void Path::Shorten(unsigned int i){
    m_path.erase(m_path.begin()+i,m_path.end());
};

void Path::Insert(vector <City> a, unsigned int i){
    int n=m_path.size();
    m_path.insert(m_path.begin()+i, a.begin(), a.end());
    Shorten(m_path.size()+1);
};

void Path::Insert(unsigned int i, unsigned int j, unsigned int k){
    int n=m_path.size();
    
    vector <City> copy;
    
    for(int l=0; l<i; l++) copy.push_back(m_path[l]);
    for(int l=j; l<k; l++) copy.push_back(m_path[l]);
    for(int l=i; l<j; l++) copy.push_back(m_path[l]);
    for(int l=k; l<n; l++) copy.push_back(m_path[l]);
    
    m_path=copy;
};

void Path::Swap(unsigned int i, unsigned int j) {

    City appo = m_path[i];
    m_path[i]=m_path[j];
    m_path[j]=appo;

}

void Path::Shift(unsigned int shift, unsigned int begin, unsigned int end) {

    //the constructor works using [first,last)
    vector<City>::iterator it_1 = m_path.begin()+begin;           //indicating the position of the start of the vector to shift
    vector<City>::iterator it_2 = m_path.begin()+end+1;          //indicating the position of the end of the vector to shift
    vector<City>::iterator it_3 = m_path.begin()+begin-shift;  //indicating the start of the new position of the shifted vector

    vector <City> part1(m_path.begin(), it_3 );    // first part that remains the same because it's before the shift happens
    vector <City> part2(it_3,it_1);                // shifted vector's new position
    vector <City> part3(it_1, it_2);               // shifted vector's old position
    vector <City> part4(it_2, m_path.end());       // final part that remains the same because it's after the chosen element to shift

    m_path.clear();

    m_path.insert(m_path.end(),part1.begin(),part1.end());  //inserting each part at the end
    m_path.insert(m_path.end(),part2.begin(),part2.end());
    m_path.insert(m_path.end(),part3.begin(),part3.end());
    m_path.insert(m_path.end(),part4.begin(),part4.end());
}

void Path::Rotate(unsigned int begin, unsigned int end, unsigned int r) {

    vector<City>::iterator it_1 = m_path.begin()+begin;
    vector<City>::iterator it_2 = m_path.begin()+end+1;
    vector<City>::iterator it_3 = m_path.begin()+r;

    rotate(it_1, it_3, it_2);

}

void Path::Reverse(unsigned int begin, unsigned int end) {

    vector<City>::iterator it_1 = m_path.begin()+begin;
    vector<City>::iterator it_2 = m_path.begin()+end+1;

    reverse(it_1,it_2);

}

void Travelling_salesman::Check(){
    for(int i=0; i<m_population.size(); i++){
        if(m_population[i].GetDim()!=GetN()){
            cerr<<"The "<<i<<"° path dimension is "<<m_population[i].GetDim()<<", which is different from the total number of cities ("<<GetN()<<")";
            exit (-1);
        }
        if(m_population[i].GetPath()[0].GetLabel()!=m_cities[0].GetLabel()){
            cerr<<"The "<<i<<"° path has a different starting city";
            exit (-2);
        }
        

        for(int j=1; j<m_cities.size(); j++){
            int check=0;
            for(int k=1; k<m_cities.size(); k++){
                if(m_cities[j].GetLabel()==m_population[i].GetPath()[k].GetLabel()) check+=1;
            }

            if (check!=1){
                cerr<<"The city in position "<<j<<" appears "<<check<<" times in the "<<i<<"° path";
                exit(-3);
            }
        }
    }
        
};

void Travelling_salesman::Starting_Population(){
    unsigned int npop=pow(m_cities.size(),2);
    vector <City> cities(m_cities);
    
    for(int i=0; i<npop; i++){
        random_shuffle(cities.begin()+1, cities.end());
        Path p(cities);
        m_population.push_back(p);
    }
};

void Travelling_salesman::Mutation1(double mutation_prob, unsigned int k) {

        if(rnd.Rannyu()<mutation_prob) {
            
            //cout<<"mutation 1"<<endl;

            unsigned int i,j;
    
            do {
                i = rnd.Standard_Dice(m_cities.size()-1);           //choosing the index to swap
                j = rnd.Standard_Dice(m_cities.size()-1);
            } while(i==j );

            m_population[k].Swap(i,j);
        }
}

void Travelling_salesman::Mutation2(double mutation_prob, unsigned int k) {

        if(rnd.Rannyu()<mutation_prob) {
            
            //cout<<"mutation 2"<<endl;
        
            unsigned int i = rnd.Standard_Dice(m_cities.size()-3)+1;      // first index of the vector we need to move forward
            
            unsigned int j = rnd.Standard_Dice(m_cities.size()-1-i)+i;    // last index of the vector we need to move

            unsigned int shift = rnd.Standard_Dice(i-1);                  // The first element is fixed and I cannot shift forward more than the position of i
            
            //cout<<i<<" "<<j<<" "<<shift<<endl;
    
            
            m_population[k].Shift(shift,i,j);
        }


}

void Travelling_salesman::Mutation3(double mutation_prob, unsigned int k) {

        if(rnd.Rannyu()<mutation_prob) {
            
            //cout<<"mutation 3"<<endl;

            unsigned int i = rnd.Standard_Dice(m_cities.size()-2);          // first index of the vector we need to translate
            unsigned int j = rnd.Standard_Dice(m_cities.size()-1-i)+i;      // last index of the vector we need to translate

            unsigned int r = static_cast<int>(rnd.Rannyu(i+1,j-1));         // deciding of how much
            
            //cout<<i<<" "<<j<<" "<<r<<endl;

            m_population[k].Rotate(i,j,r);
        }

}

void Travelling_salesman::Mutation4(double mutation_prob, unsigned int k) {
    
    //cout<<"Mutation 4"<<endl;

    if(rnd.Rannyu()<mutation_prob) {
        
        unsigned int i = rnd.Standard_Dice(m_cities.size()-1);         // first index of the vector we need to reverse
        unsigned int j = rnd.Standard_Dice(m_cities.size()-1);         // last index of the vector we need to reverse
        
        //cout<<i<<" "<<j<<endl;

        m_population[k].Reverse(i,j);
        
    }
}

Path Travelling_salesman::BestPath(){
    
    double fit=m_population[0].GetFit();
    int k=0;
    
    for(int i=1; i<m_population.size(); i++){

        double prova=m_population[i].GetFit();
    
        if(prova<fit){
            fit=prova;
            k=i;
        }
    }
    
    return m_population[k];
};

bool FitCompare (Path p1, Path p2) {return (p1.GetFit()<p2.GetFit());};

vector <Path> Travelling_salesman::Crossover(double crossover_prob, unsigned int i, unsigned int j){
    
    vector <Path> sons;
    
    if(rnd.Rannyu()<crossover_prob){
        
        int k=rnd.Standard_Dice(m_cities.size()-1);       //choosing the index where we need to swap
            
        vector <City> son1;
        vector <City> son2;
        
        for(int l=0; l<k; l++){
            son1.push_back(m_population[i].GetPath()[l]);
            son2.push_back(m_population[j].GetPath()[l]);
        }
        
        for(int n=0; n<GetN(); n++){
            int s1=0, s2=0;
            
            for(int l=0; l<k; l++){
                
                if(m_population[j].GetPath()[n].GetLabel()==son1[l].GetLabel()) s1=1;
                if(m_population[i].GetPath()[n].GetLabel()==son2[l].GetLabel()) s2=1;
                
            }
            if(s1==0) son1.push_back(m_population[j].GetPath()[n]);
            if(s2==0) son2.push_back(m_population[i].GetPath()[n]);
        }
        
        Path s1(son1);
        Path s2(son2);

        sons.push_back(s1);
        sons.push_back(s2);
        
        return sons;
    }
    
    Path s1(m_population[i].GetPath());
    Path s2(m_population[j].GetPath());

    sons.push_back(s1);
    sons.push_back(s2);
    
    return sons;
};

void Travelling_salesman::New_Generation(double crossover_prob, double mutation_prob){
    vector <Path> New_Pop;
    
    sort(m_population.begin(), m_population.end(), FitCompare);
  
    for(int i=0; i<m_population.size()/2; i++){
        
        /*double fit_tot=0;
        for(int j=0; j<m_population.size(); j++) fit_tot+=1./m_population[j].GetFit();
        
        int a=rnd.Standard_Dice(static_cast<int>(fit_tot))-1;
        int b=rnd.Standard_Dice(static_cast<int>(fit_tot))-1;
        
        //sort(m_population.begin(), m_population.end(), FitCompare);

        double accu=0;
        int a1=0, b1=0;
        for(int j=0; j<m_population.size(); j++){
            

            accu+=1./m_population[j].GetFit();
            
            if(a<accu and a1==0) {
                a=j;
                a1=1;
            }
            
            if(b<accu and b1==0){
                b=j;
                b1++;
            }
        }*/
        
        int a=static_cast<int>(m_population.size()*pow(rnd.Rannyu(), 6));       //this is more time efficient
        int b=static_cast<int>(m_population.size()*pow(rnd.Rannyu(), 6));
        
        
        vector <Path> New=Crossover(crossover_prob,a,b);
        
        New_Pop.push_back(New[0]);
        New_Pop.push_back(New[1]);
        
    }
    
    
    m_population=New_Pop;
    
    
    for(int i=0; i<m_population.size(); i++){
        Mutation1(mutation_prob,i);
        Mutation2(mutation_prob,i);
        Mutation3(mutation_prob,i);
        Mutation4(mutation_prob,i);
    }
    
};

vector <double> Travelling_salesman::Ave_Fit(){
    sort(m_population.begin(), m_population.end(), FitCompare);
    
    int i=round(m_population.size()/2);
    
    double fit_tot=0.;
    double fit_2=0.;
    
    for(int j=0; j<i; j++) {
        fit_tot+=m_population[j].GetFit();
        fit_2+=pow(m_population[j].GetFit(),2);
    }
    
    fit_tot/=i;
    fit_2/=i;
    
    vector <double> fit;
    
    fit.push_back(fit_tot);
    fit.push_back(fit_2-pow(fit_tot,2));
    
    return fit;
};
