#include <vtkPLYReader.h>
#include <vtkSmartPointer.h>

using namespace std;

string inputFilename;
string outputFilename;

int main( int argc, char ** argv )
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << "filename.ply outputName" << endl;
        return EXIT_FAILURE;
    }

    inputFilename = argv[1];
    outputFilename = argv[2];

    loadFile();

    return EXIT_SUCCESS;
}

void loadFile()
{
    vtkSmartPointer<vtkPLYReader> reader =
        vtkSmartPointer<vtkPLYReader>::New();
    reader->SetFileName ( inputFilename.c_str() );
}
