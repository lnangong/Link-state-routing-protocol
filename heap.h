
#ifndef _HEAP_H_
#define _HEAP_H_

const int INFINITY = 999999;
const int MAXNODES = 1000;

// Heap node
typedef struct Node{
	int id;          //router id
        int distance;    //distance from source router
        int prev_router; //previous router id
}Node;


/*Min-Heap->Priority Queue*/
class Heap{
private:
	int heap_size;

public:
	Node* node_p[MAXNODES];

public:
	/*Heap constructor, we actually utilize it from node_p[1]*/
	Heap();

	~Heap();

	//swap parent node with child node to maintian heap property
	void swap_node(int parent, int child);

	//this is core function to maintain min_heap property
	void heapify_up(int i);
	
	/*Insert an element into the heap */
	void Insert(Node *element);

	Node* Extract_Min();
	
	//update element in the heap with new value
	void update_Q(int next_router,int distance,int prev_router);
	
	int size(){ return heap_size;}	

};

#endif
