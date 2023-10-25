// #include "shark/LinAlg/Base.h"
// #include "shark/Models/NeuronLayers.h"
#include "shark/Data/BatchInterface.h"
#include <iostream>
// #include <shark/Data/Dataset.h>
#include <shark/Models/LinearModel.h>
#include <shark/Algorithms/Trainers/LinearRegression.h>
#include <shark/Data/Csv.h>
#include <shark/ObjectiveFunctions/Loss/SquaredLoss.h>

// to run
// ./linalg-shark ../data/regressionInputs.csv ../data/regressionLabels.csv


using namespace shark;
using namespace std;

int main(int argc, char **argv) {

	if(argc < 3) {
                cerr << "usage: " << argv[0] << " (file with inputs/independent variables) (file with outputs/dependent variables)" << endl;
                exit(EXIT_FAILURE);
        }

        Data<RealVector> inputs;
        Data<RealVector> labels;
        
	try {
                importCSV(inputs, argv[1], ' ');
        }
        catch (...) {
                cerr << "unable to read input data from file " <<  argv[1] << endl;
                exit(EXIT_FAILURE);
        }

        try {
                importCSV(labels, argv[2]);
        }
        catch (...) {
                cerr << "unable to read labels from file " <<  argv[2] << endl;
                exit(EXIT_FAILURE);
        }

	RegressionDataset data(inputs, labels);

	LinearModel<> model;

	LinearRegression trainer;

	trainer.train(model, data);

	cout << "intercept: " << model.offset() << endl;
	cout << "matrix: " << model.matrix() << endl;

	Data<RealVector> prediction = model(data.inputs());

	SquaredLoss<> loss;

	cout << "squared loss: " << loss(data.labels(), prediction) << endl;

	return 0;
}



// int main(){
// 
// 	RealVector vec(3);
//     	vec(0) = 1.0;
//     	vec(1) = 2.0;
//     	vec(2) = 3.0;
// 	shark::Data<shark::RealVector> x(1, vec);
// 
// 
// 	RealVector vecY(3);
//     	vecY(0) = 10.0;
//     	vecY(1) = 20.0;
//     	vecY(2) = 30.0;
// 	shark::Data<shark::RealVector> y(1, vecY);
// 	
// 
// 	RegressionDataset data(x, y);
// 	LinearModel<> model;
// 
// 	LinearRegression trainer;
// 	trainer.train(model, data);
// 
// 
// 	cout << "intercept: " << model.offset() << endl;
// 	cout << "matrix: " << model.matrix() << endl;
// 
// 	// // We can get the calculated parameters (the linear regression task solution) 
// 	// // vector by running the following code:
// 	// auto b = model.parameterVector();
// 
// 	// RealVector new_x(3);
//     	// new_x(0) = 7.0;
//     	// new_x(1) = 8.0;
//     	// new_x(2) = 9.0;
//     	// Data<RealVector> new_x_data(1, new_x);
// 
// 	// // For new x inputs, we can predict new y values in the following way:
// 	// // Data<RealVector> new_x(7.0);
// 	// // Data<RealVector> prediction = model(new_x);
// 	// // Data<RealVector> prediction = prod(new_x, b);
// 	// double prediction = dot(new_x, b);
// 
// 	// cout << "See the prediction: " << prediction << endl;
// 
// 	return 0;
// }

