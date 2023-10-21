#pragma once

#include "Exception.h"

#include <fstream>
#include <random>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <cassert>

constexpr auto company_name_pos                       = 0;    // change
constexpr auto job_type_pos                           = 1;    // change
constexpr auto unit_pos                               = 2;    // change
constexpr auto price_pos                              = 3;    // change
constexpr auto date_pos                               = 4;    // change
constexpr auto amount_of_work_done_pos                = 5;    // change
constexpr auto random_string_size_range_begin         = 5;    // change 
constexpr auto random_string_size_rage_end            = 10;   // change 
constexpr auto random_price_range_begin               = 100;  // change 
constexpr auto random_price_range_end                 = 999;  // change 
constexpr auto random_year_range_begin                = 1989; // change 
constexpr auto random_year_range_end                  = 2023; // change 
constexpr auto random_month_range_begin               = 1;    // change 
constexpr auto random_month_range_end                 = 12;   // change 
constexpr auto random_day_range_begin                 = 1;    // change 
constexpr auto random_day_range_end                   = 30;   // change 
constexpr auto random_amount_of_data_range_begin      = 100;  // change 
constexpr auto random_amount_of_data_range_end        = 200;  // change 
constexpr auto random_amount_of_work_done_range_begin = 1;    // change 
constexpr auto random_amount_of_work_done_range_end   = 100;  // change 

class [[maybe_unused]] GenerateRandom {
public:
	// generate a random string of size 5-10
	static std::string companyName() {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution size(random_string_size_range_begin,
			                               random_string_size_rage_end);
		size_t string_size = size(rng);

		std::uniform_int_distribution character(65, 90); // A-Z
		std::string result;
		for (size_t i = 0; i <= string_size; ++i) result.push_back(char(character(rng)));
		return result + "_Inc.";
	}

	// generate random type of job
	static std::string jobType() {
		std::unordered_map<size_t, std::string> jobs{
			{1, "Fleet_Maintenance"}, {2, "Elecricity_Maintenance"},
			{3, "Pipe_Inspection"},   {4, "Wax_Removal_And_Prevention"},
			{5, "Sand_Washover"},     {6, "Pipe_String_Replacement"},
			{7, "Simple_Fishing"},    {8, "Water_Shutoff"},
			{9, "Minor_Failure_Treatment"}
		};

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution type(1, 9);

		return jobs[type(rng)];
	}

	// generate random unit of measurement
	static std::string currency() {
		std::unordered_map<size_t, std::string> currs{
			{1, "USD"},  {2, "EUR"},  {3, "JPY"},  {4, "GBP"},  {5, "CNY"},
			{6, "AUD"},  {7, "CAD"},  {8, "CHF"},  {9, "HKD"},  {10, "SGD"},
			{11, "SEK"}, {12, "KRW"}, {13, "NOK"}, {14, "NZD"}, {15, "INR"},
			{16, "MXN"}, {17, "TWD"}, {18, "ZAR"}, {19, "BRL"}, {20, "DKK"},
			{21, "PLN"}, {22, "THB"}, {23, "ILS"}, {24, "IDR"}, {25, "CZK"},
			{26, "AED"}, {27, "TRY"}, {28, "HUF"}, {29, "CLP"}, {30, "SAR"},
			{31, "PHP"}, {32, "MYR"}, {33, "COP"}, {34, "RUB"}, {35, "RON"},
			{36, "PEN"}, {37, "BHD"}, {38, "BGN"}, {39, "ARS"},
		};

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution unit(1, 39);

		return currs[unit(rng)];
	}

	// generate random number
	static std::string price() {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution range(random_price_range_begin,
			                                random_price_range_end);

		return std::to_string(range(rng));
	}

	// generate random string date
	static std::string date() {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution year(random_year_range_begin,
			                               random_year_range_end);
		std::uniform_int_distribution month(random_month_range_begin,
			                                random_month_range_end);
		std::uniform_int_distribution day(random_day_range_begin,
			                              random_day_range_end);

		int year_int = year(rng);
		int month_int = month(rng);
		int day_int = day(rng);

		std::string month_string         = std::to_string(month_int);
		std::string day_string           = std::to_string(day_int);
		if (month_int < 10) month_string = "0"   + std::to_string(month_int);
		if (day_int < 10)   day_string   = "0"   + std::to_string(day_int);

		return std::to_string(year(rng)) + "-" + month_string + "-" + day_string;
	}

	// generate random number
	static std::string work_done() {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution range(random_amount_of_work_done_range_begin,
			                                random_amount_of_work_done_range_end);

		return std::to_string(range(rng)) + "%";
	}

};

// function for string splicing
inline std::vector<std::string> splice(const std::string& str) {
	std::vector<std::string> res;
	std::string temp;

	for (size_t i = 0; i < str.size(); ++i) {
		if (str[i] != ' ') temp.push_back(str[i]);

		else if (temp.size() > 0) {
			res.push_back(temp);
			temp.clear();
		}
	}

	if (temp.size() > 0) res.push_back(temp);
	return res;
}

struct Repairs {
	std::string _companyName;
	std::string _jobType;
	std::string _unit;
	std::string _price;
	std::string _date;
	std::string _workDone;

	void write(std::ostream&) const;
	void read(std::istream&);
};

// operator overloading == for struct
inline bool operator == (const Repairs& mystruct1, const Repairs& mystruct2) {
	return mystruct1._companyName == mystruct2._companyName &&
		   mystruct1._jobType     == mystruct2._jobType     &&
		   mystruct1._unit        == mystruct2._unit        &&
		   mystruct1._price       == mystruct2._price       &&
		   mystruct1._date        == mystruct2._date        &&
		   mystruct1._workDone    == mystruct2._workDone;
}

// operator overloading != for struct
inline bool operator != (const Repairs& mystruct1, const Repairs& mystruct2) {
	return mystruct1._companyName != mystruct2._companyName &&
		   mystruct1._jobType     != mystruct2._jobType     &&
		   mystruct1._unit        != mystruct2._unit        &&
		   mystruct1._price       != mystruct2._price       &&
		   mystruct1._date        != mystruct2._date        &&
		   mystruct1._workDone    != mystruct2._workDone;
}

/// ---------------

// serialize string 
inline void writeString(std::ostream& out, const std::string& str)
{
	// write length of string (two bytes, little endian)
	assert(str.size() < 1 << 16);
	const size_t size = str.size();
	char buffer[2] = { (char)(size & 0xff), (char)(size >> 8 & 0xff) };
	out.write(buffer, sizeof buffer)
		// write string contents
		&& out.write(str.c_str(), size);
}

// read string
inline void readString(std::istream& in, std::string& str)
{
	// read length
	char buffer[2];
	if (!in.read(buffer, 2)) return; // failed
	const size_t size = (unsigned char)buffer[0] | (unsigned char)buffer[1] << 8;
	// allocate size
	str.resize(size);
	// read contents
	in.read(&str[0], size);
}

// write structure
inline void Repairs::write(std::ostream& out) const
{
	writeString(out, _companyName);
	writeString(out, _jobType);
	writeString(out, _unit);
	writeString(out, _price);
	writeString(out, _date);
	writeString(out, _workDone);
}

// read structure
inline void Repairs::read(std::istream& in)
{
	readString(in, _companyName);
	readString(in, _jobType);
	readString(in, _unit);
	readString(in, _price);
	readString(in, _date);
	readString(in, _workDone);
}
