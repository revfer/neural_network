#pragma once
#include "Neuron.h"

class NeuronNetwork
{
private:
	Neuron** network;
	int layCnt, inpCnt, outCnt, hiddenCnt;
	int* lay_sizes;
	double learning_rate = 0.02;
	bool is_bias = false;
	Neuron* bias_line;
	void set_input(double* arr, int len);
	void feed();
public:
	NeuronNetwork(int layCount, int hidNeurCount, int inpCount, int outCount);
	NeuronNetwork(int* arr, int arr_len);
	void show();
	void feeder(double* arr, int len);


	void weights_updater(double lr);

	void back_propogation(double* result, double lr);
	int return_answer();
};