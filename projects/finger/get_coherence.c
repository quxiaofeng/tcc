#include <math.h>

double get_coherence(int row, int col, double **gx, double **gy) {
    double Gxx = 0;
    double Gyy = 0;
    double Gxy = 0;
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            Gxx += pow(gx[i][j], 2);
            Gyy += pow(gy[i][j], 2);
            Gxy += gx[i][j]*gy[i][j];
        }
    }
    return sqrt(pow((Gxx-Gyy), 2) + 4 * pow(Gxy, 2))/(Gxx + Gyy);
}