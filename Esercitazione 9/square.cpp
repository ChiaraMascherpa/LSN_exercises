//
//  square.cpp
//  
//
//  Created by Chiara Mascherpa on 20/05/22.
//

#include <fstream>
#include <iostream>
#include <iomanip>
#include "../Random/random.h"

using namespace std;

int main(int argc, char* argv[]) {

    Random rnd;
    rnd.Initialize();

    ofstream output("square.dat");

    int N;

    if(argc >= 2) N = stoi(argv[1]);
    else {

        cout << "Type the number of points to be generated on a square: ";
        cin >> N;

    }

    for(int i=0; i<N; ++i) {
        double x = rnd.Rannyu(-1.,1.);
        double y = rnd.Rannyu(-1.,1.);
        output<<setw(15)<<i+1<<setw(15)<<x<<setw(15)<<y;
        if(i!=(N-1)) output<<endl;
    }

    output.close();
    
    return 0;
}

