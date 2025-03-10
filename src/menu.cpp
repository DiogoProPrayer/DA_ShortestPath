#include "graph.h"
#include "node.h"
#include "edge.h"
#include "getDriving.h"
#include "getWalking.h"
#include "route.h"
#include "planner.h"

// Call input
// check mode

// if driving only
// if idependent route
    // Get results
    Route r;
    pair<vector<int>, int> bestRes = r.bestDrivingRoute(g, orig, dest);
    pair<vector<int>, int> altRes = r.altDrivingRoute(g, orig, dest);
    
    // Get routes and distances
    vector<int> br = bestRes.first; // best route
    vector<int> ar = altRes.first; // alternative route
    int bd = res.second; // best distance
    int ad = res.second; // alternative distance

    // Output orig and dest
    cout << "Source:" << orig.getId() << "\n" << "Destination:" << dest.getId() << "\n";

    // Output best driving route
    cout << "BestDrivingRoute:" << orig.getId();
    for (int id = 1; id < br.size(); id++){
        cout << "," << br[id];
    }
    cout << "(" << bd << ")" << "\n";

    // Output alternative driving route
    cout << "AlternativeDrivingRoute:" << orig.getId();
    for (int id = 1; id < ar.size(); id++){
        cout << "," << ar[id];
    }
    cout << "(" << ad << ")" << "\n";

// if restricted route
    //call resDrivingRoute


// if environmental
// if best route - call mainEnvironmentalRoute - handle output
// if best route failed because exceeds maximum limit - call nwlEnvironmentalRoute - handle output
// if best route failed because absence of parking - call apoEnvironmentalRoute - handle output
// if best route failed because exceeds maximum limit && absence of parking - call nrEnvironmentalRoute - handle output