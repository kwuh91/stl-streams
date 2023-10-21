#include "Part2.h"

// create file with user input
void Part2::createFile(const std::string& name) {
	std::filesystem::path p = std::filesystem::current_path();
	std::filesystem::create_directories(p / "files");
	std::ofstream file(p / ("files/" + name), std::ios_base::binary);
	if (!file.is_open())
		throw Exception("Unable to create file at path: " + p.generic_string() + "/files/" + name);

	std::cout << "To write data by hand enter \"user\""       << std::endl;
	std::cout << "To generate data randomly enter \"random\"" << std::endl;
	std::string input;
	Repairs temp_struct;
	std::vector<Repairs> temp_struct_vec;
	std::cin >> input;
	if (input == "random") {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution size(random_amount_of_data_range_begin,
			                               random_amount_of_data_range_end);
		size_t amount_of_data = size(rng);
		_datasize = amount_of_data;
		for (size_t i = 0; i < amount_of_data; ++i) {
			temp_struct._companyName = GenerateRandom::companyName();
			temp_struct._jobType     = GenerateRandom::jobType();
			temp_struct._unit        = GenerateRandom::currency();
			temp_struct._price       = GenerateRandom::price();
			temp_struct._date        = GenerateRandom::date();
			temp_struct._workDone    = GenerateRandom::work_done();

			temp_struct_vec.push_back(temp_struct);
		}
		
		for (const Repairs& rep : temp_struct_vec) rep.write(file);
	}
	else if (input == "user") {
		std::cout.flush();
		std::cin.ignore();
		inputDataToFile(file);
	}
	else throw Exception("Invalid input (" + input + ")");

	file.close();
}

// add data to file
void Part2::addData(const std::string& name) {
	std::filesystem::path p = std::filesystem::current_path();
	std::filesystem::create_directories(p / "files");

	std::ofstream file(p / ("files/" + name),
		                                     std::ios::binary   |
		                                     std::ios_base::app);
	if (!file.is_open())
		throw Exception("Unable to open file at path: " + p.generic_string() + "/files/" + name);

	inputDataToFile(file);
	file.close();
}

// utility function for entering data to file from keyboard
void Part2::inputDataToFile(std::ofstream& file) {
	std::cout << "Enter data(company name, type of job, unit of measurement, price, execution date, amount of work done)" << std::endl;
	std::cout << "Enter date as YEAR-MONTH-DAY(2023-01-01)"                                                               << std::endl;

	std::vector<Repairs> temp_struct_vec;
	while (true) {
		std::string cname;
		std::string jobtype;
		std::string unit;
		std::string price;
		std::string date;
		std::string workdone;

		std::string whole_string;
		std::getline(std::cin, whole_string);
		if (whole_string.empty()) break;

		std::vector<std::string> spliced_string = splice(whole_string);
		Repairs temp_struct;

		temp_struct._companyName = spliced_string[company_name_pos];
		temp_struct._jobType     = spliced_string[job_type_pos];
		temp_struct._unit        = spliced_string[unit_pos];
		temp_struct._price       = spliced_string[price_pos];
		temp_struct._date        = spliced_string[date_pos];
		temp_struct._workDone    = spliced_string[amount_of_work_done_pos];

		temp_struct_vec.push_back(temp_struct);
		_datasize++;
	}

	for (const Repairs& rep : temp_struct_vec) rep.write(file);
}

// delete data from file 
void Part2::deleteData(const std::string& name, const Repairs& struct_for_removal) {
	std::filesystem::path p = std::filesystem::current_path();

	std::ifstream file(p / ("files/" + name), std::ios::binary);
	if (!file.is_open())
		throw Exception("Unable to open file at path: " + p.generic_string() + "/files/" + name);

	std::ofstream tempfile(p / "files/tempfile.dat", std::ios::binary);
	if (!tempfile.is_open())
		throw Exception("Unable to create file at path: " + p.generic_string() + "/files/tempfile.dat");

	std::vector<Repairs> buffer(_datasize);

	for (Repairs& rep : buffer) rep.read(file);

	for (const Repairs& rep : buffer) {
		if (rep != struct_for_removal)
			rep.write(tempfile);
	}

	file.close();
	tempfile.close();

	std::filesystem::rename(p / "files/tempfile.dat", p / ("files/" + name)); 
}

