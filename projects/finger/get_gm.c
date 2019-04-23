#include <math.h>

double get_gm(int row, int col, double **gx, double **gy) {
    double gm = 0;
    double eps = 0.0001;
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            gm += sqrt(pow(gx[i][j],2) + pow(gy[i][j],2));
        }
    }
    return gm/(row*col+eps);
}