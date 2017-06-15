#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
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

double getMaxValueOfVertex(double *x, double **m, int dimx, int indexVertex, int indexCover)
{
    int j;
    double sum = 0;

    for(j = 0; j < dimx; j++)
    {
        if(m[indexVertex+1][j] == 1)
            sum += x[j];
    }

    return (m[0][indexCover] - sum);
}

void maximizeIndex(bool **covered, double **x, int **y, double **m, int dimx, int dimy, int indexVertex)
{
    int j;
    double minVertexWeight = INT_MAX;
    int indexCover;

    for(j = 0; j < dimy; j++)
    {
        if(m[indexVertex+1][j] == 1)
        {
            if(getMaxValueOfVertex(*x, m, dimx, indexVertex, j) < minVertexWeight)
            {
                minVertexWeight = m[0][j];
                indexCover = j;
                printf("minVertexWeight = %.3lf && indexCover = %d\n", minVertexWeight, indexCover);
            }

            // TODO else if(getMaxValueOfVertex(*x, m, dimx, indexVertex, j) == minVertexWeight) Pegar o cover com maior abrangencia
        }
    }


}

void setCover(double ***m, int dimx, int dimy)
{
    bool *covered;
    int numVertex = dimx-1, uncoveredCounter = numVertex, indexVertex;
    double *x;
    int *y;

    covered = (bool*) calloc(numVertex,sizeof(bool));
    x = (double*) calloc(numVertex,sizeof(double));
    y = (int*) calloc(dimy,sizeof(int));

    while(uncoveredCounter > 0)
    {
        indexVertex = getRandomVertex(covered, uncoveredCounter, numVertex);
        printf("indexVertex = %d\n", indexVertex);
        covered[indexVertex] = true;

        maximizeIndex(&covered, &x, &y, *m, dimx, dimy, indexVertex);

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
