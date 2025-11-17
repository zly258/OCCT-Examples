#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

class Document {
public:
    Document(const std::string& title);
    ~Document();

    void addObject(const std::string& object);
    void removeObject(const std::string& object);
    const std::vector<std::string>& getObjects() const;

    void save(const std::string& filename) const;
    void load(const std::string& filename);

private:
    std::string title;
    std::vector<std::string> objects;
};

#endif // DOCUMENT_H