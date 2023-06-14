#include<iostream>
#include<vector>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include<Eigen/Dense>
#include <xtensor/xlayout.hpp>
#include <xtensor/xadapt.hpp>
#include <xtensor/xtensor_forward.hpp>

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

	xt::xtensor_fixed<double, xt::xshape<3,2,4>> xs;
	std::cout << "xtensor_fixed: " << xs << std::endl;
	

	return 0;
}
