//
//  main.cpp
//  
//
//  Created by Chiara Mascherpa on 20/05/22.
//

#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include "../Random/random.h"

using namespace std;

int main(int argc, char* argv[]) {

    Random rnd;
    rnd.Initialize();

    ofstream output("circle.dat");

    int N;

    if(argc >= 2) N = stoi(argv[1]);
    else {

        cout << "Type the number of points to be generated on a circle: ";
        cin >> N;

    }

    for(int i=0; i<N; ++i) {
        double theta = rnd.Rannyu(0,2*M_PI);
        //output<<setw(15)<<i+1<<setw(15)<<cos(theta)<<setw(15)<<sin(theta);
        output<<" "<<i+1<<" "<<cos(theta)<<" "<<sin(theta);
        if(i!=(N-1)) output<<endl;
    }

    output.close();
    
    return 0;
}
