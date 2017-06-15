#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

void matrixPrinter(double **m, int dimx, int dimy)
{
    int i, j;

    for(i = 0; i < dimx; i++)
    {
        for(j = 0; j < dimy; j++)
        {
            printf("%.6lf ", m[i][j]);
        }
        printf("\n");
    }
}

void matrixAlocation(double ***m, int dimx, int dimy)
{
    int i;

    (*m) = (double**) calloc(dimx,sizeof(double));
    for(i = 0; i < dimx; i++)
        (*m)[i] = (double*) calloc(dimy,sizeof(double));
}

void inputReader(FILE *input, double ***m, int dimx, int dimy)
{
    int i, j;

    for(i = 0; i < dimx; i++)
    {
        for(j = 0; j < dimy; j++)
        {
            fscanf(input, "%lf ", &((*m)[i][j]));
        }
    }
}

void matrixReader(char *location, double ***m, int *dimx, int *dimy)
{
    FILE *input;

    input = fopen(location, "r");

    fscanf(input, "%d %d ", dimx, dimy);

    (*dimx)++;

    matrixAlocation(m, *dimx, *dimy);

    inputReader(input, m, *dimx, *dimy);

    fclose(input);
}

int getRandomVertex(bool *covered, int uncoveredCounter, int numVertex)
{
    int i;

    srand(time(NULL));
    int random = rand() % uncoveredCounter;
    printf("\nRandom = %d\n", random);

    for(i = 0; i < numVertex; i++)
    {
        if(!(covered[i]))
        {
            if(random == 0)
                return i;
            else
                random--;
        }
    }
    return -1;
}

void setCover(double ***m, int dimx, int dimy)
{
    bool *covered;
    int numVertex = dimx-1, indexVertex, uncoveredCounter = numVertex;

    covered = (bool*) calloc(numVertex,sizeof(bool));

    while(uncoveredCounter > 0)
    {
        indexVertex = getRandomVertex(covered, uncoveredCounter, numVertex);
        printf("indexVertex = %d\n", indexVertex);
        covered[indexVertex] = true;
        uncoveredCounter--;
    }
}

int main(int argc, char *argv[])
{
    double **m;
    int dimx, dimy;

    matrixReader(argv[1], &m, &dimx, &dimy);

    matrixPrinter(m, dimx, dimy);

    setCover(&m, dimx, dimy);

    return 0;
}
