/**
 * @file Graph.hpp
 * @brief This header file contains the declaration of the Graph class.
 * 
 */
#ifndef GRAPH_H
#define GRAPH_H
#include<vector>
#include<string>
#include<map>
#include<set>
#include <fstream>
using namespace std;
ofstream fout("output.txt");
ofstream plot("plot.txt");
ofstream plot1("plot.txt");
ofstream fout1("output.txt");
ofstream cfout("command.txt");
/**
 * @class Graph_R
 * @brief Forward declaration of Graph_R class
 * 
 */
class Graph_R;
/**
 * 
 * @class Graph
 * @brief A  class to represent a graph
 * 
 */
class Graph{
 public:
 /**
  * @brief Construct a new Graph object
  * @param lst A list of edges (represented as vectors) with their corresponding capacities
  * 
  */
    Graph(vector<vector<int>>lst);
    /**
     * @brief no vertices in the graph
     * 
     */
    int v;
    /**
     * @brief Adjacency list containing where each entry key is the front point and has a value of vectors where each entry in vector is from to_point,capacity and flow
     * 
     */
    map<int,vector<vector<int>>> adj;
    /**
     * @brief Edges of the Graph where each entry is from,to and flow
     * 
     */
    vector<vector<int>>edges;//edges[i]->{form,to,capacity,curr}
    /**
     * @brief edges of residual graph
     * 
     */
    vector<vector<int>>residual_edges;//edges[i]->{from,to,capacity}
    Graph_R* residual;
    int min_st_cut();
    void print();
    void write_into_plot();
};
/**
 * @brief Construct a new Graph:: Graph object
 * 
 */
Graph::Graph(vector<vector<int>>lst){
        edges=lst;
        set<int>s;
        for(auto vals:lst){
            s.insert(vals[0]);s.insert(vals[1]);
            adj[vals[0]].push_back({vals[1],vals[2],0});
            residual_edges.push_back({vals[1],vals[0],0});
            residual_edges.push_back({vals[0],vals[1],vals[2]});
        }
        v=s.size();
}
/**
 * @brief returns min_st_cut i.e flow of the graph
 * 
 * @return int 
 */
int Graph::min_st_cut(){
    int res=0;
    auto it=adj.begin();
    for(auto vals:it->second){
        res+=vals[2];
    }
    return res;
}
/**
 * @brief Pritns the graph
 * 
 * @return void
 */
void Graph::print(){
    fout<<this->v<<" vertices\n";
    for(auto pair:adj){
        int i=pair.first;
        fout<<i<<"-> {";
        for(auto vals:adj[i]){
            fout<<vals[0]<<","<<vals[1]<<","<<vals[2]<<"} {";
        }
        fout<<"\n";
    }
}
/**
 * @brief Writes the graph's edges into a file in a format suitable for plotting
 * 
 * @return void
 */
void Graph::write_into_plot(){
    plot<<edges.size()<<"\n";
    for(auto vals:edges){
        plot<<vals[0]<<" "<<vals[1]<<" "<<vals[3]<<"\n";
    }
}

#endif
