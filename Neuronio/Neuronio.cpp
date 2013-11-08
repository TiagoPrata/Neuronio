/*
  Neuronio.cpp - Biblioteca para criação de Neuronio Artificial
  Created by Tiago Prata
*/

#include "Arduino.h"
#include "Neuronio.h"

neurone::neurone()
{
  
}

void neurone::begin(int Inputs)
{
  float _rand;
  const int _randRange = 1000000;
  
  Input = new double [Inputs + 1];
  Weight = new double [Inputs + 1];
  Input[0] = -1;
  Function = "sigmoid";
  qtyInputs = Inputs;
  
  randomSeed(analogRead(0));

  for (int j = 0; j <= qtyInputs; j++) {
    _rand = random(_randRange)/(float)_randRange;
    Weight[j] = _rand;
  }
}

void neurone::begin(int Inputs, int _randomSeed)
{
  float _rand;
  const int _randRange = 1000000;
  
  Input = new double [Inputs + 1];
  Weight = new double [Inputs + 1];
  Input[0] = -1;
  Function = "sigmoid";
  qtyInputs = Inputs;
  
  randomSeed(_randomSeed);

  for (int j = 0; j <= qtyInputs; j++) {
    _rand = random(_randRange)/(float)_randRange;
    Weight[j] = _rand;
  }
}

void neurone::calc()
{
	double euler = 2.71828182846;
	Sum = 0;
	for (int i = 0; i <= qtyInputs; i++) {
		Sum = Sum + Input[i]*Weight[i];
	}
	if (Function == "sigmoid") {
		Output = 1.0/(1+pow(euler, -Sum));
	} else if (Function == "tanh") {
		Output = ((pow(euler, Sum))-(pow(euler, -Sum)))/((pow(euler, Sum))+(pow(euler, -Sum)));
	} else if (Function == "linear") {
		Output = Sum;
	}
}

double neurone::derived()
{
	double euler = 2.71828182846;
	
	if (Function == "sigmoid") {
		return 1.0/((pow(euler, Sum))*(pow((1.0/(pow(euler, Sum))), 2.0)));
	} else if (Function == "tanh") {
		return 1.0 - pow(((pow(euler, Sum))-(pow(euler, -Sum)))/((pow(euler, Sum))+(pow(euler, -Sum))), 2.0);
	} else if (Function == "linear") {
		return 1;
	}
}

Layer::Layer()
{

}

void Layer::config(int _neuroneQty)
{
  Cell = new neurone [_neuroneQty];
  neuroneQty = _neuroneQty;
}

void Layer::config(int _neuroneQty, String _neuroneFunction)
{
  Cell = new neurone [_neuroneQty];
  neuroneQty = _neuroneQty;
  neuroneFunction = _neuroneFunction;
}

void Layer::begin(int _neuroneQty, int InputPerNeurone)
{
  Cell = new neurone [_neuroneQty];
  neuroneQty = _neuroneQty;
  for (int i = 0; i < _neuroneQty; i++) {
    Cell[i].begin(InputPerNeurone);
  }
}

void Layer::begin(int _neuroneQty, int InputPerNeurone, String _neuroneFunction)
{
  Cell = new neurone [_neuroneQty];
  neuroneQty = _neuroneQty;
  for (int i = 0; i < _neuroneQty; i++) {
    Cell[i].begin(InputPerNeurone);
	Cell[i].Function = _neuroneFunction;
  }
}

MLP::MLP()
{
	accuracy = 0.000001;
	eta = 0.1;
}

void MLP::build(int _InputQty, Layer * _Topology, int _Topology_arraySize)
{
  InputQty = _InputQty;
  Topology = _Topology;
  for (int i = 0; i < _Topology_arraySize; i++) {
    if (i == 0) {
	  for (int j = 0; j < _Topology[i].neuroneQty; j++) {
	    _Topology[i].Cell[j].begin(_InputQty);
		if (_Topology[i].neuroneFunction != "") {
		  _Topology[i].Cell[j].Function = _Topology[i].neuroneFunction;
		}
	  }
	} else {
	  for (int j = 0; j < _Topology[i].neuroneQty; j++) {
	    _Topology[i].Cell[j].begin(_Topology[i-1].neuroneQty);
		if (_Topology[i].neuroneFunction != "") {
		  _Topology[i].Cell[j].Function = _Topology[i].neuroneFunction;
		}
	  }
	}
  }
}

void MLP::Input(int* _InputArray, int _InputQty, int _ElementQty)
{
  for(int i = 0; i < _ElementQty; i++){
      for(int j = 0; j < _InputQty; j++){
         InputArray[(i * _InputQty) + j] = _InputArray[(i * _InputQty) + j];
		 Serial.println((i * _InputQty) + j);
		 Serial.println(_InputArray[(i * _InputQty) + j]);
        }
    }
}

double MLP::Input(int _Input, int _Element)
{
         return InputArray[_Input * _Element + _Element];
}

//========================================================