#include "header.h"
#include <time.h>
#include <ctime> 
#include <ratio>
#include <chrono>

int main(int argc, char **argv){

	string fname = argv[1];

	unsigned long N = 0;

	vector<double> pdata = load_data(fname, N);
	vector<double> obs_data = fwth(pdata);
	vector<double> parameters(OMEGA);
	vector<uint64_t> model;
	model.push_back(0);

	// pairwise model 
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			uint64_t op = (ONE << i) + (ONE << j);
			model.push_back(op);
		}
	}

	vector<double> obs_model = model_observables(parameters);

	auto start = chrono::system_clock::now();
	parameters = gradient_descent(parameters, obs_model, obs_data, model);
	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << elapsed.count() << " seconds." << endl;

	write_parameters(parameters,  model, fname);

	return 0;
	
}