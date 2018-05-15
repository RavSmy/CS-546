//Ravela Smyth -- LAB 2 -- CS 546 

#include <iostream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) {
	short month, day, year;
	short hexDate = 0x0000;

	cout << "Enter a month, day, and year between 1-1-1980 and 12-31-2107 without the dashes: " << endl;

	bool valid = false;
	cin >> month >> day >> year;
	if (month > 12 || month < 1 || day > 31 || day < 1 || year < 1980 || year > 2107) {
		cout << "Bad input!" << endl;
		system("PAUSE");
		exit(0);
	}
	year = year - 1980;

	__asm {
		mov	ax, hexDate;
		mov	bx, day;
		or ax, bx;

		ror	ax, 5;

		mov	bx, month;
		or ax, bx;

		ror	ax, 4;

		mov	bx, year;
		or ax, bx;

		ror	ax, 7;

		mov hexDate, ax;
	}

	cout << hex << hexDate << endl;
	system("PAUSE");
	return 0;
}
