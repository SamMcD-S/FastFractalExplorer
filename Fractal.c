#include "Fractal.h"


#ifdef MEX
#define PRINTF(x) (mexPrintf(x))
#else
#define PRINTF(x) (printf(x))
#endif

///Methods for the Mandelbrot Fractal

int MandelbrotCompute(struct _Fractal *F){
    long double  real               = 0; //Actually used in calculations
    long double  imaginary          = 0;
    long double working_real        = 0;
    long double working_imag        = 0;
    int max = 0;
    int progress = 0;



    progress = SQR(F->dimension)/25;//for the progress bar, figure out what percentage done we are


    for(int i = 0;i<SQR(F->dimension);i++){
        if(!(i%progress) && F->pb)PRINTF("-"); //progress bar

        F->output[i] = 0; //initialize the output array
        real = F->Fra.mandAtt.location_real = F->lowerx + (ROW_AT_INDEX(i,F->dimension)*F->step); //obtain the initial values
        imaginary = F->Fra.mandAtt.location_complex = F->lowery + (COL_AT_INDEX(i,F->dimension)*F->step);

        while((ABS(real,imaginary)<2.00) && (F->output[i]<DEPTH)){
            working_real = SQR(real)-SQR(imaginary) + F->Fra.mandAtt.location_real; //Square the Complex number R = A**2-B**2
            working_imag = 2*real*imaginary + F->Fra.mandAtt.location_complex; //Complex equals 2AB
            real = working_real;
            imaginary = working_imag;
            F->output[i]+=1; //increment the amount of cycles it took to escape
        }
#ifdef DEBUG
        if (F->output[i]>max) {
            printf("Index %d depth %d\n",i,F->output[i]);
            max = F->output[i];
        }
#endif

    }
    PRINTF("\n");
    return 0;
}
int MandelbrotFree(struct _Fractal *F){
    return 0;
}

///Methods for the Julia Set Plotter


/// Compute the Julia Set
/// \param F Fractal Struct, passed in
/// \return 0 on success
int JuliaCompute(struct _Fractal *F){
    long double  real               = 0; //Actually used in calculations
    long double  imaginary          = 0;
    long double working_real        = 0;
    long double working_imag        = 0;
    int max = 0;
    int progress = 0;


    //for the progress bar, figure out what percentage done we are
    progress = SQR(F->dimension)/25;


    for(int i = 0;i<SQR(F->dimension);i++){

        if(!(i%progress) && F->pb)PRINTF("-"); //progress bar
         F->output[i] = 0; //initialize the output array

        real = F->lowerx + (ROW_AT_INDEX(i,F->dimension)*F->step); //obtain the initial values
        imaginary = F->lowery + (COL_AT_INDEX(i,F->dimension)*F->step);

        while((ABS(real,imaginary)<2.00) && (F->output[i]<DEPTH)){
            working_real = SQR(real)-SQR(imaginary) + F->Fra.juliAtt.real_initial; //Square the Complex number R = A**2-B**2
            working_imag = 2*real*imaginary + F->Fra.juliAtt.complex_inital; //Complex equals 2AB
            real = working_real;
            imaginary = working_imag;
            F->output[i]+=1; //increment the amount of cycles it took to escape
        }
#ifdef DEBUG
      if (F->output[i]>max) {
            printf("Index %d depth %d\n",i,F->output[i]);
            max = F->output[i];
        }
#endif

    }
    PRINTF("\n");
    return 0;
}
/// Free the Fractal Struct
/// \param F Fractal Struct
/// \return 0 on success
int JuliaFree(struct _Fractal *F){
    return 0;
}