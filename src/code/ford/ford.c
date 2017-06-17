#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void graphTester(double **m, int numVertex)
{
    int i, j;

    printf("\nGraph print:\n");
    for(i = 0; i < numVertex; i++)
    {
        for(j = 0; j < numVertex; j++)
        {
            if(m[i][j] > 0)
                printf("[%d -- %.3lf --> %d] ", i, m[i][j], j);
        }
        printf("\n");
    }
}

void matrixPrinter(double **m, double *capacity, int numVertex, int numPipes)
{
    int i, j;

    for(i = 0; i < numPipes; i++)
    {
        printf("%.3lf ", capacity[i]);
    }
    printf("\n\n");

    for(i = 0; i < numVertex; i++)
    {
        for(j = 0; j < numVertex; j++)
        {
            printf("%.3lf ",m[i][j]);
        }
        printf("\n");
    }
}

void matrixAlocation(double ***m, int numVertex)
{
    int i;

    (*m) = (double**) calloc(numVertex,sizeof(double*));
    for(i = 0; i < numVertex; i++)
        (*m)[i] = (double*) calloc(numVertex,sizeof(double*));
}

void inputReader(FILE *input, double ***m, double **capacity, int numVertex, int numPipes)
{
    int i, j;

    for(i = 0; i < numPipes; i++)
        fscanf(input, "%lf ", &((*capacity)[i]));

    for(i = 0; i < numVertex; i++)
        for(j = 0; j < numVertex; j++)
            fscanf(input, "%lf ", &((*m)[i][j]));
}

void matrixReader(char *location, double ***m, double **capacity, int *numVertex, int *numPipes)
{
    FILE *input;

    input = fopen(location, "r");

    fscanf(input, "%d %d ", numVertex, numPipes);

    matrixAlocation(m, *numVertex);

    *capacity = (double*) calloc(*numPipes,sizeof(double));

    inputReader(input, m, capacity, *numVertex, *numPipes);

    fclose(input);
}

int main(int argc, char *argv[])
{
    int numVertex, numPipes;
    double **m, *capacity;

    matrixReader(argv[1], &m, &capacity, &numVertex, &numPipes);

    matrixPrinter(m, capacity, numVertex, numPipes);

    graphTester(m, numVertex);

    return 0;
}
