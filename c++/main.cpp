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

	vector<double> obs_model = model_observables(parameters);

	uint64_t mbo = most_biased_op(obs_data, obs_model);
	model.push_back(mbo);

	auto start = chrono::system_clock::now();
	for (int i = 0; i < 50; i++){
		parameters = gradient_descent(parameters, obs_model, obs_data, model);
		obs_model = model_observables(parameters);
		mbo = most_biased_op(obs_data, obs_model);
		model.push_back(mbo);
	}
	auto end = chrono::system_clock::now();
	chrono::duration<double> elapsed = end - start;
	cout << elapsed.count() << endl;

	










	return 0;
	
}