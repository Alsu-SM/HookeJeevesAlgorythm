#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

float Rosenbrok_function(vector <float> X0)
{
	return (100 * pow(X0[1] - pow(X0[0], 2), 2) + pow(1 - X0[0], 2));
}

float example_function(vector <float> X0)
{
	return (pow(X0[0] - 2, 2) + pow(X0[1] - 9, 2) + X0[0] * X0[1]);
}

float manage_function(int functionId, vector <float> X0)
{
	switch (functionId)
	{
	case 0:
		return Rosenbrok_function(X0);
		break;
	case 1:
		return example_function(X0);
		break;

	}
}

void print_function(int functionId)
{
	switch (functionId)
	{
	case 0:
		cout << "\nRosenbrok Function: Q(x1,x2) = 100 * (x2 - x1^2)^2 + (1 - x1)^2 -> min \n" << endl;
		break;
	case 1:
		cout << "\nExample Function: Q(x1,x2) = (x1 - 2)^2 + (x2 - 9)^2 + x1*x2 -> min \n" << endl;
		break;

	}
}

vector <float> neighborhood_search(vector <float> X0, float delta, int functionId)
{
	vector <float> point_x2_fixed = { X0[0] + delta, X0[1] };
	vector <float> newPoint;

	if (manage_function(functionId, point_x2_fixed) < manage_function(functionId, X0))
		newPoint.push_back(point_x2_fixed[0]);
	else
	{
		point_x2_fixed[0] = X0[0] - delta;
		if (manage_function(functionId, point_x2_fixed) < manage_function(functionId, X0))
			newPoint.push_back(point_x2_fixed[0]);
		else
			newPoint.push_back(X0[0]);
	}

	vector <float> point_x1_fixed = { newPoint[0], X0[1] + delta };

	if (manage_function(functionId, point_x1_fixed) < manage_function(functionId, X0))
		newPoint.push_back(point_x1_fixed[1]);
	else
	{
		point_x1_fixed[1] = X0[1] - delta;
		if (manage_function(functionId, point_x1_fixed) < manage_function(functionId, X0))
			newPoint.push_back(point_x1_fixed[1]);
		else
			newPoint.push_back(X0[1]);
	}

	return newPoint;
}

void HookeJeevesAlgorythm(vector <float> X0, float delta, int step_reduction_coef, float end_point_param, int functionId)
{
	print_function(functionId);
	vector <float> X1 = X0;
	vector <float> X2;
	vector < vector <float> > X_array;
	X_array.push_back(X0);
	bool stopPoint = false;
	bool nextStepFlag = true;

	cout << "starting point: X = (" << X0[0] << ", " << X0[1] << ") Q(X) = " << manage_function(functionId, X0) << endl;
	int counter = 0;

	while (delta > end_point_param)
	{
		X1 = neighborhood_search(X1, delta, functionId);
		if (X1[0] == X0[0] && X1[1] == X0[1])
		{
			delta = delta / step_reduction_coef;
			//cout << "X1 = X0 = (" << X0[0] << ", " << X0[1] << "), new delta: " << delta << endl;
		}
		else if (find(X_array.begin(), X_array.end(), X1) != X_array.end()) {
			delta = delta / step_reduction_coef;
			//cout << "same value: (" << X1[0] << ", " << X1[1] << "), new delta: " << delta << endl;
		}
		else {
			X_array.push_back(X1);
			if (counter == 0)
			{
				//cout << "iteration " << counter + 1 << ": X = (" << X1[0] << ", " << X1[1] << ") Q(X) = " << manage_function(functionId, X1) << " delta : " << delta << endl;
				counter++;

			}

			X2 = { X_array[X_array.size() - 1][0] + X_array[X_array.size() - 1][0] - X_array[X_array.size() - 2][0],
				X_array[X_array.size() - 1][1] + X_array[X_array.size() - 1][1] - X_array[X_array.size() - 2][1] };

			X_array.push_back(X2);

			X0 = X1;
			X1 = X2;

			//cout << "iteration " << counter + 1 << " X = (" << X2[0] << ", " << X2[1] << ") Q(X) = " << manage_function(functionId, X2) << " delta: " << delta << endl;

			counter++;

		}



	}

	cout << "\nresult:\nX = (" << X1[0] << ", " << X1[1] << ")\nQ(X) = " << manage_function(functionId, X1) << "\ndelta = " << delta << "\niterations:  " << counter - 1 << "\n\n" << endl;

}

int main()
{
	vector <float> X0 = { -1.1, -1.5 };

	float delta = 1;
	int step_reduction_coef = 2;
	float end_point_param = 0.0000001;
	int functionId = 0; // функция розенброка

	HookeJeevesAlgorythm(X0, delta, step_reduction_coef, end_point_param, functionId);

	X0 = { -8, -9 };
	end_point_param = 0.001;
	functionId = 1; // другой пример функции

	HookeJeevesAlgorythm(X0, delta, step_reduction_coef, end_point_param, functionId);

	return 0;
}