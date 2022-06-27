//
//  statistica.cpp
//  
//
//  Created by Chiara Mascherpa on 10/03/22.
//

#include "statistica.hpp"

double error (double *AV, double *AV2, int n){
    return sqrt((AV2[n] - pow((AV[n]),2))/n);
}
