#include "header.h"

vector<double> load_data(string fname, unsigned long &N){

	cout << "loading: " << fname << " ... ";

	string line, subline;
	uint32_t state;
	ifstream input_file(fname);
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