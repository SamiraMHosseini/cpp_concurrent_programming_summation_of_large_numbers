#include <vector>
#include <thread>
#include <iostream>
#include <algorithm>

typedef unsigned long long ULLONG;

void sumNum(ULLONG& vectSum, ULLONG  start, ULLONG  end)
{

	for (ULLONG i = start; i <= end; ++i)
	{
		vectSum += i;
	}
}

ULLONG vectAccumulate(std::vector<ULLONG>& vect)
{
	ULLONG total{ 0 };
	for (const auto& item : vect)
	{
		total += item;
	}
	return total;
}
int main()
{
	constexpr int number_of_threads = 1000;                      //3  ,6 , 8 , 9 , 5 , 10000
	constexpr ULLONG  number_of_items = 1000 * 1000 * 1000;      //7 , 21 ,21 ,26, 10 ,1000 * 1000 * 1000

	constexpr ULLONG  step = number_of_items / number_of_threads;

	ULLONG  NUM = number_of_threads;

	if (number_of_items % number_of_threads != 0)
	{
		NUM = number_of_threads - 1;
	}

	ULLONG  counter = 1;
	size_t  index = 0;
	ULLONG  start = 0;
	ULLONG  end = 0;
	std::vector<std::thread> workers;
	std::vector<ULLONG > vectSum(number_of_threads, 0);

	//Assigning a task to a specific thread
	for (; index < NUM; ++index, counter += step)
	{
		start = counter;
		end = counter + step - 1;
		std::cout << start << "  , " << end << " , " << index << '\n';
		workers.emplace_back(sumNum, std::ref(vectSum.at(index)), start, end);


	}
	if (number_of_items % number_of_threads != 0)
	{
		std::cout << counter << "  , " << number_of_items << " , " << index << '\n';
		workers.emplace_back(sumNum, std::ref(vectSum.at(index)), counter, number_of_items);

	}

	//Waiting for the threads to join
	std::for_each(workers.begin(), workers.end(),

		[](std::thread& th) -> void
		{th.join(); }

	);

	const ULLONG  total = vectAccumulate(vectSum);

	std::cout << "total: " << total << "\n";

}


