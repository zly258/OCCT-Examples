#ifndef GEOMETRY_UTILS_H
#define GEOMETRY_UTILS_H

#include <cmath>
#include <array>

namespace GeometryUtils {

// Function to calculate the distance between two points in 2D space
template<typename T>
T distance(const std::array<T, 2>& point1, const std::array<T, 2>& point2) {
    return std::sqrt(std::pow(point2[0] - point1[0], 2) + std::pow(point2[1] - point1[1], 2));
}

// Function to calculate the area of a triangle given its vertices
template<typename T>
T triangleArea(const std::array<T, 2>& a, const std::array<T, 2>& b, const std::array<T, 2>& c) {
    return std::abs((a[0] * (b[1] - c[1]) + b[0] * (c[1] - a[1]) + c[0] * (a[1] - b[1])) / 2.0);
}

// Function to check if a point is inside a triangle
template<typename T>
bool isPointInTriangle(const std::array<T, 2>& pt, const std::array<T, 2>& a, const std::array<T, 2>& b, const std::array<T, 2>& c) {
    T areaABC = triangleArea(a, b, c);
    T areaPAB = triangleArea(pt, a, b);
    T areaPAC = triangleArea(pt, a, c);
    T areaPBC = triangleArea(pt, b, c);
    return (areaABC == areaPAB + areaPAC + areaPBC);
}

} // namespace GeometryUtils

#endif // GEOMETRY_UTILS_H