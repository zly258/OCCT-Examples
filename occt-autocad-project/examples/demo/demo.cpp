#include <iostream>
#include "occt_autocad/api.h"

int main() {
    std::cout << "Welcome to the OCCT AutoCAD Project!" << std::endl;

    // Initialize the application
    OCCTAutoCAD::API api;
    if (!api.initialize()) {
        std::cerr << "Failed to initialize the OCCT AutoCAD API." << std::endl;
        return 1;
    }

    // Create a new document
    auto document = api.createDocument();
    if (!document) {
        std::cerr << "Failed to create a new document." << std::endl;
        return 1;
    }

    // Add some geometry to the document
    document->addCircle(0.0, 0.0, 10.0);
    document->addRectangle(5.0, 5.0, 15.0, 10.0);

    // Render the document
    api.render(document);

    std::cout << "Demo completed successfully!" << std::endl;
    return 0;
}