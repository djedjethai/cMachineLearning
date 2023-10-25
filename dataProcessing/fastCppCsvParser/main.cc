#include"fastCppCsvParser/csv.h"

#include <bits/utility.h>
#include <cstddef>
#include<iostream>
#include<vector>
#include<string>
#include<tuple>
#include<fstream>

// ./fast-csv ../../data/iris.data

/// for only 4 columns.... with the double** data
// ./fast-csv ../../data/iris.csv

using RowType = std::tuple<double, double, double, double, std::string>;

template<std::size_t... Idx, typename T, typename R>
bool readRowHelp(std::index_sequence<Idx...>, T& row, R& r) {
	return r.read_row(std::get<Idx>(row)...);
};


template<std::size_t... Idx, typename T>
void fillValues(std::index_sequence<Idx...>, T& row, std::vector<double>& data){
	data.insert(data.end(), {std::get<Idx>(row)...});
};



int main(int argc, char **argv) {

	if(argc < 2){
		std::cerr << "usage: " << argv[0] << " (file with inputs/independent variables)" << std::endl;	
		exit(EXIT_FAILURE);
	}

	const uint32_t columns_num = 5;
	const char* csv_filename = argv[1];
	io::CSVReader<columns_num> csv_reader(csv_filename);

	std::vector<std::string> categorical_column;
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
	};

	file.close();

	for(auto v:values){
		std::cout << "Value: " << v << std::endl;
	}

	return 0;

	// WORKS
	// double** data = new double*[151];
	// for (int i = 0; i < 151; ++i) {
    	// 	data[i] = new double[4];
	// }


	// // const uint32_t columns_num = 5;
	// const uint32_t columns_num = 4;
	// io::CSVReader<columns_num> csv_reader(argv[1]);

	// try{
	// 	bool done = true;
	// 	double a; double b; double c; double d; 
	// 	int n = 0;
	// 	while (done){
	// 			
	// 		// here the f**.. done always return true
	// 		done =csv_reader.read_row(a, b, c, d); 

	// 		if(n == 149){
	// 			done = false;
	// 		}
	// 	    		
	// 		printf("time elapse: %i\n", n); 
	// 		printf("time done: %d\n", done); 
	// 	
	// 	    	data[n][0] = a;
	// 	    	data[n][1] = b;
	// 	    	data[n][2] = c;
	// 	    	data[n][3] = d;
	// 	
	// 	    	n++;
	// 	
	// 	}
	// } catch(const io::error::no_digit& err) {

	// 	std::cerr << "In err: " << err.what() << std::endl;
	// 	// std::cout << "dealocate data in the catch " << std::endl;
	// 	// Deallocate the inner arrays (columns) first
	// 	for (int i = 0; i < 151; ++i) {
    	// 		delete[] data[i];
	// 	}

	// 	// Deallocate the outer array (rows)
	// 	delete[] data;
	// }

	// // see the data
	// for(int i{0}; i < 30; i++){
	// 	std::cout << "dat col 2: " << data[i][2] << std::endl; 
	// }


	// // Deallocate the inner arrays (rows) first
	// for (int i = 0; i < 151; ++i) {
    	// 	delete[] data[i];
	// }

	// // Deallocate the outer array (rows)
	// delete[] data;

};
