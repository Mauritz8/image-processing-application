#include <fstream>
#include <string>
#include <vector>


std::string read(int n, std::ifstream& file);
void write(const std::vector<unsigned char>& chars, std::ofstream& file);
int calcLittleEndianByteSequence(const std::string& bytes);
int convertCharToUnsignedInt(char ch);
std::vector<unsigned char> getBytes(int num, int nBytes);
