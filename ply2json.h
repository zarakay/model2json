#ifndef ply2json_h
#define ply2json_h

void ply2json(bool preserveTopology, bool splitting, bool boundaryVertexDeletion, 
    bool verbose, float decAmount, std::string inputFilename, std::string outputFilename);
    
#endif
