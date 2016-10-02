#include <cstdio>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "LPL.hpp"

using namespace sf;

int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        printf("Error: this program requires one argument.");
        return 0;
    }
    int i = 0;
    char * lpl_filename = argv[1];
    while (lpl_filename[i] != 0)
    {
        i++;
    }
    char * filename = new char[i+5];
    i = 0;
    while (lpl_filename[i] != 0)
    {
        filename[i] = lpl_filename[i];
        i++;
    }
    filename[i  ] = '.';
    filename[i+1] = 'p';
    filename[i+2] = 'n';
    filename[i+3] = 'g';
    filename[i+4] = 0;
    FILE * file = fopen(lpl_filename, "rb");
    fseek(file, 0, SEEK_END);
    long int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char * lpl_image = new unsigned char[size];
    fread(lpl_image, 1, size, file);
    fclose(file);
    Image * image = LPL::GetImageFromLPL(lpl_image);
    if (image == 00)
    {
        printf("Error\n");
        return 0;
    }
    image->saveToFile(filename);
    delete(image);
    delete[](filename);
    return 0;
}
