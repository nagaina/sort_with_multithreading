#include "merge_sort.hpp"
#include <iostream>

void Merge_sort::set_file(std::fstream& file)
{
	int n = 0;
	m_vector.clear();
	if (file.is_open())
	{
		while ( file >> n)
		{
			m_vector.push_back(n);
			file.get();
		}
	}
	file.close();	
}

//
//iterative
//

void Merge_sort::single_threaded()
{
	merge_sort(0,m_vector.size() - 1);
}

void Merge_sort::merge_sort(int left, int right)
{
	int size = right- left + 1;
	int curr_size = 0;
	int left_start = 0;

	for (curr_size = left + 1; curr_size <=size - 1; curr_size = 2*curr_size)
		for (left_start = left; left_start < size - 1; left_start += 2*curr_size)
		{
		
			int mid = left_start + curr_size - 1;
			int right_end = std::min(left_start +2*curr_size -1, size - 1 );
			merge(left_start,right_end, mid);
		}
}

void Merge_sort::display()
{
	for (std::vector<int>::iterator it = m_vector.begin(); it != m_vector.end(); ++it)
		std::cout<<*it<<" ";
	std::cout<<std::endl;	
}

void Merge_sort::merge(int left, int right, int mid)
{
	int temp[right - left + 1];
	int k = 0;
	int i = left;
	int j = mid + 1; 
	while (i <= mid && j <= right)
	{
		if (m_vector[i] > m_vector[j])
			temp[k++] = m_vector[j++];
		else
			temp[k++] = m_vector[i++];
	}

	for (; i <= mid; ++i)
		temp[k++] = m_vector[i];

	for (; j <= right; ++j)
		temp[k++] = m_vector[j];

	for ( i = left, j = 0; i <= right && j < right - left +1 ; ++i, ++j)
	{
		m_vector[i] = temp[j];
	}	
}

void Merge_sort::multi_threaded()
{
	if (max_threads == 1)
		single_threaded();
	else
	{	
		multi_merge_sort(0, m_vector.size() -1);
	}
}

void Merge_sort::multi_merge_sort(int left, int right)
{
	int mid = 0;
	int size = right - left +1;
	if (size <= 1)
		return;

	mid =  (right + left)/2;
	if (size > m_vector.size() / max_threads)
	{
			std::thread first (&Merge_sort::multi_merge_sort,this, left, mid);
			std::thread second (&Merge_sort::multi_merge_sort,this, mid+1, right);
			if (first.joinable())
				first.join();
			if (second.joinable())
				second.join();
			merge(left,right, mid);
	}
	else
		merge_sort(left,right);
}
