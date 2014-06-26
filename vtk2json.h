#ifndef vtk2json_h
#define vtk2json_h

void vtk2json(bool preserveTopology, bool splitting, bool boundaryVertexDeletion, 
    bool verbose, float decAmount, std::string inputFilename, std::string outputFilename);

#endif
