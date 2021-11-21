///FINAL PAGE RANK ALGORITHM
///Sorting done using insertion sort
///Input Taken Manually


#include<stdio.h>
#include<stdlib.h>
#include<time.h>


///Defining Structure of Node for nodes of Adjacency List
struct ListNode{
    int vertex;                 //stores vertex number
    struct ListNode*next;

};

///defining structure of vertex for graph
struct Vertex{
    int vnum; //stores the vertex number
    struct ListNode *head;
    double oldPR;     //stores pagerank of vertex
    double newPR ;
    int links;      //for storing the number of outgoing links
};

///defining structure for graph
struct graph{
    int totalv;                 //total number of vertices in graph
    struct Vertex* array;

};



///function declaratioms
void createGraph(int n);
void directedEdge(struct graph* G, int a, int b);
void pagerank(struct graph*G);
void printPageRank(struct graph *G);
void getfromfile();
void sortPR(struct graph *G);



#define epsilon 0.000001
#define d 0.85 //damping factor
struct graph *G;
int edges=0;//for calculating total number of edges in graph
int n;


int main(){

    getfromfile();

    printf("----------------------------------------------------------------------------\n");

    printf("\t\t\tENTERED GRAPH\n\n\t\tTotal Number of Vertices = %d\n\t\tTotal Number of Edges = %d\n",G->totalv,edges);


    // Keep track of the execution time
	clock_t begin, end;
	long double time_spent;
	begin = clock();

   //printf("1\n");
    pagerank(G);
    //printf("2\n");

    // Stop the timer and compute the time spent
	end = clock();
	time_spent = (long double)(end - begin) / CLOCKS_PER_SEC;
	printf("\n\tEXECUTION TIME OF PAGERANK ALGORITHM: %E seconds.\n", time_spent);


return 0;

}


void getfromfile()
{
    //taking filename input 	
    FILE *f;
    char filename[16];
    printf("Enter name of file containing graph data.\n");
    fgets(filename, 16, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    //opening file
    f = fopen(filename, "r");
    if (f==NULL)
    {
        fprintf(stderr,"Cannot open file, error\n");
        exit(0);
    }
    int from_node, to_node;
    fscanf(f,"%d", &n);
    printf("\nNumber of nodes: %d\n", n);


    createGraph(n);


       while(!feof(f))
    {
	    fscanf(f,"%d %d",&from_node,&to_node);

	    //printf("\nNode 1: %d, Node 2: %d\n",from_node,to_node);       // Debugging with using printf() statement

	    if(from_node!=to_node && from_node<n && to_node<n && from_node>=0 && to_node>=0){
            directedEdge(G,from_node,to_node);
        }
	}

	fclose(f);

}

///function to create a graph with total number of vertices 'n'
void createGraph(int n){

    //creating a Graph 'G' with n vertices
    G = (struct graph*)malloc(sizeof(struct graph));
    G->totalv = n;                                      //total number of vertices in graph is n
    G->array =(struct Vertex*)malloc(n*sizeof(struct Vertex));  //making an array to store exactly n vertices

    for(int i =0; i<n;i++){
        G->array[i].head = NULL; //intialising the head of the adjacency list of each vertex to NULL
        G->array[i].links = 0;  //initialising the number of outgoing links from each vertex to zero
        G->array[i].vnum = i;   //assigning vertex number

    }


}
///function to add a new edge to a directed graph

void directedEdge(struct graph* G, int a, int b){

    /// for edge a->b
    struct ListNode* p =(struct ListNode*)malloc(sizeof(struct ListNode));
    p->vertex = b;
    p->next = NULL;


    //if adjacency list corresponding to vertex a is empty
    if(G->array[a].head==NULL){
      G->array[a].head = p;
      G->array[a].links++; //incrementing total number of links by 1 since a new edge has been added
      edges = edges +1;
    }

    //if adjacency list corresponding to vertex a is not empty
    else{
        struct ListNode* t =G->array[a].head;

        while(t->next!=NULL){
            if(t->vertex == b){return;}     //making sure edge is distinct from all previously entered edges
            t=t->next;
        }
        if(t->vertex == b){return;}
        t->next =p;
        G->array[a].links++;    //incrementing total number of links by 1 since a new edge has been added
        edges = edges+ 1;
    }

}


///function to calculate page rank of webpages
void pagerank(struct graph*G){

    //printf("3\n");
    int iteration =0; //for counting total number of iterations

    //initialising the Page rank of all vertices to 1/total number of vertices
    for(int i =0; i<G->totalv;i++){
        G->array[i].oldPR = (double)(1/(double)G->totalv);
        G->array[i].newPR= 0;
    }

    struct ListNode* p =(struct ListNode*)malloc(sizeof(struct ListNode));

    while(1){
        iteration ++;
        //traversing the adjacency list of each vertex

        for(int i =0; i<G->totalv;i++){

            //if vertex has outgoing links
                if(G->array[i].links !=0){
                    p = G->array[i].head;
                    while(p!=NULL){
                        G->array[p->vertex].newPR += d*G->array[i].oldPR/G->array[i].links;
                        p = p->next;
                    }
                }
            //if vertex doesnt have outgoing links
                else{
                    for(int j=0; j<G->totalv;j++){
                        G->array[j].newPR += d*G->array[i].oldPR/G->totalv;
                    }
                }
            //adding last term to determine new page rank of each vertex
            G->array[i].newPR += (1-d)/G->totalv;

        }

        //Calculating change in Page Rank value for each vertex
        int flag =0;
        double change;
        for(int m=0; m<G->totalv;m++){
                change = (double)(G->array[m].oldPR - G->array[m].newPR);
                if(change<0){
                    change = change*-1;
                }
                //if change is greater than epsilon make flag =-1 else flag remains zero
                if(change>epsilon){
                   flag = -1;
                   break;
                }
        }

    //printf("4\n");

        //if change in page rank for all vertices is less than epsilon break
        //else continue
        if(flag==0){break;}
        else{
            for(int m=0; m<G->totalv;m++){
                G->array[m].oldPR = G->array[m].newPR;      //updating value of new,old page rank for next iteration
                G->array[m].newPR = 0;

            }
            flag=0;}

    }
    printf("\n------------------------------------------------------------------------------\n");
    printf("\t\t IMPLEMENTATION OF PAGERANK ALGORITHM\n\n");
    printf("\t\t   Total number of iterations = %d\n",iteration);
    sortPR(G);
}

///function to sort graphs according to calculated Page Ranks
void sortPR(struct graph *G){


    for(int n =1; n<G->totalv;n++){
        int m = n-1;
        double key = G->array[n].newPR;
        struct Vertex p = G->array[n];
        while(key<G->array[m].newPR && m>=0){
            G->array[m+1] = G->array[m];
            --m;
        }
        G->array[m+1] =p;
    }
    printPageRank(G);

}

void printPageRank(struct graph *G){
    for(int i =G->totalv-1; i>=0;i--){
        printf("\t\tVertex : %d Calculated Pagerank %lf\n",G->array[i].vnum,G->array[i].newPR);
    }

}
