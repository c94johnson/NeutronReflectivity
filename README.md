# NeutronReflectivity
Sean Ruane + Connah Johnson's Neutron Reflectivity modelling software, name TBD.


### Doesn't run as of 10/11/2016 ###

Neutron Reflectivity programme

Software to plot data from Neutron Reflecivity measurements of a sample
composed of up to three layers of protein adsorbed at an oil layer.

Written by Connah Johnson 8th November 2016

using the "gnuplot_i.hpp" Copyright (c) 2013 Daniel Stahlke (dan@stahlke.org)
requireing the BOOST library.

Gnuplot.exe must be located on file path:
"C:/Program Files/gnuplot/bin/"

Data, Model, Layer define the class objects used for the main file
NR08112016.cpp

Included files:
    -NR08112016.cpp
    -NRFunctions.cpp
    -NRFunctions.h
    -Data.cpp
    -Data.h
    -Model.cpp
    -Model.h
    -Layer.cpp
    -Layer.h



    Modelling Assumptions:
    -substrate and aqueous layer assumed
    -constant angle of incidence at each layer
    -assuming measurements are taken at one angle of incidence
    -non-complex refraction angle
    -classical wavelike description of neutron
    -thermal neutrons
    -homogenous sample layers
    -born approximation

    Plotting Assumptions:
    -windows 32
    -gnuplot.exe.located at "C:/Program Files/gnuplot/bin/"
    -comma separated file on entry with three data columns: X, Y, Error in Y
    -data in format of Q or wavelength, Reflecivity, and error in Reflecitivity
    -data file is located within the project directory

