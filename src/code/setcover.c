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

void printResults(double *x, int *y, int numVertex, int dimy)
{
    int i;

    printf("\nX = (");
    for(i = 0; i < numVertex; i++)
    {
        printf("%.3lf", x[i]);
        if(i < numVertex-1)
            printf(" ");
        else
            printf(")");
    }

    printf("\nY = (");

    for(i = 0; i < dimy; i++)
    {
        printf("%d", y[i]);
        if(i < dimy-1)
            printf(" ");
        else
            printf(")");
    }
    printf("\n");
}

void printFinalWeight(int *y, double **m, int dimy)
{
    int i;
    double sum = 0;

    for(i = 0; i < dimy; i++)
    {
        if(y[i] == 1)
            sum += m[0][i];
    }

    printf("Cover Cost = %.3lf\n", sum);
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

int uncoveredCounter(bool *covered, int numVertex)
{
    int i;
    int uncoveredCounter = 0;

    printf("\nuncovered ");
    for(i = 0; i < numVertex; i++)
    {
        printf("%d ", covered[i]);
        if(!(covered[i]))
            uncoveredCounter++;
    }
    printf("\n");

    return uncoveredCounter;
}

int getRandomVertex(bool *covered, int numVertex)
{
    int i;
    int uncovered = uncoveredCounter(covered, numVertex);

    printf("uncovered = %d\n", uncovered);

    srand(time(NULL));
    int random = rand() % uncovered;
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

int getMajorCover(double **m, int dimx, int indexCover1, int indexCover2)
{
    int i;
    int count1 = 0, count2 = 0;

    for(i = 0; i < dimx; i++)
    {
        if(m[i][indexCover1] == 1)
            count1++;
    }

    for(i = 0; i < dimx; i++)
    {
        if(m[i][indexCover2] == 1)
            count2++;
    }

    return (count1 > count2 ? indexCover1 : indexCover2);
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

            else if(getMaxValueOfVertex(*x, m, dimx, indexVertex, j) == minVertexWeight)
            {
                indexCover = getMajorCover(m, dimx, indexCover, j);
            }
        }
    }

    (*x)[indexVertex] = minVertexWeight;
    (*y)[indexCover] = 1;

    for(j = 1; j < dimx; j++)
    {
        if(m[j][indexCover] == 1)
            (*covered)[j-1] = true;
    }
}

void setCover(double ***m, int dimx, int dimy)
{
    bool *covered;
    int numVertex = dimx-1, indexVertex;
    double *x;
    int *y;

    covered = (bool*) calloc(numVertex,sizeof(bool));
    x = (double*) calloc(numVertex,sizeof(double));
    y = (int*) calloc(dimy,sizeof(int));

    while(uncoveredCounter(covered, numVertex) > 0)
    {
        indexVertex = getRandomVertex(covered, numVertex);
        printf("indexVertex = %d\n", indexVertex);
        covered[indexVertex] = true;

        maximizeIndex(&covered, &x, &y, *m, dimx, dimy, indexVertex);

        printResults(x, y, numVertex, dimy);
    }

    printFinalWeight(y, *m, dimy);
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
