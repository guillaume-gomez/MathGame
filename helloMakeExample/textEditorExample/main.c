#include "command.h"
#include "defs.h"

#include <iostream>


using namespace std;

int main()
{
	string text = "salut";

	cout << "salut" << endl;

	text = insert(text, "toi");

	cout << text << endl;

	text = duplicate(text);

	cout << text << endl;

	return 0;
}
