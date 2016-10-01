#ifndef PJ_LPL_C
#define PJ_LPL_C

#include <PJ/Image/LPL.hpp>

#ifdef PJ_DEBUG
#include <PJ/Util/Exception.hpp>
#endif

using namespace std;

namespace pj{namespace LPL
{

bool IsSFColorEqual(const sf::Color &c1, const sf::Color &c2)
{
    return ((c1.a == c2.a && c1.a == 0) || (c1 == c2));
}

sf::Image* GetImageFromLPL(const uint8_t* ptr, uint32_t* index, const uint32_t beginIndex){
#ifdef PJ_DEBUG
    if (ptr == NULL)
    {
        throw NullPointerException("LPL::GetImageFromLPL : ptr is NULL\0");
    }
    else if (index == NULL)
    {
        throw NullPointerException("LPL::GetImageFromLPL : cannot return index (= NULL)\0");
    }
#endif
    uint32_t i = beginIndex;
    if (!(ptr[i] == 'L' && ptr[i+1] == 'P' && ptr[i+2] == 'L'))
    {
        return NULL;
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
            return NULL;
            break;
    }
}

sf::Image* IFLPL_P8L2(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex){
    uint32_t w, h, x = 0, y = 0, i = 0, j = beginIndex;
    uint16_t nb, WxH;
    uint8_t c;
    sf::Color tab[256];
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
    sf::Image* img = new sf::Image(w, h, sf::Color(255,0,255,255));
    if (img == NULL)
    {
        return NULL;
    }
    while (WxH > 0)
    {
        nb = ptr[j]*256+ptr[j+1];
        WxH -= nb;
        c = ptr[j+2];
        j += 3;
        while (nb > 0&&y<h)
        {
            img->SetPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return img;
}

sf::Image* IFLPL_P8L1(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex){
    uint32_t w, h, x = 0, y = 0, i = 0, j = beginIndex;
    uint16_t nb, WxH;
    uint8_t c;
    sf::Color tab[256];
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
    sf::Image* img = new sf::Image(w, h, sf::Color(255,0,255,255));
    if (img == NULL)
    {
        return NULL;
    }
    while (WxH > 0)
    {
        nb = ptr[j];
        WxH -= nb;
        c = ptr[j+1];
        j += 2;
        while (nb > 0&&y<h)
        {
            img->SetPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return img;
}

sf::Image* IFLPL_P4L2(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex){
    uint32_t w, h, x = 0, y = 0, i = 0, j = beginIndex;
    uint16_t nb, WxH;
    uint8_t c;
    sf::Color tab[16];
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
    sf::Image* img = new sf::Image(w, h, sf::Color(255,0,255,255));
    if (img == NULL)
    {
        return NULL;
    }
    while (WxH > 0)
    {
        nb = ptr[j]*256+ptr[j+1];
        WxH -= nb;
        c = ptr[j+2];
        j += 3;
        while (nb > 0&&y<h)
        {
            img->SetPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return img;
}

sf::Image* IFLPL_P4L1(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex){
    uint32_t w, h, x = 0, y = 0, i = 0, j = beginIndex;
    uint16_t nb, WxH;
    uint8_t c;
    sf::Color tab[16];
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
    sf::Image* img = new sf::Image(w, h, sf::Color(255,0,255,255));
    if (img == NULL)
    {
        return NULL;
    }
    while (WxH > 0)
    {
        nb = ptr[j];
        WxH -= nb;
        c = ptr[j+1];
        j += 2;
        while (nb > 0&&y<h)
        {
            img->SetPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return img;
}

sf::Image* IFLPL_P2L2(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex){
    uint32_t w, h, x = 0, y = 0, i = 0, j = beginIndex;
    uint16_t nb, WxH;
    uint8_t c;
    sf::Color tab[4];
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
    sf::Image* img = new sf::Image(w, h, sf::Color(255,0,255,255));
    if (img == NULL)
    {
        return NULL;
    }
    while (WxH > 0)
    {
        nb = (ptr[j]&63)+ptr[j+1];
        WxH -= nb;
        c = ptr[j]/64;
        j += 2;
        while (nb > 0&&y<h)
        {
            img->SetPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return img;
}

sf::Image* IFLPL_P2L1(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex){
    uint32_t w, h, x = 0, y = 0, i = 0, j = beginIndex;
    uint16_t nb, WxH;
    uint8_t c;
    sf::Color tab[4];
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
    sf::Image* img = new sf::Image(w, h, sf::Color(255,0,255,255));
    if (img == NULL)
    {
        return NULL;
    }
    while (WxH > 0)
    {
        nb = ptr[j]&63;
        WxH -= nb;
        c = ptr[j]/64;
        j++;
        while (nb > 0&&y<h)
        {
            img->SetPixel(x, y, tab[c]);
            x = (x+1)%w;
            if (x == 0)
            {
                y++;
            }
            nb--;
        }
    }
    *index = j;
    return img;
}

uint8_t* GetLPLFromImage(const sf::Image* ptr, uint32_t* index, const uint8_t mode){
#ifdef PJ_DEBUG
    if (ptr == NULL)
    {
        throw NullPointerException("LPL::GetLPLFromImage : ptr is NULL\0");
    }
    else if (index == NULL)
    {
        throw NullPointerException("LPL::GetLPLFromImage : cannot return index (= NULL)\0");
    }
#endif
    if ((mode&T4) == T4 && (ptr->GetWidth()>=16 || ptr->GetHeight()>=16))
    {
        return NULL;
    }
    switch(mode%T4)
    {
        case (P2+L1):
            return LPLFI_P2L1(ptr, index, mode);
            break;
        case (P2+L2):
            return LPLFI_P2L2(ptr, index, mode);
            break;
        case (P4+L1):
            return LPLFI_P4L1(ptr, index, mode);
            break;
        case (P4+L2):
            return LPLFI_P4L2(ptr, index, mode);
            break;
        case (P8+L1):
            return LPLFI_P8L1(ptr, index, mode);
            break;
        case (P8+L2):
            return LPLFI_P8L2(ptr, index, mode);
            break;
        default:
            return NULL;
            break;
    }
}

uint8_t* LPLFI_P8L2(const sf::Image* img, uint32_t* index, const uint8_t mode){
    uint32_t nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4;
    uint8_t C1, C2;
    bool truc = false;
    sf::Color c1(0,0,0,0), c2(0,0,0,0);
    sf::Color c[256] = {sf::Color(0,0,0,0)};
    uint8_t Tab[256][256];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
        {
            c2 = c1;
            c1 = img->GetPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (LPL::IsSFColorEqual(c1, c[k]))
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
            if (!LPL::IsSFColorEqual(c1, c2))
            {
                nb++;
            }
            x++;
        }
        y++;
    }
    nb++;
    *index = 4+1024+2+nb*3;
    uint8_t* tab = new uint8_t[*index];
    if (tab == NULL)
    {
        return NULL;
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
        tab[i] = img->GetWidth()*16+img->GetHeight();
        i += 1;
    }
    else
    {
        tab[i] = img->GetWidth();
        tab[i+1] = img->GetHeight();
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
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

uint8_t* LPLFI_P8L1(const sf::Image* img, uint32_t* index, const uint8_t mode){
    uint32_t nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4, cmp = 0;
    uint8_t C1, C2;
    bool truc = false;
    sf::Color c1(0,0,0,0), c2(0,0,0,0);
    sf::Color c[256] = {sf::Color(0,0,0,0)};
    uint8_t Tab[256][256];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
        {
            c2 = c1;
            c1 = img->GetPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (LPL::IsSFColorEqual(c1, c[k]))
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
            if (LPL::IsSFColorEqual(c1, c2) && cmp < 255)
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
    uint8_t* tab = new (nothrow) uint8_t[*index];
    if (tab == NULL)
    {
        return NULL;
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
        tab[i] = img->GetWidth()*16+img->GetHeight();
        i += 1;
    }
    else
    {
        tab[i] = img->GetWidth();
        tab[i+1] = img->GetHeight();
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
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

uint8_t* LPLFI_P4L2(const sf::Image* img, uint32_t* index, const uint8_t mode){
    uint32_t nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4;
    uint8_t C1, C2;
    bool truc = false;
    sf::Color c1(0,0,0,0), c2(0,0,0,0);
    sf::Color c[16] = {sf::Color(0,0,0,0)};
    uint8_t Tab[256][256];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
        {
            c2 = c1;
            c1 = img->GetPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (LPL::IsSFColorEqual(c1, c[k]))
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
            if (!LPL::IsSFColorEqual(c1, c2))
            {
                nb++;
            }
            x++;
        }
        y++;
    }
    nb++;
    *index = 4+64+2+nb*3;
    uint8_t* tab = new uint8_t[*index];
    if (tab == NULL)
    {
        return NULL;
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
        tab[i] = img->GetWidth()*16+img->GetHeight();
        i += 1;
    }
    else
    {
        tab[i] = img->GetWidth();
        tab[i+1] = img->GetHeight();
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
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

uint8_t* LPLFI_P4L1(const sf::Image* img, uint32_t* index, const uint8_t mode){
    uint32_t nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4, cmp = 0;
    uint8_t C1, C2;
    bool truc = false;
    sf::Color c1(0,0,0,0), c2(0,0,0,0);
    sf::Color c[16] = {sf::Color(0,0,0,0)};
    uint8_t Tab[256][256];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
        {
            c2 = c1;
            c1 = img->GetPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (LPL::IsSFColorEqual(c1, c[k]))
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
            if (LPL::IsSFColorEqual(c1, c2) && cmp < 255)
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
    uint8_t* tab = new uint8_t[*index];
    if (tab == NULL)
    {
        return NULL;
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
        tab[i] = img->GetWidth()*16+img->GetHeight();
        i += 1;
    }
    else
    {
        tab[i] = img->GetWidth();
        tab[i+1] = img->GetHeight();
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
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

uint8_t* LPLFI_P2L2(const sf::Image* img, uint32_t* index, const uint8_t mode){
    uint32_t nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4, cmp = 0;
    uint8_t C1, C2;
    bool truc = false;
    sf::Color c1(0,0,0,0), c2(0,0,0,0);
    sf::Color c[4] = {sf::Color(0,0,0,0)};
    uint8_t Tab[256][256];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
        {
            c2 = c1;
            c1 = img->GetPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (LPL::IsSFColorEqual(c1, c[k]))
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
            if (LPL::IsSFColorEqual(c1, c2) && cmp < 16383)
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
    uint8_t* tab = new uint8_t[*index];
    if (tab == NULL)
    {
        return NULL;
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
        tab[i] = img->GetWidth()*16+img->GetHeight();
        i += 1;
    }
    else
    {
        tab[i] = img->GetWidth();
        tab[i+1] = img->GetHeight();
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
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

uint8_t* LPLFI_P2L1(const sf::Image* img, uint32_t* index, const uint8_t mode){
    uint32_t nc = 0, x = 0, y = 0, nb = 0, k = 0, i = 4, cmp = 0;
    uint8_t C1, C2;
    bool truc = false;
    sf::Color c1(0,0,0,0), c2(0,0,0,0);
    sf::Color c[4] = {sf::Color(0,0,0,0)};
    uint8_t Tab[256][256];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
        {
            c2 = c1;
            c1 = img->GetPixel(x, y);
            k = 0;
            truc = false;
            while (k < nc && !truc)
            {
                if (LPL::IsSFColorEqual(c1, c[k]))
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
            if (LPL::IsSFColorEqual(c1, c2) && cmp < 63)
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
    uint8_t* tab = new uint8_t[*index];
    if (tab == NULL)
    {
        return NULL;
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
        tab[i] = img->GetWidth()*16+img->GetHeight();
        i += 1;
    }
    else
    {
        tab[i] = img->GetWidth();
        tab[i+1] = img->GetHeight();
        i += 2;
    }
    nb = 0;
    C1 = Tab[0][0];
    while (y < img->GetHeight())
    {
        x = 0;
        while (x < img->GetWidth())
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

}}

#endif
