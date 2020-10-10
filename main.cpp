//
//  main.cpp
//  Better graph
//
//  Created by Ian Brown on 8/14/20.
//  Copyright © 2020 Ian Brown. All rights reserved.
//

#include "Utils.h"
#include "Graph.h"
#include "tree3.h"
#include <iostream>
using namespace std;


int main(){
    srand(static_cast<unsigned int>(time(0)));
    Graph g(10, 0.25, 0, 10);
    cout << g;
    cout << "Shortest path between node 0 and node 9: " << endl;
    cout << g.dijkstra(0, 9) << endl;
    cout << "Prim MST: " << endl;
    cout << g.getPrimMST() << endl;
    cout << "Kruskal MST: " << endl;
    cout << g.getKruskalMST() << endl;
    return 0;
}
