#include"fastCppCsvParser/csv.h"

#include <bits/utility.h>
#include <cstddef>
#include<iostream>
#include <iterator>
#include<vector>
#include<string>
#include<tuple>
#include<fstream>
#include<regex>

// ./fast-csv ../../data/iris.data

/// for only 4 columns.... with the double** data
// ./fast-csv ../../data/iris.csv

// using RowType = std::tuple<double, double, double, double, std::string>;
using RowType = std::tuple<double, double, double, double, double>;

template<std::size_t... Idx, typename T, typename R>
bool readRowHelp(std::index_sequence<Idx...>, T& row, R& r) {
	return r.read_row(std::get<Idx>(row)...);
};


template<std::size_t... Idx, typename T>
void fillValues(std::index_sequence<Idx...>, T& row, std::vector<double>& data){
	data.insert(data.end(), {std::get<Idx>(row)...});
};

template<typename T>
std::vector<double> extractCSVDatas(T& fileName){
// std::vector<double> extractCSVDatas(const char* fileName){
	const uint32_t columns_num = 5;
	const char* csv_filename = fileName;
	io::CSVReader<columns_num> csv_reader(csv_filename);

	std::vector<double> categorical_column;
	std::vector<double> values;

	RowType row;

	// Open the file
	std::ifstream file(csv_filename);
    	std::string line;	
    	int line_count = 0;
	int track = 0;
		
	bool done = true;

	try{
		while(true){

			// the way to get the end of the file
			// csv_reader crash at the end of the file if not stopped bf
			if (std::getline(file, line)) {
				line_count++;
			} else {
				break;
			}

			// stay one row before line_count
			if(track < line_count - 1){
				track++;
				done = readRowHelp(std::make_index_sequence<std::tuple_size<RowType>::value>{}, row, csv_reader);

				categorical_column.push_back(std::get<4>(row));
				fillValues(std::make_index_sequence<columns_num -1>{}, row, values);
			};
		};
	} catch(const io::error::no_digit& err){
		file.close();
		std::cerr << "In err: " << err.what() << std::endl;
		exit(EXIT_FAILURE);
	};

	file.close();

	// return values; // contains all the values
	return categorical_column; // contains the 5fth column values
}



int main(int argc, char **argv) {

	if(argc < 2){
		std::cerr << "usage: " << argv[0] << " (file with inputs/independent variables)" << std::endl;	
		exit(EXIT_FAILURE);
	}


	const char* iris_data = "../../data/iris_fix.csv"; 
	
	try{
		// convert string datas to number as machineLearning lib does not read strings
		std::ifstream data_stream(argv[1]); 
		std::string data_string((std::istreambuf_iterator<char>(data_stream)), std::istreambuf_iterator<char>());

		data_string = std::regex_replace(data_string, std::regex("Iris-setosa"), "1");
		data_string = std::regex_replace(data_string, std::regex("Iris-versicolor"), "2");
		data_string = std::regex_replace(data_string, std::regex("Iris-virginica"), "3");



		std::ofstream out_stream(iris_data);
		out_stream << data_string;

	} catch(const io::error::no_digit& err){
		std::cerr << "In err: " << err.what() << std::endl;
		exit(EXIT_FAILURE);
	} 

	// extract datas from the previously generated file
	std::vector<double> values = extractCSVDatas(iris_data);
	
	for(auto v:values){
		std::cout << "Value: " << v << std::endl;
	}

	return 0;	
};
