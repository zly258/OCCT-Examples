#include "PrimitiveFactory.h"
#include "GeometryUtils.h"
#include <memory>
#include <vector>

// Implementation of the PrimitiveFactory class

PrimitiveFactory::PrimitiveFactory() {
    // Constructor implementation
}

std::unique_ptr<Shape> PrimitiveFactory::createCircle(double radius) {
    // Create and return a circle shape
    return std::make_unique<Circle>(radius);
}

std::unique_ptr<Shape> PrimitiveFactory::createRectangle(double width, double height) {
    // Create and return a rectangle shape
    return std::make_unique<Rectangle>(width, height);
}

std::vector<std::unique_ptr<Shape>> PrimitiveFactory::createShapes(const std::vector<ShapeType>& shapeTypes) {
    std::vector<std::unique_ptr<Shape>> shapes;
    for (const auto& type : shapeTypes) {
        switch (type) {
            case ShapeType::Circle:
                shapes.push_back(createCircle(1.0)); // Default radius
                break;
            case ShapeType::Rectangle:
                shapes.push_back(createRectangle(1.0, 2.0)); // Default dimensions
                break;
            // Add more shapes as needed
            default:
                break;
        }
    }
    return shapes;
}