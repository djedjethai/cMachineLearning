// #include "dlib/svm/function.h"
#include "dlib/svm/kernel.h"
#include "dlib/svm/krr_trainer.h"
#include<iostream>
#include<vector>
#include<dlib/matrix.h>
#include<dlib/svm.h>


typedef dlib::matrix<double> SampleType;
typedef std::vector<SampleType> SampleVector;

int main(){

	SampleVector x;

	// case 1
	// std::vector<float> y;
	// dlib::krr_trainer<dlib::linear_kernel<SampleType>> trainer;
	// trainer.set_kernel(dlib::linear_kernel<SampleType>()); // Use the linear kernel for compatibility
	// dlib::decision_function<dlib::linear_kernel<SampleType>> model = trainer.train(x, y);
							       
	// case 2
	std::vector<double> y;
	dlib::krr_trainer<dlib::linear_kernel<SampleType>> trainer;
	trainer.set_kernel(dlib::linear_kernel<SampleType>());

	dlib::decision_function<dlib::linear_kernel<SampleType>> model = trainer.train(x, y); 
	
	// Add some data to x and y vectors
    	SampleType sample1(2, 2);
    	sample1(0, 0) = 1.0;
    	sample1(0, 1) = 2.0;
    	sample1(1, 0) = 3.0;
    	sample1(1, 1) = 4.0;

    	SampleType sample2(2, 2);
    	sample2(0, 0) = 5.0;
    	sample2(0, 1) = 6.0;
    	sample2(1, 0) = 7.0;
    	sample2(1, 1) = 8.0;

    	x.push_back(sample1);
    	x.push_back(sample2);

    	y.push_back(1.0);
    	y.push_back(-1.0);	
	

	// Make predictions using the trained model
    	std::vector<SampleType> new_x;

    	// Create new samples for prediction
    	SampleType new_sample1(2, 2);
    	new_sample1(0, 0) = 0.5;
    	new_sample1(0, 1) = 1.5;
    	new_sample1(1, 0) = 2.5;
    	new_sample1(1, 1) = 3.5;

    	SampleType new_sample2(2, 2);
    	new_sample2(0, 0) = 4.5;
    	new_sample2(0, 1) = 5.5;
    	new_sample2(1, 0) = 6.5;
    	new_sample2(1, 1) = 7.5;

    	new_x.push_back(new_sample1);
    	new_x.push_back(new_sample2);

	// make prediction
	for(const auto& v: new_x){
		double prediction = model(v);
		std::cout << prediction << std::endl;
	};

	return 0;
}
