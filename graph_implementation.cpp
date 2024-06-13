#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"uthash.h"


/*Note: in graph representation,(esp adjacency list) the nodes typically contain references(or indices)
to other nodes rather than storing the actual data of the node themselves.
- the data(such as names or other information) is often stored separately in a more efficicent structure
,like an an array or hash map

- The below code effectively seperates the data storage(vertex names) 
from the structural representation(adjacency lists) of the graph
--> clean, efficicent graph implementation
*/

// any C structure can be store in a hash table using uthash
// just add a UT_hash_handle to the structure and choose one or more field in your structure to act as key


#define NAME_SIZE 50

//adjacency list node 

typedef struct AdjListNode {
	int dest; // destination vertex index
	struct AdjListNode*next; // pointer to the next adjancency list node
}AdjListNode;

//adjacency list
typedef struct AdjList {
	AdjListNode* head;
}AdjList;

// STORE THIS STRUCTURE IN A HASH TABLE WITH NAME VERTEX AS KEY IN ORDER TO LOOK UP THE ID OF VERTEX IN O(1) TIME
typedef struct VertexNameMap {
	char name[NAME_SIZE]; // VERTEX NAME, make this field as key
	int id; // vertex id
	UT_hash_handle hh; // make this structure hashable 
}VertexNameMap;

//Graph 

typedef struct Graph {
	int num_vertices; // current number of vertices
	int capacity; // maximum capacity of vertices befor resizing 
	AdjList*array; // array of adjacency list
	char** vertex_names; // array of vertex names
	VertexNameMap* vertex_map; // hash map of vertex names to indices
}Graph;

//Function to create a new Adjacency list node

AdjListNode*newAdjListNode(int dest) {
	AdjListNode*newNode=(AdjListNode*)malloc(sizeof(AdjListNode));
	newNode->next=NULL;
	newNode->dest=dest;
	return newNode;
}

//Function to create a graph with a given initial capacity

Graph*createGraph(int capacity) {
	Graph*graph=(Graph*)malloc(sizeof(Graph));
	graph->num_vertices=0;
	graph->capacity=capacity;
	graph->array=(AdjList*)malloc(sizeof(AdjList)*capacity);
	graph->vertex_names=(char**)malloc(capacity*sizeof(char*));
	graph->vertex_map=NULL;
	for(int i=0; i<capacity; i++) {
		graph->array[i].head=NULL;
		graph->vertex_names[i]=NULL;
	}
	return graph;
}

//Function to resize the graph's storage

void resizeGraph(Graph*graph) {
	int new_capacity=graph->capacity*2;
	graph->array=(AdjList*)realloc(graph->array, new_capacity*sizeof(AdjList));
	graph->vertex_names=(char**)realloc(graph->vertex_names, new_capacity*sizeof(char*));
	for(int i=graph->capacity; i<new_capacity; i++) {
		graph->array[i].head=NULL;
		graph->vertex_names[i]=NULL;
	}
	graph->capacity=new_capacity;
}

int addVertex(Graph*graph, const char*name) {
	if(graph->num_vertices==graph->capacity)
		resizeGraph(graph);
	int vertex_id=graph->num_vertices;
	graph->vertex_names[vertex_id]=(char*)malloc(sizeof(char)*NAME_SIZE);
	strcpy(graph->vertex_names[vertex_id], name);
	
	
	//Add to the hash map
	VertexNameMap*v =(VertexNameMap*)malloc(sizeof(VertexNameMap));
	v->id=vertex_id;
	strcpy(v->name, name);
	HASH_ADD_STR(graph->vertex_map, name, v);
	
	graph->num_vertices++;
	return vertex_id;
}

// Function to get the vertex index given its name 

int getVertexIndex(Graph*graph, const char*name) {
	VertexNameMap*v;
	HASH_FIND_STR(graph->vertex_map,name,v);
	return v ? v->id: -1;
}



//Function to get the vertex name given its index
const char*getVertexName(Graph*graph, int index) {
	if(index>=graph->num_vertices)
		return NULL; // Invalid index
	return graph->vertex_names[index];
}


