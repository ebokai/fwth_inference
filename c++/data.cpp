#include "header.h"

vector<double> load_data(string fname, unsigned long &N){

	cout << "loading: " << fname << " ... ";

	string line, subline;
	uint32_t state;
	string input_path = "../data/set_02/" + fname + ".dat";
	ifstream input_file(input_path);
	vector<double> pdata(OMEGA);

	while(getline(input_file, line)){
		subline = line.substr(0,n);
		state = bitset<n>(subline).to_ulong();
		pdata[state]++;
		N++;
	} 

	input_file.close();
	cout << N << " samples" << endl;

	for (uint64_t i = 0; i < OMEGA; i++){
		pdata[i] /= static_cast <double> (N);
	}

	return pdata;
}

void write_parameters(vector<double> parameters, vector<uint64_t> model, string fname){

	uint64_t op;
	double par;

	string output_path = "../data/set_02_jij_new/" + fname + "_jij.dat";
	ofstream output_file(output_path);

	// skip identity operator 
	for(unsigned int i = 1; i < model.size(); i++){
		op = model[i];
		par = parameters[op];
		//cout << op << " " << par << endl;
		output_file << bitset<n>(op) << "\t" << par << endl;
	}

	output_file.close();

}