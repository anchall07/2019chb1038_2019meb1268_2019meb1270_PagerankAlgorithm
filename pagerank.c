#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <math.h>
#define long double double
const double d = 0.850;
const int N = 1e5 + 4;
struct listnode
{
    int key;
    struct listnode *next;
    struct listnode *prev;
    struct listnode *NodeHead;
};
struct listnode *crnode(int u)
{
    struct listnode *vertex = (struct listnode *)malloc(sizeof(struct listnode));
    vertex->key = u;
    vertex->next = vertex->prev = vertex->NodeHead = NULL;
    return vertex;
};
struct listnode *nodeins(struct listnode **grp, int u, struct listnode *vertex)
{
    struct listnode *head = grp[u];
    int k = vertex->key;
    vertex->NodeHead = grp[k];
    while (head && head->next)
    {
        head = head->next;
    }
    head->next = vertex;
    vertex->prev = head;
    head = head->next;
    return grp[u];
};
struct listnode *nodeinsdir(struct listnode **grp, int u, struct listnode *vertex)
{
    struct listnode *head = grp[u];
    int k = vertex->key;
    vertex->NodeHead = grp[k];
    while (head && head->next)
    {
        head = head->next;
    }
    head->next = vertex;
    head = head->next;
    return grp[u];
};
void lisprint(int v, struct listnode *curr)
{
    curr = curr->next;
    printf("Vertex %d: ", v);
    if (!curr)
    {
        return;
    }
    while (curr && curr->next)
    {
        printf("%d -> ", curr->key);
        curr = curr->next;
    }
    printf("%d", curr->key);
    return;
}
void grpprint(struct listnode **grp, int vertex)
{
    for (int i = 0; i < vertex; ++i)
    {
        lisprint(i, grp[i]);
        printf("\n");
    }
}
void calcpagerank(struct listnode **grp, int vertex)
{
    int *linkcount = (int *)calloc(vertex, sizeof(int));
    for (int i = 0; i < vertex; i++)
    {
        struct listnode *curr = (struct listnode *)calloc(1, sizeof(struct listnode));
        curr = grp[i]->next;
        while (curr != NULL)
        {
            linkcount[i]++;
            curr = curr->next;
        }
    }
    double *oldpagerank = (double *)calloc(vertex, sizeof(double));
    double *newpagerank = (double *)calloc(vertex, sizeof(double));
    for (int i = 0; i < vertex; i++)
    {
        oldpagerank[i] = 1 / vertex;
        newpagerank[i] = 0.00;
    }
    for (int i = 0; i < vertex; i++)
    {
        struct listnode *temp = (struct listnode *)calloc(1, sizeof(struct listnode));
        temp = grp[i]->next;
        if (temp == NULL)
        {
            for (int i = 0; i < vertex; i++)
            {
                newpagerank[i] += (double)(d * oldpagerank[i] / vertex);
            }
        }
        else
        {
            while (temp != NULL)
            {
                if (linkcount[temp->key] != 0)
                {
                    newpagerank[temp->key] += (double)(d * oldpagerank[temp->key] / linkcount[temp->key]);
                    temp = temp->next;
                }
                else
                {
                    for (int i = 0; i < vertex; i++)
                    {
                        newpagerank[i] += (double)(d * oldpagerank[i] / vertex);
                    }
                }
            }
        }
    }
    for (int i = 0; i < vertex; i++)
    {
        newpagerank[i] += (double)((1 - d) / vertex);
    }
    for (int i = 0; i < vertex; i++)
    {
        printf("%d: %f\n", i, newpagerank[i]);
    }
}
int main()
{
    int vertex;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertex);
    printf("\n");
    printf("Enter D for directed or U for undirected graphs: \n");
    char c;
    scanf(" %c", &c);
    struct listnode *grp[vertex];
    if (vertex == 0)
    {
        printf("Invalid entry\n");
        exit(0);
    }
    if (c == 'U' || c == 'u')
    {
        for (int i = 0; i < vertex; ++i)
        {
            struct listnode *temp = (struct listnode *)malloc(sizeof(struct listnode));
            temp = crnode(-1);
            grp[i] = temp;
        }
        char q;
        while (1)
        {
            int u, v;
            scanf(" %c", &q);
            if (q == 'Q' || q == 'q')
            {
                break;
            }
            u = q - '0';
            scanf("%d", &v);
            struct listnode *node1 = crnode(u);
            struct listnode *node2 = crnode(v);
            grp[u] = nodeins(grp, u, node2);
            grp[v] = nodeins(grp, v, node1);
        }
        grpprint(grp, vertex);
    }
    else if (c == 'D' || c == 'd')
    {
        for (int i = 0; i < vertex; ++i)
        {
            struct listnode *temp = (struct listnode *)malloc(sizeof(struct listnode));
            temp = crnode(-1);
            grp[i] = temp;
        }
        char q;
        while (1)
        {
            int u, v;
            scanf(" %c", &q);
            if (q == 'Q')
            {
                break;
            }
            u = q - '0';
            scanf("%d", &v);
            struct listnode *node2 = crnode(v);
            grp[u] = nodeinsdir(grp, u, node2);
        }
        grpprint(grp, vertex);
    }
    calcpagerank(grp, vertex);
}