#pragma once

#ifndef PART2_H
#define PART2_H

#include "Data2.h"

class Part2 {
public:

	// create file with user input
	void createFile(const std::string&);

	// add data to file
	void addData(const std::string&);

	// delete data from file 
	void deleteData(const std::string&, const Repairs&);

	// change data in a file
	void changeDate(const std::string&, const Repairs&, const Repairs&);

	// copy data to a txt file
	void copytoTXT(const std::string&, const std::string&);

	// search by company name 
	void searchByName(const std::string&, 
		              const std::string&, 
		              const std::string&);

	// search by job type
	void searchByJobType(const std::string&, 
		                 const std::string&, 
		                 const std::string&);

	// search by date
	void searchByDate(const std::string&, 
		              const std::string&, 
		              const std::string&);

	// search by all parameters
	void search(const std::string&,
		        const std::string&,
		        const std::string&);

private:
	// utility function for entering data to file from keyboard
	void inputDataToFile(std::ofstream&);

	// helper function for printing a table
	void printTable(const std::vector<Repairs>&, std::ofstream&);

	// field for controlling amount of structures 
	// is needed for correct string serialization
	size_t _datasize = 0;
};

#endif
