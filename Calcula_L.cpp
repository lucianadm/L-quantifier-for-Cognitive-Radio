/*
/*% Programa para decodificar Turbo Código, con el algoritmo MAP / BCJR, con Interleaver más grande
% Autores Matlab: Damian Gustavo Levin Jorge Castiñeira   pasado a C por luciana :)
% Creado el: 5/10/2003
% Última actualización: 16/12/2003        pasado a C 16/06/2010
%--------------------------------------------------------------------------------------------
 */

#define INFINITY (1.0/0.0)
#pragma hdrstop
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
//#include <condefs.h>
//#include <fstream.h>    //para abrir y cerrar archivos
#include <time.h> // para el calculo del tiempo empleado
#include <math.h>
#include "conio.h"
//#include <iostream.h>
#include "nr.h"// la pide NUMRECN. Es NR.H modificada para long double
#include "nrutil.h"
#include "nrutil.c"
//#include "maxiutils.h"
#define NR_END 1        // la usan vector, freevector, matrix y freematrix
#define FREE_ARG char*  // puntero a una variable tipo char
#define log2(val) (log((val))/log(2.0))
//------------------------------------------------------------------------------
// DECLARACION DE ARCHIVOS DE DATOS/RESULTADOS
//------------------------------------------------------------------------------

 FILE *sali = fopen("x.txt","w");
 FILE *salu = fopen("L.txt","w");

//-------------------------Punteros a matrices y vectores----------------------
double *x;

double abso(double);
double L(double*,double);
float gasdev(long *);
float ran1(long *);

//----------------funciones-----------------------------------------------------
#include <math.h>
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

float ran1(long *idum) {
    int j;
    long k;
    static long iy=0;
    static long iv[NTAB];
    float temp;

    if (*idum <= 0 || !iy) {
        if (-(*idum) < 1) *idum=1;
        else *idum = -(*idum);
        for (j=NTAB+7;j>=0;j--) {
            k=(*idum)/IQ;
            *idum=IA*(*idum-k*IQ)-IR*k;
            if (*idum < 0) *idum += IM;
            if (j < NTAB) iv[j] = *idum;
        }
        iy=iv[0];
    }
    k=(*idum)/IQ;
    *idum=IA*(*idum-k*IQ)-IR*k;
    if (*idum < 0) *idum += IM;
    j=iy/NDIV;
    iy=iv[j];
    iv[j] = *idum;
    temp=(float)AM*iy;
    if (temp > RNMX) return (float)RNMX;
    else return temp;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX

float gasdev(long *idum)
{
    float ran1(long *idum);
    static int iset=0;
    static double gset;
    double fac,rsq,v1,v2;

    if (iset == 0) {
        do {
            v1=2.0*ran1(idum)-1.0;
            v2=2.0*ran1(idum)-1.0;
            rsq=v1*v1+v2*v2;
        } while (rsq >= 1.0 || rsq == 0.0);
        fac=sqrt(-2.0*log(rsq)/rsq);
        gset=v1*fac;
        iset=1;
        return (float)(v2*fac);
    } else {
        iset=0;
        return (float)gset;
    }
}

double abso(double x) {
double val=sqrt(x*x);
return val;
}


double L(double* x, double E, int N) {
int Ltotal=0;
int diagonales=0;
double Lsal;
double g1=0,g2=0,g3;


//printf("Ltotal=%d   diagonales=%d   \n\n ",Ltotal,diagonales);

for (int r=1;r<=N-2;r++){
x[0]=x[r]+E+0.5;  //condicion de contorno
    for(int i=1;i<=N-r-1;i++){


         Ltotal= Ltotal+((ceil(E-abso(x[i]-x[i+r]))*2-ceil(E-abso(x[i-1]-x[i-1+r])))*ceil(E-abso(x[i+1]-x[i+1+r]))*ceil(E-abso(x[i]-x[i+r])));
         diagonales= diagonales+((ceil(E-abso(x[i]-x[i+r]))-ceil(E-abso(x[i-1]-x[i-1+r])))*ceil(E-abso(x[i+1]-x[i+1+r]))*ceil(E-abso(x[i]-x[i+r])));

 //    getch();
    }
   }
printf("Ltotal=%d   diagonales=%d    \n",Ltotal,diagonales);
Lsal=(double)Ltotal/(double)diagonales;
return Lsal;
}


#include <math.h>


//------------------------------------------------------------------------------
//Empieza el programa
//------------------------------------------------------------------------------
int main(int argc, char **argv)
{
int N=100;
x=dvector(1,N+1); //datos a calcularle L
double E=0.3;

long utime;
utime=(long)time(NULL);					/*Unix time*/
long idum3=utime;
float ale2;

//for (int ii=1;ii<=10000;ii++){

for(int i=0;i<=N;i++){    //genera vector de datos aleatorios para calcularles el L
ale2=ran1(&idum3);
x[i]=(double)ale2;
//fprintf(sali,"%f  ",ale2);

}

/*x[1]=0.9;
x[2]=0.9;
x[3]=0.9;
x[4]=0.9;
x[5]=0.9;
x[6]=0.9;*/

//printf(" \n");
//getch();
//normalize_vector(double x_vec[], double Margins[2])  //normaliza x entre 0 y 1-E

double Lmead;

Lmead=L(x,E,N);
printf("Lmead=%f  ",Lmead);
//printf("Lmean=%f   ",Lmead);
 
/**Agregado por Maxi**/
    FILE* outx = fopen("x.txt","w");
    for (unsigned long int i_vec = 0; i_vec < N; i_vec++)
    {
        fprintf(outx,"%.10e\n",x[i_vec]);
    }
    fclose (outx);
    
    FILE* outL = fopen("Lmead.txt","w");
    fprintf(outL,"%.10e\n",Lmead);
    fclose (outL);
/*********************/
 
//}
free_dvector(x,1,N+1);
return 0;
}







