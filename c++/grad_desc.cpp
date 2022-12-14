#include "header.h"
#include <functional>
#include <numeric>

vector<double> gradient_descent(
	vector<double> parameters, 
	vector<double> obs_model, 
	vector<double> obs_data, 
	vector<uint64_t> model
	string fname){

	// cout << "====== GRADIENT DESCENT ======" << endl;

	vector<double> gradient(OMEGA);

	vector<double> old_gradient(OMEGA);
	vector<double> old_parameters(OMEGA);

	vector<double> delta_gradient(OMEGA);
	vector<double> delta_x(OMEGA);
	
	double dx, df;
	double grad_norm = 1;
	double gamma = 0.75; // initial learning rate / step size
	uint64_t k;
	unsigned int iters = 0;

	// gradient descent
	while ((grad_norm > EPSILON) && (iters < MAX_ITERS)){

		iters++;
		grad_norm = 0;

		// calculate gradient (n)
		transform(obs_model.begin(), obs_model.end(), obs_data.begin(), gradient.begin(), minus<double>());

		// calculate delta gradient 
		transform(gradient.begin(), gradient.end(), old_gradient.begin(), delta_gradient.begin(), minus<double>());

		// calculate delta pars
		transform(parameters.begin(), parameters.end(), old_parameters.begin(), delta_x.begin(), minus<double>());

		old_parameters = parameters;

		dx = fabs(inner_product(delta_x.begin(), delta_x.end(), delta_gradient.begin(), 0.0));
		df = inner_product(delta_gradient.begin(), delta_gradient.end(), delta_gradient.begin(), 0.0);

		if(iters > 1){gamma = dx/df;} // set step size
		
		// update parameters
		for (unsigned int j = 0; j < model.size(); j++){
			k = model[j];
			parameters[k] -= gamma * gradient[k]; 
			grad_norm += gradient[k] * gradient[k];
		}

		old_gradient = gradient;
		obs_model = model_observables(parameters);
		
	}	


	string check_path = "../conv_res/" + to_string(iters) + "_" + fname;
	ofstream check_file(check_path);
	check_file.close();
	
	cout << iters << " iterations" << endl;

	return parameters;
}

