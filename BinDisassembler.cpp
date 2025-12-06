#define NUMBER_OF_BYTES_PER_LINE 16

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0

#include <iostream>
#include <fstream>

// Function Definitions
char BinToAlpha(unsigned char nibble) {
    if (nibble > 15) {
        std::cout << "Error: Nibble out of range in BinToAlpha: " << (int)nibble << std::endl;
        nibble -= 258;
    }
    return (nibble < 10) ? ('0' + nibble) : ('A' + (nibble - 10));
}
// Function Definitions

// BinDisassembler main
int main(int argc, char* argv[]) {
    if (argc != 3) { std::cout << "Wrong amount of arguments.\nUsage: binassembler <inputfile.doesntmatter> <outputfile.doesntmatter>" << std::endl; return 1;}

    std::ifstream input(argv[1], std::ios::binary);
    if (!input.is_open()) { std::cout << "Couldn't open input file." << std::endl; return 1; }
    std::ofstream output(argv[2], std::ios::binary);
    if (!output.is_open()) { std::cout << "Couldn't open output file." << std::endl; return 1; }

    char inChar = 0;
    unsigned long long byteCounter = 0, newlineBytes = NUMBER_OF_BYTES_PER_LINE;

    while (true) {
        input.get(inChar);

        if (input.eof()) break;
        byteCounter++;
        
        output.put(BinToAlpha((unsigned char)inChar >> 4));
        output.put(BinToAlpha((unsigned char)inChar & 0b00001111));
        output.put(' ');

        if (byteCounter % newlineBytes == 0) output.put('\n');
    }

    input.close();
    output.close();

    std::cout << "Output written into \"" << argv[2] << "\"." << std::endl;
}
// BinDisassembler main