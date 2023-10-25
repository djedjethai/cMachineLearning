#include<iostream>
#include<Eigen/Dense>
#include <Eigen/IterativeLinearSolvers>

typedef float DType;
using Matrix = Eigen::Matrix<DType, Eigen::Dynamic, Eigen::Dynamic>;
// using Vector = Eigen::Matrix<DType, Eigen::Dynamic, 1>;


int main(){
	int n = 10000;
	int p = 2;

	Matrix x(n, p);
	// Matrix y(n, 1);
	Matrix y(n, p);

	// Fill x and y with appropriate values (you should replace this with your data)
    	// For example, let's fill them with random data here:
    	x.setRandom();
    	y.setRandom();

	Eigen::LeastSquaresConjugateGradient<Matrix> gd;
	gd.setMaxIterations(1000);
	gd.setTolerance(0.001);
	
	gd.compute(x);
	// auto b = gd.solve(y); // OK
	
	// Also, we can calculate parameter's b vector (the linear regression task solution) by solving the normal equation directly, as follows
	// !!! auto b does not work in this case, it must be Matrix b
	Matrix b = (x.transpose() * x).ldlt().solve(x.transpose() * y);

	// For new x inputs, we can predict new y values with matrices operations, as follows
	Eigen::MatrixXf new_x(5, p);
	new_x <<  1, 1, 1, 2, 1, 3, 1, 4, 1, 5;
	// auto new_y = new_x.array().rowwise() * b.transpose().array();
	Eigen::MatrixXf new_y = new_x * b;

	std::cout << "The new_x" << new_x << std::endl;
	std::cout << "The new_y" << new_y << std::endl;


	return 0;
};

