#pragma once
#include <iostream>
class Neuron
{
private:
	double value = 0;
	double derivedVal;
	double* weights;
public:
	double error;
	Neuron();
	double get_value();
	void set_value(double var);
	void create_weights(int next_layer_count);
	double* get_weights();
	double activate();
	double get_derval();
	void update_weight(double error, int index);
	void inc_value(double val);
};