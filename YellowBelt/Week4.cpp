#include <iostream>
#include <numeric>
#include <utility>
#include <iterator>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>
#include <set>
#include <map>


uint32_t GetSeedByCurrentTime() {
	using namespace std::chrono;

	time_point<steady_clock> tp = steady_clock::now();
	nanoseconds ns = tp.time_since_epoch();
	milliseconds ms = duration_cast<milliseconds>(ns);
	int64_t seed_ll = ms.count();
	uint32_t seed = static_cast<uint32_t>(seed_ll);

	return seed;
}

size_t GetRandomVectorSize() {
	std::default_random_engine dre { GetSeedByCurrentTime() };
	std::uniform_int_distribution uid { 10, 30 };

	return static_cast<size_t>(uid(dre));
}

bool f(const int& num) {
	return (num & 0x1) == 0;
}

int main() {
	/*std::default_random_engine dre { GetSeedByCurrentTime() };
	std::uniform_int_distribution uid { 20, 30 };

	std::vector<int> VInt(GetRandomVectorSize());
	for (auto& x : VInt) {
		x = uid(dre);
		std::cout << x << " ";
	}
	
	std::cout << std::endl;

	//std::sort(std::begin(VInt), std::end(VInt));
	std::partition(std::begin(VInt), std::end(VInt), IsEven);

	for (const auto& x : VInt) {
		std::cout << x << " ";
	}*/

	using namespace std;

	/*vector<int> vec;
	auto vector_begin = begin(vec);
	auto vector_end = end(vec);

	string str;
	auto string_begin = begin(str);
	auto string_end = end(str);

	set<int> s;
	auto set_begin = begin(s);
	auto set_end = end(s);*/

	////////////

	set<int> s = { 1, 2, 3, 4 };
	vector<int> v;
	

	auto it = remove_if(begin(s), end(s),
						[](int x) { return !f(x); });
	copy(it, end(s), back_inserter(v));



	return 0;
}