// change data in a file
void Part2::changeDate(const std::string& name, const Repairs& struct_to_change, 
	                                            const Repairs& to_this_struct) {
	std::filesystem::path p = std::filesystem::current_path();

	std::ifstream file(p / ("files/" + name), std::ios::binary);
	if (!file.is_open())
		throw Exception("Unable to open file at path: " + p.generic_string() + "/files/" + name);

	std::ofstream tempfile(p / "files/tempfile.dat", std::ios::binary);
	if (!tempfile.is_open())
		throw Exception("Unable to create file at path: " + p.generic_string() + "/files/tempfile.dat");

	std::vector<Repairs> buffer(_datasize);

	for (Repairs& rep : buffer) rep.read(file);

	for (const Repairs& rep : buffer) {
		if (rep == struct_to_change) to_this_struct.write(tempfile);
		else rep.write(tempfile);
	}

	file.close();
	tempfile.close();

	std::filesystem::rename(p / "files/tempfile.dat", p / ("files/" + name));
}

// search by company name 
void Part2::searchByName(const std::string& name, 
	                     const std::string& resultfilename, 
	                     const std::string& cname) {
	std::filesystem::path p = std::filesystem::current_path();

	std::ifstream file(p / ("files/" + name), std::ios::binary);
	if (!file.is_open())
		throw Exception("Unable to open file at path: " + p.generic_string() + "/files/" + name);

	std::ofstream resfile(p / ("files/" + resultfilename), std::ios::binary);
	if (!resfile.is_open())
		throw Exception("Unable to create file at path: " + p.generic_string() + "/files/" + resultfilename);

	std::vector<Repairs> buffer(_datasize);

	for (Repairs& rep : buffer) rep.read(file);

	for (const Repairs& rep : buffer) {
		if (rep._companyName == cname) rep.write(resfile);
	}
}

// search by job type
void Part2::searchByJobType(const std::string& name, 
	                        const std::string& resultfilename,
	                        const std::string& jtype) {
	std::filesystem::path p = std::filesystem::current_path();

	std::ifstream file(p / ("files/" + name), std::ios::binary);
	if (!file.is_open())
		throw Exception("Unable to open file at path: " + p.generic_string() + "/files/" + name);

	std::ofstream resfile(p / ("files/" + resultfilename), std::ios::binary);
	if (!resfile.is_open())
		throw Exception("Unable to create file at path: " + p.generic_string() + "/files/" + resultfilename);

	std::vector<Repairs> buffer(_datasize);

	for (Repairs& rep : buffer) rep.read(file);

	for (const Repairs& rep : buffer) {
		if (rep._jobType == jtype) rep.write(resfile);
	}
}

// search by date
void Part2::searchByDate(const std::string& name, 
	                     const std::string& resultfilename,
	                     const std::string& date) {
	std::filesystem::path p = std::filesystem::current_path();

	std::ifstream file(p / ("files/" + name), std::ios::binary);
	if (!file.is_open())
		throw Exception("Unable to open file at path: " + p.generic_string() + "/files/" + name);

	std::ofstream resfile(p / ("files/" + resultfilename), std::ios::binary);
	if (!resfile.is_open())
		throw Exception("Unable to create file at path: " + p.generic_string() + "/files/" + resultfilename);

	std::vector<Repairs> buffer(_datasize);

	for (Repairs& rep : buffer) rep.read(file);

	for (const Repairs& rep : buffer) {
		if (rep._date == date) rep.write(resfile);
	}
}

