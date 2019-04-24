double _get_sign(double a, double b) {
    return (a>b)?1:0;
}

double get_clud(int row, int col, double **data, double img_mean, double thres_clud) {
    double clud = 0;
    double eps = 0.0001;
    for (int i=2; i<row-2; i++)
    {
        for (int j=2; j<col-2; j++)
        {
            double Dij = 0;
            for (int k=-2; k<3; k++) {
                for (int l=-2; l<3; l++) {
                    Dij += _get_sign(data[i][j], img_mean);
                }
            }
            //printf("D[%d][%d] = %f\n", i, j, Dij);
            clud += _get_sign(data[i][j], img_mean)*_get_sign(Dij, thres_clud);
        }
    }
    return clud;
}