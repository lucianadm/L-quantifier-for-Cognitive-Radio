% Reseteo Matlab
close all
clear
clc

% Variables iniciales
nombreArchivo = 'x.txt';

% Variables de los cuantis
e = 0.07; %Distancia euclideana para decir que dos números son lo suficientemente distintos

% cargo los datos
load(nombreArchivo)

% Calculo L
L = LmioModif(x,e);
