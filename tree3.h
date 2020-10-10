//
//  tree3.hpp
//  Better graph
//
//  Created by Ian Brown on 9/20/20.
//  Copyright © 2020 Ian Brown. All rights reserved.
//

#ifndef tree3_h
#define tree3_h
#include <vector>
using namespace std;

typedef int node_t;
typedef double weight_t;

struct Edge;

struct Node{
    Node(node_t i);
    Node();
    ~Node();
    node_t index;
    vector<Edge> adj;
};

struct Edge{
    Edge(Node* v, weight_t wt);
    Edge();
    ~Edge();
    Node* vertex;
    weight_t weight;
};

struct UndirectedEdge{
    UndirectedEdge(Node* a, Node* b, weight_t wt);
    ~UndirectedEdge();
    Node* node1;
    Node* node2;
    weight_t weight;
};

class Tree{
public:
    Tree();
    //Takes 2 trees and makes a new tree that connects them using the connection edge
    Tree(Tree&& tr1, Tree&& tr2, UndirectedEdge connection);
    Tree(const Tree& old);
    Tree(Tree&& temp);
    Tree& operator=(const Tree& rhs);
    Tree& operator=(Tree&& rhs);
    ~Tree();
    void addNode(Node* newNode);
    void addNode(Node* oldNode, Node* newNode, weight_t wt);
    bool has(Node* n);
    unsigned long size()const;
    friend ostream& operator<<(ostream& out, const Tree* tr);
private:
    vector<Node*> nodes;
    weight_t weight;
};

#endif /* tree3_hpp */
