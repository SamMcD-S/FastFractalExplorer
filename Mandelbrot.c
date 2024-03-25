//
// Created by Sam McDiarmid-Sterling on 9/16/22.
//


#include "matrix.h"
#include "mex.h"
#include <stdlib.h>
#include <stdio.h>


#define DIMENSION(upper,lower,step) ((int)((upper-lower)/step))
#define LENGTH(di2,di1) (di1*di2)
#define ARG_CHECK

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
    if (nrhs != 5){
        mexErrMsgIdAndTxt( "MATLAB:Mandelbrot:Inputsize",
                           "This function accepts five doubles in the following format: LowerX bound, Upper X bound, Lower Y Bound, Upper Y bound, Step. \n Note it is strongly recommended that you use square ranges to maintain propper viewing qualities");
    }
#endif
    double lowerx, lowery, upperx, uppery, step;
    int * out, dimension, dimensionx , dimensiony, length;
   

    lowerx = *mxGetPr(prhs[0]);
    upperx = *mxGetPr(prhs[1]);
    lowery = *mxGetPr(prhs[2]);
    uppery = *mxGetPr(prhs[3]);
    step = *mxGetPr(prhs[4]);
    
    
    dimensionx = DIMENSION(upperx,lowerx,step);
    dimensiony = DIMENSION(uppery,lowery,step);

    
    length = LENGTH(dimensionx,dimensiony);

#ifdef VERBOSE
    mexPrintf("%lf:%lf:%lf in the x \n %lf:%lf:%lf in the y \n",lowerx,step,upperx,lowery,step,uppery);
#endif
    double * Real, * Imaginary;
    Real = (double*) malloc(length*sizeof(double));
    Imaginary = (double*) malloc(length*sizeof(double));
    if (Real == NULL){
        mexErrMsgIdAndTxt( "MATLAB:Mandelbrot:Allocation",
                           "The function failed to allocate neccesary memory for the Real Vairable");
    }
    if (Imaginary == NULL){
        mexErrMsgIdAndTxt( "MATLAB:Mandelbrot:Allocation",
                           "The function failed to allocate neccesary memory for the Imaginary Vairable");
    }
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
    Mandelbrot(outputMatrix,Real,Imaginary, length);
    
    

#ifdef VERBOSE
    mexPrintf("Madelbrot done,printing to file\n");
#endif

    return;

}

