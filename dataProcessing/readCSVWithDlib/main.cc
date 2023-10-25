#include"fastCppCsvParser/csv.h"
#include<dlib/matrix.h>

		  
#include <ios>
#include<iostream>
#include <istream>
#include <iterator>
#include<string>
#include<fstream>
#include<vector>
#include<regex>



// ./csv-dlib ../../data/iris.data

void rewriteDataFile(const char* outputFile, char** argv){
	try {
		std::ifstream data_stream(argv[1]);
		std::string data_string((std::istreambuf_iterator<char>(data_stream)), std::istreambuf_iterator<char>());
		data_string = std::regex_replace(data_string, std::regex("Iris-setosa"), "1");
		data_string = std::regex_replace(data_string, std::regex("Iris-versicolor"), "2");
		data_string = std::regex_replace(data_string, std::regex("Iris-virginica"), "3");

		std::ofstream out_stream(outputFile);
		out_stream << data_string;
			
	} catch(const io::error::no_digit& err) {
		std::cerr << "Error rewriting iris_data.csv" << std::endl;
		exit(EXIT_FAILURE);
	};
}

int main(int argc, char** argv){

	if(argc < 2) {
		std::cerr << "usage: " << argv[0] << " (input file err)" << std::endl; 
		exit(EXIT_FAILURE);
	};

	// !!! path from the executable position
	const char* iris_data = "../../data/iris_fix.csv";

	rewriteDataFile(iris_data, argv);
	
	// we define the matrix object and load data from the file, like this:
	dlib::matrix<double> data;
	std::ifstream file(iris_data);
	file >> data;
	std::cout << data << std::endl;

	
	
	return 0;
};
