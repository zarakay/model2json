#include <vtkPLYReader.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>

#include <iostream>
#include <fstream>

#include "ply2json.h"

using namespace std;

static string inputFilename;
static string outputFilename;

int main( int argc, char ** argv )
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " filename.ply outputName" << endl;
        return EXIT_FAILURE;
    }

    inputFilename = argv[1];
    outputFilename = argv[2];

    generateJSON();

    return EXIT_SUCCESS;
}

void generateJSON()
{
    std::ofstream outputFile;
    outputFile.open(outputFilename.c_str());

    outputFile << "{\n";

    vtkSmartPointer<vtkPLYReader> reader =
        vtkSmartPointer<vtkPLYReader>::New();

    reader->SetFileName ( inputFilename.c_str() );

    reader->Update();

    vtkDataSet * data = reader->GetOutput();
    vtkIdType vert = data->GetNumberOfPoints();

    vtkPolyData * pdata = reader->GetOutput();
    vtkCellArray * faces = pdata->GetPolys();

    vtkIdType numCells = faces->GetNumberOfCells();
    vtkIdType cellLocation = 0;

    outputFile << "\"metadata\":{\"formatVersion\":3,\"vertices\":" << vert << ",\"faces\":" << numCells << ",\"materials\":1},\n";
    outputFile << "\"scale\":1.0,\n\"materials\":[{\"DbgColor\":15658734,\"DbgIndex\":0,\"DbgName\":\"default\",\"vertexColors\": false}],\n";
    outputFile << "\"vertices\":[";
    for(vtkIdType i = 0; i < vert; i++)
    {
        double p[3];
        data->GetPoint(i, p);
        outputFile << p[0] << "," << p[1] << "," << p[2];
        if (i != vert - 1) outputFile << ",";
    }

    outputFile << "],\n";
    outputFile << "\"faces\":[";

    for (vtkIdType i = 0; i < numCells; i++)
    {
        vtkIdType numIDs;
        vtkIdType * pointIds;

        faces->GetCell(cellLocation, numIDs, pointIds);
        cellLocation += 1 + numIDs;

        for (vtkIdType j = 0; j < numIDs; j++)
        {
            if (j == 0) outputFile << 0 << ",";
            outputFile << pointIds[j];
            if (i != numCells - 1) 
            {
                outputFile << ",";
            } 
            else
            {
                if(j != numIDs - 1) outputFile << ",";
            }
        }
    }

    outputFile << "]\n";
    outputFile << "}\n";

    outputFile.close();
}
