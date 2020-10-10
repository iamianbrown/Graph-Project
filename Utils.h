//
//  Utils.h
//  Better graph
//
//  Created by Ian Brown on 9/3/20.
//  Copyright © 2020 Ian Brown. All rights reserved.
//

#ifndef Utils_h
#define Utils_h
#include <list>
#include "Graph.h"
using namespace std;
typedef double bound_t;
double randWeight(bound_t lower, bound_t upper);
double prob();
template<class container_t, class element_t>
bool contains(container_t cntnr, element_t elem){return find(cntnr.begin(), cntnr.end(), elem) != cntnr.end();}
#endif /* Utils_h */
