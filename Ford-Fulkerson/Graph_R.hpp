/**
 * @file Graph_R.hpp
 * @brief Residual grapg header file
 */

#ifndef GRAPH_R_HPP
#define GRAPH_R_HPP
#include "Graph.hpp"
/**
 * @brief Represents residual graph of a network flow 
 * @class Graph_R
 */
class Graph_R{
 public:
     /**
     * Constructs a residual graph for a given list of edges.
     * @param lst a list of edges where each edge is represented as {from, to, capacity}
     */
    Graph_R(vector<vector<int>>lst);
    
    int v; ///< Number of vertices in the residual graph
    Graph* master;///< Pointer to the original graph
    map<int,vector<vector<int>>> adj;///adjacency list of Residual Graph
    vector<vector<int>>edges;///list of edges
     /**
     * Prints the adjacency list of the residual graph.
     */
    void print();
    void write_into_plot();
    void dfs(int i,vector<bool>&v,vector<int> curr,vector<int>& ans,bool got_path);
    vector<int> path();
    int  bottleneck(const vector<int>& path);
    void augument(const vector<int>& path);
    void ffa();
   
};
//lst[i]={from,to,wt}
/**
 * @brief Construct a new Graph_R::Graph_R object
 * 
 */
Graph_R::Graph_R(vector<vector<int>>lst){
    edges=lst;
        for(auto vals:lst){
            adj[vals[0]].push_back({vals[1],vals[2]});
        }
        
        v=adj.size();
}
/**
*@brief  Prints the adjacency list of the residual graph.
*/
void Graph_R::print(){
    fout<<"vertices "<<this->v<<"\n";
    for(auto pair:adj){
        int i=pair.first;
        fout<<i<<"-> {";
        for(auto vals:adj[i]){
            fout<<vals[0]<<","<<vals[1]<<"} {";
        }
        fout<<"\n";
    }
}
/**
 * @brief Writes the list of edges in the residual graph to an output file for visualization.
 * 
 */
void Graph_R::write_into_plot(){
    plot1<<edges.size()<<"\n";
    for(auto vals:edges){
        plot1<<vals[0]<<" "<<vals[1]<<" "<<vals[2]<<"\n";
    }
}
/**
 * @brief Performs a depth-first search on the residual graph to find an augmenting path from source to sink.
 * 
 * @param i the vertex to start the search from
 * @param vis a vector indicating which vertices have already been visited
 * @param curr the current augmenting path being considered
 * @param ans the final augmenting path found
 * @param got_path a boolean value indicating whether an augmenting path has already been found
 */
void Graph_R::dfs(int i,vector<bool>&vis,vector<int> curr,vector<int>& ans,bool got_path){
    if(i==v){
        curr.push_back(i);
        ans=curr;
        got_path=true;
        return;
    }
    vis[i]=true;
    for(auto vals:adj[i]){
        int wt=vals[1],to=vals[0];
        if(!vis[to] and wt){
            curr.push_back(i);
            dfs(to,vis,curr,ans,got_path);
            if(got_path){
                break;
            }
            curr.pop_back();
        }
    }
}
/**
 * @brief Finds an augmenting path in the residual graph from source to sink.
 * 
 * @return vector<int> 
 */
vector<int> Graph_R::path(){
    vector<bool>vis(v+1,false);    
    vector<int> path={};
    dfs(1,vis,{},path,false);
    return path;
}
/**
 * @brief Finds the bottleneck capacity of an augmenting path in the residual graph.
 * 
 * @param path a vector containing the vertices in the augmenting path from source to sink
 * @return the bottleneck capacity of the augmenting path
 */
int Graph_R::bottleneck(const vector<int>& path){
    int len=path.size(),ans=INT_MAX;
    for(int i{};i<len-1;i++){
        for(auto vals:edges){
                if(vals[0]==path[i] and vals[1]==path[i+1] and vals[2]!=0){
                    ans=min(ans,vals[2]);
                }
        }
    }
    return ans;
}
/**
 * @brief Augments the flow along an augmenting path in the residual graph.
 * 
 * @param path a vector containing the vertices in the augmenting path from source to sink
 */
void Graph_R::augument(const vector<int>& path){
    int b=bottleneck(path); 
    //fout<<"bottleneck is "<<b<<"\n";
    vector<vector<int>>path_edges;
    for(int i{};i<path.size()-1;i++){
        path_edges.push_back({path[i],path[i+1]});
    }
    for(auto vals:path_edges){
        auto from=vals[0],to=vals[1];
        if(from<to){
            for(int i{};i<master->edges.size();i++){
                if(master->edges[i][0]==from and master->edges[i][1]==to){

                    master->edges[i][3]+=b;
                }
            }
        }else{
            for(int i{};i<master->edges.size();i++){
                if(master->edges[i][1]==from and master->edges[i][0]==to){
              
                    master->edges[i][3]-=b;
                }
            }
        }
    }
    
    //upadating master adj
    map<int,vector<vector<int>>> new_adj;
    for(auto vals:master->edges){
        new_adj[vals[0]].push_back({vals[1],vals[2],vals[3]});
    }
    master->adj=new_adj;

    //updating residual edges
    vector<vector<int>>new_residual_edges;
    for(auto vals:master->edges){
        new_residual_edges.push_back({vals[0],vals[1],vals[2]-vals[3]});
        new_residual_edges.push_back({vals[1],vals[0],vals[3]}); 
    }
    edges=new_residual_edges;
    new_adj.clear();
    for(auto vals:new_residual_edges){
        new_adj[vals[0]].push_back({vals[1],vals[2]});
    }
    this->adj=new_adj;
}
void print_path(vector<int>&path){
fout<<"path is ";
for(auto vals:path){
    fout<<vals<<" ";
}
}
/**
 * @brief Computes the maximum flow using the Ford-Fulkerson algorithm with the residual graph.
 * 
 */
void Graph_R::ffa(){
    vector<int> path=this->path();
    //fout<<"Hello\n";
            while(path.size()){
                 augument(path);
                 path=this->path();
            }    
}
#endif