// function to add an edge to undirected graph
void addEdge(Graph*graph, int src, int dest) {
	if(src>=graph->num_vertices || dest >= graph->num_vertices) {
		printf("Vertex not found in the graph");
		return;
	}
	
	// Add an edge from src to dest 
	AdjListNode*newNode=newAdjListNode(dest);
	newNode->next=graph->array[src].head;
	graph->array[src].head=newNode;
	
	// since graph is undirected, add an edge from dest to src also
	newNode=newAdjListNode(src);
	newNode->next=graph->array[dest].head;
	graph->array[dest].head=newNode;
}

// function to print the graph

void printGraph(Graph*graph) {
	for(int v=0; v<graph->num_vertices; v++) {
		AdjListNode*p=graph->array[v].head;
		printf("%s (%d):", graph->vertex_names[v], v);
		while(p!=NULL) {
			printf("%s (%d) -> ", graph->vertex_names[p->dest], p->dest);
			p=p->next;
		}
		printf("NULL\n");	
	}
}


// BFS traversal from a given source vertex 
void BFS(Graph*graph, int startVertex) {
	bool*visited=(bool*)malloc(graph->num_vertices* sizeof(bool));
	for(int i=0; i<graph->num_vertices; i++) 
		visited[i]=false;
	int*queue=(int*)malloc(graph->num_vertices*sizeof(int));
	int front=0, rear=0;
	visited[startVertex]=true;
	//enqueue the vertex at startvertex
	queue[rear++]=startVertex;
	while(front!=rear) {
		//get the current vertex and explore all its immediate's neighbors
		int currentVertex=queue[front++];
		printf("%s ", graph->vertex_names[currentVertex]);
		AdjListNode*ptr=graph->array[currentVertex].head;
		while(ptr!=NULL) {
			int connectedVertex=ptr->dest;
			if(!visited[connectedVertex]) {
				queue[rear++]=connectedVertex;
				visited[connectedVertex]=true;
			}
			ptr=ptr->next;
		}
	}
	printf("\n");
	free(queue);
	free(visited);
}

//recursive function for DFS

void DFSUtil(Graph*graph, int v, bool visited[]) {
	visited[v]=true;
	printf("%s ", graph->vertex_names[v]);
	
	AdjListNode*ptr=graph->array[v].head;
	while(ptr!=NULL) {
		int connectedVertex=ptr->dest;
		if(!visited[connectedVertex]) {
			DFSUtil(graph, connectedVertex, visited);
		}
		ptr=ptr->next;
	}
}


// DFS traversal of the vertices reachable from v

void DFS(Graph*graph, int startVertex) {
	bool*visited=(bool*)malloc(sizeof(bool)*graph->num_vertices);
	for(int i=0; i<graph->num_vertices; i++)
		visited[i]=false;
	DFSUtil(graph, startVertex, visited);
	/*for disconnected graph
	for(int i=0; i<graph->num_vertices; i++) {
		if(!visited[i]) {
		DFSUtil(graph,i,visited);
		printf("\n");	
	}
}
	*/
	printf("\n");
	free(visited);
}

int main () {
	
	// Initial capacity is 2
	Graph*graph=createGraph(2);
	
	int v1 = addVertex(graph, "A");
	int v2 = addVertex(graph, "B");
	int v3 = addVertex(graph, "C");
	
	addEdge(graph, v1, v2);
    addEdge(graph, v2, v3);
    
//    printGraph(graph);
    
        // Adding more vertices dynamically
    int v4 = addVertex(graph, "D");
    int v5 = addVertex(graph, "E");
    
    addEdge(graph, v3, v4);
    addEdge(graph, v4, v5);

//    printGraph(graph);
	    // Get vertex name by index
    printf("Vertex name at index %d: %s\n", v3, getVertexName(graph, v3));
		//Get vertex i/?ndex by name 
	printf("Vertex index for name %s: %d\n", "A",getVertexIndex(graph, "A"));
	BFS(graph, 1);
	DFS(graph,1);
}