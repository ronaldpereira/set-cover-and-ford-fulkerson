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
            printf("%.3lf ", m[i][i]);
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

double **matrixReader(char *location, int *dimx, int *dimy)
{
    FILE *input;
    double **m;

    input = fopen(location, "r");

    fscanf(input, "%d %d ", dimx, dimy);

    matrixAlocation(&m, *dimx, *dimy);

    fclose(input);

    return m;
}

int main(int argc, char *argv[])
{
    double **n;
    int dimx, dimy;

    n = matrixReader(argv[1], &dimx, &dimy);

    matrixPrinter(n, dimx, dimy);

    return 0;
}
