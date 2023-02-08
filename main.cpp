#include <iostream>
#include <random>
#include <time.h>
#include <math.h>
#include "Neuron.h";
#include "Network.h"

using namespace std;


int main()
{
	srand(time(NULL));
	int var1, var2, rr, op;
	int input_size = 10;
	int TP = 0;
	int all = 0;
	int hr, i = 0;
	int svrr;
	double percent = 0;
	int output_size = input_size / 2 + 1;
	double learning_rate = 0.8;
	double* result = new double[output_size];
	double* in_arr = new double[input_size];
	//NeuronNetwork nn(1, 30, input_size, output_size);
	int arr[] = { input_size, 70, output_size };
	NeuronNetwork nn(arr, sizeof(arr) / sizeof(int));
	while (percent < 90)
	{
		var1 = rand() % (int)pow(2, input_size / 2);
		var2 = rand() % (int)pow(2, input_size / 2);
		rr = var1 + var2;
		svrr = rr;
		for (int j = input_size - 1; j >= 0; j--)
		{
			if (j > (input_size / 2) - 1)
			{
				in_arr[j] = var2 % 2;
				var2 /= 2;
			}
			else
			{
				in_arr[j] = var1 % 2;
				var1 /= 2;
			}
		}
		for (int j = output_size - 1; j >= 0; j--)
		{
			result[j] = rr % 2;
			rr /= 2;
		}
		nn.feeder(in_arr, input_size);
		hr = nn.return_answer();
		if (hr == svrr) TP++;
		nn.back_propogation(result, learning_rate);
		all++;
		
		if (i % 10000 == 0)
		{
			percent = ((double)TP * 100.0) / (double)all;
			cout << percent << '%' << endl;
			TP = 0;
			all = 0;
			cout << svrr << '\t';
			cout << hr << endl;
		}
		i++;
	}
	char answ = 'y';
	while (answ != 'n')
	{
		cout << "\nWrite from 0 to 31: ";
		cin >> var1;
		cout << "\nWrite from 0 to 31: ";
		cin >> var2;
		for (int j = input_size - 1; j >= 0; j--)
		{
			if (j > (input_size / 2) - 1)
			{
				in_arr[j] = var2 % 2;
				var2 /= 2;
			}
			else
			{
				in_arr[j] = var1 % 2;
				var1 /= 2;
			}
		}
		cout << endl;
		nn.feeder(in_arr, input_size);
		cout << nn.return_answer();
	}

	return 0;
}
