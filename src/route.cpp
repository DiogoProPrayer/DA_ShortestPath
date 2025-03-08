#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include "graph.h"
#include "getDriving.h"
#include "getWalking.h"

using namespace std;

class Route {
    public:
        pair<vector<int>, int> mainDrivingRoute(Graph* g, Node* orig, Node* dest){
            GetDriving gd;
            gd.dijkstra(g, orig);

            vector<int> path;
            if (dest->getPath() == nullptr || dest->getParking() == 0){
                return {path, -1};
            }
            Node *cn = g->findNode(dest);
            while (cn){
                path.push_back(cn->getId());
                cn = cn->getPath();
            }

            reverse(path.begin(), path.end());
            return {path, dest->getDistance()};
        }

        pair<vector<int>, int> altDrivingRoute(Graph* g, Node* orig, Node* dest){
            GetDriving gd;
            gd.dijkstra(g, orig);

            vector<int> tempPath;
            if (dest->getPath() == nullptr || dest->getParking() == 0){
                return {path, -1};
            }
            Node *cn = g->findNode(dest);
            while (cn){
                tempPath.push_back(cn->getId());
                cn = cn->getPath();
            }

            reverse(tempPath.begin(), tempPath.end());
            for (int i = 1; i < tempPath.size()-1; i++){
                g->removeNode(tempPath[i]);
            }
            
            gd.dijkstra(g, orig);

            vector<int> path;
            if (dest->getPath() == nullptr || dest->getParking() == 0){
                return {path, -1};
            }
            cn = g->findNode(dest);
            while (cn){
                path.push_back(cn->getId());
                cn = cn->getPath();
            }

            reverse(path.begin(), path.end());
            return {path, dest->getDistance()};
        }     
        
        pair<vector<int>, int> resDrivingRoute(Graph* g, Node* orig, Node* dest, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges, Node* iNode){
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
                if (dest->getPath() == nullptr || dest->getParking() == 0){
                    return {path, -1};
                }
                Node *cn = g->findNode(dest);
                while (cn){
                    path.push_back(cn->getId());
                    cn = cn->getPath();
                }

                reverse(path.begin(), path.end());
                return {path, dest->getDistance()};
            }

            else {
                GetDriving gd;
                gd.dijkstra(g, iNode);
                
                vector<int> path;
                if (dest->getPath() == nullptr || dest->getParking() == 0){
                    return {path, -1};
                }
                Node *cn = g->findNode(dest);
                while (cn){
                    path.push_back(cn->getId());
                    cn = cn->getPath();
                }

                gd.dijkstra(g, orig);

                if (iNode->getPath() == nullptr){
                    return {path, -1};
                }
                cn = g->findNode(iNode);
                cn = cn->getPath();
                while (cn){
                    path.push_back(cn->getId());
                    cn = cn->getPath();
                }

                reverse(path.begin(), path.end());
                return {path, dest->getDistance()};
            }
        }

        pair<pair<vector<int>, vector<int>>, pair<int, int>> mainEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){
            for (int id : aNodes){
                g->removeNode(id);
            }

            for (auto& edge : aEdges){
                g->removeEdge(edge.first, edge.second);
            }
            
            vector<int> pns;
            for (Node* n : g->getNodes()){
                if (n->getParking() == 1){
                    pns.push_back(n->getID());
                }
            }

            vector<int> bdr;
            vector<int> bwr;
            int bdt = INT_MAX;
            int bwt = INT_MAX;
            for (int pni : pns){
                Node *pn = g->findNode(pni);

                GetDriving gd;
                gd.dijkstra(g, orig);

                vector<int> dPath;
                if (pn->getPath() == nullptr){
                    continue;
                }
                Node *cn = g->findNode(pn);
                cn = cn->getPath();
                while (cn){
                    dPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(dPath.begin(), dPath.end());
                int cdt = pn->getDistance();

                GetWalking gw;
                gw.dijkstra(g, pn);

                vector<int> wPath;
                if (dest->getPath() == nullptr || dest->getDistance() > mwt){
                    continue;
                }
                cn = g->findNode(dest);
                while (cn){
                    wPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(wPath.begin(), wPath.end());
                int cwt = dest->getDistance();

                if ((cdt + cwt < bdt + bwt) || (cdt + cwt == bdt + bwt && cwt > bwt)){
                    bdt = cdt;
                    bwt = cwt;
                    bdr = dPath;
                    bwr = wPath;
                }
            }

            return {{bdr, bwr}, {bdt, bwt}};
        }
}

