#include<Eigen/Dense>
#include <iomanip>
#include<iostream>
#include <vector>
#include <typeinfo>

typedef Eigen::Matrix<float, 3, 1> MyVector3f;
typedef Eigen::Matrix<float, 3, 3> MyMatrix33f;
typedef Eigen::Matrix<float, 2, 2> MyMatrix22f;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MyMatrix;


int main(){

	{
		// declaration
		MyMatrix33f a;
		MyVector3f v;
		MyMatrix m(10, 15);

		// see m
		std::cout << "See m:\n" << m << std::endl;

		// initialization
		v = MyVector3f::Zero();
		std::cout << "Zero vector:\n" << v << std::endl;

		v = MyVector3f::Random();
		std::cout << "Random vector:\n" << v << std::endl;


		a = MyMatrix33f::Zero();
		std::cout << "Zero matrix:\n" << a << std::endl;

		a = MyMatrix33f::Identity();
		std::cout << "Identity matrix:\n" << a << std::endl;

		a = MyMatrix33f::Random();
		std::cout << "Random matrix:\n" << a << std::endl;

		// filup manually
		a << 1,2,3,4,5,6,7,8,9;
		std::cout << "Manual fillup matrix:\n" << a << std::endl;

		// 2 is row, 1 column
		a(2,1) =34;
		std::cout << "Change specific elm in matrix:\n" << a << std::endl;

		// existant array to an Eigen::map
		int data[] = {1,2,3,4};
		Eigen::Map<Eigen::RowVectorXi> am(data, 4);
		std::cout << "See an array to Eigen::map: " << am << std::endl;

		// existant vector to an Eigen::map
		std::vector<float> data1 = {1,2,3,4,5,6,7,8,9};
		Eigen::Map<MyMatrix33f> av(data1.data());
		std::cout << "See a vector to Eigen::map: " << av << std::endl;	
	}
	// ex math operation with eigen
	{
		// auto a = Eigen::Matrix2d::Random();
		// MyMatrix22f a;
		Eigen::Matrix2d a;
		a << 1,2,3,4;
		std::cout << "see matrix 2d a: " << a << std::endl;
		std::cout << "see matrix 2d a.array(): " << a.array() << std::endl;
		// auto b = Eigen::Matrix2d::Random();
		// MyMatrix22f b;
		Eigen::Matrix2d b;
		b << 1,2,3,4;
		std::cout << "see matrix 2d b: " << b << std::endl;
		std::cout << "see matrix 2d b.array(): " << b.array() << std::endl;

		// Set precision and fixed format for output
    		std::cout << std::fixed << std::setprecision(6);

		std::cout << "result add: " << a + b << std::endl;	
		std::cout << "result mult: " << a * b << std::endl;
		// std::cout << "result div: " << a / b << std::endl;


		std::cout << "result add with array: " << a.array() + b.array() << std::endl;
		std::cout << "result mult with array: " << a.array() * b.array() << std::endl;
		// auto result2 = a.array() / b.array();
		std::cout << "result div with array: " << a.array() / b.array() << std::endl;

		
		// a += b;
		// std::cout << "res a += b: " << a << std::endl;

		// a.array() = b.array() * 4;
		std::cout << "result scalars: " << b.array() * 4 << std::endl;
	}
	{
		Eigen::MatrixXf m(4,4);
		m.setConstant(1.0f); // set value to 1 for all elements
		std::cout << "m " << m << std::endl;
		Eigen::Matrix2f b = m.block(1,1,2,2); // copy middle part
		// (1, 1) indicates the second row and second column (2, 2) specify that the block has 2 rows and 2 columns 
		std::cout << "m middle part " << b << std::endl;

		m.block(1,1,2,2) *= 4;
		std::cout << "change value in original matrix " << m << std::endl;

		m.row(1).array() += 3;
		std::cout << "add 3 to m.row(1) " << m;

		m.col(2).array() += 8;
		m.col(2).array() /= 4;
		std::cout << "add 8 then / 4 on col 2 " << m << std::endl;

		// Broadcasting
		Eigen::MatrixXf mat(2,4);
		mat.setConstant(1.0f); // set value to 1 for all elements
		std::cout << "mat before .colwise() " << mat << std::endl;
		Eigen::VectorXf v(2);
		v.setConstant(1.0f); // set value to 1 for all elements
		std::cout << "v before .colwise() " << v << std::endl;
		mat.colwise() += v; // 
		std::cout << "mat after .colwise() " << mat << std::endl;

	}
	
}

