#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>

struct Cell {
    long long height = -1;
    int country = -1;
};

int main() {
    long long rows, cols;
    std::cin >> rows >> cols;
    std::vector<std::vector<Cell>> cells(rows, std::vector<Cell>(cols));
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            std::cin >> cells[r][c].height >> cells[r][c].country;
        }
    }

    std::map<int, int> border_counts;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            auto& cell = cells[r][c];
            if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) {
                border_counts[cell.country]++;
                continue;
            }
            if (cells[r - 1][c].country != cell.country ||
                cells[r + 1][c].country != cell.country ||
                cells[r][c - 1].country != cell.country ||
                cells[r][c + 1].country != cell.country)
            {
                border_counts[cell.country]++;
                continue;
            }
        }
    }

    for (auto& p : border_counts) {
        std::cout << p.second << '\n';
    }

#if 0
    long long min = *std::min_element(vals.begin(), vals.end());
    long long max = *std::max_element(vals.begin(), vals.end());
    long long sum = std::accumulate(vals.begin(), vals.end(), 0ll);
    long long avg = sum / (long long)(vals.size());

    std::cout << min << " " << max << " " << avg << std::endl;
#endif
}
