#include<iostream>

#include<mkl.h>
#include<omp.h>
#include<random>

#include<stdlib.h>
#include<fstream>
#include<time.h>

#include<chrono>

using namespace std;

int main() {
	srand(time(NULL));
	mkl_set_num_threads(4);

	ofstream outfile("results.txt");
	if (!outfile.is_open()) {
		cout << "File opening error" << endl;
		return 1;
	}

	for (long vector_size = 1000; vector_size <= 1000000; vector_size *= 1.05) {
		double* v1 = (double*)mkl_malloc(vector_size * sizeof(double), 64);
		double* v2 = (double*)mkl_malloc(vector_size * sizeof(double), 64);

		double lBound = -2531.0; double uBound = 1e6;
		double delta = uBound - lBound;
		for (int i = 0; i < vector_size; i++) {
			double f = ((double)rand() / RAND_MAX);
			v1[i] = lBound + f * delta;
			f = ((double)rand() / RAND_MAX);
			v2[i] = lBound + f * delta;
		}

		auto start = chrono::high_resolution_clock::now();
		double _1res = cblas_ddot(vector_size, v1, 1, v2, 1);
		auto stop = chrono::high_resolution_clock::now();

		auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
		double time_sec = duration.count() / 1e6;
		double gflops = (2.0 * vector_size - 1) / (time_sec * 1e9);
		double bandwidth = (2.0 * vector_size * sizeof(double)) / (1024.0 * 1024 * 1024 * time_sec);

		/*cout << "size = " << vector_size << endl;
		cout << gflops << " GFLOPS" << endl;
		cout << bandwidth << " GB/s" << endl;
		cout << time_sec << " sec" << endl;
		cout << "_____________________________________________________________" << endl;*/

		outfile << vector_size << " " << gflops << " " << bandwidth << endl;

		mkl_free(v1); 
		mkl_free(v2);
	}
		
	outfile.close();
	return 0;
}
