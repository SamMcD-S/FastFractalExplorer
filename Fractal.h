#ifndef FRACTAL_H
#define FRACTAL_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
/*Define the basic characteristics of the Fractal project
A fractal can have it's own attribute structure.
Each fractal must have the following functions:
 int compute(Fractal *);
 int end(Fractal *);
 */

#define ROW_AT_INDEX(x,n) ((int) x/n)
#define COL_AT_INDEX(x,n) (x%n)
#define ABS(r,c) (cabs((double complex)(r + c*I)))
#define SQR(x)  (x*x)

#undef DEBUG

#define DEPTH 25 //the number of iterations we wait to see if a point will escape
#define MANDELBROT 1
#define JULIA 2
///Attributes of the Mandelbrot Fractal
struct _mandelbrotAttributes{
    double location_real;
    double location_complex;
};

///Attributes of the Julia Set
struct _juliaAttributes{
     double complex_inital;
     double real_initial;
};
union _generalFractalAtt{
    struct _mandelbrotAttributes mandAtt;
    struct _juliaAttributes juliAtt;
};
struct _Fractal{
    uint8_t pb;
    int identity;
    int dimension;
    int *output;
     double upperx;
     double lowerx;
     double uppery;
     double lowery;
     double step;
    int resolution;
    union _generalFractalAtt Fra;

    int (*compute)(struct _Fractal * F);
    int (*fracFree)(struct _Fractal *F);

};
typedef  struct _Fractal Fractal;
///Methods for the Mandelbrot Fractal

int MandelbrotCompute(struct _Fractal *F);
int MandelbrotFree(struct _Fractal *F);

///Methods for the Julia Set Plotter

int JuliaCompute(struct _Fractal *F);
int JuliaFree(struct _Fractal *F);
///Methods for the Mandelbrot Fractal

#endif