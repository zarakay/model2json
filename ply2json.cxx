/*
 * ply2json
 *
 * The program is a ply file format to json file format converter for use
 * with three.js. The program uses the C++ libraries from the VTK toolkit
 * in order to read in a ply file and convert it into the json file format
 * which can be recongnized by three.js for rendering in the browsing.
 *
 * @Author Migara Liyanamage
 * @Date 19 June 2014
 * @Version 1.0
 *
 */


// Import for VTK Libraries
#include <vtkPLYReader.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>

// Import for standard C++ libraries
#include <iostream>
#include <fstream>

// Import for program header
#include "ply2json.h"

using namespace std;

// stores the filename of the input file
static string inputFilename;

// store the filename of the output file
static string outputFilename;


/*
 * Main Method
 *
 * This method reads in the file which is to be converted from the command line
 * and calls the appropriate methods to begin the conversion.
 *
 */
int main( int argc, char ** argv )
{
    if (argc != 3)
    {
        // Print Usage Message
        cout << "Usage: " << argv[0] << " filename.ply outputName" << endl;
        return EXIT_FAILURE;
    }

    // Assign appropriate file names for the program
    inputFilename = argv[1];
    outputFilename = argv[2];

    // begin generation
    generateJSON();

    return EXIT_SUCCESS;
}


/*
 * Generate JSON Method
 *
 * This method calls the appropriate methods in the vtk toolkit and outputs the
 * JSON file to the output file name specified
 *
 */
void generateJSON()
{
    // File stream for output file
    std::ofstream outputFile;
    outputFile.open(outputFilename.c_str());

    // begin the json file
    outputFile << "{\n";

    // Reader to read in PLY File
    vtkSmartPointer<vtkPLYReader> reader =
        vtkSmartPointer<vtkPLYReader>::New();

    // Specify filename
    reader->SetFileName ( inputFilename.c_str() );

    // Call vtk pipeline to read in the file
    reader->Update();

    // Get the outpuyt for vertices
    vtkDataSet * data = reader->GetOutput();
    vtkIdType vert = data->GetNumberOfPoints();

    // Get the output for polygons
    vtkPolyData * pdata = reader->GetOutput();
    vtkCellArray * faces = pdata->GetPolys();

    vtkIdType numCells = faces->GetNumberOfCells();
    vtkIdType cellLocation = 0;

    // Write the standard format header for the json file
    outputFile << "\"metadata\":{\"formatVersion\":3,\"vertices\":" << vert << ",\"faces\":" << numCells << ",\"materials\":1},\n";
    outputFile << "\"scale\":1.0,\n\"materials\":[{\"DbgColor\":15658734,\"DbgIndex\":0,\"DbgName\":\"default\",\"vertexColors\": false}],\n";

    // Begin writing vertices
    outputFile << "\"vertices\":[";

    // Iterate over all the points and print them to the file
    for(vtkIdType i = 0; i < vert; i++)
    {
        double p[3];
        data->GetPoint(i, p);
        outputFile << p[0] << "," << p[1] << "," << p[2];
        if (i != vert - 1) outputFile << ","; // Avoid putting comma before end bracket
    }

    // End the vertices section
    outputFile << "],\n";

    // Begin writing faces
    outputFile << "\"faces\":[";

    // Iterate over the faces and print them to file
    for (vtkIdType i = 0; i < numCells; i++)
    {
        vtkIdType numIDs;
        vtkIdType * pointIds;

        faces->GetCell(cellLocation, numIDs, pointIds);
        cellLocation += 1 + numIDs; // increment to include already printed faces

        for (vtkIdType j = 0; j < numIDs; j++)
        {
            // print to the file
            // printing the zero is for the bit mask signifying face type
            if (j == 0) outputFile << 0 << ",";
            outputFile << pointIds[j];
            if (i != numCells - 1)
            {
                outputFile << ",";
            }
            else
            {
                if(j != numIDs - 1) outputFile << ","; // avoid additional comma at end
            }
        }
    }

    // end faces section
    outputFile << "]\n";

    // end the json file
    outputFile << "}\n";

    // close file stream
    outputFile.close();
}
