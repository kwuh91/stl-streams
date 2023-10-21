#pragma once

#include "Part1.h"

class Part1Menu {
public:
	// main run method
	void run() {
		std::cout << "Choose createData variation(1/2): " << std::endl;
		size_t createDataChoice;
		std::cin >> createDataChoice;

		std::cout << "Enter file path(0 for default): " << std::endl;
		std::string filepath;
		std::cin >> filepath;
		bool usedefualtpath = false;

		bool usedefualtsep = false;
		char separator;
		if (filepath == "0") usedefualtpath = true;
		else {
			std::cout << "Enter separator(0 for default): " << std::endl;
			std::cin >> separator;
			if (separator == '0') usedefualtsep = true;
		}

		switch (createDataChoice) {
			case 1: {
				if (usedefualtpath && usedefualtsep) createData1();
				else if (!usedefualtpath && usedefualtsep) createData1(filepath);
				else if (!usedefualtpath && !usedefualtsep) createData1(filepath, separator);
				break;
			}
			case 2: {
				if (usedefualtpath && usedefualtsep) createData2();
				else if (!usedefualtpath && usedefualtsep) createData2(filepath);
				else if (!usedefualtpath && !usedefualtsep) createData2(filepath, separator);
				break;
			}
			default: {
				std::cout << "Invalid input" << std::endl;
				exit(0);
			}
		}

		std::cout << "Choose loadData variation(1/2): " << std::endl;
		size_t loadDataChoice;
		std::cin >> loadDataChoice;

		std::ifstream myfile;
		if (usedefualtpath) myfile.open("file.txt");
		else myfile.open(filepath);

		cont_type mycont;

		switch (loadDataChoice) {
			case 1: {
				loadData1(myfile, mycont);
				break;
			}
			case 2: {
				loadData2(myfile, mycont);
				break;
			}
			default: {
				std::cout << "Invalid input" << std::endl;
				exit(0);
			}
		}

		size_t modifyChoice;
		bool modifyFlag = true;
		while (modifyFlag) {
			std::cout << "Choose Modify variation(1-4)\n0 - exit: " << std::endl;
			std::cin >> modifyChoice;

			size_t funcChoice;
			if (modifyChoice != 0 && (modifyChoice == 1 || modifyChoice == 2)) {
				std::cout << "Choose function(1-20): " << std::endl;
				std::cin >> funcChoice;
				if (funcChoice < 1 || funcChoice > 20) {
					std::cout << "Invalid input" << std::endl;
					break;
				}
			}

			std::string resfilepath;
			bool usedefualtrespath = false;
			if (modifyChoice == 4 && usedefualtpath) {
				std::cout << "Enter file path for result(0 for default): " << std::endl;
				std::cin >> resfilepath;
				if (filepath == "0") usedefualtrespath = true;
			}

			switch (modifyChoice) {
				case 0: {
					modifyFlag = false;
					break;
				}
				case 1: {
					modify1(mycont, funcChoice);
					break;
				}
				case 2: {
					modify2(mycont.begin(), mycont.end(), funcChoice);
					break;
				}
				case 3: {
					modify3(mycont, [](const int& el) { \
						if (el >= 0) return std::to_string(50) + "\n"; \
						else return std::to_string(el) + "\n"; \
							;});
					break;
				}
				case 4: {
					if (usedefualtpath && usedefualtrespath) {
						modify4([](const value_type& el) { \
							if (el >= 0) return std::to_string(50) + "\n"; \
							else return std::to_string(el) + "\n"; \
								;});
					}
					else if (!usedefualtpath && usedefualtrespath) {
						modify4([](const value_type& el) { \
							if (el >= 0) return std::to_string(50) + "\n"; \
							else return std::to_string(el) + "\n"; \
								;}, filepath);
					}
					else if (!usedefualtpath && !usedefualtrespath) {
						modify4([](const value_type& el) { \
							if (el >= 0) return std::to_string(50) + "\n"; \
							else return std::to_string(el) + "\n"; \
								;}, filepath, resfilepath);
					}
					break;
				}
				default: {
					std::cout << "Invalid input" << std::endl;
					break;
				}
			}
		}

		std::cout << "Choose outputResult variation(1/2): " << std::endl;
		size_t outputResultChoice;
		std::cin >> outputResultChoice;

		std::ofstream mynewfile;

		std::cout << "Enter file path for output(0 for default): " << std::endl;
		std::cin >> filepath;
		if (filepath == "0") mynewfile.open("newfile.txt");
		else mynewfile.open(filepath);

		std::cout << "Enter separator(0 for default): " << std::endl;
		std::cin >> separator;
		if (separator == '0') usedefualtsep = true;

		switch (outputResultChoice) {
			case 1: {
				if (usedefualtsep)  outputResult1(mynewfile, mycont);
				if (!usedefualtsep) outputResult1(mynewfile, mycont, separator);
				break;
			}
			case 2: {
				if (usedefualtsep)  outputResult2(mynewfile, mycont);
				if (!usedefualtsep) outputResult2(mynewfile, mycont, separator);
				break;
			}
			default: {
				std::cout << "Invalid input" << std::endl;
				exit(0);
			}
		}

		myfile.close();
		mynewfile.close();
	}
};
