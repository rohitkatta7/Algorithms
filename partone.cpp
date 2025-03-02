#include <iostream>
#include <fstream>
#include <map>
#include "utility.h" // You should include the utility.h file with your project.

int main() {
    // Open the input file 'clear.txt'
    std::ifstream inputFile("clear.txt");

    // Check if the input file is opened successfully
    if (!inputFile) {
        std::cerr << "Error opening input file 'clear.txt'" << std::endl;
        return 1;
    }

    // Create a map to store character frequencies
    std::map<char, int> charFrequency;

    // Read characters from the input file and count frequencies
    char currentChar;
    while (inputFile.get(currentChar)) {
        // Check if the character is a printable ASCII character
        if (currentChar >= 32 && currentChar <= 126) {
            charFrequency[currentChar]++;
        }
        // Handle LF character (ASCII code 10)
        else if (currentChar == 10) {
            charFrequency['L']++; // Assuming 'L' represents LF
        }
    }

    // Close the input file
    inputFile.close();

    // Open the output file 'freq.txt'
    std::ofstream outputFile("freq.txt");

    // Check if the output file is opened successfully
    if (!outputFile) {
        std::cerr << "Error opening output file 'freq.txt'" << std::endl;
        return 1;
    }

    // Write character frequencies to the output file
    for (const auto& pair : charFrequency) {
        outputFile << pair.first << " " << pair.second << std::endl;
    }

    // Close the output file
    outputFile.close();

    // Print a message indicating successful completion
    std::cout << "Character frequencies written to 'freq.txt'" << std::endl;

    return 0;
}
