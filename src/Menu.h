#ifndef MENU_H
#define MENU_H
#include "Mode.h"
#include <iostream>
#include <fstream>
 
 std::pair<std::pair<std::vector<int>,double>,std::pair<std::vector<int>,double>>  noRestrictions(int source, int dest, Graph &graph, int mode) {
    std::pair<std::pair<std::vector<int>,double>,std::pair<std::vector<int>,double>> paths;
    std::set<int> lim;
    noRestriction(source,dest,graph,mode);
    paths.first= getPath(source,dest,graph);
    lim=limit(source,dest,paths.first);
    restrictNode(source,dest,graph,lim,mode);
    paths.second=getPath(source,dest,graph);
    return paths;
 }
 std::pair<std::vector<int>,double> restrictN(int source, int dest, Graph &graph,std::set<int> &limit,int mode) {
    restrictNode(source,dest,graph,limit,mode);
    return getPath(source,dest,graph);
 }

 std::pair<std::vector<int>,double> restrictEd(int source, int dest, Graph &graph,std::vector<std::pair<int,int>> &edgesToAvoid,int mode) {
    restrictEdges(source,dest,graph,edgesToAvoid,mode);
    return getPath(source,dest,graph);
 }
std::pair<std::vector<int>,double> restrictEdgesAndNodes(int source, int dest, Graph &graph,std::set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid, int mode) {
    restrictedEdgesAndNodes(source,dest,graph,limit,edgesToAvoid,mode);
    return getPath(source,dest,graph);
}
std::pair<std::vector<int>,double> include(int source, int dest, Graph &graph,int include, int mode) {
    includeNode(source,dest,graph,include,mode);
    return getPath(source,dest,graph);
}

std::pair<std::vector<int>,double> includeWithRN(int source, int dest, Graph &graph,std::set<int> &limit,int include, int mode){
    includeNodeWithRestrictNodes(source,dest,graph,limit,include,mode);
    return getPath(source,dest,graph);
}
std::pair<std::vector<int>,double> includeNodeWRE(int source,int dest,Graph &graph,std::vector<std::pair<int,int>> &edgesToAvoid,int include,int mode){
    includeNodeWithRestrictEdges(source,dest,graph,edgesToAvoid,include,mode);
    return getPath(source,dest,graph);
}

std::pair<std::vector<int>,double> includeWithRNE(int source, int dest,  Graph& graph,std::set<int> &limit,std::vector<std::pair<int,int>> &edgesToAvoid,int include,int mode){
    includeNodeWithRestrictNodesAndEdges(source,dest,graph,limit,edgesToAvoid,include,mode);
    return getPath(source,dest,graph);
}


#endif // MENU_H