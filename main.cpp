#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <time.h>
using namespace std;
int minimum = 0; // included.
int maximum = 255; // included.

// Function to convert binary data to enhanced ASCII numbers (1 to 256) and add prerandom functions, modulo 256.
void convert_binary_to_enhanced_ascii(const string& input_file, const string& output_file) {
    ifstream binary_file(input_file, ios::binary);
    if (!binary_file.is_open()) {
        throw runtime_error("Could not open input file.");
    }

    ofstream ascii_file(output_file);
    if (!ascii_file.is_open()) {
        throw runtime_error("Could not open output file.");
    }

    // Random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 256);

    char byte;
    while (binary_file.read(&byte, 1)) {
        // Original value from the binary file
        unsigned int value = static_cast<unsigned char>(byte);
        // Add a random value to add more "random big jump" if needed, and take modulo 256:
        unsigned int random_value = dist(gen);
        unsigned int final_value = ((value + rand() + random_value - 1) % (maximum+1)) + minimum;
        ascii_file << final_value << " ";
    }
    binary_file.close();
    ascii_file.close();
}

int main(int argc, char* argv[]) {
        if ((argc != 3) && (argc != 4)) {
        cout << "Usage: " << argv[0] << " <input_file> <output_file> (<key modifier>)" << endl;
        return 1;
    }
    string input_file = argv[1];
    string output_file = argv[2];
   int keyModifier = atoi(argv[3]);
srand (132486786 + keyModifier +time(NULL));

    try {
        convert_binary_to_enhanced_ascii(input_file, output_file);
        cout << "Enhanced conversion randomized completed successfully. \nOutput saved to " << output_file << " from " << input_file  << "." <<endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        cerr << "Input file tried: " << input_file << "." << endl;
        cerr << "Output file tried: " << output_file << "." << endl;
        return 1;
    }
    return 0;
}
