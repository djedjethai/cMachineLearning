#include "dlib/matrix/matrix_subexp.h"
#include "dlib/matrix/matrix_utilities.h"
#include"iostream"
#include<dlib/matrix.h>

int main() {

	dlib::matrix<double,3,1> y;

	dlib::matrix<double> m(3, 3);

	// change the size of the previous m(3, 3)
	m.set_size(6, 6);

	std::cout << "y " << y << std::endl;
	std::cout << "m " << m << std::endl;

	// We can initialize matrix values with a comma operator,
	m.set_size(3, 3); // resize m to match first
	m = 54.2, 7.4, 12.1,
 	    1, 2, 3,
            5.9, 0.05, 1;

	std::cout << "m after comma operator " << m << std::endl;

	// As in the previous libraries, we can wrap an existing C++ array to the matrix object
	double data[] = {1,2,3,4,5,6};
	auto a = dlib::mat(data, 2,3); // create matrix with size 2x3

	std::cout << "a " << a << std::endl;

	// we can access matrix elements with the () operator to modify or get a particular value
	m(0,2) = 0;
	std::cout << "m " << m << std::endl;

	auto aa = dlib::identity_matrix<double>(3);
	std::cout << "aa " << aa << std::endl;
	auto ab = dlib::ones_matrix<double>(3, 4);
	std::cout << "ab " << ab << std::endl;
	auto ac = dlib::randm(3, 4);
	std::cout << "ac " << ac << std::endl;

	// Most linear algebra arithmetic operations in the Dlib library are implemented through
	// overloads
	auto e = aa + ab;
	std::cout << "e " << e << std::endl;
	auto f = aa * ab;
	std::cout << "f " << f << std::endl;
	auto ew = dlib::pointwise_multiply(aa, ab); // element wise multiplication
	std::cout << "ew " << ew << std::endl;
	dlib::matrix<double> t = dlib::trans(aa); // transpose matrix
	std::cout << "t " << t << std::endl;

	auto ba = dlib::rowm(ab, 0); // takes first row of matrix
	std::cout << "ba " << ba << std::endl;
	auto bb = dlib::rowm(ab, dlib::range(0,1)); //  takes first 2 row of matrix
	std::cout << "bb " << bb << std::endl;
	auto bc = dlib::colm(ab, 0); // take first column
	std::cout << "bc " << bc << std::endl;
	auto bd = dlib::subm(ab, dlib::range(1, 2), dlib::range(1,2)); // takes a rectangular part from center	
	std::cout << "bd " << bd << std::endl;
	// dlib::subm(ab, dlib::range(0, 1), dlib::range(0, 1)) = 7; // initialize part of the matrix
	// dlib::subm(ab, dlib::range(0, 1), dlib::range(0, 1)) += 7; // add a value to the part of the matrix

	dlib::matrix<float, 2, 1> x;
	std::cout << "x " << x << std::endl;
	dlib::matrix<float, 2, 3> yy;
	std::cout << "yy " << yy << std::endl;
	dlib::set_colm(yy, dlib::range(0,1)) += x;
	std::cout << "yy2 " << yy << std::endl;


	return 0;
}
