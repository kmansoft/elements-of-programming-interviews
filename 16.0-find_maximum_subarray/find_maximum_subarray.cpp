#include <vector>
#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v) {
	out << "[";
	for (int i = 0; i < v.size(); i += 1) {
		if (i != 0) {
			out << ", ";
		}
		out << v[i];
	}
	out << "]";

	return out;
}

int FindMaximumSubarray(const std::vector<int>& v) {
	int max_end = 0, max_sum = 0;

	for (const int a : v) {
		max_end = std::max(a, a + max_end);
		max_sum = std::max(max_sum, max_end);
	}

	return max_sum;
}

void test(const std::initializer_list<int>& list) {
	const std::vector<int> v(list);
	const int max = FindMaximumSubarray(v);

	std::cout << v << " -> " << max << std::endl;
}

int main() {

	test({5, -20, -21, 1, 2, 3});

    return 0;
}
