#include <math.h>

double get_std(int row, int col, double **data, double mean){
    double sum = 0;
    double eps = 0.0001;
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            sum += pow((data[i][j] - mean), 2);
            //printf("The diff is %f. The sum is %f.\n", (data[i][j] - mean), sum);
        }
    }
    return sqrt(sum / (row*col + eps));
}