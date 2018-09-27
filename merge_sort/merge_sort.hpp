#ifndef _merge_sort_hpp_
#define _merge_sort_hpp_

#include <thread>
#include <vector>
#include <fstream>

class Merge_sort
{
public:
	void set_file(std::fstream&);
	void single_threaded();
	void multi_threaded();
	void display();	
private:
	void merge(int, int, int);
	void merge_sort(int, int);
	void multi_merge_sort(int,int);
	
	std::vector<int> m_vector;
	int max_threads = std::thread::hardware_concurrency();
};

#endif
