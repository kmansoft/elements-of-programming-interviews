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

int LongestSubarrayWithDistinctEntries(
    const std::vector<char>& A) {

    std::unordered_map<char, size_t> most_recent_occurrence;
    size_t longest_dup_free_subarray_start_idx = 0, result = 0;

    for (size_t i = 0; i < A.size(); i += 1) {
        const auto insert = most_recent_occurrence.emplace(A[i], i);
        const auto inserted_entry = insert.first;
        const auto inserted_happen = insert.second;

        if (!inserted_happen) {
            if (inserted_entry->second >= longest_dup_free_subarray_start_idx) {
                result = std::max(result, i - longest_dup_free_subarray_start_idx);
                longest_dup_free_subarray_start_idx = inserted_entry->second + 1;
            }
        }

        inserted_entry->second = i;
    }

    result = std::max(result, A.size() - longest_dup_free_subarray_start_idx);

    std::cout << A << " -> " << result << std::endl;

    return result;
}

int main() {

    const std::string s0 = "fsfetwenwe";
    const std::vector<char> v0(s0.begin(), s0.end());
    LongestSubarrayWithDistinctEntries(v0);

    return 0;
}
