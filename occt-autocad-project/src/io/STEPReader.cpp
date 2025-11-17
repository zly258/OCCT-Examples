#include "STEPReader.h"
#include <STEPControl_Reader.hxx>
#include <TCollection_AsciiString.hxx>
#include <TopoDS_Shape.hxx>
#include <Standard_ErrorHandler.hxx>

STEPReader::STEPReader() {
    // Constructor implementation
}

bool STEPReader::readFile(const std::string& filename, TopoDS_Shape& shape) {
    STEPControl_Reader reader;
    Standard_Integer status = reader.ReadFile(TCollection_AsciiString(filename.c_str()));

    if (status != IFSelect_RetDone) {
        // Handle error
        return false;
    }

    reader.TransferRoots();
    shape = reader.OneShape();
    return true;
}