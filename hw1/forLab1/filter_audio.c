#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Load in stuff needed for Andriod NDK
#include <jni.h>
#include <android/log.h>

double *convolve(double* x, double* h, int x_size, int h_size);
void modulate(double* AM, int signal_len, double fs, double omega);
int read_file(const char* name, double* buffer, int start);

void filter();
/*

    You will need to change the name of these functions according
    to the standards specified in the following website:
    http://developer.android.com/ndk/samples/sample_hellojni.html

*/
void Java_lab1_AudioProcessActivity_filterNoise(JNIENV* env, jobject javaThis);

void Java_lab1_AudioProcessActivity_filterNoise(JNIENV* env, jobject javaThis){
    int h_len = 2435; 
    int x_len = 220500; 
    int fs = 44100; 
    int i;
    FILE *fp;

    double* noisy = calloc(x_len, sizeof(double));
    double* filter = calloc(h_len, sizeof(double));
    double* conv;

    //Read our sound and filter data
    /* 
        Also need to change the file_names here to match those
        being used on the tablet.
        e.g. /storage/emulated/0/Android/data/ .... 
    */
    read_file("noisy.dat", noisy, 0);
    read_file("filter.dat", filter, 0);

    // Part 1
    //Perform the filtering by convolution
    conv = convolve(noisy, filter, x_len, h_len);

    //Saving the filtered data in txt file
    fp =fopen("tmp_conv.txt","w+");
    for(i = 0; i< x_len; i++){
        fprintf(fp,"%f \n", conv[i]);
    }
    fclose(fp);

    free(filter);

    // Part 2
    //Modulate the filtered signal
    modulate(conv, x_len, fs, 10000);

    //Saving the modulated data in txt file
    fp =fopen("tmp_modulated.txt","w+");
    for(i = 0; i< x_len; i++){
        fprintf(fp,"%f \n", conv[i]);
    }

    fclose(fp);
    free(noisy);

    return 0;
}

double* convolve(double* x, double* h, int x_size, int h_size){
    double * conv = calloc(x_size + h_size - 1, sizeof(double));

    int i,j;
    for(i = 0; i < h_size + x_size - 1; i++){
        for(j = 0; j < x_size; j++){
            if(i - j >= 0 && i-j < h_size){
                conv[i] = x[j] * h[i - j];
            }
        }
    }
 
    return conv;

}

void modulate(double* AM, int signal_len, double fs, double omega){
    double tau = 6.283185; //2*pi
    int i;

    double A = 0.5;

    for(i = 0; i < signal_len; i++){
        double angle = tau*(double)(omega*i/fs);

        AM[i] = (A + AM[i]) * sin(angle);
    }
}

int read_file(const char* name, double* buffer, int start){
    int buf_size = 0;
    FILE* file;
    double d;

    file = fopen(name, "rb");
    if (file == NULL){
        perror("Error opening file");
    }
   
    int i = 0;
    while(!feof(file)){
        fread(&d, sizeof(double), 1, file);
        if (i < start) i++;
        else{
            buffer[buf_size] = d;
            buf_size += 1;
        }
    }   

    fclose(file);
    return buf_size;
}