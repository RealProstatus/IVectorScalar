#include<iostream>

#include<mkl.h>
#include<random>

#include<stdlib.h>
#include<time.h>

#include<chrono>

using namespace std;

int main() {
	srand(time(NULL));
	for (long vector_size = 10; vector_size <= 100000000; vector_size *=10) {
		double* v1 = (double*)mkl_malloc(vector_size * sizeof(double), 64);
		double* v2 = (double*)mkl_malloc(vector_size * sizeof(double), 64);

		double lBound = -2531.0; double uBound = 1e6;
		double delta = uBound - lBound;
		for (int i = 0; i < vector_size; i++) {
			double f = 1000*((double)rand() / RAND_MAX);
			v1[i] = (double)(lBound + f * delta);
			f = 1000 * ((double)rand() / RAND_MAX);
			v2[i] = lBound + f * delta;
		}

		auto start = chrono::high_resolution_clock::now();
		double _1res = cblas_ddot(vector_size, v1, 1, v2, 1);
		auto stop = chrono::high_resolution_clock::now();

		auto res = chrono::duration_cast<chrono::microseconds>(stop - start);
		cout << "size = " << vector_size << endl;
		cout << (2 * vector_size - 1) / (1e3*res.count()) << " GFLOPS" << endl;
		cout << (2 * vector_size * sizeof(double)) / (1024 * 1024 * 1024 * 1e3 * res.count()) << " Gb/s" << endl;
		cout << res.count()/1e6 << " sec"<<endl;
		cout << "_____________________________________________________________"<<endl;

		mkl_free(v1); mkl_free(v2);
	}
		
}