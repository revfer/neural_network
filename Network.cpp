#include <iostream>
#include "Network.h"

using namespace std;
void NeuronNetwork::set_input(double* arr, int len)
{
	int end;
	if (len > inpCnt || len == 0) end = inpCnt;
	else end = len;
	for (int i = 0; i < end; i++)
	{
		network[0][i].set_value(arr[i]);
	}
}
void NeuronNetwork::feed()
{
	for (int i = 1; i < layCnt; i++)
	{
		for (int j = 0; j < lay_sizes[i]; j++)
		{
			network[i][j].set_value(0);
			for (int z = 0; z < lay_sizes[i - 1]; z++)
			{
				network[i][j].inc_value(network[i - 1][z].get_value() * network[i - 1][z].get_weights()[j]);
			}
			if (is_bias)
			{
				network[i][j].inc_value(bias_line[i - 1].get_weights()[j] * 1);
			}
			network[i][j].activate();
		}
	}
}

NeuronNetwork::NeuronNetwork(int layCount, int hidNeurCount, int inpCount, int outCount)
{
	layCnt = layCount + 2;
	inpCnt = inpCount;
	outCnt = outCount;
	lay_sizes = new int[layCnt];
	hiddenCnt = hidNeurCount;
	network = new Neuron * [layCount + 2];
	network[0] = new Neuron[inpCount];
	for (int j = 0; j < inpCount; j++)
	{
		network[0][j].create_weights(hidNeurCount);
	}
	lay_sizes[0] = inpCount;
	if (is_bias)
	{
		bias_line = new Neuron[layCount + 1];
		for (int j = 0; j < layCount + 1; j++)
		{
			if (j != layCount) bias_line[j].create_weights(hidNeurCount);
			else bias_line[j].create_weights(outCount);
		}
	}
	for (int i = 1; i < layCount + 1; i++)
	{
		lay_sizes[i] = hidNeurCount;
		network[i] = new Neuron[hidNeurCount];
		for (int j = 0; j < hidNeurCount; j++)
		{
			if (i != layCount) network[i][j].create_weights(hidNeurCount);
			else network[i][j].create_weights(outCount);
		}
	}
	lay_sizes[layCount + 1] = outCount;
	network[layCount + 1] = new Neuron[outCount];
}
NeuronNetwork::NeuronNetwork(int* arr, int arr_len)
{
	lay_sizes = arr;
	inpCnt = lay_sizes[0];
	layCnt = arr_len;
	outCnt = lay_sizes[arr_len - 1];
	network = new Neuron * [arr_len];
	for (int i = 0; i < arr_len - 1; i++)
	{
		network[i] = new Neuron[lay_sizes[i]];
		for (int j = 0; j < lay_sizes[i]; j++)
		{
			network[i][j].create_weights(lay_sizes[i + 1]);
		}
	}
	network[arr_len - 1] = new Neuron[lay_sizes[arr_len - 1]];
}
void NeuronNetwork::show()
{
	for (int j = 0; j < lay_sizes[layCnt - 1]; j++)
	{
		cout << network[layCnt - 1][j].get_value() << '\n';
	}
}
void NeuronNetwork::feeder(double* arr, int len)
{
	this->set_input(arr, len);
	this->feed();
}


void NeuronNetwork::weights_updater(double lr)
{
	learning_rate = lr;
	double error;
	for (int i = 0; i < layCnt - 1; i++)
	{
		for (int j = 0; j < lay_sizes[i]; j++)
		{
			for (int z = 0; z < lay_sizes[i + 1]; z++)
			{
				error = learning_rate * network[i + 1][z].error * network[i + 1][z].get_derval() * network[i][j].get_value();
				network[i][j].update_weight(error, z);
			}
		}
		if (is_bias)
		{
			for (int z = 0; z < lay_sizes[i + 1]; z++)
			{
				error = learning_rate * network[i + 1][z].error * network[i + 1][z].get_derval();
				bias_line[i].update_weight(error, z);
			}
		}
	}
}

void NeuronNetwork::back_propogation(double* result, double lr)
{
	for (int i = layCnt - 1; i > 0; i--)
	{
		if (i == layCnt - 1)
		{
			for (int j = 0; j < lay_sizes[i]; j++)
			{
				if (result[j] == 1)
				{
					network[i][j].error = 1.0 - network[i][j].get_value();
				}
				else
				{
					network[i][j].error = -network[i][j].get_value();
				}
			}
		}
		else
		{
			for (int j = 0; j < lay_sizes[i]; j++)
			{
				network[i][j].error = 0.0;
				for (int z = 0; z < lay_sizes[i + 1]; z++)
				{
					network[i][j].error += network[i + 1][z].error * network[i][j].get_weights()[z];
				}
			}
		}
	}
	weights_updater(lr);
}
int NeuronNetwork::return_answer()
{
	double val, max = 0;
	int answ = 0;
	for (int i = 0; i < lay_sizes[layCnt - 1]; i++)
	{
		val = network[layCnt - 1][lay_sizes[layCnt - 1] - i - 1].get_value();
		if (val > 0.7)
		{
			answ += pow(2, i);
		}
		//cout << val << endl;
	}
	//cout << "Answer is: " << answ << endl;
	return answ;

}