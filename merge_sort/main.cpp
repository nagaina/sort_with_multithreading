#include <iostream>
#include "merge_sort.hpp"

int main()
{
	std::fstream file("integers.txt");
	Merge_sort m;
	m.set_file(file);
	m.multi_threaded();
	m.display();
}
