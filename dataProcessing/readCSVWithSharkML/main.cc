#include"fastCppCsvParser/csv.h"
#include <cstddef>
#include<shark/Data/Csv.h>
#include<shark/Data/Dataset.h>
		  
#include <ios>
#include<iostream>
#include <istream>
#include <iterator>
#include<string>
#include<fstream>
#include<vector>
#include<regex>


// using namespace std;

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
	
	// import datas from the file to the dataset
	shark::ClassificationDataset dataset;
	shark::importCSV(dataset, iris_data, shark::LAST_COLUMN);

	// Also, we can also print some statistics about the imported dataset, as follows:
	std::size_t classes = shark::numberOfClasses(dataset);
	std::cout << "Number of classes " << classes << std::endl;
	std::vector<std::size_t> sizes = shark::classSizes(dataset);
	std::cout << "Class size: " << std::endl;
	for(auto cs: sizes) {
		std::cout << cs << std::endl;
	};
	std::size_t dim = shark::inputDimension(dataset);
	std::cout << "Input dimenssion: " << dim << std::endl;


	return 0;
};
