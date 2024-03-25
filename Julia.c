//
// Created by Sam McDiarmid-Sterling on 9/16/22.
//
#include <stdlib.h>
#include <stdio.h>


#define MEX
#define VERBOSE
#undef MAIN_APP
#define DEBUG
#define ARG_CHECK

#include "matrix.h"
#ifdef MEX
#include "mex.h"
#define PRINTF(x) (MexPrintF(x))
#else
#define PRINTF(x) (printf(x))
#endif


#define ABS(r,c) (cabs((double complex)(r + c*I)))
#define DIMENSION(upper,lower,step) ((int)((upper-lower)/step))
#define LENGTH(dim) (dim*dim)

#ifndef MAIN_APP
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    //OUTPUTS integer array
    //INPUTS: Lower and upper bounds, step size
#ifdef VERBOSE
    mexPrintf("starting the mex program\n");
#endif
#ifdef ARG_CHECK
    if (nlhs != 1){
        mexErrMsgIdAndTxt( "MATLAB:Mandelbrot:OutputSize",
                           "This function returns and int* (pointer to an array");
    }
    if (nrhs != 7){
        mexErrMsgIdAndTxt( "MATLAB:Mandelbrot:Inputsize",
                           "This function accepts five doubles in the following format: LowerX bound, Upper X bound, Lower Y Bound, Upper Y bound, Step. \n Note it is strongly recommended that you use square ranges to maintain propper viewing qualities");
    }
#endif
    double lowerx, lowery, upperx, uppery, step, JR, JC;
    int * out, dimension, dimensionx , dimensiony, length;
   

    lowerx = *mxGetPr(prhs[0]);
    upperx = *mxGetPr(prhs[1]);
    lowery = *mxGetPr(prhs[2]);
    uppery = *mxGetPr(prhs[3]);
    JR = *mxGetPr(prhs[4]);
    JC = *mxGetPr(prhs[5]);
    step = *mxGetPr(prhs[6]);
    
    
    dimensionx = DIMENSION(upperx,lowerx,step);
    dimensiony = DIMENSION(uppery,lowery,step);
    if (dimensiony>dimensionx){
        dimension = dimensiony;
    }
    else{
        dimension = dimensionx;
    }
    
    length = LENGTH(dimension);

#ifdef VERBOSE
    mexPrintf("%lf:%lf:%lf in the x \n %lf:%lf:%lf in the y \n",lowerx,step,upperx,lowery,step,uppery);
#endif
    double * Real, * Imaginary;
    Real = (double*) malloc(length*sizeof(double));
    Imaginary = (double*) malloc(length*sizeof(double));
    int i = 0;
#ifdef VERBOSE
    mexPrintf("Creating Range arrays \n");
#endif
    for(i=0;i<dimension;i++) {
        for(int count = 0; count < dimension; count++) {
            Real[(i*dimension) + count] = lowerx + (step*i);
            Imaginary[(i*dimension) + count] = lowery + (step*count);
            //printf("Currently setting index %d to %lf \n",((i*DIMENSION) + count),(LOWER + (STEP*i)));
        }
    }


#ifdef VERBOSE
    mexPrintf("Data loaded \n");
    mexPrintf("Beginning Mandelbrot\n");
#endif
    plhs[0]  = mxCreateNumericMatrix(1, length, mxINT32_CLASS, mxREAL); //handel the output of the function
    int* outputMatrix = (int *)mxGetData(plhs[0]);
    juliaMandelbrot(JR, JC,outputMatrix,Real,Imaginary, length);
    
    

#ifdef VERBOSE
    mexPrintf("Madelbrot done,printing to file\n");
#endif

    return;

}
/*
*
*
*
*
*
*
*
*
*/
//Evaluation method, used for when debugging
#else

int main(){
    //OUTPUTS integer array
    //INPUTS: Lower and upper bounds, step size
#ifdef VERBOSE
    PRINTF("starting the mex program\n");
#endif

    FILE *fp;
    fp = fopen("./jUnitTest.txt","w");

    double lowerx, lowery, upperx, uppery, step, JR, JC;
    int * out, dimension, dimensionx , dimensiony, length;


    lowerx = -2;
    upperx = 2;
    lowery = -2;
    uppery = 2;
    JR = -0.79;
    JC = 0.15;
    step = 0.004;


    dimensionx = DIMENSION(upperx,lowerx,step);
    dimensiony = DIMENSION(uppery,lowery,step);
    if (dimensiony>dimensionx){
        dimension = dimensiony;
    }
    else{
        dimension = dimensionx;
    }

    length = LENGTH(dimension);

#ifdef VERBOSE
    PRINTF("%lf:%lf:%lf in the x \n %lf:%lf:%lf in the y \n",lowerx,step,upperx,lowery,step,uppery);
#endif
    double * Real, * Imaginary;
    Real = (double*) malloc(length*sizeof(double));
    Imaginary = (double*) malloc(length*sizeof(double));
    int i = 0;
#ifdef VERBOSE
    PRINTF("Creating Range arrays \n");
#endif
    for(i=0;i<dimension;i++) {
        for(int count = 0; count < dimension; count++) {
            Real[(i*dimension) + count] = lowerx + (step*i);
            Imaginary[(i*dimension) + count] = lowery + (step*count);
            //printf("Currently setting index %d to %lf \n",((i*DIMENSION) + count),(LOWER + (STEP*i)));
        }
    }


#ifdef VERBOSE
    PRINTF("Data loaded \n");
    PRINTF("Beginning Mandelbrot\n");
#endif



#ifdef VERBOSE
    PRINTF("Madelbrot done,printing to file\n");
#endif
    int* outputMatrix  = malloc(length*sizeof(int)); //handel the output of the function
    juliaMandelbrot(JR, JC,outputMatrix,Real,Imaginary, length);
    for (int index=0;index<length;index++){
        fprintf(fp,"%d,",outputMatrix[index]);
    }
    fclose(fp);
#ifdef VERBOSE
    PRINTF("Execution done, terminating\n");
#endif
    return 0;

}
#endif
