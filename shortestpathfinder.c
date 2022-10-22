
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define INFINITY 9999
#define MAX 10

//global variables for algorithm
int customLocation ;
int cost[MAX][MAX], distance[MAX], pred[MAX];
char districts[5][25] = {"Colombo", "Matara", "Kaluthara", "Jafna", "kaduwela"};

void dijkstra(int G[MAX][MAX], int n, int startnode,int endnode);
void printLocaitons();
void printShortestPaths(int startnode, int endnode, int pred[MAX], int distance[MAX]);


// Hard coded path weights between districts
int G[MAX][MAX] = {
    {0, 10, 0, 30, 100},
    {10, 0, 50, 0, 0},
    {0, 50, 0, 20, 10},
    {30, 0, 20, 0, 60},
    {100, 0, 10, 60, 0}};

//main method
void main()
{
    int ch, n, u;

    do
    {
        printf("\n**************************************\n");
        printf("----Shortest Distance Finder----");
	    printf("\n**************************************\n");
    
        printf("\n1.Show Shortest Paths for given Cities    (Press 1)");
        printf("\n2.Get Shortest path Between Custom Cities (Press 2) ");
        printf("\n3.Exit from the system                    (Press 3) ");
        printf("\n-------------------------------------------");
        printf("\nENTER Your Choice : ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            printLocaitons();
            printf("\n1.Enter Start Location : ");
            scanf("%d", &n);
            customLocation = 0;
            dijkstra(G, 5, n,1);
            break;
        case 2:
            printLocaitons();
            printf("\n---Find distance to Custom path---");
            printf("\n1.Enter Start Location : ");
            scanf("%d", &n);
            printf("2.Enter Destination : ");
            scanf("%d", &u);
            customLocation=1;
            dijkstra(G, 5,n,u);
            break;
        case 3:
            exit(0);
        default:
            printf("...........................\n---! Choice is incorrect, try again---\n.............................\n");
        }
    } while (1);
}

//This funciton represents dijkstra algorithm
void dijkstra(int G[MAX][MAX], int n, int startnode ,int endnode)
{

    int visited[MAX], count, mindistance, nextnode, i, j;
    // pred[] stores the predecessor of each node
    // count gives the number of nodes seen so far
    // create the cost matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (G[i][j] == 0)
                cost[i][j] = INFINITY;
            else
                cost[i][j] = G[i][j];

    // initialize pred[],distance[] and visited[]
    for (i = 0; i < n; i++)
    {
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    while (count < n - 1)
    {
        mindistance = INFINITY;
        // nextnode gives the node at minimum distance
        for (i = 0; i < n; i++)
            if (distance[i] < mindistance && !visited[i])
            {
                mindistance = distance[i];
                nextnode = i;
            }
        // check if a better path exists through nextnode
        visited[nextnode] = 1;
        for (i = 0; i < n; i++)
            if (!visited[i])
                if (mindistance + cost[nextnode][i] < distance[i])
                {
                    distance[i] = mindistance + cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }

    // print the path and distance of each node
    printShortestPaths(startnode,endnode, pred, distance);

    printf("\n\n");
}

// This funciton represent Print selected locations to Terminal
void printLocaitons()
{
    int i;
    printf("\nLocation ordered by Numbers\n----------------------------------");
    for (i = 0; i < 5; i++)
    {
        printf("\nPress %d : %s ", i, districts[i]);
    }
    printf("\n----------------------------------");
}

// This function print shortest path to each node
void printShortestPaths(int startnode, int endnode, int pred[MAX], int distance[MAX])
{
    int i, j, n = 5;
    if (customLocation==1)
    {   printf("\nShortest Path Between Custom Cities\n.........................................");
        for (i = 0; i < n; i++)
            if (i = endnode)
            {
                j = i;
                
                printf("\nDistance to %s =%d", districts[i], distance[i]);
                printf("\nPaths To Destination= %s", districts[i]);

                do
                {
                    j = pred[j];
                    printf(" <- %s", districts[j]);
                } while (j != startnode);
                printf("\n");
                break;
            }
    }
    else
       {
        printf("\nShortest Path To All Cities\n.........................................");
         for (i = 0; i < n; i++)
            if (i != startnode)
            {
                j = i;
                
                printf("\nDistance to %s = %d", districts[i], distance[i]);
                printf("\nPath To Destination= %s", districts[i]);

                do
                {
                    j = pred[j];
                    printf(" <- %s", districts[j]);
                } while (j != startnode);
                printf("\n");
            }
       }
   }

