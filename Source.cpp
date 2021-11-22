#include "complex.h"
#include <iostream>

using namespace std;

int main()
{
	complex c1(2, 1);
	complex c2(4, 0);

	cout << "c1 = " << c1 << endl;
	cout << "c2 = " << c2 << endl;

	cout << "c1 + c2 = " << c1 + c2 << endl;
	cout << "c1 - c2 = " << c1 - c2 << endl;
	cout << "c1 * c2 = " << c1 * c2 << endl;
	cout << " c1 / 2 = " << c1 / 2 << endl;

	cout << "conj(c1) = " << conj(c1) << endl;
	cout << "norm(c1) = " << norm(c1) << endl;
	cout << "polar(10, 4) = " << polar(10, 4) << endl;

	cout << "(c1 += c2) = " << (c1 += c2) << endl;

	cout << "(c1 == c2) = ";
	(c1 == c2) ? cout << "true" : cout << "false";
	cout << endl;
	cout << "(c1 != c2) = ";
	(c1 != c2) ? cout << "true" : cout << "false";
	cout << endl;
	cout << "+c2 = " << +c2 << endl;
	cout << "-c2 = " << -c2 << endl;

	cout << "(c2 - 2) = " << (c2 - 2) << endl;
	cout << "(5 + c2) = " << (5 + c2) << endl;

	return 0;
}