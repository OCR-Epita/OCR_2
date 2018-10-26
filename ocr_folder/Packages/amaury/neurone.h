//
// Created by amaury.michel on 10/9/18.
//

#ifndef XOR_NEURONE_H
#define XOR_NEURONE_H


typedef struct
{
    float x;
    float xz;
    float xh;

    float y;
    float yz;
    float yh;

    float bh;
    float bhh;

    float h;
    float hz;

    float bz;
    float bzz;

    float z;

    float errorZ;
    float errorH;

}NEURONE;

void Init_Neurone();

float sigmoide(float x);

void calcOz();

void calcOh();

void SignalErreurDeZ(float ValeurSouhaite);

void ChangePoidXZ(float pas);

void ChangePoidYZ(float pas);

void ChangePoidHZ(float pas);

void ChangePoidBzZ(float pas);

void SignalErreurDeH(float ValeurSouhaite);

void ChangePoidXH(float pas);

void ChangePoidYH(float pas);

void ChangePoidBhH(float pas);

NEURONE backprop(float x, float y, float expected,  float pas);

NEURONE retNeurone();

float res();

int mainNeuroneXOR();

#endif //XOR_NEURONE_H
