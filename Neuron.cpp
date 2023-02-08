#include "Neuron.h"

Neuron::Neuron()
{
	this->weights = NULL;
}

double Neuron::get_value()
{
	return this->value;
}


void Neuron::set_value(double var)
{
	this->value = var;
}
void Neuron::create_weights(int next_layer_count)
{
	if (this->weights != NULL)
	{
		delete this->weights;
	}
	this->weights = new double[next_layer_count];
	for (int i = 0; i < next_layer_count; i++)
	{
		this->weights[i] = (double)(rand() % 90 + 5) / 100.0;
	}
}
double* Neuron::get_weights()
{
	return this->weights;
}
double Neuron::activate()
{
	this->value = 1 / (1 + exp(-(this->value)));
	return this->value;
}
double Neuron::get_derval()
{
	this->derivedVal = this->value * (1 - this->value);
	return this->derivedVal;
}
void Neuron::update_weight(double error, int index)
{
	this->weights[index] += error;
}
void Neuron::inc_value(double val)
{
	this->value += val;
}