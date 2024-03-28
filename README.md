# Fast Fractal Plotter
##  Sam McDiarmid-Sterling, CU Boulder
Welcome!

*The "Fast Fractal Explorer" is a interactive user interface, designed to enable a easy and playful investigation of the Mandelbrot Fractal and its associated Julia Sets*

The project allows the user a low-latency interractive experience by maintaining a constant resolution even when viewing the set from different perspectives.

### Quick Start:
Run the "make mexBuild" target to build for your architecture.
Run the "FractalExplorer.m" script. Note, by default, use color space Parula

When prompted, Select to initially plot either the Mandelbrot Set or  a Julia Set

If Julia:
    Enter Real and Complex value, or Enter for Default

Once the first plot appears,
* press **'z'**, select a lower left and upper right corner of a new square region
* press **'r'**, enter a new resolution. Note, the default is 400x400. The program hasn't been tested above 1500x1500
* press **'t'**, to go to the next stop on the tour of famous fractals
* press **'v'**, to switch between Mandelbrot and Julia Set, either revealing the location of the Julia set, or allowing selection of a new complex value in the Mandelbrot window
* press **'u'**, to undo the last view-changing command ('v', or 'z')
* press **'e'** to exit.
* press **'h'** for a short help message.



### Project Overview
The Fast Fractal Explorer allows dynamic exploration of these particular fractals by redrawing the requested selection at a constant resolution. This way, an end user can explore the fractal at depth without having to precompute the whole thing.

### File Overview
* FractalExplorer.m *Main Matlab Script for the Function*

* Interface.c *File called from Matlab using MEX Interface. Load input arguments into the Fractal 'class' and run the appropriate compute method.*


* Fractal.c, Fractal.h *Create a simple Fractal 'class'.
    Each element of the class has a 'compute method' (and an optional destructor), and may have a struct for its own attributes. This should be trivially expandable.*
* Mandelbrot.c, Julia.c: *Earlier prototype functions, no longer used*

* unitTest.c *compiles a separate executible to allow for debugging, described below*

Note: when a MEX program crashes (or halts), Matlab crashes too without recoverable information. To allow for debugging, I wrote unitTest.c  (and included #ifdef conditionals in previous versions) so there is a unitTest executible.

The Makefile has the following targets:
* mexBuild -- build for the Matlab Enviornment, standard
* unitTest -- build unitTest for standalone execution
* clean

### Performance Adjustments -- In order to change the default resolution (and program mode), the parameters in FastFractal.m may be modified in the following manner:

resolution = <n> -- by default, maintain an nxn size image
