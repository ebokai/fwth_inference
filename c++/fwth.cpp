#include "header.h"



vector<double> fwth(vector<double> v){

	uint64_t h = 1;
	while (h < OMEGA) {
		for (uint64_t i = 0; i < OMEGA; i += h * 2){
			for (uint64_t j = i; j < i + h; j++){
				double x = v[j];
				double y = v[j + h];
				v[j] = x + y;
				v[j + h] = x - y;
			}
		}
		h *= 2;
	}

	return v;
}

vector<double> model_observables(vector<double> parameters){

	vector<double> h = fwth(parameters);
	vector<double> u(OMEGA);
	vector<double> p(OMEGA);
	vector<double> obs_model;

	double z = 0;
	for (uint64_t i = 0; i < OMEGA; i++){
		u[i] = exp(h[i]);
		z += u[i];
	}

	for (uint64_t i = 0; i < OMEGA; i++){
		p[i] = u[i]/z;
	}

	obs_model = fwth(p);

	return obs_model;
}

uint64_t most_biased_op(vector<double> obs_data, vector<double> obs_model){

	double dkl, p1d, p1m;
	double max_dkl = 0;
	uint64_t mbo = 0;
	
	for (uint64_t i = 0; i < OMEGA; i++){

		p1d = (1 + obs_data[i])/2;
		p1m = (1 + obs_model[i])/2;

		dkl = p1d * log(p1d/p1m) + (1 - p1d) * log((1 - p1d)/(1 - p1m));

		if (dkl > max_dkl){
			max_dkl = dkl;
			mbo = i;
		}

	}	

	cout << "most relevant operator: " << mbo << endl;

	return mbo;
}

