//
//  Graph.h
//  Better graph
//
//  Created by Ian Brown on 9/1/20.
//  Copyright © 2020 Ian Brown. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include <list>
#include <random>
#include <iomanip>
#include "tree3.h"
using namespace std;
typedef double weight_t;
typedef double bound_t;
typedef int node_t;
typedef list<node_t> set;
typedef int tree_t;

struct path{
    path(){
        dist = 0.0;
    }
    ~path(){}
    //dist is the length of the path (which in dijkstra will be equal to dist from start)
    double dist;
    list<node_t> nodes;
};
ostream& operator<<(ostream& out, const path& p);



class Graph{
public:
    Graph(int vertices):n(vertices), e(0), current(0){
        matrix = vector<vector<weight_t>>();
        init();
    }
    Graph(int vertices, double density, bound_t lower, bound_t upper);
    ~Graph(){};
    vector<vector<weight_t>> getMatrix(){return matrix;}
    int getN(){return n;}
    int getE(){return e;}
    friend ostream& operator<<(ostream& out, const Graph& g);
    weight_t pathSize(path p);
    path dijkstra(node_t start, node_t finish);
    void addEdge(node_t a, node_t b, weight_t w){matrix[a][b] = matrix[b][a] = w; e++;}
    bool compareDist(node_t a, node_t b);
    Tree* getPrimMST();
    Tree* getKruskalMST();
private:
    vector<vector<weight_t>> matrix; int n, e; node_t current;
    void init(){
        for(int i = 0; i < n; i++){
            //create rows
            matrix.push_back(vector<weight_t>());
            for(int j = 0; j < n; j++){
                //input elements
                matrix[i].push_back(0.0);
            }
        }
    }
};



#endif /* Graph_h */
