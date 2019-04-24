#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_csv(int row, int col, char *filename, double **data){
    FILE *file;
    file = fopen(filename, "r");
    //printf("Filename %s\n", filename);

    int i = 0;
    char line[40000];
    while (fgets(line, 40000, file) && (i < row))
    {
        char* tmp = strdup(line);
        //printf("line %d: %s\n", i, tmp);

        int j = 0;
        const char* tok;
        for (tok = strtok(line, ","); tok && *tok && j < col; j++, tok = strtok(NULL, ",\n"))
        {
            //printf("The number is %s\t", tok);
            data[i][j] = atof(tok);
            //printf("data(%d, %d): %f\t", i, j, data[i][j]);
            //printf("%f\t", data[i][j]);
        }
        //printf("\n");

        free(tmp);
        i++;
    }
    fclose(file);
}

void save_csv(int row, int col, char *filename, double **data){
    //printf("Save_csv: row %d, col %d, filename %s.\n", row, col, filename);
    FILE *file;
    file = fopen(filename, "w");    
    if (file == NULL) 
    { 
        printf("Could not open file"); 
        return; 
    } 
  
    for (int i=0; i<row; i++) 
    {
        for (int j=0; j<col; j++)
        {
            fprintf(file,"%f,", data[i][j]); 
        }
        fprintf(file,"\n");        
    } 
    fclose(file); 
}

void print_csv(int row, int col, double **data){
    //printf("Save_csv: row %d, col %d, filename %s.\n", row, col, filename);
    printf("\n");
    for (int i=0; i<row; i++) 
    {
        for (int j=0; j<col; j++)
        {
            printf("%f,", data[i][j]); 
        }
        printf("\n");        
    }  
}