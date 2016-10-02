#ifndef PJ_LPL_C
#define PJ_LPL_C

//#include <cstdio>
#include "LPL.hpp"

using namespace sf;

namespace LPL
{

bool IsSFColorEqual(const Color &c1, const Color &c2)
{
    return ((c1.a == c2.a && c1.a == 0) || (c1 == c2));
}

Image* GetImageFromLPL(const unsigned char* ptr, unsigned int* index, const unsigned int beginIndex)
{
    if (ptr == 00)
    {
        return 00;
    }
    unsigned int Index = 0;
    if (index == 00)
    {
        index = &Index;
    }
    unsigned int i = beginIndex;
    if (!(ptr[i] == 'L' && ptr[i+1] == 'P' && ptr[i+2] == 'L'))
    {
        return 00;
    }
    *index += 4;
    switch(ptr[i+3]%T4)
    {
        case (P2+L1):
            return IFLPL_P2L1(ptr, index, ptr[i+3], i+4);
            break;
        case (P2+L2):
            return IFLPL_P2L2(ptr, index, ptr[i+3], i+4);
            break;
        case (P4+L1):
            return IFLPL_P4L1(ptr, index, ptr[i+3], i+4);
            break;
        case (P4+L2):
            return IFLPL_P4L2(ptr, index, ptr[i+3], i+4);
            break;
        case (P8+L1):
            return IFLPL_P8L1(ptr, index, ptr[i+3], i+4);
            break;
        case (P8+L2):
            return IFLPL_P8L2(ptr, index, ptr[i+3], i+4);
            break;
        default:
            return 00;
            break;
    }
}

Image* IFLPL_P8L2(const unsigned char* ptr, unsigned int* index, const unsigned char mode, const unsigned int beginIndex)
{
    unsigned int w, h, x = 0, y = 0, i = 0, j = beginIndex;
    unsigned short nb, WxH;
    unsigned char c;
    Color tab[256];
    while (i < 256)
    {
        tab[i].r = ptr[j];
        tab[i].g = ptr[j+1];
        tab[i].b = ptr[j+2];
        tab[i].a = ptr[j+3];
        i++;
        j += 4;
    }
    if ((mode&T4)==T4)
    {
        w = ptr[j]/16;
        h = ptr[j]&15;
        j += 1;
    }
    else
    {
        w = ptr[j];
        h = ptr[j+1];
        j += 2;
    }
    WxH = w*h;
    Image* image = new Image();
    if (image == 00)
    {
        return 00;
    }
    image->create(w, h);
    while (WxH > 0)
    {
        nb = ptr[j]*256+ptr[j+1];
        WxH -= nb;
        c = ptr[j+2];
        j += 3;
        while (nb > 0&&y<h)
        {
            image->setPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return image;
}

Image* IFLPL_P8L1(const unsigned char* ptr, unsigned int* index, const unsigned char mode, const unsigned int beginIndex)
{
    unsigned int w, h, x = 0, y = 0, i = 0, j = beginIndex;
    unsigned short nb, WxH;
    unsigned char c;
    Color tab[256];
    while (i < 256)
    {
        tab[i].r = ptr[j];
        tab[i].g = ptr[j+1];
        tab[i].b = ptr[j+2];
        tab[i].a = ptr[j+3];
        i++;
        j += 4;
    }
    if ((mode&T4)==T4)
    {
        w = ptr[j]/16;
        h = ptr[j]&15;
        j += 1;
    }
    else
    {
        w = ptr[j];
        h = ptr[j+1];
        j += 2;
    }
    WxH = w*h;
    Image* image = new Image();
    if (image == 00)
    {
        return 00;
    }
    image->create(w, h);
    while (WxH > 0)
    {
        nb = ptr[j];
        WxH -= nb;
        c = ptr[j+1];
        j += 2;
        while (nb > 0&&y<h)
        {
            image->setPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return image;
}

Image* IFLPL_P4L2(const unsigned char* ptr, unsigned int* index, const unsigned char mode, const unsigned int beginIndex)
{
    unsigned int w, h, x = 0, y = 0, i = 0, j = beginIndex;
    unsigned short nb, WxH;
    unsigned char c;
    Color tab[16];
    while (i < 16)
    {
        tab[i].r = ptr[j];
        tab[i].g = ptr[j+1];
        tab[i].b = ptr[j+2];
        tab[i].a = ptr[j+3];
        i++;
        j += 4;
    }
    if ((mode&T4)==T4)
    {
        w = ptr[j]/16;
        h = ptr[j]&15;
        j += 1;
    }
    else
    {
        w = ptr[j];
        h = ptr[j+1];
        j += 2;
    }
    WxH = w*h;
    Image* image = new Image();
    if (image == 00)
    {
        return 00;
    }
    image->create(w, h);
    while (WxH > 0)
    {
        nb = ptr[j]*256+ptr[j+1];
        WxH -= nb;
        c = ptr[j+2];
        j += 3;
        while (nb > 0&&y<h)
        {
            image->setPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return image;
}

Image* IFLPL_P4L1(const unsigned char* ptr, unsigned int* index, const unsigned char mode, const unsigned int beginIndex)
{
    unsigned int w, h, x = 0, y = 0, i = 0, j = beginIndex;
    unsigned short nb, WxH;
    unsigned char c;
    Color tab[16];
    while (i < 16)
    {
        tab[i].r = ptr[j];
        tab[i].g = ptr[j+1];
        tab[i].b = ptr[j+2];
        tab[i].a = ptr[j+3];
        i++;
        j += 4;
    }
    if ((mode&T4)==T4)
    {
        w = ptr[j]/16;
        h = ptr[j]&15;
        j += 1;
    }
    else
    {
        w = ptr[j];
        h = ptr[j+1];
        j += 2;
    }
    WxH = w*h;
    Image* image = new Image();
    if (image == 00)
    {
        return 00;
    }
    image->create(w, h);
    while (WxH > 0)
    {
        nb = ptr[j];
        WxH -= nb;
        c = ptr[j+1];
        j += 2;
        while (nb > 0&&y<h)
        {
            image->setPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return image;
}

Image* IFLPL_P2L2(const unsigned char* ptr, unsigned int* index, const unsigned char mode, const unsigned int beginIndex)
{
    unsigned int w, h, x = 0, y = 0, i = 0, j = beginIndex;
    unsigned short nb, WxH;
    unsigned char c;
    Color tab[4];
    while (i < 4)
    {
        tab[i].r = ptr[j];
        tab[i].g = ptr[j+1];
        tab[i].b = ptr[j+2];
        tab[i].a = ptr[j+3];
        i++;
        j += 4;
    }
    if ((mode&T4)==T4)
    {
        w = ptr[j]/16;
        h = ptr[j]&15;
        j += 1;
    }
    else
    {
        w = ptr[j];
        h = ptr[j+1];
        j += 2;
    }
    WxH = w*h;
    Image* image = new Image();
    if (image == 00)
    {
        return 00;
    }
    image->create(w, h);
    while (WxH > 0)
    {
        nb = (ptr[j]&63)+ptr[j+1];
        WxH -= nb;
        c = ptr[j]/64;
        j += 2;
        while (nb > 0&&y<h)
        {
            image->setPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return image;
}

Image* IFLPL_P2L1(const unsigned char* ptr, unsigned int* index, const unsigned char mode, const unsigned int beginIndex)
{
    unsigned int w, h, x = 0, y = 0, i = 0, j = beginIndex;
    unsigned short nb, WxH;
    unsigned char c;
    Color tab[4];
    while (i < 4)
    {
        tab[i].r = ptr[j];
        tab[i].g = ptr[j+1];
        tab[i].b = ptr[j+2];
        tab[i].a = ptr[j+3];
        i++;
        j += 4;
    }
    if ((mode&T4)==T4)
    {
        w = ptr[j]/16;
        h = ptr[j]&15;
        j += 1;
    }
    else
    {
        w = ptr[j];
        h = ptr[j+1];
        j += 2;
    }
    WxH = w*h;
    Image* image = new Image();
    if (image == 00)
    {
        return 00;
    }
    image->create(w, h);
    while (WxH > 0)
    {
        nb = ptr[j]&63;
        WxH -= nb;
        c = ptr[j]/64;
        j++;
        while (nb > 0&&y<h)
        {
            image->setPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return image;
}

unsigned char* GetLPLFromImage(const Image* image, unsigned int* index, const unsigned char mode)
{
    if (image == 00 || index == 00)
    {
        return 00;
    }
    Vector2u size = image->getSize();
    if ((mode&T4) == T4 && (size.x >= 16 || size.y >= 16))
    {
        return 00;
    }
    switch(mode%T4)
    {
        case (P2+L1):
            return LPLFI_P2L1(image, index, mode);
            break;
        case (P2+L2):
            return LPLFI_P2L2(image, index, mode);
            break;
        case (P4+L1):
            return LPLFI_P4L1(image, index, mode);
            break;
        case (P4+L2):
            return LPLFI_P4L2(image, index, mode);
            break;
        case (P8+L1):
            return LPLFI_P8L1(image, index, mode);
            break;
        case (P8+L2):
            return LPLFI_P8L2(image, index, mode);
            break;
        default:
            return 00;
            break;
    }
}

unsigned char* LPLFI_P8L2(const Image* image, unsigned int* index, const unsigned char mode)
{
    unsigned int nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4;
    unsigned char C1, C2;
    bool truc = false;
    Color c1(0,0,0,0), c2(0,0,0,0);
    Color c[256] = {Color(0,0,0,0)};
    unsigned char Tab[256][256];
    Vector2u size = image->getSize();
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            c2 = c1;
            c1 = image->getPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (IsSFColorEqual(c1, c[k]))
                {
                    truc = true;
                }
                k++;
            }
            if (!truc)
            {
                c[nc] = c1;
                nc++;
            }
            else
            {
                k--;
            }
            Tab[x][y] = k;
            if (!IsSFColorEqual(c1, c2))
            {
                nb++;
            }
            x++;
        }
        y++;
    }
    nb++;
    *index = 4+1024+2+nb*3;
    unsigned char* tab = new unsigned char[*index];
    if (tab == 00)
    {
        return 00;
    }
    x = 0;
    y = 0;
    tab[0] = 'L';
    tab[1] = 'P';
    tab[2] = 'L';
    tab[3] = mode;
    k = 0;
    while (k < 256)
    {
        tab[i] = c[k].r;
        tab[i+1] = c[k].g;
        tab[i+2] = c[k].b;
        tab[i+3] = c[k].a;
        k++;
        i += 4;
    }
    if ((mode&T4)==T4)
    {
        tab[i] = size.x*16+size.y;
        i += 1;
    }
    else
    {
        tab[i] = size.x;
        tab[i+1] = size.y;
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            C2 = C1;
            C1 = Tab[x][y];
            if (C1 == C2)
            {
                nb++;
            }
            else
            {
                tab[i] = nb/256;
                tab[i+1] = nb%256;
                tab[i+2] = C2;
                nb = 1;
                i += 3;
            }
            x++;
        }
        y++;
    }
    tab[i] = nb/256;
    tab[i+1] = nb%256;
    tab[i+2] = C1;
    return tab;
}

unsigned char* LPLFI_P8L1(const Image* image, unsigned int* index, const unsigned char mode)
{
    unsigned int nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4, cmp = 0;
    unsigned char C1, C2;
    bool truc = false;
    Color c1(0,0,0,0), c2(0,0,0,0);
    Color c[256] = {Color(0,0,0,0)};
    unsigned char Tab[256][256];
    Vector2u size = image->getSize();
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            c2 = c1;
            c1 = image->getPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (IsSFColorEqual(c1, c[k]))
                {
                    truc = true;
                }
                k++;
            }
            if (!truc)
            {
                c[nc] = c1;
                nc++;
            }
            else
            {
                k--;
            }
            Tab[x][y] = k;
            if (IsSFColorEqual(c1, c2) && cmp < 255)
            {
                cmp++;
            }
            else
            {
                nb++;
                cmp = 1;
            }
            x++;
        }
        y++;
    }
    nb++;
    *index = 4+1024+2+nb*2;
    unsigned char* tab = new unsigned char[*index];
    if (tab == 00)
    {
        return 00;
    }
    x = 0;
    y = 0;
    tab[0] = 'L';
    tab[1] = 'P';
    tab[2] = 'L';
    tab[3] = mode;
    k = 0;
    while (k < 256)
    {
        tab[i] = c[k].r;
        tab[i+1] = c[k].g;
        tab[i+2] = c[k].b;
        tab[i+3] = c[k].a;
        k++;
        i += 4;
    }
    if ((mode&T4)==T4)
    {
        tab[i] = size.x*16+size.y;
        i += 1;
    }
    else
    {
        tab[i] = size.x;
        tab[i+1] = size.y;
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            C2 = C1;
            C1 = Tab[x][y];
            if (C1 == C2 && nb < 255)
            {
                nb++;
            }
            else
            {
                tab[i] = nb;
                tab[i+1] = C2;
                nb = 1;
                i += 2;
            }
            x++;
        }
        y++;
    }
    tab[i] = nb;
    tab[i+1] = C1;
    return tab;
}

unsigned char* LPLFI_P4L2(const Image* image, unsigned int* index, const unsigned char mode)
{
    unsigned int nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4;
    unsigned char C1, C2;
    bool truc = false;
    Color c1(0,0,0,0), c2(0,0,0,0);
    Color c[16] = {Color(0,0,0,0)};
    unsigned char Tab[256][256];
    Vector2u size = image->getSize();
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            c2 = c1;
            c1 = image->getPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (IsSFColorEqual(c1, c[k]))
                {
                    truc = true;
                }
                k++;
            }
            if (!truc)
            {
                c[nc] = c1;
                nc++;
            }
            else
            {
                k--;
            }
            Tab[x][y] = k;
            if (!IsSFColorEqual(c1, c2))
            {
                nb++;
            }
            x++;
        }
        y++;
    }
    nb++;
    *index = 4+64+2+nb*3;
    unsigned char* tab = new unsigned char[*index];
    if (tab == 00)
    {
        return 00;
    }
    x = 0;
    y = 0;
    tab[0] = 'L';
    tab[1] = 'P';
    tab[2] = 'L';
    tab[3] = mode;
    k = 0;
    while (k < 16)
    {
        tab[i] = c[k].r;
        tab[i+1] = c[k].g;
        tab[i+2] = c[k].b;
        tab[i+3] = c[k].a;
        k++;
        i += 4;
    }
    if ((mode&T4)==T4)
    {
        tab[i] = size.x*16+size.y;
        i += 1;
    }
    else
    {
        tab[i] = size.x;
        tab[i+1] = size.y;
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            C2 = C1;
            C1 = Tab[x][y];
            if (C1 == C2)
            {
                nb++;
            }
            else
            {
                tab[i] = nb/256;
                tab[i+1] = nb%256;
                tab[i+2] = C2;
                nb = 1;
                i += 3;
            }
            x++;
        }
        y++;
    }
    tab[i] = nb/256;
    tab[i+1] = nb%256;
    tab[i+2] = C1;
    return tab;
}

unsigned char* LPLFI_P4L1(const Image* image, unsigned int* index, const unsigned char mode)
{
    unsigned int nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4, cmp = 0;
    unsigned char C1, C2;
    bool truc = false;
    Color c1(0,0,0,0), c2(0,0,0,0);
    Color c[16] = {Color(0,0,0,0)};
    unsigned char Tab[256][256];
    Vector2u size = image->getSize();
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            c2 = c1;
            c1 = image->getPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (IsSFColorEqual(c1, c[k]))
                {
                    truc = true;
                }
                k++;
            }
            if (!truc)
            {
                c[nc] = c1;
                nc++;
            }
            else
            {
                k--;
            }
            Tab[x][y] = k;
            if (IsSFColorEqual(c1, c2) && cmp < 255)
            {
                cmp++;
            }
            else
            {
                nb++;
                cmp = 1;
            }
            x++;
        }
        y++;
    }
    nb++;
    *index = 4+64+2+nb*2;
    unsigned char* tab = new unsigned char[*index];
    if (tab == 00)
    {
        return 00;
    }
    x = 0;
    y = 0;
    tab[0] = 'L';
    tab[1] = 'P';
    tab[2] = 'L';
    tab[3] = mode;
    k = 0;
    while (k < 16)
    {
        tab[i] = c[k].r;
        tab[i+1] = c[k].g;
        tab[i+2] = c[k].b;
        tab[i+3] = c[k].a;
        k++;
        i += 4;
    }
    if ((mode&T4)==T4)
    {
        tab[i] = size.x*16+size.y;
        i += 1;
    }
    else
    {
        tab[i] = size.x;
        tab[i+1] = size.y;
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            C2 = C1;
            C1 = Tab[x][y];
            if (C1 == C2 && nb < 255)
            {
                nb++;
            }
            else
            {
                tab[i] = nb;
                tab[i+1] = C2;
                nb = 1;
                i += 2;
            }
            x++;
        }
        y++;
    }
    tab[i] = nb;
    tab[i+1] = C1;
    return tab;
}

