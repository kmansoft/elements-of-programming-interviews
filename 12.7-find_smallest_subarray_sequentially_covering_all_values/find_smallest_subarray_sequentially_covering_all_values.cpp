#include <string>
#include <unordered_map>
#include <vector>
#include <limits>
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

struct Sub {
	int start, end;
};

Sub FindSmallestSequentiallyCoveringSubset(
	const std::vector<std::string>& paragraph,
	const std::vector<std::string>& keywords) {

	std::unordered_map<std::string, int> keyword_to_idx;
	for (int i = 0; i < keywords.size(); i += 1) {
		keyword_to_idx.emplace(keywords[i], i);
	}

	std::vector<int> latest_occurrence(keywords.size(), -1);
	std::vector<int> shortest_subarray_length(keywords.size(), std::numeric_limits<int>::max());

	int shortest_distance = std::numeric_limits<int>::max();
	Sub result = { -1, -1};

	for (int i = 0; i < paragraph.size(); i += 1) {
		if (keyword_to_idx.count(paragraph[i])) {
			int keyword_idx = keyword_to_idx.find(paragraph[i])->second;
			if (keyword_idx == 0) {
				shortest_subarray_length[keyword_idx] = 1;
			} else if (shortest_subarray_length[keyword_idx-1] != std::numeric_limits<int>::max()) {
				int distance_to_previous_keyword = i - latest_occurrence[keyword_idx-1];
				shortest_subarray_length[keyword_idx] = distance_to_previous_keyword +
					shortest_subarray_length[keyword_idx-1];
			}
			latest_occurrence[keyword_idx] = i;

			if (keyword_idx == keywords.size() - 1 &&
				shortest_distance > shortest_subarray_length.back()) {
				shortest_distance = shortest_subarray_length.back();
				result = { i - shortest_subarray_length.back() + 1, i};
			}
		}
	}

	std::cout
		<< paragraph << ", " << keywords << " -> "
		<< result.start << ", " << result.end << std::endl;

	return result;
}

int main() {
	auto res = FindSmallestSequentiallyCoveringSubset(
		{"apple", "banana", "cat", "apple"},
		{"banana", "apple"});

	return 0;
}
