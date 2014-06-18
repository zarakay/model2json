#include <vtkPLYReader.h>
#include <vtkSmartPointer.h>
#include <vtkCellArray.h>

#include <iostream>

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
    vtkSmartPointer<vtkPLYReader> reader =
        vtkSmartPointer<vtkPLYReader>::New();

    reader->SetFileName ( inputFilename.c_str() );

    reader->Update();

    vtkDataSet * data = reader->GetOutput();
    vtkIdType vert = data->GetNumberOfPoints();
    cout << "Vertices: " << vert << endl;

    for(vtkIdType i = 0; i <= vert; i++)
    {
        double p[3];
        data->GetPoint(i, p);
        //cout << "Point " << i << ": x " << p[0] << " y " << p[1]
        //    << " z " << p[2] << endl;
    }

    vtkPolyData * pdata = reader->GetOutput();
    vtkCellArray * faces = pdata->GetPolys();

    vtkIdType numCells = faces->GetNumberOfCells();
    vtkIdType cellLocation = 0;

    cout << "Polygons: " << numCells << endl;

    for (vtkIdType i = 0; i < numCells; i++)
    {
        vtkIdType numIDs;
        vtkIdType * pointIds;

        faces->GetCell(cellLocation, numIDs, pointIds);
        cellLocation += 1 + numIDs;

        for (vtkIdType j = 0; j < numIDs; j++)
        {
            cout << pointIds[j] << endl;
        }
    }
}
