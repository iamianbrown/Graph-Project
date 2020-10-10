//
//  Graph.cpp
//  Better graph
//
//  Created by Ian Brown on 9/1/20.
//  Copyright © 2020 Ian Brown. All rights reserved.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include "Graph.h"
#include "Utils.h"
#include "tree3.h"



path Graph:: dijkstra(node_t start, node_t finish){
    current = start;
    vector<node_t> visited, open;
    vector<path> paths;
    for(int i = 0; i < n; i++)
        paths.push_back(path());
    visited.push_back(start);
    paths[start].nodes.push_back(start);
    make_heap(open.begin(),open.end(), [&](node_t a, node_t b){return paths[a].dist > paths[b].dist;});
    for(node_t i = 0; i < n; i++){
        if(matrix[current][i] != 0){
            open.push_back(i);
            push_heap(open.begin(), open.end(), [&](node_t a, node_t b){return paths[a].dist < paths[b].dist;});
            paths[i].dist = matrix[current][i];
            paths[i].nodes = paths[start].nodes;
            paths[i].nodes.push_back(i);
        }
    }
    while(open.size() != 0){
        current = open.front();
        pop_heap(open.begin(), open.end(), [&](node_t a, node_t b){return paths[a].dist > paths[b].dist;});
        open.pop_back();
        visited.push_back(current);
        if(contains(visited, finish)){break;}
        for(node_t i = 0; i < n; i++){
            if(matrix[current][i] != 0 && !contains(visited, i)){
                if(!contains(open, i)){
                    open.push_back(i);
                    paths[i] = paths[current];
                    paths[current].dist += matrix[current][i];
                    paths[i].nodes.push_back(i);
                    push_heap(open.begin(), open.end(), [&](node_t a, node_t b){return paths[a].dist < paths[b].dist;});
                }
                else if(paths[i].dist > paths[current].dist + matrix[current][i]){
                    paths[i] = paths[current];
                    paths[i].dist += matrix[current][i];
                    paths[i].nodes.push_back(i);
                    make_heap(open.begin(), open.end(), [&](node_t a, node_t b){return paths[a].dist < paths[b].dist;});
                }
            }
        }
    }
    return paths[finish];
}
bool Graph:: compareDist(node_t a, node_t b){return matrix[current][a] > matrix[current][b];};

Graph:: Graph(int vertices, double density, bound_t wMin, bound_t wMax):n(vertices), e(0), matrix(vector<vector<weight_t>>()){
    init();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < i; j++){
            if(prob() < density){
                matrix[i][j] = matrix[j][i] = randWeight(wMin, wMax);
                e++;
            }
        }
    }
}

ostream& operator<<(ostream& out, set s){
    for(set::iterator it = s.begin(); it != s.end(); it++){
        out << *it << "  ";
    }
    return out;
}
ostream& operator<<(ostream& out, const Graph& g){
    vector<vector<weight_t>> mat = g.matrix;
    for(int i = 0; i < g.n; i++){
        for(int j = 0; j < g.n; j++){
            (mat[i][j] == 0)?out << fixed << setprecision(0) << mat[i][j] << "    ":out << fixed << setprecision(1) << mat[i][j] << "  ";
        }
        out << endl << endl;
    }
    return out;
}
ostream& operator<<(ostream& out, const path& p){
    out << "Begin --> ";
    for(auto it = p.nodes.begin(); it != p.nodes.end(); it++){
        out << *it << " --> ";
    }
    out << "End";
    return out;
}

