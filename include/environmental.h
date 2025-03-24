#include <vector>
#include <utility>
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "getDriving.h"
#include "getWalking.h"

using namespace std;

// Class route to get the routes
class Route {
    public:

        // Calculate main driving route
        pair<vector<int>, int> mainDrivingRoute(Graph* g, Node* orig, Node* dest);

        // Calculate alternative driving route
        pair<vector<int>, int> altDrivingRoute(Graph* g, Node* orig, Node* dest);
        
        // Calculate restricted driving route
        pair<vector<int>, int> resDrivingRoute(Graph* g, Node* orig, Node* dest, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges, Node* iNode);

        // Calculate main environmental route
        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>>, pair<bool, bool>> mainEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges);

        // Calculate environmental route with no walking limit
        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> nwlEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges);

        // Calculate environmental route with any parking option
        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> apoEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges);

        // Calculate environmental route with no rules
        pair<pair<pair<vector<int>, vector<int>>, pair<int, int>, pair<vector<int>, vector<int>>, pair<int, int>>> nrEnvironmentalRoute(Graph* g, Node* orig, Node* dest, int mwt, vector<int> aNodes, vector<pair<Node*, Node*>> aEdges);
};

