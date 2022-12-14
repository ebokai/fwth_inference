#include <iostream>
#include <bitset>
#include <map>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


const int n = 20;
const uint64_t ONE = 1;
const uint64_t OMEGA = (ONE << n); // 2^n
const unsigned int MAX_ITERS = 500; // maximum iterations for gradient descent
const double EPSILON = 1e-12; // squared tolerance  

vector<double> load_data(string fname, unsigned long &N);
vector<double> fwth(vector<double> v);
vector<double> model_observables(vector<double> parameters);

// use a struct for these arguments
vector<double> gradient_descent(vector<double> parameters, vector<double> obs_model, vector<double> obs_data, vector<uint64_t> model);
uint64_t most_biased_op(vector<double> obs_data, vector<double> obs_model);