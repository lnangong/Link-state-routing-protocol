
#include "heap.h"
#include <cstddef>

//Heap constructor, build sentinel node
Heap::Heap(){
	heap_size = 0;
	node_p[0] = new Node;
	node_p[0]->id  = -1;
	node_p[0]->distance = INFINITY;
	node_p[0]->prev_router = 0;
}

//Heap destructor
Heap::~Heap(){ delete node_p[0]; }

//swap parent node with child node to maintian heap property
void Heap::swap_node(int parent, int child)
{
    Node *temp;
    temp = node_p[parent];
    node_p[parent] = node_p[child];
    node_p[child] = temp;

}

//this is core function to maintain min_heap property
void Heap::heapify_up(int i)
{
	if(node_p[i/2]->id != -1){
		if (node_p[i/2]->distance > node_p[i]->distance)
		{
			swap_node(i/2, i);
			heapify_up(i/2);
		}
	}

}

void Heap::Insert(Node *element)
{
	heap_size++;
	node_p[heap_size] = element;

	/*Adjust its position*/
	heapify_up(heap_size);
}


Node* Heap::Extract_Min()
{
	/* heap[1] is the minimum element. So we remove heap[1]. Size of the heap is decreased by one.
	   Now heap[1] has to be filled. We put the last element in its place and do heapify_up for each
	   child node to maintain min_heap property.*/
	Node* minNode;
	int iter;

	minNode = node_p[1];
	node_p[1] = node_p[heap_size];
	heap_size--;

	/* iteration to maintain min-heap property by min_heapify*/
	for(iter = 2; iter <= heap_size ; iter++)
		heapify_up(iter);

	return minNode;
}

//update element in the heap with new value
void Heap::update_Q(int next_router,int distance,int prev_router)
{
	int v;

	for(v = 1; v <= heap_size; v++){
		if(node_p[v]->id == next_router){   //check node in the heap which contains this router's information
			node_p[v]->distance = distance;
			node_p[v]->prev_router = prev_router;
			heapify_up(v);    //do heapify to maintain heap property
		}

	}
}

