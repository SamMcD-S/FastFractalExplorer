#include "Fractal.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#undef MEX
#define DIMENSION(upper,lower,step) ((int)((upper-lower)/step))
#undef  ARG_CHECK
#define VERBOSE
//int configureFractal(Fractal * F,mxArray *plhs[], const mxArray *prhs[],int nlhs, int nrhs);
/// This function interfaces with the MATLAB User interface
/// \param nlhs The number of Left Hand Side (output) arguments
/// \param plhs A pointer to the Matlab Objects
/// \param nrhs The number of Right side Arguments
/// \param prhs Pointers to Inputs
int main(int argc, char **argv){
    //OUTPUTS integer array
    //INPUTS: Lower and upper bounds, step size
    Fractal myFrac; //declare our variable only if the proper arguments are given
    myFrac.identity = JULIA;
    char *fn;
    FILE *f;
    if(argc<2) {
        printf("enter a output file name as a command line argument\n") ;
        exit(0);
    }
    fn = argv[1];
    if(!fn) exit(0);
    f = fopen(fn,"w");



#ifdef VERBOSE
    printf("The Fractal identity is %d\n", myFrac.identity);
#endif

    //printf("Lowerx:%Lf\n Upperx:%Lf\n Lowery:%Lf\n Uppery:%Lf\nStep:%Lf\nComplex:%Lf\nReal:%Lf\n", *((float *) mxGetPr(prhs[1])),*((float *) mxGetPr(prhs[2])),*(float *) mxGetPr(prhs[3])),*((float *) mxGetPr(prhs[4])),*((float *) mxGetPr(prhs[7])),*((float *)mxGetPr(prhs[6])),*((float *) mxGetPr(prhs[5])));
    myFrac.identity = 2;
    myFrac.lowerx = -2;
    myFrac.upperx = 2;
    myFrac.lowery =-2;
    myFrac.uppery = 2;
    myFrac.step = 0.004;
    myFrac.Fra.juliAtt.real_initial = -0.79;
    myFrac.Fra.juliAtt.complex_inital = 0.15;


    myFrac.compute = &JuliaCompute; //set the function pointers we'll use lateer
    myFrac.fracFree = &JuliaFree;

#ifdef VERBOSE
    printf("Lowerx:%f\n Upperx:%f\n Lowery:%f\n Uppery:%f\nStep:%f\nComplex:%f\nReal:%f\n", myFrac.lowerx,myFrac.upperx,myFrac.lowery,myFrac.uppery,myFrac.step,myFrac.Fra.juliAtt.complex_inital,myFrac.Fra.juliAtt.real_initial);
#endif
    int * out, dimension, dimensionx , dimensiony;

    dimensionx = DIMENSION(myFrac.upperx,myFrac.lowerx,myFrac.step);
    dimensiony = DIMENSION(myFrac.uppery,myFrac.lowery,myFrac.step);

    if (dimensiony>dimensionx) myFrac.dimension = dimensiony;
    else myFrac.dimension = dimensionx; //Force the dimension to be the greater of the and y dimensions
    if ((myFrac.output = malloc(SQR(myFrac.dimension)*sizeof(int))) == NULL) exit(-1);
    //plhs[0]  = mxCreateNumericMatrix(1, SQR(myFrac.dimension), mxINT32_CLASS, mxREAL); //handel the output of the function
    //myFrac.output = (int *)mxGetData(plhs[0]);
    assert(!myFrac.compute(&myFrac));
    assert(!myFrac.fracFree(&myFrac));


#ifdef VERBOSE
    printf("Madelbrot done,printing to file\n");
#endif
    for(int i=0;i<(SQR(myFrac.dimension)-1);i++)fprintf(f,"%d,",(int) myFrac.output[i]);
    fprintf(f,"%d",(int) myFrac.output[SQR(myFrac.dimension)]); //no trailing comma behind last value
    fclose(f);
    return 0;

}

/*int configureFractal(Fractal * F,mxArray *plhs[], const mxArray *prhs[],int nlhs, int nrhs){

    return 0;
}*/
