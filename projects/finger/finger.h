#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

double get_mean(int row, int col, double **data);
double get_std(int row, int col, double mean, double **data);
double get_contrast(double mean, double std);
double get_coherence(int row, int col, double **gx, double **gy);
void get_gradient(int row, int col, double **data, double **fx, double **fy);
double get_gm(int row, int col, double **gx, double **gy);
void get_cvag(int row, int col, double **data, double **gx, double **gy, double **cvag);

void get_block(double **image, double **block, int block_n_row, int block_n_col, int pos_x, int pos_y);
void read_csv(int row, int col, char *filename, double **data);
void save_csv(int row, int col, char *filename, double **data);
void print_csv(int row, int col, double **data);

void mlp(double *x, double *x3);