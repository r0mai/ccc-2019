#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>

struct Cell {
    long long height = -1;
    int country = -1;
    bool is_border = false;
};

int d2(int r1, int c1, int r2, int c2) {
    int rd = r1 - r2;
    int rc = c1 - c2;
    return rd * rd + rc * rc;
}

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
                cell.is_border = true;
                continue;
            }
            if (cells[r - 1][c].country != cell.country ||
                cells[r + 1][c].country != cell.country ||
                cells[r][c - 1].country != cell.country ||
                cells[r][c + 1].country != cell.country)
            {
                cell.is_border = true;
                continue;
            }
        }
    }

    std::map<int, int> sum_r;
    std::map<int, int> sum_c;
    std::map<int, int> count;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            auto& cell = cells[r][c];
            sum_r[cell.country] += r;
            sum_c[cell.country] += c;
            count[cell.country]++;
        }
    }

    std::vector<int> avg_r(sum_r.size());
    std::vector<int> avg_c(sum_c.size());

    for (int i = 0; i < sum_r.size(); ++i) {
        avg_r[i] = sum_r[i] / count[i];
        avg_c[i] = sum_c[i] / count[i];
    }

    for (int country = 0; country < sum_r.size(); ++country) {
        auto& proposed_capital = cells[avg_r[country]][avg_c[country]];
        if (proposed_capital.country == country && not proposed_capital.is_border) {
            continue;
        }
        int candidate_r = -1;
        int candidate_c = -1;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                auto& cell = cells[r][c];
                if (cell.country != country || cell.is_border) {
                    continue;
                }
                if (candidate_c == -1) {
                    candidate_r = r;
                    candidate_c = c;
                    continue;
                }

                int new_dist = d2(avg_r[country], avg_c[country], r, c) ;
                int old_dist = d2(avg_r[country], avg_c[country], candidate_r, candidate_c);
                if (new_dist < old_dist) {
                    candidate_r = r;
                    candidate_c = c;
                    continue;
                }

                if (new_dist == old_dist) {
                    if (r < candidate_r) {
                        candidate_r = r;
                        candidate_c = c;
                        continue;
                    } else if (r == candidate_r && c < candidate_c) {
                        candidate_r = r;
                        candidate_c = c;
                        continue;
                    }
                }
            }
        }
        avg_r[country] = candidate_r;
        avg_c[country] = candidate_c;
    }

    for (int i = 0; i < sum_r.size(); ++i) {
        std::cout << avg_c[i] << " " << avg_r[i] << '\n';
    }

#if 0
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            std::cout << cells[r][c].country << " ";
        }
        std::cout << '\n';
    }
#endif
}
