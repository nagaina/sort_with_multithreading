#include "quick_sort.hpp"

int main()
{
	std::fstream file("integers.txt");
	Quick_sort q;
	q.set_file(file);
	q.single_threaded();
	q.display();
	std::cout<<"multi theaded sort"<<std::endl;
	q.multi_threaded();
	q.display();
}
