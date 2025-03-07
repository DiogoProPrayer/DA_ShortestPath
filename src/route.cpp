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
            Node *cn = c->findNode(dest);
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
            for (int id : tempPath){
                g->removeNode(id);
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
        
        vector<int>
}

