#include "xtensor/xaccumulator.hpp"
#include<iostream>
#include<vector>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include<Eigen/Dense>
#include <xtensor/xlayout.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xtensor_forward.hpp>
#include <xtensor/xrandom.hpp>
#include <xtensor/xview.hpp>
// #include <xtensor/xmath.hpp>
#include <xtensor-blas/xlinalg.hpp>

typedef Eigen::Matrix<float, 3, 1> MyVector3f;

int main(){
	// make sure eigen is available via CPATH
	MyVector3f v;
	v = MyVector3f::Zero();
	std::cout << "Zero vector:\n" << v << std::endl;


	xt::xarray<double> arr1{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    	std::cout << "See arr1 " << arr1 << std::endl;

	std::vector<size_t> shape = {3, 2, 4};
	// multidimensional array which take the shape of shape, RESIZABLE
	xt::xarray<double, xt::layout_type::column_major> a(shape);
	std::cout << "array a(shape):\n" << a << std::endl;

	// multidimensional array which take the shape of shape, FIX SIZE BUT FAST ACCESS
	xt::xtensor<double, 3> d3 = xt::adapt(std::vector<double>(xt::compute_size(shape)), shape);

	// fill up the value
	int value = 1;
	for(auto& element:d3){
		element = value;
		value++;
	};
	std::cout << "tensor d3(shape):\n" << d3 << std::endl;

	xt::xtensor_fixed<double, xt::xshape<2,3,2>> xs;
	std::cout << "xtensor_fixed: " << xs << std::endl;
	
	// Initialization of xtensor arrays can be done with C++ initializer lists
	xt::xarray<double> arr2{{1.0, 2.0, 3.0},
				{4.0, 5.0, 6.0},
				{7.0, 8.0, 9.0}};
	std::cout << "See the arr2: " << arr2 << std::endl;

	// The xtensor library also has builder functions for special tensor types, ex:
	std::vector<uint64_t> shape1 = {4, 3};
	std::cout << "See shape1 shape: " << std::endl;
	// that is the shape, which is 2 arrays of 3 elements each
	for (const auto& element : shape1)
        	std::cout << element << " ";
        std::cout << std::endl;

	xt::xarray<uint64_t> arr3 = xt::ones<uint64_t>(shape1);
	std::cout << "See shape1 after xt::ones: ";
	// that shows the array shape
    	for (const auto& dimension : arr3.shape()) 
        	std::cout << dimension << " ";
    	std::cout << std::endl;
	// that shows the arrays data(all at 1)
	for (const auto& element : arr3)
        	std::cout << element << " ";
        std::cout << std::endl;

	xt::xarray<uint64_t> arr4 = xt::zeros<uint64_t>(shape1);
	std::cout << "See shape1 after xt::zero: ";
	// that shows the array shape
    	for (const auto& dimension : arr4.shape()) 
        	std::cout << dimension << " ";
    	std::cout << std::endl;
	// that shows the arrays data(all at 0)
	for (const auto& element : arr4)
        	std::cout << element << " ";
        std::cout << std::endl;

	xt::xarray<uint64_t> arr5 = xt::eye<uint64_t>(shape1);
	std::cout << "See shape1 after xt::eye: ";
	// that shows the array shape
    	for (const auto& dimension : arr5.shape()) 
        	std::cout << dimension << " ";
    	std::cout << std::endl;
	// matrix with ones on the diagonal
	// 100
	// 010
	// 001
	// 000
	for (const auto& element : arr5)
        	std::cout << element << " ";
        std::cout << std::endl;

	// we can map existing C++ arrays into the xtensor container with the xt::adapt function
	// This function returns the object that uses the memory and values from the underlying object
	std::cout << "map existing array to xtensor container " << std::endl;
	std::vector<float> dataM{1,2,3,4};
	std::vector<size_t> shapeM{2,4}; // 2 arrays of 4 elements
	auto data_x = xt::adapt(dataM, shapeM);
	// 1 2 3 4 0 0 0 0
	for (const auto& element : data_x)
        	std::cout << element << " ";
        std::cout << std::endl;

	//  use direct access to container elements, with the () operator
	std::cout << "direct access to container element " << std::endl;
	std::vector<size_t> shapeA = {3, 2, 4}; // 3 blocks of 2 arrays of 4 elements/each 
	xt::xarray<float> aA = xt::ones<float>(shapeA);
	std::cout << "array aA bf:\n" << aA << std::endl;
	aA(2, 1, 3) = 3.14f;
	std::cout << "array aA after:\n" << aA << std::endl;

	// The xtensor library implements linear algebra arithmetic operations through overloads of standard C++ arithmetic operators such as +, - and *
	// To use other operations such as dotproduct operations, we have to link an application with the library named xtensor-blas
	auto aR = xt::random::rand<double>({2,2});
	std::cout << "array aR:\n" << aR << std::endl;
	// auto bR = xt::random::rand<double>({2,2});
	auto bR = xt::random::rand<double>({2,2});
	std::cout << "array bR:\n" << bR << std::endl;
	auto cR = aR + bR; // result of cR is wrong, why ? asa random are used when add it's wrong
	std::cout << "array cR:\n" << cR << std::endl;
	
	// auto aRR = xt::view(aR, xt::all()) -= bR; // is the same as aR -= bR;
	auto aRR = xt::eval(xt::view(aR, xt::all()) - bR);
	std::cout << "array aRR after -=bR:\n" << aRR << std::endl;

	auto view = xt::view(aRR, xt::all(), xt::range(0, 1));  // Create a view of the first columns
	std::cout << "View:\n" << view << std::endl;

	view(0, 0) = 10.0;  // Modify the view
    	std::cout << "Modified view:\n" << view << std::endl;

	// auto cRR = xt::linalg::dot(aR,bR); // works but create a compiler error

	// std::cout << "cRR after xt::linalg::dot() " << cRR << std::endl;

	xt::xarray<int> m{{1, 2, 3, 4},
 			{5, 6, 7, 8},
 			{9, 10, 11, 12},
 			{13, 14, 15, 16}};
	auto mn = xt::view(m, xt::range(1, 3), xt::range(1, 3));
	std::cout << "See the m " << m << std::endl;
	std::cout << "See the mn " << mn << std::endl;

	auto x = xt::random::rand<double>({2,2});
	auto y = xt::random::rand<double>({2,1});
	auto z = x + y;
	std::cout << "see z  " << z << std::endl;

	return 0;
}
