#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

    for(j = 0; j < dimy; j++)
        fscanf(input, "%lf ", &((*m)[0][j]));

    for(i = 1; i < dimx; i++)
    {
        for(j = 0; j < dimy; j++)
        {
            fscanf(input, "%lf ", &((*m)[i][j]));
        }
    }
}

double **matrixReader(char *location, int *dimx, int *dimy)
{
    FILE *input;
    double **m;

    input = fopen(location, "r");

    fscanf(input, "%d %d ", dimx, dimy);

    (*dimx)++;

    matrixAlocation(&m, *dimx, *dimy);

    inputReader(input, &m, *dimx, *dimy);

    fclose(input);

    return m;
}

int main(int argc, char *argv[])
{
    double **m;
    int dimx, dimy;

    m = matrixReader(argv[1], &dimx, &dimy);

    matrixPrinter(m, dimx, dimy);

    return 0;
}
