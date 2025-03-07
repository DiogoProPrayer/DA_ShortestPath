#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <graph.h>

using namespace std;

template <class T>
class RoutePlanner {
    private:
        Graph<T>* g;
        Node<T>* orig;
        Node<T>* dest;
        GetDriving<T> gd;

    public:
        // fill the data

        vector<int> 1DrivingRoute(){
            gd.dijkstra(g, orig);

            vector<T> path;

            if (dest->getParking() == 0 || dest->getPath() == nullptr){
                return path;
            }

            Node<T> *cn = g->findNode(dest);
            while (v){
                path.push_back(v->getId());
                cn = cn->getPath();
            }

            reverse(path.begin(), path.end());
            return path;
        }

        vector<int> 2DrivingRoute(){
            // see which mode - if driving only 
            gd.dijkstra(g, orig);

            // Build path
            vector<T> path;

            if (dest->getParking() == 0 || dest->getPath() == nullptr){
                return path;
            }

            Node<T> *cn = g->findNode(dest);
            while (v){
                path.push_back(v->getId());
                cn = cn->getPath();
            }

            reverse(path.begin(), path.end());
            return path;
        }
            
}

#endif

