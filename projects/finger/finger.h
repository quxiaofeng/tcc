#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

double get_mean(int row, int col, double **data);
double get_std(int row, int col, double **data, double mean);
double get_contrast(double mean, double std);
double get_coherence(int row, int col, double **gx, double **gy);
void get_gradient(int row, int col, double **data, double **fx, double **fy);
double get_gm(int row, int col, double **gx, double **gy);
void get_cvag(int row, int col, double **data, double **gx, double **gy, double **cvag);


void read_csv(int row, int col, char *filename, double **data);
void save_csv(int row, int col, char *filename, double **data);