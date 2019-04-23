#include <math.h>

void get_cvag(int row, int col, double **data, double **gx, double **gy, double **cvag) {
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            cvag[i][j] = sqrt(pow(gx[i][j],2) + pow(gy[i][j],2)) * data[i][j];
        }
    }
}