unsigned char* LPLFI_P2L2(const Image* image, unsigned int* index, const unsigned char mode)
{
    unsigned int nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4, cmp = 0;
    unsigned char C1, C2;
    bool truc = false;
    Color c1(0,0,0,0), c2(0,0,0,0);
    Color c[4] = {Color(0,0,0,0)};
    unsigned char Tab[256][256];
    Vector2u size = image->getSize();
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            c2 = c1;
            c1 = image->getPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (IsSFColorEqual(c1, c[k]))
                {
                    truc = true;
                }
                k++;
            }
            if (!truc)
            {
                c[nc] = c1;
                nc++;
            }
            else
            {
                k--;
            }
            Tab[x][y] = k;
            if (IsSFColorEqual(c1, c2) && cmp < 16383)
            {
                cmp++;
            }
            else
            {
                nb++;
                cmp = 1;
            }
            x++;
        }
        y++;
    }
    nb++;
    *index = 4+16+2+nb*2;
    unsigned char* tab = new unsigned char[*index];
    if (tab == 00)
    {
        return 00;
    }
    x = 0;
    y = 0;
    tab[0] = 'L';
    tab[1] = 'P';
    tab[2] = 'L';
    tab[3] = mode;
    k = 0;
    while (k < 4)
    {
        tab[i] = c[k].r;
        tab[i+1] = c[k].g;
        tab[i+2] = c[k].b;
        tab[i+3] = c[k].a;
        k++;
        i += 4;
    }
    if ((mode&T4)==T4)
    {
        tab[i] = size.x*16+size.y;
        i += 1;
    }
    else
    {
        tab[i] = size.x;
        tab[i+1] = size.y;
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            C2 = C1;
            C1 = Tab[x][y];
            if (C1 == C2)
            {
                nb++;
            }
            else
            {
                tab[i] = C2*64+nb/256;
                tab[i+1] = nb%256;
                nb = 1;
                i += 2;
            }
            x++;
        }
        y++;
    }
    tab[i] = C1*64+nb/256;
    tab[i+1] = nb%256;
    return tab;
}

