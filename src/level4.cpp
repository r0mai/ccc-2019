#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>

// #define DEBUG

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

struct Point {
    int x = -1;
    int y = -1;
};


bool operator==(const Point& p, const Point& o) {
    return p.x == o.x && p.y == o.y;
}

#define LOG(x) " " << #x ": " << x

bool IsTouched(int ox, int oy, int dx, int dy, int x, int y) {
    double x1 = x + 0.5;
    double x2 = x - 0.5;

    double m = double(dy) / double(dx);

    double y1 = m * x1 + oy - ox * m;
    double y2 = m * x2 + oy - ox * m;

    double min_y = y - 0.5;
    double max_y = y + 0.5;

    double eps = -1.0e-9;
    if (y1 - eps < min_y && y2 - eps < min_y) {
        return false;
    }
    if (y1 + eps > max_y && y2 + eps > max_y) {
        return false;
    }
    return true;
}

int main() {
    int rows, cols;
    int queries;
    std::cin >> rows >> cols >> queries;

#ifdef DEBUG
    std::cout << LOG(rows) << LOG(cols) << std::endl;
#endif
    for (int q = 0; q < queries; ++q) {
        int ox, oy, dx, dy;
        std::cin >> ox >> oy >> dx >> dy;
#ifdef DEBUG
        std::cout  << "------ "<< ox << " " << oy << " " << dx << " " << dy << std::endl;
#endif

        std::vector<Point> points;

        bool dominant_x = abs(dx) >= abs(dy);

        auto addPoint = [&](Point p) {
            if (p.x >= 0 && p.x < cols && p.y >= 0 && p.y < rows) {
                points.push_back(p);
            }
        };
        if (dx == 0) {
            if (dy > 0) {
                for (int y = oy; y < rows; ++y) {
                    addPoint({ox, y});
                }
            } else {
                for (int y = oy; y >= 0; --y) {
                    addPoint({ox, y});
                }
            }
        } else if (dy == 0) {
            if (dx > 0) {
                for (int x = ox; x < cols; ++x) {
                    addPoint({x, oy});
                }
            } else {
                for (int x = ox; x >= 0; --x) {
                    addPoint({x, oy});
                }
            }
        } else if (dominant_x) {
            int y_dir = dy / abs(dy);
            int x_dir = dx / abs(dx);
            for (int y = oy; y_dir > 0 ? y < rows : y >= 0; y += y_dir) {
                for (int x = ox; x_dir > 0 ? x < cols : x >= 0; x += x_dir) {
                    if (IsTouched(ox, oy, dx, dy, x, y)) {
                        addPoint({x, y});
                    }
                }
            }
        } else {
            int y_dir = dy / abs(dy);
            int x_dir = dx / abs(dx);
            for (int x = ox; x_dir > 0 ? x < cols : x >= 0; x += x_dir) {
                for (int y = oy; y_dir > 0 ? y < rows : y >= 0; y += y_dir) {
                    if (IsTouched(ox, oy, dx, dy, x, y)) {
                        addPoint({x, y});
                    }
                }
            }
        }

#ifdef DEBUG
        std::stringstream ss;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (std::find(begin(points), end(points), Point{c, r}) != end(points)) {
                    ss << "X";
                } else {
                    ss << " ";
                }
                ss << "";
            }
            ss << "|" << std::endl;
        }
        std::cout << ss.str();
#endif

        for (auto& p : points) {
            std::cout << p.x << " " << p.y << " ";
        }
        std::cout << std::endl;
#if 0
        if (dominant_x) {
            int x_direction = dx > 0 ? 1 : -1;
            for (int i = 0; true; ++i) {
                double m = double(dy) / double(dx);
                double x = ox + x_direction * (0.5 + i);
                double y = m * x + oy - ox * m;

                int ix = dx > 0 ? ceil(x - 0.5) : floor(x - 0.5);
                int iy = floor(y + 0.5); // TODO why + and not -

                std::cout << "x: " << x << ", y: " << y << " ... " << y - floor(y) << std::endl;
                if (abs(y - floor(y) - 0.5) < 1.e-8) {
                    std::cout << "ahh!" << std::endl;
                    // specko
                } else {
                    addPoint({ix, iy});
                    std::cout << ix << " " << iy << '\n';
                }

                if (x <= -1.0 || x >= cols - 1 || y <= -1.0 || y >= rows -1) {
                    break;
                }
            }
        }
#endif

    }
}
