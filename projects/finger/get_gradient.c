void get_gradient(int row, int col, double **data, double **fx, double **fy) {
    // x is j increasing direction
    // y is i increasing direction
    for (int i=0; i<row; i++)
    {
        fx[i][0] = data[i][1] - data[i][0];
        fx[i][col-1] = data[i][col-1] - data[i][col-2];
        for (int j=1; j<col-1; j++)
        {
            fx[i][j] = (data[i][j+1] - data[i][j-1])/2.0;
        }
    }
    for (int j=0; j<col; j++)
    {
        fy[0][j] = data[1][j] - data[0][j];
        fy[row-1][j] = data[row-1][j] - data[row-2][j];
        for (int i=1; i<row-1; i++)
        {
            fy[i][j] = (data[i+1][j] - data[i-1][j])/2.0;
        }
    }
}