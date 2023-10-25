// #include "shark/Data/BatchInterface.h"
// #include "shark/Data/DataView.h"
// #include "shark/LinAlg/BLAS/detail/storage.hpp"
// #include "shark/LinAlg/BLAS/proxy_expressions.hpp"
// #include "shark/LinAlg/Base.h"
#include<iostream>
#include<shark/Data/Dataset.h>


int main() {

	size_t size = 100;
	double initialValue = 1.0;

	shark::RealVector b(size);
	b = shark::RealVector(size, initialValue);

	std::cout << "See the b " << b << std::endl;

	shark::RealMatrix c(2, 2);

	std::cout << "See the c " << c << std::endl;

	// There are two main types of container initialization in the Shark-ML library.
	// We can initialize a container object with the constructor that takes the initializer list. 
	// The following code sample shows this:
	shark::RealMatrix d{{1,1},{1,1}};

	std::cout << "See the d " << d << std::endl;

// The second option is to wrap the existing C++ array into the container object and reuse its memory and values. 
// The following code sample shows how to use the same array for the initialization of matrix and vector objects:
	float data[] = {1,2,3,4};

	int numRow{2};
	int numCol = 2;

	shark::RealMatrix e(numRow, numCol);

	// // my solution
	// int count{0};
	// for(size_t i{0}; i < numRow; i++){
	// 	for(size_t y{0}; y < numCol; y++){
	// 		e(i, y) = data[count];
	// 		count++;
	// 	};
	// };
	
	// give the same as
	for(size_t i{0}; i < numRow; i++){
		for(size_t y{0}; y < numCol; y++){
			e(i, y) = data[i * numCol + y];
		};
	};

	std::cout << "See the e " << e << std::endl;

	// manual assignement
	shark::RealMatrix f(2,3);
	std::cout << "See the f " << f << std::endl;
	f(1, 2) = 89;
	std::cout << "See the f1 " << f << std::endl;

	// create a random matrix g
	// Create a matrix with random values
    	shark::RealMatrix g(numRow, numCol);
    	for (size_t i = 0; i < numRow; ++i) {
    	    for (size_t j = 0; j < numCol; ++j) {
    	        g(i, j) = static_cast<double>(rand()) / RAND_MAX;
    	    }
    	}
	std::cout << "The g random matrix: " << g << std::endl;

	shark::RealMatrix h(numRow, numCol);
	for (size_t i = 0; i < numRow; ++i) {
    	    for (size_t j = 0; j < numCol; ++j) {
    	        h(i, j) = static_cast<double>(rand()) / RAND_MAX;
    	    }
    	}
	std::cout << "The h random matrix: " << h << std::endl;

	shark::RealMatrix i(numRow, numCol);
	i = g + h;
	std::cout << "The i random matrix: " << i << std::endl;
	auto j = g * h;
	std::cout << "The j random matrix: " << j << std::endl;
	auto k = g % h; // !!! dot product operator !!!
	std::cout << "The k random matrix: " << k << std::endl;
	g -= h;
	std::cout << "The g -= h random matrix: " << g << std::endl;


	shark::RealMatrix l(10, 10);
	for (size_t i = 0; i < 10; ++i) {
    	    for (size_t j = 0; j < 10; ++j) {
    	        l(i, j) = static_cast<double>(std::rand()) / RAND_MAX;
    	    }
    	}
	std::cout << "The l random matrix: " << l << std::endl;
	

	// auto sr = remora::subrange(l, 0, 5);
	// std::cout << "The subRange random matrix: " << sr << std::endl;
	
	// row (A,k): This function returns the kth row of A as a vector proxy
	auto rw = remora::row(l, 2);
	std::cout << "The row random matrix: " << rw << std::endl;
	// rows (A,k,l): This function returns the rows k,…,l−1 of A as a matrix proxy
	auto rws = remora::rows(l, 0, 2);
	std::cout << "The rows random matrix: " << rws << std::endl;
	// column (A,k): This function returns the kth column of A as a vector proxy.
	auto cw = remora::column(l, 0);
	std::cout << "The column random matrix: " << cw << std::endl;
	// columns (A,k,l): This function returns the columns k,…, l−1 of A as a matrix proxy 
	auto cws = remora::columns(l, 0, 3);
	std::cout << "The columns random matrix: " << cws << std::endl;


	// There is no broadcasting implementation in the Shark-ML library. Limited support of
 	// broadcasting exists only in the form of reduction functions (the set of functions that
 	// calculate one numeric value for a whole matrix or vector). There are two functions—the
 	// as_rows() and as_columns() function—that allow reduction operations to be performed
 	// independently on matrix rows or columns respectively. We can pass the result of these
 	// functions to any of the reduction functions. The following code sample shows how to
 	// perform summation reduction:
	auto cols = remora::as_columns(l);	
	// std::cout << "The cols random matrix: " << cols << std::endl;
	auto sum = remora::sum(cols);
	std::cout << "The sum random matrix: " << sum << std::endl;

	remora::matrix<float> m{{1, 2, 3}, {4, 5, 6}};
	remora::vector<float> v{10, 20};
	// Update matrix rows
	for (size_t i = 0; i < m.size2(); ++i) {
 		remora::column(m, i) += v;
	}
	std::cout << "The m random matrix: " << m << std::endl;
	std::cout << "The v random matrix: " << v << std::endl;


	// ====================== with remora =============================
	// where comes from remora ...??
	
	remora::vector<double> rb(100, 1.0);
	std::cout << "The rb: " << rb << std::endl;

	remora::matrix<double> rc(2, 2);
	std::cout << "The rc: " << rc << std::endl;

	remora::matrix<float> m_ones{{1, 1}, {1, 1}};	
	std::cout << "The m_ones: " << m_ones << std::endl;

	float rdata[]= {1,2,3,4};
	// remora::matrix<float> rm(rdata, 2, 2); // fail
	// rm <= rdata; // fail
	// m(0,0) = 3.14f;
	remora::vector<float> rv(rdata, rdata + 4);
	std::cout << "The rv: " << rv << std::endl;

	rv(0) = 3.14f;
	std::cout << "The rv1: " << rv << std::endl;

	remora::matrix<float> rra(2, 2);
	remora::matrix<float> rrb(2, 2);
	auto rrc = rra + rrb;
	rra -= rrb;
  	
	remora::matrix<float>  rrd = remora::prod(rra,rrb);
	rrd = rra%rrb; // also dot product operation
	rrd = rra + 5;


	return 0;
}
