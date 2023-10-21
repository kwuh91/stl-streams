#include "Part1menu.h"
#include "Part2.h"

int main() {
	//Part1Menu obj1;
	//obj1.run();
	
	Part2 obj;
	obj.createFile("part2test.dat");
	obj.addData("part2test.dat");

	Repairs rep;
	rep._companyName = "cname1";
	rep._jobType = "jobtype1";
	rep._unit = "RUB";
	rep._price = "5000";
	rep._date = "1992-01-28";
	rep._workDone = "45%";

	obj.deleteData("part2test.dat", rep);

	Repairs rep1;
	rep1._companyName = "cname4";
	rep1._jobType = "jobtype4";
	rep1._unit = "JPY";
	rep1._price = "423";
	rep1._date = "2000-01-01";
	rep1._workDone = "100%";

	obj.changeDate("part2test.dat", rep, rep1);
	
	obj.search("part2test.dat", "searchresults.dat", "cname3");

	obj.copytoTXT("part2test.dat", "part2test.txt");

	return 0;
}

//cname1 jobtype1 RUB 5000 1992-01-28 45%
//cname2 jobtype2 USD 49 2023-01-01 88%
//cname3 jobtype3 EUR 231 2023-01-01 99%
//cname4 jobtype4 JPY 423 2000-01-01 100%
