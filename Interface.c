//
// Created by Sam McDiarmid-Sterling on 5/1/23.
//
#include "Fractal.h"
#include "mex.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define PROGRESS_BAR 1
#define MEX
#define DIMENSION(upper,lower,step) ((int)((upper-lower)/step))
#define ARG_CHECK
#undef VERBOSE
//int configureFractal(Fractal * F,mxArray *plhs[], const mxArray *prhs[],int nlhs, int nrhs);
/// This function interfaces with the MATLAB User interface
/// \param nlhs The number of Left Hand Side (output) arguments
/// \param plhs A pointer to the Matlab Objects
/// \param nrhs The number of Right side Arguments
/// \param prhs Pointers to Inputs
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]){
    //OUTPUTS integer array
    //INPUTS: Lower and upper bounds, step size


#ifdef VERBOSE
    mexPrintf("starting the mex program\n");
#endif
#ifdef ARG_CHECK
    if (nlhs != 1){
        mexErrMsgIdAndTxt( "MATLAB:Fractal:OutputSize",
                           "This function returns an int* (pointer to an array)");
    }

    if (nrhs == 0){
        mexErrMsgIdAndTxt( "MATLAB:Fractal:InputSie",
                           "You must Pass at least one argument, to identify the fractal");
    }

#endif
    Fractal myFrac; //declare our variable only if the propper arguments are given
    myFrac.identity = *(mxGetPr(prhs[0]));
#ifdef VERBOSE
    mexPrintf("The Fractal identity is %d\n", myFrac.identity);
#endif
    switch (myFrac.identity){
        case MANDELBROT:
            if (nrhs < 6) {
                mexErrMsgIdAndTxt( "MATLAB:Mandelbrot:Inputsize",
                                   "This function accepts Six(6) inputs in the following format: 1,LowerX bound, Upper X bound, Lower Y Bound, Upper Y bound, Step. \n Use Square views");
            }

            myFrac.lowerx = *(mxGetPr(prhs[1]));
            myFrac.upperx = *(mxGetPr(prhs[2]));
            myFrac.lowery = *(mxGetPr(prhs[3]));
            myFrac.uppery =*(mxGetPr(prhs[4]));
            myFrac.step = *(mxGetPr(prhs[5]));
            myFrac.compute = &MandelbrotCompute; //set the function pointers we'll use lateer
            myFrac.fracFree = &MandelbrotFree;
            myFrac.pb = PROGRESS_BAR;
            break;
        case JULIA:
            if (nrhs < 8) {
                mexErrMsgIdAndTxt( "MATLAB:Julia:Inputsize",
                                   "This function accepts Eight(8) inputs in the following format: 2,LowerX bound, Upper X bound, Lower Y Bound, Upper Y bound, Step,Real Component, Complex Component. \n Use Square views");
            }
#ifdef VERBOSE
            mexPrintf("Julia...\n Loading Fractal Object \n");
#endif
            myFrac.lowerx = (double) *(mxGetPr(prhs[1]));
            myFrac.upperx = (double) *(mxGetPr(prhs[2]));
            myFrac.lowery = (double) *(mxGetPr(prhs[3]));
            myFrac.uppery =(double) *(mxGetPr(prhs[4]));
            myFrac.step = (double) *(mxGetPr(prhs[5]));
            myFrac.Fra.juliAtt.real_initial = (double) *(mxGetPr(prhs[6]));
            myFrac.Fra.juliAtt.complex_inital = (double) *(mxGetPr(prhs[7]));
            myFrac.compute = &JuliaCompute; //set the function pointers we'll use lateer
            myFrac.fracFree = &JuliaFree;
            myFrac.pb = PROGRESS_BAR;
            break;
    }

   /* mexPrintf("MEXLowerx:%lf\n MEXUpperx:%lf\n ",*mxGetPr(prhs[1]), *mxGetPr(prhs[2]));
    mexPrintf("MEXLowery:%lf\n MEXUppery:%lf\n ",*mxGetPr(prhs[3]), *mxGetPr(prhs[4]));
    mexPrintf("MEXStep:%lf\n MEXSR:%lf \n MEXSC:%lf\n ",*mxGetPr(prhs[5]), *mxGetPr(prhs[6]), *mxGetPr(prhs[7]));*/
    /*
    myFrac.identity = 2;
    myFrac.lowerx = -2;
    myFrac.upperx = 2;
    myFrac.lowery =-2;
    myFrac.uppery = 2;
    myFrac.step = 0.004;
    myFrac.Fra.juliAtt.real_initial = -0.79;
    myFrac.Fra.juliAtt.complex_inital = 0.15;
    //myFrac.Fra.juliAtt.real_initial = 0;
    //myFrac.Fra.juliAtt.complex_inital = 0;
    myFrac.compute = &JuliaCompute; //set the function pointers we'll use lateer
    myFrac.fracFree = &JuliaFree;
*/
#ifdef VERBOSE
    mexPrintf("Lowerx:%lf\n Upperx:%lf\n Lowery:%lf\n Uppery:%lf\nStep:%lf\nComplex:%lf\nReal:%lf\n", myFrac.lowerx,myFrac.upperx,myFrac.lowery,myFrac.uppery,myFrac.step,myFrac.Fra.juliAtt.complex_inital,myFrac.Fra.juliAtt.real_initial);
#endif
    int * out, dimension, dimensionx , dimensiony;

    dimensionx = DIMENSION(myFrac.upperx,myFrac.lowerx,myFrac.step);
    dimensiony = DIMENSION(myFrac.uppery,myFrac.lowery,myFrac.step);

    if (dimensiony>dimensionx) myFrac.dimension = dimensiony;
    else myFrac.dimension = dimensionx; //Force the dimension to be the greater of the and y dimensions

    plhs[0]  = mxCreateNumericMatrix(1, SQR(myFrac.dimension), mxINT32_CLASS, mxREAL); //handel the output of the function
    myFrac.output = (int *)mxGetData(plhs[0]);
    assert(!myFrac.compute(&myFrac));
    assert(!myFrac.fracFree(&myFrac));


#ifdef VERBOSE
    mexPrintf("Computation Done\n");
#endif

    return;

}

/*int configureFractal(Fractal * F,mxArray *plhs[], const mxArray *prhs[],int nlhs, int nrhs){

    return 0;
}*/