unsigned char* LPLFI_P2L1(const Image* image, unsigned int* index, const unsigned char mode)
{
    unsigned int nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4, cmp = 0;
    unsigned char C1, C2;
    bool truc = false;
    Color c1(0,0,0,0), c2(0,0,0,0);
    Color c[4] = {Color(0,0,0,0)};
    unsigned char Tab[256][256];
    Vector2u size = image->getSize();
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            c2 = c1;
            c1 = image->getPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (IsSFColorEqual(c1, c[k]))
                {
                    truc = true;
                }
                k++;
            }
            if (!truc)
            {
                c[nc] = c1;
                nc++;
            }
            else
            {
                k--;
            }
            Tab[x][y] = k;
            if (IsSFColorEqual(c1, c2) && cmp < 63)
            {
                cmp++;
            }
            else
            {
                nb++;
                cmp = 1;
            }
            x++;
        }
        y++;
    }
    nb++;
    *index = 4+16+2+nb;
    unsigned char* tab = new unsigned char[*index];
    if (tab == 00)
    {
        return 00;
    }
    x = 0;
    y = 0;
    tab[0] = 'L';
    tab[1] = 'P';
    tab[2] = 'L';
    tab[3] = mode;
    k = 0;
    while (k < 4)
    {
        tab[i] = c[k].r;
        tab[i+1] = c[k].g;
        tab[i+2] = c[k].b;
        tab[i+3] = c[k].a;
        k++;
        i += 4;
    }
    if ((mode&T4)==T4)
    {
        tab[i] = size.x*16+size.y;
        i += 1;
    }
    else
    {
        tab[i] = size.x;
        tab[i+1] = size.y;
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < size.y)
    {
        x = 0;
        while (x < size.x)
        {
            C2 = C1;
            C1 = Tab[x][y];
            if (C1 == C2)
            {
                nb++;
            }
            else
            {
                tab[i] = C2*64+nb;
                nb = 1;
                i++;
            }
            x++;
        }
        y++;
    }
    tab[i] = C1*64+nb;
    return tab;
}

}

#endif
