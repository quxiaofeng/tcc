//%cflags:-std=gnu99 -lm
// Read a CSV
#include "finger.h"

int main(int argc, char const *argv[])
{
    int row     = 3;
    int col     = 3;
    char fname[256];    strcpy(fname, "test3x3.csv");

    double **data;
    data = malloc(row * sizeof(double *));
    for (int i = 0; i < row; ++i){
        data[i] = malloc(col * sizeof(double));
    }

    read_csv(row, col, fname, data);

    double mean = get_mean(row, col, data);
    printf("1. The mean is %f.\n", mean);
    
    double std = get_std(row, col, data, mean);
    printf("2. The std is %f.\n", std);
    
    printf("4. The contrast is %f.\n", get_contrast(mean, std));
    
    double **gx;
    gx = malloc(row * sizeof(double *));
    for (int i = 0; i < row; ++i){
        gx[i] = malloc(col * sizeof(double));
    }
    double **gy;
    gy = malloc(row * sizeof(double *));
    for (int i = 0; i < row; ++i){
        gy[i] = malloc(col * sizeof(double));
    }
    get_gradient(row, col, data, gx, gy);
    save_csv(row, col, "Gx.csv", gx);
    save_csv(row, col, "Gy.csv", gy);
    printf("The Gx and Gx is saved.\n");
    
    printf("3. The coherence is %f.\n", get_coherence(row, col, gx, gy));
    
    double **cvag;
    cvag = malloc(row * sizeof(double *));
    for (int i = 0; i < row; ++i){
        cvag[i] = malloc(col * sizeof(double));
    }
    get_cvag(row, col, data, gx, gy, cvag);
    save_csv(row, col, "cvag.csv", cvag);
    printf("5. The Combination of Variance and Its Gradient is saved.\n");
    
    printf("6. The Gradient Magnitude is %f.\n", get_gm(row, col, gx, gy));
    
    double img_mean = 4;
    double thres_clud = 15;
    printf("7. The Block Clusters Degree is %f.\n", get_clud(row, col, data, img_mean, thres_clud));

    return 0;
}