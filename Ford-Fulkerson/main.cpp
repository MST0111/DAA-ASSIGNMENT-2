/**
 * @file main.cpp
 * @brief This file contains the implementation of the main function and related functions for solving the minimum cut problem in a given graph.
 */

#include<vector>
#include<string>
#include<map>
#include<queue>
#include <algorithm>
#include"Graph_R.hpp"
#include<fstream>
#include <chrono>
ifstream fin("input.txt");
ofstream fout_main("output.txt");
ifstream bin("bipartite.txt");
using namespace std;
using namespace chrono;
/**
 * @brief This function writes the minimum cut found in the graph in the output file and plots the bipartite graph 
 * 
 * @param g A pointer to the Graph object
 */
void write_bipartite(Graph* g){
    int counter=0;
    for(auto vals:g->edges){
        if(vals[0]!=1 and vals[1]!=g->v and vals[3]!=0){
            counter++;
        }
    }
    plot<<counter<<"\n";
    for(auto vals:g->edges){
        if(vals[0]!=1 and vals[1]!=g->v and vals[3]!=0){
            plot<<vals[0]<<" "<<vals[1]<<" "<<vals[3]<<"\n";
        }
    }
}
/**
 * @brief This function prints all the edges of the graph in the output file
 * 
 * @param g A pointer to the Graph object
 */
void print_edges(Graph* g){
    for(auto vals:g->edges){
        for(auto valus:vals){
            fout<<valus<<" ";
        }
        fout<<"\n";
    }
}
/**
 * @brief This function performs breadth-first search on the residual graph and returns a vector of visited nodes
 * 
 * @param resi A pointer to the Graph_R object (residual graph)
 * @return A vector of visited nodes 
 */
vector<int> bfs(Graph_R* resi){
    vector<int>res;
    vector<bool>vis(resi->v+1);
    queue<int> q;
    q.push(1);
    vis[1]=true;
    while(!q.empty()){
        int v=q.front();
        q.pop();
        res.push_back(v);
        for(auto vals:resi->adj[v]){
            if(vals[1]!=0 and !vis[vals[0]]){
                vis[vals[0]]=true;
                q.push(vals[0]);
            }
        }
    }
    return res;
}
/**
 * @brief This function acts as a helper function for finding the minimum cut of the graph
 * 
 * @param g A pointer to the Graph object
 * @param resi  A pointer to the Graph_R object (residual graph)
 * @param argc Number of command-line arguments
 * @return The minimum cut of the graph
 */
int helper(Graph* g,Graph_R* resi,int argc){
     resi->master=g;
     resi->ffa();
     if(argc<2){
        g->write_into_plot();
        plot<<"\n";
        auto points=bfs(resi);
        for(auto vals:points){
            plot<<vals<<" ";
        }
        plot<<"\n";

     }else{
        write_bipartite(g);
     }
     int x=g->min_st_cut();
     plot<<x;
     return x;
}
/**
 * @brief Construct a new vector<vector<int>>bipartite to nf graph
 * 
 */
vector<vector<int>>bipartite_to_nf(){
    int maxl=INT_MIN,maxr=INT_MIN;
    string input;
    vector<vector<int>> temp;
    if(bin){
        while(getline(bin,input)){
            int i=0;
            while(input[i]!=' '){
                i++;
            }
            int n=input.size();
            int x=stoi(input.substr(0,i)),y=stoi(input.substr(i+1,n-i-1));
            maxl=max(maxl,x+1);
            maxr=max(maxr,y+1);
            temp.push_back({x+1,y+1,1,0});
        }
        for(int i{2};i<=maxl;i++){
            temp.push_back({1,i,1,0});
        }
        for(int j{1+maxl};j<=maxr;j++){
            temp.push_back({j,maxr+1,1,0});
        }
    }else{
        fout<<"Error reading file\n";
    }
    sort(temp.begin(),temp.end());
    return temp;
}

/**
 * @brief The main function of the program that initializes the graph, computes the max flow and outputs the time taken to execute the program.
 * 
 * @param argc The number of arguments passed to the function.
 * @param argv The array of arguments passed to the function.
 * @return An integer value representing the success or failure of the program.
 */

int main(int argc, char *argv[]){
    auto start = high_resolution_clock::now();
    vector<vector<int>>temp;
    if(argc<2){
        int n;fin>>n;
        while(n--){
            int from,to,wt;
            fin>>from>>to>>wt;
            temp.push_back({from,to,wt,0});
        }
    }else{
        temp=bipartite_to_nf();
    }
     Graph* g=new Graph(temp);
     Graph_R* resi=new Graph_R(g->residual_edges);
    //  g->print();resi->print();
     int min_st=helper(g,resi,argc);
     auto stop = high_resolution_clock::now(); // record stop time
     auto duration = duration_cast<microseconds>(stop - start);
     fout << "Time taken by the code: " << duration.count() << " microseconds" << endl;
     return 0;
}