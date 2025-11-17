#ifndef OCCT_AUTOCAD_API_H
#define OCCT_AUTOCAD_API_H

namespace occt_autocad {

class OCCTAutoCADAPI {
public:
    // Initializes the OCCT AutoCAD API
    static void initialize();

    // Shuts down the OCCT AutoCAD API
    static void shutdown();

    // Example function to create a new document
    static void createDocument();

    // Example function to open an existing document
    static void openDocument(const std::string& filePath);

    // Example function to save the current document
    static void saveDocument(const std::string& filePath);
};

} // namespace occt_autocad

#endif // OCCT_AUTOCAD_API_H