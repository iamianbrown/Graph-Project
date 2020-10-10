//
//  tree3.cpp
//  Better graph
//
//  Created by Ian Brown on 9/20/20.
//  Copyright © 2020 Ian Brown. All rights reserved.
//

#include "tree3.h"
#include <cassert>
#include <iostream>
Node::Node():index(0), adj(vector<Edge>()){}
Node::Node(node_t i):index(i),adj(vector<Edge>()){}
Node::~Node(){};

Edge::Edge(Node* v, weight_t wt):vertex(v),weight(wt){}
Edge::Edge():vertex(nullptr), weight(0){}
Edge::~Edge(){}

Tree::Tree():nodes(vector<Node*>()),weight(0){};
Tree::Tree(Tree&& tr1, Tree&& tr2, UndirectedEdge connection):nodes(vector<Node*>(tr1.size() + tr2.size())), weight(connection.weight + tr1.weight + tr2.weight){
    for(node_t i = 0; i < nodes.size(); i++){
        i < tr1.size() ? nodes[i] = tr1.nodes[i] : nodes[i] = tr2.nodes[i - tr1.size()];
    }
    tr1.nodes.clear();
    tr2.nodes.clear();
    //add connection edge into tree
    connection.node1->adj.push_back(Edge(connection.node2, connection.weight));
    connection.node2->adj.push_back(Edge(connection.node1, connection.weight));
}
//copy constructor
Tree::Tree(const Tree& old):weight(old.weight), nodes(vector<Node*>(old.size())){
    //array that stores info about where node with index i is stored
    vector<int> belongsTo(size());
    for(node_t i = 0; i < size(); i++){
        //create new nodes for each node in old
        nodes[i] = new Node(old.nodes[i]->index);
        //the node with index old.nodes[i]->index belongsTo nodes[i]
        belongsTo[old.nodes[i]->index] = i;
    }
    for(node_t i = 0; i < size(); i++){
        nodes[i]->adj = vector<Edge>(old.nodes[i]->adj.size());
        for(node_t j = 0; j < old.nodes[i]->adj.size(); j++){
            //copy adjacency info into new tree
            nodes[i]->adj[j] = Edge(nodes[belongsTo[old.nodes[i]->adj[j].vertex->index]], old.nodes[i]->adj[j].weight);
        }
    }
}
//move constructor
Tree::Tree(Tree&& temp){
    nodes = vector<Node*>(temp.size());
    for(node_t i = 0; i < temp.size(); i++){
        nodes[i] = temp.nodes[i];
        temp.nodes[i] = nullptr;
    }
    weight = temp.weight;
}
//assignment operator
Tree& Tree::operator=(const Tree& rhs){
    if(this != &rhs){
        nodes.clear();
        nodes = vector<Node*>(rhs.size());
        for(node_t i = 0; i < rhs.size(); i++){
            nodes[i] = new Node(rhs.nodes[i]->index);
            nodes[i]->adj = vector<Edge>(rhs.nodes[i]->adj.size());
            for(node_t j = 0; j < nodes[i]->adj.size(); j++){
                nodes[i]->adj[j] = Edge(nodes[rhs.nodes[i]->adj[j].vertex->index], rhs.nodes[i]->adj[j].weight);
            }
        }
    }
    return *this;
}
Tree& Tree::operator=(Tree&& rhs){
    if(this != &rhs){
        nodes.clear();
        nodes = vector<Node*>(rhs.size());
        for(node_t i = 0; i < rhs.size(); i++){
            nodes[i] = rhs.nodes[i];
        }
    rhs.nodes.clear();
    }
    return *this;
}
//destructor
Tree::~Tree(){
    for(auto* node :nodes){
        delete node;
    }
};

UndirectedEdge::UndirectedEdge(Node* a, Node* b, weight_t wt):weight(wt), node1(a), node2(b){}
UndirectedEdge::~UndirectedEdge(){}

void Tree::addNode(Node* newNode){
    nodes.push_back(newNode);
}
void Tree::addNode(Node* oldNode, Node* newNode, weight_t wt){
    nodes.push_back(newNode);
    oldNode->adj.push_back(Edge(newNode, wt));
    newNode->adj.push_back(Edge(oldNode, wt));
    weight += wt;
}
bool Tree::has(Node* n){
    for(node_t i = 0; i < size(); i++){
        if(nodes[i] == n)
            return true;
    }
    return false;
}
unsigned long Tree::size()const{
    return nodes.size();
}
ostream& operator<<(ostream& out, const Tree* tr){
    if(tr == nullptr){
        return (out << "Graph is not connected");
    }
    for(auto* node : tr->nodes){
        out << node->index << ":" << endl;
        for(auto adjacent : node->adj){
            out << "--> " << adjacent.vertex->index << endl;
        }
    }
    out << "Weight = " << tr->weight;
    return out;
};
