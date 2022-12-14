#include "header.h"

vector<double> gradient_descent(vector<double> parameters, vector<double> obs_model, vector<double> obs_data, vector<uint64_t> model){

	// cout << "====== GRADIENT DESCENT ======" << endl;

	vector<double> gradient(OMEGA);

	double grad_norm = 1;
	double dg;
	double grad_check = 100;
	double gamma = 0.8; // learning rate
	uint64_t k;
	unsigned int iters = 0;

	// gradient descent
	while ((grad_norm > EPSILON) && (iters < MAX_ITERS)){

		iters++;
		grad_norm = 0;

		transform(obs_model.begin(), obs_model.end(), obs_data.begin(), gradient.begin(), minus<double>());

		for (unsigned int j = 0; j < model.size(); j++){
			k = model[j];

			//cout << k << " " << obs_model[k] << " " << obs_data[k] << " " << gradient[k] << endl;
			parameters[k] -= gamma * gradient[k];
			grad_norm += gradient[k] * gradient[k];
		}

		obs_model = model_observables(parameters);

		dg = grad_norm - grad_check;
		if (dg > 0){
			//cout << dg << endl;
			//cout << "gradient is increasing!" << endl;
			gamma /= 1.25;
			//cout << "lowering learning rate to: " << gamma << endl;
		}

		grad_check = grad_norm;
		
	}	



	//cout << "gradient norm squared: " << grad_norm << endl;
	cout << iters << " iterations" << endl;

	return parameters;
}

