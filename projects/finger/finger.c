//%cflags:-std=gnu99 -lm
// Read a CSV
#include "finger.h"

void get_block(
    double **image,
    double **block,
    int block_n_row,
    int block_n_col,
    int pos_x,
    int pos_y) {
    // printf("From %d to %d.\n",
    //     pos_y*block_n_row, pos_y*block_n_row+block_n_row-1);
    // printf("From %d to %d.\n",
    //     pos_x*block_n_col, pos_x*block_n_col+block_n_col-1);
    for (int i = 0; i < block_n_row; ++i)
    {
        for (int j = 0; j < block_n_col; ++j)
        {
            block[i][j] 
            = image[pos_y*block_n_row + i][pos_x*block_n_col + j];
            //printf("block[%d][%d] = image[%d][%d]\n", 
            //    i, j, pos_y*block_n_row + i, pos_x*block_n_col + j);
        }
    }
    // printf("block copied.\n");
}

/**
 * Function to check whether a file exists or not.
 * It returns 1 if file exists at given path otherwise
 * returns 0.
 */
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fptr = fopen(path, "r");

    // If file does not exists 
    if (fptr == NULL)
        return 0;

    // File exists hence close file and return true.
    fclose(fptr);

    return 1;
}


int main(int argc, char const *argv[])
{
    char fname[256]; strcpy(fname, "0.csv");
    if (argc == 2)
    {
       strcpy(fname, argv[1]);
    }
    if( isFileExists(fname) == 0 ) {
        printf("File (%s) does not exists.\n", fname);
        return 1;
    }
    int row     = 192;
    int col     = 192;

    int block_n_row = 16;
    int block_n_col = 16;
    int n_feature = 12;
    char feature_fname[256];
    strcpy(feature_fname, "feature.csv");
    int n_categories = 3;
    char categories_fname[256];
    strcpy(categories_fname, "categories.csv");



    double **image;
    image = malloc(row * sizeof(double *));
    for (int i = 0; i < row; ++i)
        image[i] = malloc(col * sizeof(double));

    read_csv(row, col, fname, image);

    // Global feature
    //printf("## Global Feature\n");
    double g_mean = get_mean(row, col, image);
    printf("G_MEAM is %f.\n", g_mean);
    
    double g_std = get_std(row, col, g_mean, image);
    printf("G_STD is %f.\n", g_std);

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
    get_gradient(row, col, image, gx, gy);

    double g_gx_mean = get_mean(row, col, gx);
    printf("G_GX_MEAM is %f.\n", g_gx_mean);
    double g_gy_mean = get_mean(row, col, gy);
    printf("G_GY_MEAM is %f.\n", g_gy_mean);
    double g_gx_std  = get_std(row, col, g_gx_mean, gx);
    printf("G_GX_STD  is %f.\n", g_gx_std);
    double g_gy_std  = get_std(row, col, g_gy_mean, gy);
    printf("G_GY_STD  is %f.\n", g_gy_std);

    // double g_contrast = get_contrast(g_mean, g_std);
    // printf("4. The global contrast is %f.\n", g_contrast);

    // Block-wise feature
    // printf("## Block-wise Feature\n");
    int block_cnt_y = floor(row/block_n_row);
    int block_cnt_x = floor(col/block_n_col);
    //printf("block shape is (%d, %d)\n", block_cnt_x, block_cnt_y);

    double **block_feature;
    block_feature = malloc(
        block_cnt_y*block_cnt_x * sizeof(double *));
    for (int i = 0; i < block_cnt_y*block_cnt_x; ++i)
        block_feature[i] = malloc(
            n_feature * sizeof(double));

    double **block_categories;
    block_categories = malloc(
        block_cnt_y*block_cnt_x * sizeof(double *));
    for (int i = 0; i < block_cnt_y*block_cnt_x; ++i)
        block_categories[i] = malloc(
            n_categories * sizeof(double));

    double **current_block;
    current_block = malloc(block_n_row * sizeof(double *));
    for (int i = 0; i < block_n_row; ++i)
        current_block[i] = malloc(block_n_col * sizeof(double));

    double **block_gx;
    block_gx = malloc(block_n_row * sizeof(double *));
    for (int i = 0; i < block_n_row; ++i)
        block_gx[i] = 
            malloc(block_n_col * sizeof(double));

    double **block_gy;
    block_gy = malloc(block_n_row * sizeof(double *));
    for (int i = 0; i < block_n_row; ++i)
        block_gy[i] = 
            malloc(block_n_col * sizeof(double));

    for (int i = 0; i < block_cnt_y; ++i)
    {
        for (int j = 0; j < block_cnt_x; ++j)
        {
            get_block(image, current_block,
                block_n_row, block_n_col, j, i);
            //char fname[256];
            //sprintf(fname, "eval-block-%d-%d.csv", i, j);
            //save_csv(block_n_row, block_n_col, fname, current_block);
            double block_mean = get_mean(
                block_n_row, block_n_col, current_block);
            //printf("B_MEAN is %f.\n", block_mean);
            double block_std = get_std(
                block_n_row, block_n_col,
                block_mean, current_block);
            //printf("B_STD is %f.\n", block_std);
            get_block(gx, block_gx,
                block_n_row, block_n_col, j, i);
            get_block(gy, block_gy,
                block_n_row, block_n_col, j, i);
            double block_gx_mean = get_mean(
                block_n_row, block_n_col, block_gx);
            //printf("B_GX_MEAM is %f.\n", block_gx_mean);
            double block_gy_mean = get_mean(
                block_n_row, block_n_col, block_gy);
            //printf("B_GY_MEAM is %f.\n", block_gy_mean);
            double block_gx_std  = get_std(
                block_n_row, block_n_col,
                block_gx_mean, block_gx);
            //printf("B_GX_STD  is %f.\n", block_gx_std);
            double block_gy_std  = get_std(
                block_n_row, block_n_col,
                block_gy_mean, block_gy);
            //printf("B_GY_STD  is %f.\n", block_gy_std);
            block_feature[i * block_cnt_x + j][0] = g_mean;
            block_feature[i * block_cnt_x + j][1] = block_mean;
            block_feature[i * block_cnt_x + j][2] = g_std;
            block_feature[i * block_cnt_x + j][3] = block_std;
            block_feature[i * block_cnt_x + j][4] = g_gx_mean;
            block_feature[i * block_cnt_x + j][5] = g_gy_mean;
            block_feature[i * block_cnt_x + j][6] = g_gx_std;
            block_feature[i * block_cnt_x + j][7] = g_gy_std;
            block_feature[i * block_cnt_x + j][8] = block_gx_mean;
            block_feature[i * block_cnt_x + j][9] = block_gy_mean;
            block_feature[i * block_cnt_x + j][10] = block_gx_std;
            block_feature[i * block_cnt_x + j][11] = block_gy_std;
            mlp(block_feature[i * block_cnt_x + j], block_categories[i * block_cnt_x + j]);
            //printf("The categories of block(%d, %d) is [%f, %f, %f].\n",
            //    j, i, categories[0], categories[1], categories[2]);
        }
    }
    save_csv(block_cnt_y*block_cnt_x, n_feature, feature_fname,
        block_feature);
    save_csv(block_cnt_y*block_cnt_x, n_categories, categories_fname,
        block_categories);
    print_csv(block_cnt_y*block_cnt_x, n_categories, block_categories);


    // Global block-wise feature
   
    // double **gx;
    // gx = malloc(row * sizeof(double *));
    // for (int i = 0; i < row; ++i){
    //     gx[i] = malloc(col * sizeof(double));
    // }
    // double **gy;
    // gy = malloc(row * sizeof(double *));
    // for (int i = 0; i < row; ++i){
    //     gy[i] = malloc(col * sizeof(double));
    // }
    // get_gradient(row, col, image, gx, gy);
    // printf("The Gx and Gx is computed.\n");
    
    // printf("3. The coherence is %f.\n", get_coherence(row, col, gx, gy));
    
    // double **cvag;
    // cvag = malloc(row * sizeof(double *));
    // for (int i = 0; i < row; ++i){
    //     cvag[i] = malloc(col * sizeof(double));
    // }
    // get_cvag(row, col, image, gx, gy, cvag);
    // save_csv(row, col, "cvag.csv", cvag);
    // printf("5. The Combination of Variance and Its Gradient is saved.\n");
    
    // printf("6. The Gradient Magnitude is %f.\n", get_gm(row, col, gx, gy));
    
    // double thres_clud = 15;
    // printf("7. The Block Clusters Degree is %f.\n", get_clud(row, col, image, g_mean, thres_clud));

    return 0;
}