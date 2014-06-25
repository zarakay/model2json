#ifndef convert2json_h
#define convert2json_h

enum ModelType {PLY, VTK};

void convert2json(double decAmount, std::string inputFilename, std::string outputFilename, ModelType);

#endif
