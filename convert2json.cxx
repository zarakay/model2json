/*
 * convert2json
 *
 * The program is a PLY/VTK file format to JSON file format converter for use
 * with three.js. The program uses the C++ libraries from the VTK toolkit
 * in order to read in a model file and convert it into the json file format
 * which can be recongnized by three.js for rendering in browser WebGL.
 *
 * Migara Liyanamage <>
 * Frank Zhao <frank@frankzhao.net>
 * June 2014
 *
 */


// Import for VTK Libraries
#include <vtkGenericDataObjectReader.h>
#include <vtkPLYReader.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>
#include <vtkDecimatePro.h>

// Import for standard C++ libraries
#include <iostream>
#include <fstream>

// Import program header
#include "convert2json.h"

using namespace std;

// // Input model types
// static const char* PLY = "PLY";
// static const char* VTK = "VTK";

/*
 * Generate JSON Method
 *
 * This method calls the appropriate methods in the vtk toolkit and outputs the
 * JSON file to the output file name specified
 *
 */
void convert2json(double decAmount, string inputFilename, string outputFilename, ModelType model) {
    // File stream for output file
    std::ofstream outputFile;
    outputFile.open(outputFilename.c_str());

    // begin the json file
    outputFile << "{\n";
    
    // Conditional type declaration
    typedef std::conditional<model == PLY,
        vtkPLYReader, vtkGenericDataObjectReader>::type ModelPointer;

    // Reader to read in model
    vtkSmartPointer<ModelPointer> reader =
        vtkSmartPointer<ModelPointer>::New();

    // Specify filename
    reader->SetFileName ( inputFilename.c_str() );

    // Call vtk pipeline to read in the file
    reader->Update();

    // Variables for storing polygons and points
    vtkDataSet * data;
    vtkIdType vert;
    vtkPolyData * pdata;
    vtkCellArray * faces;
    vtkSmartPointer<vtkPolyData> decimated;

    if (decAmount == 0.0) {
        if (model == PLY) {
             // Get the output for vertices
            data = reader->GetOutput();
            vert = data->GetNumberOfPoints();

            // Get the output for polygons
            pdata = reader->GetOutput();
            faces = pdata->GetPolys();
        } else if (model == VTK) {
             // Get the outpuyt for vertices
            data = reader->GetPolyDataOutput();
            vert = data->GetNumberOfPoints();

            // Get the output for polygons
            pdata = reader->GetPolyDataOutput();
            faces = pdata->GetPolys();
        }
    }
    else if (decAmount < 0.0) {
        cout << "Invalid Decimate Amount, Program will now exit" << endl;
        exit(EXIT_FAILURE);
    } else {
        // create decimator
        vtkSmartPointer<vtkDecimatePro> decimate = vtkSmartPointer<vtkDecimatePro>::New();

        // set decimator to the selected file
        //TODO change this if it breaks with VTK
        decimate->SetInputData(reader->GetOutput());

        // set target to reduce to, and set topology to be preserved
        decimate->PreserveTopologyOn();
        decimate->SetTargetReduction(decAmount);

        // start decimation
        decimate->Update();

        decimated =
            vtkSmartPointer<vtkPolyData>::New();
        decimated->ShallowCopy(decimate->GetOutput());

        // Get the outpuyt for vertices
        data = decimated;
        vert = decimated->GetNumberOfPoints();

        // Get the output for polygons
        faces = decimated->GetPolys();
    }

    vtkIdType numCells = faces->GetNumberOfCells();

    vtkIdType cellLocation = 0;

    // Write the standard format header for the json file
    outputFile << "\"metadata\":{\"formatVersion\":3,\"vertices\":" << vert << ",\"faces\":" << numCells << ",\"materials\":1},\n";
    outputFile << "\"scale\":1.0,\n\"materials\":[{\"DbgColor\":15658734,\"DbgIndex\":0,\"DbgName\":\"default\",\"vertexColors\": false}],\n";

    // Begin writing vertices
    outputFile << "\"vertices\":[";

    // Iterate over all the points and print them to the file
    for(vtkIdType i = 0; i < vert; i++) {
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
    for (vtkIdType i = 0; i < numCells; i++) {
        vtkIdType numIDs;
        vtkIdType * pointIds;

        faces->GetCell(cellLocation, numIDs, pointIds);
        cellLocation += 1 + numIDs; // increment to include already printed faces

        for (vtkIdType j = 0; j < numIDs; j++) {
            // print to the file
            // printing the zero is for the bit mask signifying face type
            if (j == 0) outputFile << 0 << ",";
            outputFile << pointIds[j];
            if (i != numCells - 1) {
                outputFile << ",";
            }
            else {
                if(j != numIDs - 1) outputFile << ","; // avoid additional comma at end
            }
        }
    }

    // end faces section
    outputFile << "]\n";

    // end the json file
    outputFile << "}\n";

    // flush the file stream
    outputFile.flush();

    // close file stream
    outputFile.close();
}
