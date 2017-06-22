#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

void matrixAlocation(double ***m, int dimx, int dimy)
{
    int i;

    (*m) = (double**) calloc(dimx,sizeof(double*));
    for(i = 0; i < dimx; i++)
        (*m)[i] = (double*) calloc(dimy,sizeof(double*));
}

void inputReader(FILE *input, double ***m, int dimx, int dimy)
{
    int i, j;

    for(i = 0; i < dimx; i++)
        for(j = 0; j < dimy; j++)
            fscanf(input, "%lf ", &((*m)[i][j]));
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

void printResults(FILE *output, double *x, int *y, int numVertex, int dimy)
{
    int i;

    fprintf(output, "X = (");
    for(i = 0; i < numVertex; i++)
    {
        fprintf(output, "%.3lf", x[i]);
        if(i < numVertex-1)
            fprintf(output, " ");
        else
            fprintf(output, ")");
    }

    fprintf(output, "\nY = (");

    for(i = 0; i < dimy; i++)
    {
        fprintf(output, "%d", y[i]);
        if(i < dimy-1)
            fprintf(output, " ");
        else
            fprintf(output, ")");
    }

    fprintf(output, "\n\n");
}

void printFinalWeight(FILE *output, int *y, double **m, int dimy)
{
    int i;
    double sum = 0;

    for(i = 0; i < dimy; i++)
    {
        if(y[i] == 1)
            sum += m[0][i];
    }

    fprintf(output, "Cover Cost = %.3lf\n", sum);
}

int uncoveredCounter(bool *covered, int numVertex)
{
    int i;
    int uncoveredCounter = 0;

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

    srand(time(NULL));
    int random = rand() % uncovered;

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
                minVertexWeight = getMaxValueOfVertex(*x, m, dimx, indexVertex, j);
                indexCover = j;
            }

            else if(getMaxValueOfVertex(*x, m, dimx, indexVertex, j) == minVertexWeight)
                indexCover = getMajorCover(m, dimx, indexCover, j);
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

void setCover(char *outputFilePath, double ***m, int dimx, int dimy)
{
    FILE *output;
    bool *covered;
    int numVertex = dimx-1, indexVertex;
    double *x;
    int *y;

    output = fopen(outputFilePath, "w");

    covered = (bool*) calloc(numVertex,sizeof(bool));
    x = (double*) calloc(numVertex,sizeof(double));
    y = (int*) calloc(dimy,sizeof(int));

    while(uncoveredCounter(covered, numVertex) > 0)
    {
        indexVertex = getRandomVertex(covered, numVertex);
        covered[indexVertex] = true;

        maximizeIndex(&covered, &x, &y, *m, dimx, dimy, indexVertex);

        printResults(output, x, y, numVertex, dimy);
    }

    printFinalWeight(output, y, *m, dimy);

    fclose(output);
}

int main(int argc, char *argv[])
{
    double **m;
    int dimx, dimy;

    matrixReader(argv[1], &m, &dimx, &dimy);

    setCover(argv[2], &m, dimx, dimy);

    return 0;
}
