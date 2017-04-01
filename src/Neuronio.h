/*
  Neuronio.h - Biblioteca para criação de Neuronio Artificial
  Created by Tiago Prata
*/
#ifndef Neuronio_h
#define Neuronio_h

#include "Arduino.h"


class neurone
{
  public:
    neurone();
	void begin(int Inputs);
	void begin(int Inputs, int _randomSeed);
	double derived();
    double * Input;
    double * Weight;
    double Delta;
    String Function;
    double Sum;
    double Output;
    void calc();
    int qtyInputs;
  //private:
}; 

class Layer
{
  public:
    Layer();
	void config(int neuroneQty);
	void config(int neuroneQty, String neuroneFunction);
	void begin(int neuroneQty, int InputPerNeurone);
	void begin(int neuroneQty, int InputPerNeurone, String neuroneFunction);
	neurone * Cell;
    int neuroneQty;
	String neuroneFunction;
  //private:
};

class MLP
{
  public:
	MLP();
	void build(int _InputQty, Layer * _Topology, int _Topology_arraySize);
	void Input(int* _InputArray, int _InputQty, int _ElementQty);
	double Input(int _Input, int _Element);
	double accuracy;
	double eta;
	Layer * Topology;
	int InputQty;
	double* InputArray;
  //private:
};

#endif