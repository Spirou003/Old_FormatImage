#include <cstdio>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "LPL.hpp"

using namespace sf;

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("Error: this program requires at least one argument.");
        return 0;
    }
    int i = 0;
    char * filename = 00;
    unsigned char mode = 0, T = 0, L = 0, P = 0;
    char firstChar = 0, secondChar = 0;
    while (i < argc)
    {
        firstChar = argv[i][0];
        if (firstChar == 'p' || firstChar == 'P')
        {
            if (i+1 < argc)
            {
                secondChar = argv[i+1][0];
                i++;
                switch (secondChar)
                {
                    case '2':
                        P = LPL::P2;
                        break;
                    case '4':
                        P = LPL::P4;
                        break;
                    case '8':
                        P = LPL::P8;
                        break;
                    default:
                        i--;
                        break;
                }
            }
        }
        else if (firstChar == 'l' || firstChar == 'L')
        {
            if (i+1 < argc)
            {
                secondChar = argv[i+1][0];
                i++;
                switch (secondChar)
                {
                    case '1':
                        L = LPL::L1;
                        break;
                    case '2':
                        L = LPL::L2;
                        break;
                    default:
                        i--;
                        break;
                }
            }
        }
        else if (firstChar == 't' || firstChar == 'T')
        {
            if (i+1 < argc)
            {
                secondChar = argv[i+1][0];
                i++;
                switch (secondChar)
                {
                        break;
                    case '4':
                        T = LPL::T4;
                        break;
                    case '8':
                        T = LPL::T8;
                        break;
                    default:
                        i--;
                        break;
                }
            }
        }
        else
        {
            filename = argv[i];
        }
        i++;
    }
    mode = T + L + P;
    Image image;
    if (!image.loadFromFile(filename))
    {
        return 0;
    }
    i = 0;
    while (filename[i] != 0)
    {
        i++;
    }
    char * lpl_filename = new char[i+5];
    i = 0;
    while (filename[i] != 0)
    {
        lpl_filename[i] = filename[i];
        i++;
    }
    lpl_filename[i  ] = '.';
    lpl_filename[i+1] = 'l';
    lpl_filename[i+2] = 'p';
    lpl_filename[i+3] = 'l';
    lpl_filename[i+4] = 0;
    unsigned int size = 0;
    unsigned char * lpl_image = LPL::GetLPLFromImage(&image, &size, mode);
    if (lpl_image == 00)
    {
        printf("Memory error\n");
        return 0;
    }
    FILE * file = fopen(lpl_filename, "w+b");
    if (file == 00)
    {
        printf("Can't write to %s\n", lpl_filename);
        return 0;
    }
    fwrite(lpl_image, 1, size, file);
    fclose(file);
    delete[](lpl_filename);
    return 0;
}
