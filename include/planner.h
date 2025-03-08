// Call input
// check mode
// if driving only, main route - call mainDrivingRoute - handle output
// if driving only, alternative route - call altDrivingRoute - handle output
// if driving only, restricted route - call resDrivingRoute - handle output
// if environmental, main route - call mainEnvironmentalRoute - handle output
// if environmental, main route failed because exceeds maximum limit - call nwlEnvironmentalRoute - handle output
// if environmental, main route failed because absence of parking - call apoEnvironmentalRoute - handle output
// if environmental, main route failed because exceeds maximum limit && absence of parking - call nrEnvironmentalRoute - handle output