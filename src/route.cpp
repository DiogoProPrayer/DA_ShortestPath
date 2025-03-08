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
                return {tempPath, -1};
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

        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>>, pair<bool, bool>> mainEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){
            bool eml = true;
            bool aop = true;

            for (int id : aNodes){
                g->removeNode(id);
            }

            for (auto& edge : aEdges){
                g->removeEdge(edge.first, edge.second);
            }

            vector<int> bdr;
            vector<int> bwr;
            int bdt = INT_MAX;
            int bwt = INT_MAX;
            for (Node* n : g->getNodes()){
                GetDriving gd;
                gd.dijkstra(g, orig);

                vector<int> dPath;
                if (n->getPath() == nullptr){
                    continue;
                }
                Node *cn = g->findNode(n);
                cn = cn->getPath();
                while (cn){
                    dPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(dPath.begin(), dPath.end());
                int cdt = n->getDistance();

                GetWalking gw;
                gw.dijkstra(g, n);

                vector<int> wPath;
                if (dest->getPath() == nullptr){
                    continue;
                }
                cn = g->findNode(dest);
                while (cn){
                    wPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(wPath.begin(), wPath.end());
                int cwt = dest->getDistance();

                if (cwt < mwt && n->getParking() == 1){
                    if ((cdt + cwt < bdt + bwt) || (cdt + cwt == bdt + bwt && cwt > bwt)){
                        bdt = cdt;
                        bwt = cwt;
                        bdr = dPath;
                        bwr = wPath;
                    }
                    eml = false;
                    aop = false;
                }
                else if (dest->getDistance() < mwt){
                    eml = false;
                }
                else if (n->getParking() == 1) {
                    aop = false;
                }
                else{
                    continue;
                }
            }

            return {{{bdr, bwr}, {bdt, bwt}}, {eml, aop}};
        }

        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> nwlEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){
            for (int id : aNodes){
                g->removeNode(id);
            }

            for (auto& edge : aEdges){
                g->removeEdge(edge.first, edge.second);
            }

            vector<int> fbdr;
            vector<int> fbwr;
            int fbdt = INT_MAX;
            int fbwt = INT_MAX;
            vector<int> sbdr;
            vector<int> sbwr;
            int sbdt = INT_MAX;
            int sbwt = INT_MAX;
            for (Node* n : g->getNodes()){
                GetDriving gd;
                gd.dijkstra(g, orig);

                vector<int> dPath;
                if (n->getPath() == nullptr){
                    continue;
                }
                Node *cn = g->findNode(n);
                cn = cn->getPath();
                while (cn){
                    dPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(dPath.begin(), dPath.end());
                int cdt = n->getDistance();

                GetWalking gw;
                gw.dijkstra(g, n);

                vector<int> wPath;
                if (dest->getPath() == nullptr){
                    continue;
                }
                cn = g->findNode(dest);
                while (cn){
                    wPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(wPath.begin(), wPath.end());
                int cwt = dest->getDistance();

                if (n->getParking() == 1){
                    if ((cdt + cwt < fbdt + fbwt) || (cdt + cwt == fbdt + fbwt && cwt > fbwt)){
                        sbdt = sbdt;
                        sbwt = sbwt;
                        sbdr = sbdr;
                        sbwr = sbwr;
                        fbdt = cdt;
                        fbwt = cwt;
                        fbdr = dPath;
                        fbwr = wPath;
                    }
                    else if ((cdt + cwt < sbdt + sbwt) || (cdt + cwt == sbdt + sbwt && cwt > sbwt)){
                        sbdt = cdt;
                        sbwt = cwt;
                        sbdr = dPath;
                        sbwr = wPath;
                    }
                    else{
                        continue;
                    }
                }
                else{
                    continue;
                }
            }

            return {{{fbdr, fbwr}, {fbdt, fbwt}}, {{sbdr, sbwr}, {sbdt, sbwt}}};
        }

        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> apoEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){
            for (int id : aNodes){
                g->removeNode(id);
            }

            for (auto& edge : aEdges){
                g->removeEdge(edge.first, edge.second);
            }

            vector<int> fbdr;
            vector<int> fbwr;
            int fbdt = INT_MAX;
            int fbwt = INT_MAX;
            vector<int> sbdr;
            vector<int> sbwr;
            int sbdt = INT_MAX;
            int sbwt = INT_MAX;
            for (Node* n : g->getNodes()){
                GetDriving gd;
                gd.dijkstra(g, orig);

                vector<int> dPath;
                if (n->getPath() == nullptr){
                    continue;
                }
                Node *cn = g->findNode(n);
                cn = cn->getPath();
                while (cn){
                    dPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(dPath.begin(), dPath.end());
                int cdt = n->getDistance();

                GetWalking gw;
                gw.dijkstra(g, n);

                vector<int> wPath;
                if (dest->getPath() == nullptr){
                    continue;
                }
                cn = g->findNode(dest);
                while (cn){
                    wPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(wPath.begin(), wPath.end());
                int cwt = dest->getDistance();

                if (cwt < mwt){
                    if ((cdt + cwt < fbdt + fbwt) || (cdt + cwt == fbdt + fbwt && cwt > fbwt)){
                        sbdt = fbdt;
                        sbwt = fbwt;
                        sbdr = fbdr;
                        sbwr = fbwr;
                        fbdt = cdt;
                        fbwt = cwt;
                        fbdr = dPath;
                        fbwr = wPath;
                    }
                    else if ((cdt + cwt < sbdt + sbwt) || (cdt + cwt == sbdt + sbwt && cwt > sbwt)){
                        sbdt = cdt;
                        sbwt = cwt;
                        sbdr = dPath;
                        sbwr = wPath;
                    }
                    else{
                        continue;
                    }
                }
                else{
                    continue;
                }
            }

            return {{{fbdr, fbwr}, {fbdt, fbwt}}, {{sbdr, sbwr}, {sbdt, sbwt}}};
        }

        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> nrEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges){
            for (int id : aNodes){
                g->removeNode(id);
            }

            for (auto& edge : aEdges){
                g->removeEdge(edge.first, edge.second);
            }

            vector<int> fbdr;
            vector<int> fbwr;
            int fbdt = INT_MAX;
            int fbwt = INT_MAX;
            vector<int> sbdr;
            vector<int> sbwr;
            int sbdt = INT_MAX;
            int sbwt = INT_MAX;
            for (Node* n : g->getNodes()){
                GetDriving gd;
                gd.dijkstra(g, orig);

                vector<int> dPath;
                if (n->getPath() == nullptr){
                    continue;
                }
                Node *cn = g->findNode(n);
                cn = cn->getPath();
                while (cn){
                    dPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(dPath.begin(), dPath.end());
                int cdt = n->getDistance();

                GetWalking gw;
                gw.dijkstra(g, n);

                vector<int> wPath;
                if (dest->getPath() == nullptr){
                    continue;
                }
                cn = g->findNode(dest);
                while (cn){
                    wPath.push_back(cn->getId());
                    cn = cn->getPath();
                }
                reverse(wPath.begin(), wPath.end());
                int cwt = dest->getDistance();

                if ((cdt + cwt < fbdt + fbwt) || (cdt + cwt == fbdt + fbwt && cwt > fbwt)){
                    sbdt = fbdt;
                    sbwt = fbwt;
                    sbdr = fbdr;
                    sbwr = fbwr;
                    fbdt = cdt;
                    fbwt = cwt;
                    fbdr = dPath;
                    fbwr = wPath;
                }
                else if ((cdt + cwt < sbdt + sbwt) || (cdt + cwt == sbdt + sbwt && cwt > sbwt)){
                    sbdt = cdt;
                    sbwt = cwt;
                    sbdr = dPath;
                    sbwr = wPath;
                }
                else{
                    continue;
                }
            }

            return {{{fbdr, fbwr}, {fbdt, fbwt}}, {{sbdr, sbwr}, {sbdt, sbwt}}};
        }
}