Tree* Graph::getPrimMST(){
    Tree* tr = new Tree();
    //nodePtrs converts all of the node_t's in the graph into Node objects
    vector<Node*> nodePtrs;
    //initalize nodePtrs
    for(node_t i = 0; i < n; i++){
        nodePtrs.push_back(new Node(i));
    }
    //the node which is referred to when adding nodes to open set
    Node* inFocus = nodePtrs[0];
    //parents[i] stores the node in the tree closest to Node i and the distance to that node
    vector<Edge> parents(n);
    //open set: all nodes currently being considered for addition to tree
    vector<Node*> open;
    //add Node 0 to tree
    tr->addNode(inFocus);
    //initialize open set
    for(node_t i = 0; i < n; i++){
        if(matrix[0][i] != 0){
            //add node to open set if connected to 0
            open.push_back(nodePtrs[i]);
            //update parents with 0 as parent and the edge weight as is stored in matrix
            parents[i] = Edge(inFocus, matrix[0][i]);
        }
    }
    //sort open set
    make_heap(open.begin(), open.end(), [&](const Node* a, const Node* b){
        return parents[a->index].weight > parents[b->index].weight;
    });
    while(open.size() != 0){
        //set inFocus to be next closest node
        inFocus = open.front();
        tr->addNode(parents[inFocus->index].vertex, inFocus, parents[inFocus->index].weight);
        //remove new inFocus from open set. It's in the tree now.
        pop_heap(open.begin(), open.end(), [&](const Node* a, const Node* b){
            return parents[a->index].weight > parents[b->index].weight;});
        open.pop_back();
        for(node_t i = 0; i < n; i++){
            if(matrix[inFocus->index][i] != 0 && !tr->has(nodePtrs[i])){
                //if open doesn't have i in it, add it, then update parent
                if(!contains(open, nodePtrs[i])){
                    open.push_back(nodePtrs[i]);
                    parents[i] = Edge(inFocus, matrix[inFocus->index][i]);
                    push_heap(open.begin(), open.end(), [&](const Node* a, const Node* b){
                        return parents[a->index].weight > parents[b->index].weight;});
                }
                //if the edge in focus connects i to the tree more closely than old edge
                //update the parent of i
                else if(matrix[inFocus->index][i] < parents[i].weight){
                    parents[i] = Edge(inFocus, matrix[inFocus->index][i]);
                    make_heap(open.begin(), open.end(), [&](const Node* a, const Node* b){
                        return parents[a->index].weight > parents[b->index].weight;});
                }
            }
        }
    }
    
    if(tr->size() != n){
        delete tr;
        return nullptr;
    }
    return tr;
}

Tree* Graph::getKruskalMST(){
    //reference array to convert node_t to nodePtr
    vector<Node*> nodePtrs(n);
    //forest
    vector<Tree*> forest(n);
    //initialize each tree in forest and nodePtrs
    for(node_t i = 0; i < n; i++){
        nodePtrs[i] = new Node(i);
        forest[i] = new Tree();
        forest[i]->addNode(nodePtrs[i]);
    }
    //this vector stores information about which node belongs to which tree. belongsTo[i] where i is node_t is equal to the index of forest where
    //the node with index i can be found
    vector<tree_t> belongsTo(n);
    //initialize belongsTo
    for(node_t i = 0; i < n; i++){
        //at the beginning, each node belongs to its own forest => for all i < forest.size() belongsTo[i] == i
        belongsTo[i] = i;
    }
    //vector (heap) of all edges in graph ordered s.t. shortest edge is at top
    vector<UndirectedEdge> edges;
    for(node_t i = 0; i < n; i++){
        for(node_t j = 0; j < i; j++){
            if(matrix[i][j] != 0){
                edges.push_back(UndirectedEdge(nodePtrs[i], nodePtrs[j], matrix[i][j]));
            }
        }
    }
    make_heap(edges.begin(), edges.end(), [&](UndirectedEdge a, UndirectedEdge b){
        return a.weight > b.weight;
    });
    while(forest.size() > 1){
        Tree* temp1 = forest[belongsTo[edges.front().node1->index]];
        Tree* temp2 = forest[belongsTo[edges.front().node2->index]];
        
        if(temp1 != temp2){
            vector<Tree*> tempForest(forest.size() - 1);
            Tree* newTree = new Tree(move(*temp1), move(*temp2), edges.front());
            //assign old trees into new forest, amalgamating the two trees connected by the shortest edge
            bool added = false; //keeps track of whether newTree has already been added to the forest
            for(int i = 0, j = 0; i < forest.size(); i++){
                if(forest[i]->size() == 0 && !added){
                    tempForest[j++] = newTree;
                    added = true;
                }
                else if(forest[i]->size() != 0){
                    tempForest[j++] = forest[i];
                }
            }
            forest = tempForest;
            for(tree_t i = 0; i < forest.size(); i++){
                for(node_t j = 0; j < n; j++){
                    if(forest[i]->has(nodePtrs[j])){
                        belongsTo[j] = i;
                    }
                }
            }
            //this needs to update all of the indices of forest that point to the same tree
            //for all indices of forest where forest[i] = forest[edges.front().node1->index], update
            delete temp1;
            //cout << temp2 << endl;
            delete temp2; //k tells us how many times we've been through this loop (use for debugging)
        }
        //update edges, debug
        pop_heap(edges.begin(), edges.end(), [&](UndirectedEdge a, UndirectedEdge b){
            return a.weight > b.weight;
        });
        edges.pop_back();
        if(edges.empty() && forest.size() > 1){
            for(auto* tree : forest){
                delete tree;
            }
            return nullptr;
        }
    }
    
    return forest[0];
}
