#ifndef _quick_sort_hpp_
#define _quick_sort_hpp_

#include <fstream>
#include <thread>
#include <cstdlib>
#include <vector>
#include <iostream>

class Quick_sort
{
public:
	void set_file(std::fstream&);
	void single_threaded();
	void multi_threaded();
	void display();
private:
	void multi_quick_sort(int, int);
	void quick_sort(int, int);
	int partition(int , int, int);
	void swap(int, int);

	std::vector<int> m_vector;
	int max_threads = std::thread::hardware_concurrency();	
};

#endif
