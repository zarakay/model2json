#ifndef ply2json_h
#define ply2json_h

enum ModelType {PLY, VTK};

void ply2json(double decAmount, string inputFilename, string outputFilename);

#endif
