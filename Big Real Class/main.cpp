#include "BigReal.h"

int main()
{
	BigReal n1("-2333333333339.1134322222222292");
	BigReal n2("+11.9000000000000000000000000000000001");
	cout << "n2 = " << n2 << endl;
	BigReal n3 = n1 + n2;
	cout << n1 << " + " << n2 << " = " << n3 << endl;
	n3 = n3 + BigReal(0.1);
	cout << "n3 = " << n3 << endl;
	return 0;
}
