
#include <iostream>
#include <iomanip>

#include "shortestPath.h"

using namespace std;


void Path::print_shortest_path(int *path,int source, int destination){
        int current = destination;

        if(current != source){
                print_shortest_path(path,source,path[current-1]+1);
                cout << path[current-1]+1 << "--";   //print previous router that can reach present router
        }

}


void Path::print_optimal_result(int *path,int source,int destination, int router_cnt){
        //print optimal routing table of given router   
        if(destination == 0){
                int dst;
                cout << "The routing table for router " << source << " is:" << endl;

                cout << "Destination:";
                for(dst=0;dst<=router_cnt;dst++)
                        cout << setw(3) << dst+1;

                cout << "\n       Cost:";
                for(dst=0;dst<=router_cnt;dst++)
                        cout << setw(3) << optimal_routing_table[0][dst];

                cout << "\nNext Router:";
                for(dst=0;dst<=router_cnt;dst++){
                        cout << setw(3) << optimal_routing_table[1][dst];
                }

                cout << "\n";
        }
        //print shortest path from source to destination, and minimun cost value
        else{
                cout << "The shortest path from " << source << "to " << destination << " is\n";
                print_shortest_path(path,source,destination);
                cout << destination;
                cout << ",the total cost is " << optimal_routing_table[0][destination-1] << endl;
        }
}


int Path::get_next_router(int *path,int source, int destination){
        int current = destination;

        if(path[current-1]+1 != source)  //if previous router of destination node is not source node 
                get_next_router(path,source,path[current-1]+1);  //then recursively check previous node

        else
                return current;   //return next router from source to reach destination

}


void Path::shortest_path(int source,int destination,int router_cnt, int link_state_packet[][MAXNODES]){

        int seen[MAXNODES]={0};   //record traversed router
        int cost[MAXNODES];       //cost of source router to reach other routers
        int path[MAXNODES]={0};   //path record of source to destination
        int iter,count;

        Heap myHeap;     //initialize priority queue, so we can use it properly

        /*insert nodes to the heap*/
        for(count = 0; count <= router_cnt; count++){
                Node* router = new Node;

                router->id = count+1;
                router->distance = INFINITY;    //initialize distance as infinity
                router->prev_router = 0;
                myHeap.Insert(router);
        }

        //update source router with distance of 0 and prev router is 0
        myHeap.update_Q(source,0,0);

        //loop until all these routers in the heap have been processed
        while(myHeap.size())
        {
                Node* router = myHeap.Extract_Min();       //get router with minimum distance
                int presentVertex = router->id;        //get router id
                seen[presentVertex-1] = 1;              //set this router as seen, to inform this router has been processed
                path[presentVertex-1] = router->prev_router-1;       //record popped router's previous router into the path,
                                                                     //present router will be reached from previous router

                //update optimal routing table for source router
                optimal_routing_table[0][presentVertex-1] = router->distance;
                //get cost value for present router to reach other routers
                for(iter = 0; iter <= router_cnt; iter++){
                        cost[iter] = link_state_packet[presentVertex-1][iter];
                }
                //check directly connected routers from present router
                for(iter = 0; iter <= router_cnt; iter++)
                {
                        if(seen[iter] == 1 || cost[iter] == -1) /* This router has already been processed*/
                                continue;                       /* or cannot reach from present router */

                        else{
                                int next_router = iter+1;      //next directly connected router
                                int to;
                                for(to = 1;to <= myHeap.size();to++){
                                        if(myHeap.node_p[to]->id == next_router)  //find next router in the heap
                                                break;
                                }
                                if((router->distance + cost[iter]) < myHeap.node_p[to]->distance) //if next connected router's distance is larger than
                                {                                                      //present router's distance + cost to that router
                                        int distance = router->distance + cost[iter];  //update next router's distance with less distance
                                        myHeap.update_Q(next_router,distance,presentVertex);
                                }
                        }
                }

                delete router; //Finish it's tasks.

        }
        //Generate next router from source to reach destination
	int dst;
        for(dst = 0; dst <= router_cnt; dst++){
                if(source == dst+1)
                        optimal_routing_table[1][dst] = 0;
                else
                        optimal_routing_table[1][dst] = get_next_router(path,source,dst+1);
        }


        print_optimal_result(path,source,destination,router_cnt);

}

