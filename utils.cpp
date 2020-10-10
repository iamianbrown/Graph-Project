//
//  utils.cpp
//  Better graph
//
//  Created by Ian Brown on 9/3/20.
//  Copyright © 2020 Ian Brown. All rights reserved.
//

#include <random>
#include <list>
#include "Graph.h"
using namespace std;
typedef double bound_t;
double prob(){return static_cast<double>(rand())/RAND_MAX;};
double randWeight(bound_t lower, bound_t upper){
    double range = upper - lower, out;
    (upper > lower)?out = (prob() * range + lower) : out = (prob() * -1 * range + upper);
    return out;
}

