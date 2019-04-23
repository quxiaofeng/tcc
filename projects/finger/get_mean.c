double get_mean(int row, int col, double **data) {
    double mean = 0;
    double sum = 0;
    double eps = 0.0001;
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<col; j++)
        {
            sum += data[i][j];
            //printf("data[%d][%d] is %f;\t Sum is %f.\n", i, j, data[i][j], sum);
        }
    }
    //printf("[sum,\trow,\tcol,\teps,\trow*col,\trow*col+eps,\tsum/(row*col+eps)]\n[%f,\t%d,\t%d,\t%f,\t%d,\t%f,\t%f]\n",
    //    sum, row, col, eps, row*col, row*col+eps, sum/(row*col+eps));
    //printf("sum/(row*col+eps) is %f\n", sum/(row*col+eps));
    return sum/(row*col+eps);
}