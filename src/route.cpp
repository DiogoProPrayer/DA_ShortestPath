#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "graph.h"

using namespace std;

class Route {
    public:
        vector<int> mainDrivingRoute(Graph* g, Node* orig, Node* dest){
            GetDriving gd;
            gd.dijkstra(g, orig);

            vector<int> path;
            if (dest->getParking() == 0 || dest->getPath() == nullptr){
                return path;
            }
            Node *cn = g->findNode(dest);
            while (cn){
                path.push_back(cn->getId());
                cn = cn->getPath();
            }

            reverse(path.begin(), path.end());
            return path;
        }

        vector<int> altDrivingRoute(Graph* g, Node* orig, Node* dest){
            GetDriving gd;
            gd.dijkstra(g, orig);

            vector<int> tempPath;
            if (dest->getParking() == 0 || dest->getPath() == nullptr){
                return tempPath;
            }
            Node *cn = g->findNode(dest);
            while (cn){
                tempPath.push_back(cn->getId());
                cn = cn->getPath();
            }

            reverse(tempPath.begin(), tempPath.end());
            for (int i = 1; i < tempPath.size()-1; i++){
                g->removeNode(tempPath(i));
            }
            
            gd.dijkstra(g, orig);

            vector<int> path;
            if (dest->getParking() == 0 || dest->getPath() == nullptr){
                return path;
            }
            cn = g->findNode(dest);
            while (cn){
                path.push_back(cn->getId());
                cn = cn->getPath();
            }

            reverse(path.begin(), path.end());
            return path;
        }     
        
        vector<int> resDrivingRoute(Graph* g, Node* orig, Node* dest, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges, Node* iNode){
            for (int id : aNodes){
                g->removeNode(id);
            }

            for (auto& edge : aEdges){
                g->removeEdge(edge.first, edge.second);
            }

            if (iNode == nullptr) {
                GetDriving gd;
                gd.dijkstra(g, orig);

                vector<int> path;
                if (dest->getParking() == 0 || dest->getPath() == nullptr){
                    return path;
                }
                Node *cn = g->findNode(dest);
                while (cn){
                    path.push_back(cn->getId());
                    cn = cn->getPath();
                }

                reverse(path.begin(), path.end());
                return path;
            }

            else {
                GetDriving gd;
                gd.dijkstra(g, orig);

                vector<int> path;
                if (iNode->getPath() == nullptr){
                    return path;
                }
                Node *cn = g->findNode(iNode);
                while (cn){
                    path.push_back(cn->getId());
                    cn = cn->getPath();
                }

                gd.dijkstra(g, iNode);

                if (dest->getParking() == 0 || dest->getPath() == nullptr){
                    return path;
                }
                cn = g->findNode(dest);
                while (cn){
                    path.push_back(cn->getId());
                    cn = cn->getPath();
                }

                reverse(path.begin(), path.end());
                return path;
            }
        }
}

