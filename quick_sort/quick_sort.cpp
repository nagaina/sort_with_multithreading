#include "quick_sort.hpp"
#include <ctime>
#include <stack>

void Quick_sort::set_file(std::fstream& file)
{
	int n = 0;
	m_vector.clear();
	if (file.is_open())
	{
		while (file >> n)
		{
			m_vector.push_back(n);
			file.get();
		}
	}
	file.close();
}

int Quick_sort::partition(int left, int right, int pivot_index)
{
	swap(pivot_index,left);
	int i = left + 1;
	int j = left + 1;
	
	for ( ; j <= right; ++j)
	{
		if (m_vector[j] < m_vector[left])
		{
			swap(i,j);
			++i;
		}
	}

	swap(--i, left);
	return i;
	 
}

void Quick_sort::swap(int index1, int index2)
{	
	int temp = m_vector[index1];
	m_vector[index1] = m_vector[index2];
	m_vector[index2] = temp;
}

void Quick_sort::single_threaded()
{	
	quick_sort(0,m_vector.size()-1);
}

void Quick_sort::quick_sort(int left, int right)
{
	std::stack<int> stack;
	stack.push(left);
	stack.push(right);
	while (!stack.empty())
	{
		int r = stack.top();
		stack.pop();
		int l = stack.top();
		stack.pop();
		if (r - l < 2)
			continue;
		int pivot = (l + r)/2;
 		pivot = partition(l, r, pivot);
		stack.push(pivot + 1);
		stack.push(r );
		stack.push(l);
		stack.push(pivot);
	}
}

void Quick_sort::multi_threaded()
{
	if (max_threads == 1)
		return single_threaded();

	return multi_quick_sort(0 , m_vector.size() - 1 );
}

void Quick_sort::multi_quick_sort(int left, int right)
{
	int size = right - left;
	if (size <= 1)
		return;
	if (m_vector.size () / max_threads > size)
	{
		int pivot = (left + right)/2;
		pivot = partition(left, right, pivot);
		std::thread first (&Quick_sort::multi_quick_sort,this, left, pivot);
		std::thread second (&Quick_sort::multi_quick_sort,this, pivot+1, right);
		if (first.joinable())
			first.join();
		if (second.joinable())
			second.join();
	}
	quick_sort(left,right);
}
void Quick_sort::display()
{
	for (std::vector<int>::iterator it = m_vector.begin(); it != m_vector.end(); ++it)
	{
		std::cout<<*it<<",";
	}
	std::cout<<std::endl;
}
