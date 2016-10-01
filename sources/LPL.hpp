#ifndef PJ_LPL_H
#define PJ_LPL_H

#include <SFML/Graphics/Image.hpp>
#include <cstdint>

namespace pj{

/**
  * \namespace LPL
  * LPL contient les fonctions permettant de convertir une image chargee en
  * memoire vers le format LPL et inversement. Le format LPL se sert d'une palette
  * de 4, 16 ou 256 couleurs. La taille de l'image doit etre inferieure a 256 x 256
  * pixels.
  */

namespace LPL
{
    /**
      * \enum Mode
      * \brief Options de conversion d'image
      * Mode permet de choisir plus facilement comment convertir l'image (flags).
      * Il faut fournir trois des sept options, un Px, un Ly, un Tz.
      * Px donne la taille de la palette (2^x)
      * Ly donne la longueur max de repetitions d'une couleur (2^y)
      * Tz donne la taille max de l'image (2^z)
      * Un choix approprie de modes permet de reduire de maniere optimale la taille
      * de l'image LPL
      */
    enum Mode
    {
        P2 = 2, P4 = 4, P8 = 8, L1 = 16, L2 = 32, T4 = 64, T8 = 128
    };

    bool IsSFColorEqual(const sf::Color &c1, const sf::Color &c2);

    /**
      * \fn sf::Image* GetImageFromLPL(const uint8_t* ptr, uint32_t* index, const uint32_t beginIndex = 0)
      * \brief Convertit une image au format LPL vers une sf::Image
      * \param ptr: pointeur vers la zone memoire contenant l'image LPL
      * \param index: valeur de retour secondaire. Donne l'index du premier octet apres l'image LPL
      * \param beginIndex: index de debut du LPL dans ptr
      * \return Retourne la conversion de l'image LPL en sf::Image
      */
    sf::Image* GetImageFromLPL(const uint8_t* ptr, uint32_t* index, const uint32_t beginIndex = 0);

    sf::Image* IFLPL_P8L2(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex = 0);
    sf::Image* IFLPL_P8L1(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex = 0);

    sf::Image* IFLPL_P4L2(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex = 0);
    sf::Image* IFLPL_P4L1(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex = 0);

    sf::Image* IFLPL_P2L2(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex = 0);
    sf::Image* IFLPL_P2L1(const uint8_t* ptr, uint32_t* index, const uint8_t mode, const uint32_t beginIndex = 0);

    /**
      * \fn uint8_t* GetLPLFromImage(const sf::Image* ptr, uint32_t* index, const uint8_t mode)
      * \brief Convertit une sf::Image vers une image au format LPL
      * \param ptr: pointeur vers la sf::Image a convertir
      * \param index: valeur de retour secondaire. Donne la taille (en octets) de l'image LPL
      * \param mode: determine comment l'image va etre convertie
      * \return Retourne la conversion de la sf::Image en image LPL
      */
    uint8_t* GetLPLFromImage(const sf::Image* ptr, uint32_t* index, const uint8_t mode);

    uint8_t* LPLFI_P8L2(const sf::Image* img, uint32_t* index, const uint8_t mode);
    uint8_t* LPLFI_P8L1(const sf::Image* img, uint32_t* index, const uint8_t mode);

    uint8_t* LPLFI_P4L2(const sf::Image* img, uint32_t* index, const uint8_t mode);
    uint8_t* LPLFI_P4L1(const sf::Image* img, uint32_t* index, const uint8_t mode);

    uint8_t* LPLFI_P2L2(const sf::Image* img, uint32_t* index, const uint8_t mode);
    uint8_t* LPLFI_P2L1(const sf::Image* img, uint32_t* index, const uint8_t mode);
}

}

#endif