// ultimate search
void Part2::search(const std::string& name, 
	               const std::string& resultfilename,
	               const std::string& what) {
	std::filesystem::path p = std::filesystem::current_path();

	std::ifstream file(p / ("files/" + name), std::ios::binary);
	if (!file.is_open())
		throw Exception("Unable to open file at path: " + p.generic_string() + "/files/" + name);

	std::ofstream resfile(p / ("files/" + resultfilename), std::ios::binary);
	if (!resfile.is_open())
		throw Exception("Unable to create file at path: " + p.generic_string() + "/files/" + resultfilename);

	std::vector<Repairs> buffer(_datasize);

	for (Repairs& rep : buffer) rep.read(file);

	std::cout << "By what parameter would you like to search?" << std::endl;
	std::cout << "1 - company name\n2 - type of job\n3 - unit of measurement\n4 - price\n5 - date\n6 - amount of work done\n";

	size_t choice;
	std::cin >> choice;
	std::cout.flush();
	std::cin.ignore();

	switch (choice) {
		case 1: {
			for (const Repairs& rep : buffer) {
				if (rep._companyName == what) rep.write(resfile);
			}
			break;
		}
		case 2: {
			for (const Repairs& rep : buffer) {
				if (rep._jobType == what) rep.write(resfile);
			}
			break;
		}
		case 3: {
			for (const Repairs& rep : buffer) {
				if (rep._unit == what) rep.write(resfile);
			}
			break;
		}
		case 4: {
			for (const Repairs& rep : buffer) {
				if (rep._price == what) rep.write(resfile);
			}
			break;
		}
		case 5: {
			for (const Repairs& rep : buffer) {
				if (rep._date == what) rep.write(resfile);
			}
			break;
		}
		case 6: {
			for (const Repairs& rep : buffer) {
				if (rep._workDone == what) rep.write(resfile);
			}
			break;
		}
		default: {
			std::cout << "Invalid input" << std::endl;
			return;
		}
	}
}

// helper function for printing a table
void Part2::printTable(const std::vector<Repairs>& reps, std::ofstream& out) {
	struct {
		int width;
		std::string header;
	} columns[] = { { 20, "Company name" }, { 30, "Type of job" }, { 5, "Unit" },
					{ 10, "Price" }, { 15, "Date" }, {20, "Amount of work done"}};

	for (auto& col : columns) out << std::setw(col.width) << col.header << " | ";
	out << "\n" << std::setfill('-');
	for (auto& col : columns) out << std::setw(col.width) << "" << "-+-";
	out << "\n" << std::setfill(' ');

	for (const Repairs& rep : reps) {
		out << std::setw(columns[0].width) << rep._companyName << " | "
			<< std::setw(columns[1].width) << rep._jobType     << " | "
			<< std::setw(columns[2].width) << rep._unit        << " | "
			<< std::setw(columns[3].width) << rep._price       << " | "
			<< std::setw(columns[4].width) << rep._date        << " |" 
			<< std::setw(columns[5].width) << rep._workDone    << " |" << "\n";
	}

	for (auto& col : columns) out << std::setw(col.width) << std::setfill('-') << "" << "-+-";
	out << "\n";
}

// copy data to a txt file
void Part2::copytoTXT(const std::string& name_binary, const std::string& name_txt) {
	std::filesystem::path p = std::filesystem::current_path();

	std::ifstream source(p / ("files/" + name_binary), std::ios::binary);
	if (!source.is_open())
		throw Exception("Unable to open file at path: " + p.generic_string() + "/files/" + name_binary);

	std::ofstream dest(p / ("files/" + name_txt));
	if (!dest.is_open())
		throw Exception("Unable to open file at path: " + p.generic_string() + "/files/" + name_txt);

	std::vector<Repairs> buffer(_datasize);

	for (Repairs& rep : buffer) rep.read(source);

	printTable(buffer, dest);
}
