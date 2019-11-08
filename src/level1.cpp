#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

int main() {
    long long rows, cols;
    std::cin >> rows >> cols;
    std::vector<long long> vals(rows*cols);
    long long i = 0;
    for (long long r = 0; r < rows; ++r) {
        for (long long c = 0; c < cols; ++c) {
            std::cin >> vals[i++];
        }
    }

    long long min = *std::min_element(vals.begin(), vals.end());
    long long max = *std::max_element(vals.begin(), vals.end());
    long long sum = std::accumulate(vals.begin(), vals.end(), 0ll);
    long long avg = sum / (long long)(vals.size());

    std::cout << min << " " << max << " " << avg << std::endl;
}
