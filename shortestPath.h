
#ifndef _SHORTEST_PATH_H_
#define _SHORTEST_PATH_H_

#include "heap.h"

class Path{
private:
	int optimal_routing_table[2][MAXNODES]; //First row contains cost, second row contains next router.

private:
	int get_next_router(int *path,int source, int destination);

	void print_shortest_path(int *path,int source, int destination);

	void print_optimal_result(int *path,int source,int destination, int router_cnt);

public:
	void shortest_path(int source,int destination,int router_cnt, int link_state_packet[][MAXNODES]);

};

#endif
