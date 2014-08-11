/*
 * model2json.cxx
 *
 * Converts PLY/VTK models to JSON for use with three.js.
 * Uses the C++ VTK toolkit.
 *
 * Frank Zhao <frank@frankzhao.net>
 * Migara Liyanamage <>
 * June 2014
 *
 */

// Import for standard C++ libraries
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

// Import conversion
#include "ply2json.h"
#include "vtk2json.h"

using namespace std;

enum ModelType {PLY, VTK};

// // Input model types
// static const char* PLY = "PLY";
// static const char* VTK = "VTK";

/*
 * Main Method
 *
 * This method reads in the file which is to be converted from the command line
 * and calls the appropriate methods to begin the conversion.
 *
 */
int main( int argc, char ** argv ) {
    if (argc < 4) {
        // Print Usage Message
        cout << "Usage: " << argv[0] << \
            " [-t] [-s] [-b] [-v] [-d 0.0 .. 1.0] filename output" << endl;
        cout << "-t\t\tPreserve topology" << endl;
        cout << "-s\t\tEnable splitting" << endl;
        cout << "-b\t\tEnable boundary vertex deletion" << endl;
        cout << "-v\t\tVerbose" << endl;
        cout << "-d [0.0..1.0]\tDecimation amount (maximum 1.0)" << endl;
        cout << "filename\tFile to convert" << endl;
        cout << "output\t\tOutput file" << endl;
        return EXIT_FAILURE;
    }

    // commandline paramaters
    // stores the filename of the input file
    string inputFilename;
    // store the filename of the output file
    string outputFilename;

    char flag;
    double decimateAmount;
    bool preserveTopology = false,
            splitting = false,
            boundaryVertexDeletion = false,
            verbose = false;

    extern char *optarg;
    extern int optind;
    while ((flag = getopt(argc, argv, "tsvbd:")) != -1) {
        switch (flag) {
            case 't':
                preserveTopology = true;
                break;
            case 's':
                splitting = true;
                break;
            case 'v':
                verbose = true;
                break;
            case 'b':
                boundaryVertexDeletion = true;
                break;
            case 'd':
                decimateAmount = atof(optarg);
                break;
            default:
                cout << "Ignored invalid argument " << flag << endl;
                break;
        }
    }

    // input and output files
    if (optind < argc) {
        inputFilename  = argv[optind];
        outputFilename = argv[optind+1];
        if (verbose) {
            cout << "Input file: " << inputFilename << endl;
            cout << "Output file: " << outputFilename << endl;
        }
    } else {
        cout << "Input or output file not specified!" << endl;
    }

    if (verbose) {
        cout << "Attempting to run conversion with:" << endl;
        cout << "Preserve topology: " << preserveTopology << endl;
        cout << "Splitting: " << splitting << endl;
        cout << "Boundary Vertex Deletion: " << boundaryVertexDeletion << endl;
        cout << "Decimate amount: " << decimateAmount << endl;
    }

    // Find out whether it is PLY or VTK
    string fileExtension = inputFilename.substr(inputFilename.size() - 3);

    // convert model
    if ( (fileExtension == "vtk") or (fileExtension == "VTK") ) {
        vtk2json(preserveTopology, splitting, boundaryVertexDeletion,
            verbose, decimateAmount, inputFilename, outputFilename);
    } else if ( (fileExtension == "ply") or (fileExtension == "PLY") ) {
        ply2json(preserveTopology, splitting, boundaryVertexDeletion,
            verbose, decimateAmount, inputFilename, outputFilename);
    }

    return EXIT_SUCCESS;
}
