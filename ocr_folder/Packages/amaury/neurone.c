//
// Created by amaury.michel on 10/8/18.
//

#include <stdio.h>
#include <math.h>

#include "neurone.h"



NEURONE neurone;



float sigmoide(float x)
{
    return 1/(1+expf(-x));
}

void Init_Neurone()
{
    // neurone x avec ses liens
    neurone.x = 0;
    neurone.xz = 0;
    neurone.xh = 0;
    // neurone y avec ses lien
    neurone.y = 0;
    neurone.yz = 0;
    neurone.yh = 0;
    // neurone h avec ses liens
    neurone.h = 0.5;
    neurone.hz = 0;
    // biais bz avec ses liens
    neurone.bz =1;
    neurone.bzz = 0;
    // biais bh avec ses liens
    neurone.bh = 1;
    neurone.bhh = 0;
    // neurone z
    neurone.z = 0.5;
    // Error
    neurone.errorH = 0;
    neurone.errorZ = 0;
}


void calcOz()
{
    neurone.z = sigmoide(neurone.x*neurone.xz + neurone.bz*neurone.bzz + neurone.y*neurone.yz + neurone.h*neurone.hz);
}

void calcOh()
{
    neurone.h = sigmoide(neurone.x*neurone.xh + neurone.bh*neurone.bhh + neurone.y*neurone.yh);
}

void SignalErreurDeZ(float ValeurSouhaite)
{
    neurone.errorZ = (ValeurSouhaite - neurone.z)*neurone.z*(1-neurone.z);
}

void ChangePoidXZ(float pas)
{
    neurone.xz = neurone.xz + (pas*neurone.errorZ*neurone.x);
}

void ChangePoidYZ(float pas)
{
    neurone.yz = neurone.yz + (pas*neurone.errorZ*neurone.y);
}

void ChangePoidHZ(float pas)
{
    neurone.hz = neurone.hz + (pas*neurone.errorZ*neurone.h);
}

void ChangePoidBzZ(float pas)
{
    neurone.bzz = neurone.bzz + (pas*neurone.errorZ*neurone.bz);
}

void SignalErreurDeH(float ValeurSouhaite)
{
    neurone.errorH = neurone.h*(1-neurone.h)*neurone.errorZ*neurone.hz;
}

void ChangePoidXH(float pas)
{
    neurone.xh = neurone.xh + (pas*neurone.errorH*neurone.x);
}

void ChangePoidYH(float pas)
{
    neurone.yh = neurone.yh + (pas*neurone.errorH*neurone.y);
}

void ChangePoidBhH(float pas)
{
    neurone.bhh = neurone.bhh + (pas*neurone.errorH*neurone.bh);
}

NEURONE backprop(float x , float y, float expected, float pas)
{
    // Mettre un exemple à apprendre en entrée du réseau.
    neurone.x = x;
    neurone.y = y;
    // Calculer des valeurs d’activation des neurones cachés et de sortie
    calcOh();
    calcOz();

    // Calculer de l’erreur entre la valeur de l'exemple et celle du réseau
    SignalErreurDeZ(expected);

    //  Mettre à jour des poids des connexions allant sur l’unité de sortie
    ChangePoidXZ(pas);
    ChangePoidYZ(pas);
    ChangePoidHZ(pas);
    ChangePoidBzZ(pas);

    //  Calculer de l’erreur dans les unités de la couche cachée
    SignalErreurDeH(expected);

    //  Mettre à jour des poids des connexions allant sur la couche cachée
    ChangePoidXH(pas);
    ChangePoidYH(pas);
    ChangePoidBhH(pas);
    calcOh();
    calcOz();
}
NEURONE retNeurone()
{
    return neurone;
}

float res()
{
    return neurone.z;
}

void save()
{
    FILE* fichier = fopen("Resultats.txt","w+");
    float toWrite[1024];
    toWrite[0] = neurone.xz;
    toWrite[1] = neurone.xh;
    toWrite[2] = neurone.yz;
    toWrite[3] = neurone.yh;
    toWrite[4] = neurone.bhh;
    toWrite[5] = neurone.bzz;
    toWrite[6] = neurone.hz;
    fwrite(toWrite,1024, sizeof(float),fichier);
    fclose(fichier);

    printf("\nSave in Resultats\n");
}

void load()
{
    FILE* fichier = fopen("Resultats","r");
    float DATA[1024];
    fread(DATA,1024, sizeof(float),fichier);
    neurone.xz = DATA[0];
    neurone.xh = DATA[1];
    neurone.yz = DATA[2];
    neurone.yh = DATA[3];
    neurone.bhh = DATA[4];
    neurone.bzz = DATA[5];
    neurone.hz = DATA[6];
    fclose(fichier);
    printf("\nLoad of Resultats.txt\n");

}

int mainNeuroneXOR() {
    Init_Neurone();
    for (unsigned long i = 0; i < 20000; ++i)
    {
        backprop(0,0,0,2);
        backprop(1,1,0,2);
        backprop(1,0,1,2);
        backprop(0,1,1,2);
    }
    NEURONE neurone32 = retNeurone();
    printf("\n 0 Et 0 qui doit donner 0: \n");
    backprop(0,0,0,2);
    printf("\n res = %f",res());
    printf("\n Les poids des transitions: \n %f = Wxh\n %f = Wyh\n %f = Wbhh\n %f = Wxz\n %f = Wyz\n %f = Whz\n %f = Wbzz\n",neurone32.xh,neurone32.yh,neurone32.bhh,neurone32.xz,neurone32.yz,neurone32.hz,neurone32.bzz);


    printf("\n ================================================================================================================== \n ================================================================================================================== \n");

    printf("\n 1 Et 1 qui doit donner 0: \n");
    backprop(1,1,0,2);
    printf("\n res = %f\n",res());
    printf("\n Les poids des transitions: \n %f = Wxh\n %f = Wyh\n %f = Wbhh\n %f = Wxz\n %f = Wyz\n %f = Whz\n %f = Wbzz\n",neurone32.xh,neurone32.yh,neurone32.bhh,neurone32.xz,neurone32.yz,neurone32.hz,neurone32.bzz);


    printf("\n ================================================================================================================== \n ================================================================================================================== \n");

    printf("\n 1 Et 0 qui doit donner 1: \n");
    backprop(1,0,1,2);
    printf("\n res = %f\n",res());
    printf("\n Les poids des transitions: \n %f = Wxh\n %f = Wyh\n %f = Wbhh\n %f = Wxz\n %f = Wyz\n %f = Whz\n %f = Wbzz\n",neurone32.xh,neurone32.yh,neurone32.bhh,neurone32.xz,neurone32.yz,neurone32.hz,neurone32.bzz);


    printf("\n ================================================================================================================== \n ================================================================================================================== \n");

    printf("\n 0 Et 1 qui doit donner 1: \n");
    backprop(0,1,1,2);
    printf("\nres = %f\n",res());
    printf("\n Les poids des transitions: \n %f = Wxh\n %f = Wyh\n %f = Wbhh\n %f = Wxz\n %f = Wyz\n %f = Whz\n %f = Wbzz\n",neurone32.xh,neurone32.yh,neurone32.bhh,neurone32.xz,neurone32.yz,neurone32.hz,neurone32.bzz);



    save();
    load();
    return 0;
}
