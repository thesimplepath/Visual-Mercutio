/////////////////////////////////////////////////////////////////////////////
//@doc XXXClass
//@module XXXClass.cpp | Implementation of the <c XXXClass> class.
// 
// ProcessSoft Classes
// <nl>Copyright <cp> 2001 - ProcessSoft SA, All rights reserved.
// 
// 
// Author: Gaya
// <nl>Created: 03/2002
// 
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// BASE 64 Encoder

#include <stdio.h>

// JMR-MODIF - Le 14 septembre 2005 - Ajout des décorations Unicode _T(), nettoyage du code inutile.(En commentaires)

// JMR-MODIF - Le 14 septembre 2005 - Suppression de la macro b64pitchar : Identique à b64putchar et jamais utilisée.
#define b64putchar( xxx ) outbuf[outpos++] = xxx;

unsigned char alphabet[64 + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// Cette fonction permet de décrypter une chaîne de caractères.
string b64decode( unsigned char* pstr, int len )
{
    static char inalphabet[256];
    static char decoder[256];

    int bits        = 0;
    int char_count    = 0;
    int errors        = 0;
    int pos            = 0;
    int outpos        = 0;
    int i;
    int c;

    // JMR-MODIF - Le 14 septembre 2005 - Correction de l'allocation mémoire du buffer outbuf.
    // La chaîne décryptée est plus courte que la chaîne cryptée, on peut utiliser la longeur de la chaîne
    // cryptée pour allouer la mémoire. On ajoute 1 par sécurité.
//    unsigned char* outbuf = new unsigned char[len];
    unsigned char* outbuf = new unsigned char[len + 1];

    // Remplit les buffers de codage.
    for ( i = ( sizeof alphabet ) - 1; i >= 0 ; i-- )
    {
        inalphabet[alphabet[i]]    = 1;
        decoder[alphabet[i]]    = i;
    }

    while ( 1 )
    {
        // Si la position courante est supérieure ou égale à la longeur de la chaîne d'entrée, arrête.
        if ( pos >= len )
        {
            break;
        }

        // Récupère la valeur numérique du caractère courant de la chaîne à décrypter.
        c = pstr[pos++];

        if ( c == '=' )
        {
            break;
        }

        if ( c > 255 || !inalphabet[c] )
        {
            continue;
        }

        // Décrypte la chaîne : On décode 3 blocs par 3 blocs. Les blocs d'entrée sont combinés dans un type int,
        // dont chaque octet contient un caractère décrypté. Lorsque trois blocs de la chaîne d'entrée ont été
        // combinés, on écrit chacun des trois octets dans la chaîne de caractères de sortie, en sélectionnant le bon
        // octet par décalage (opérateur >>) et en masquant les données superflues (bits and 0xff).
        bits += decoder[c];
        char_count++;

        if ( char_count == 4 )
        {
            b64putchar( bits >> 16 );
            b64putchar( ( bits >> 8 ) & 0xff );
            b64putchar( bits & 0xff );

            bits        = 0;
            char_count    = 0;
        }
        else
        {
            bits <<= 6;
        }
    }

    // Lorsque la chaîne est arrivée à la fin, on teste s'il reste des blocs encore non décryptés. Si c'est le cas,
    // on les décrypte.
    if ( c > len )
    {
        if ( char_count )
        {
            errors++;
        }
    }
    else
    {
        /* c == '=' */
        switch ( char_count )
        {
            case 1:
            {
                errors++;
                break;
            }

            case 2:
            {
                b64putchar( bits >> 10 );
                break;
            }

            case 3:
            {
                b64putchar( bits >> 16 );
                b64putchar( ( bits >> 8 ) & 0xff );
                break;
            }
        }
    }

    if ( errors > 0 )
    {
        TRACE( _T( "Base 64 decoding error\n" ) );
    }

    outbuf[outpos]    = 0;
    string tmpret    = (char*)outbuf;
    delete [] outbuf;

    return tmpret;
}

// Cette fonction permet de crypter une chaîne de caractères.
string b64encode( unsigned char* pstr, int len )
{
    int c;
    int char_count    = 0;
    int bits        = 0;
    int cols        = 0;
    int pos            = 0;
    int outpos        = 0;
    int bufsize        = 0;

    // ***************************************************************************************
    // JMR-MODIF - Le 14 septembre 2005 - Correction de l'allocation mémoire du buffer outbuf.

    // Calcule la longeur du buffer à assigner.
    while ( 1 )
    {
        if ( pos >= len )
        {
            break;
        }

        pos++;
        char_count++;

        if ( char_count == 3 )
        {
            bufsize    += 4;
            cols    += 4;

            if ( cols == 72 )
            {
                bufsize++;
                cols = 0;
            }

            char_count = 0;
        }
    }

    // Tient compte du marquage de fin de chaîne.
    bufsize += 6;

//    unsigned char* outbuf = new unsigned char[len * 2];
    unsigned char* outbuf = new unsigned char[bufsize + 1];
    // ***************************************************************************************

    char_count    = 0;
    cols        = 0;
    pos            = 0;

    while ( 1 )
    {
        if ( pos >= len )
        {
            break;
        }

        c = pstr[pos++];

        if ( c > 255 )
        {
            TRACE( _T( "Base 64 encoding encountered char > 255\n" ) );
        }

        // On crypte la chaîne. On utilise ici une valeur de 6 bits pour les caractères. La chaîne est décryptée de
        // façon asymétrique. On inscrit 4 caractères cryptés pour 3 caractères décryptés. Pour le cryptage, un
        // caractère est considéré comme valant 6 bits. On peut remarquer ici la correspondance entre le cryptage et
        // le décryptage : En effet, 4 caractères de 6 bits = 24 bits, et 3 caractères de 8 bits = 24 bits. Mais
        // attention : cela signifie aussi que la chaîne cryptée sera plus longue d'un caractère tous les 3 caractères.
        // Il faut en tenir compte lors du calcul de l'allocation mémoire pour le buffer de sortie (outbuf).
        bits += c;
        char_count++;

        if ( char_count == 3 )
        {
            // JMR-MODIF - Le 14 septembre 2005 - Ajout du masque de bits pour le premier caractère.
//            b64putchar( alphabet[bits >> 18] );
            b64putchar( alphabet[( bits >> 18 ) & 0x3f] );
            b64putchar( alphabet[( bits >> 12 ) & 0x3f] );
            b64putchar( alphabet[( bits >> 6 )  & 0x3f] );
            b64putchar( alphabet[bits & 0x3f] );

            cols += 4;

            if ( cols == 72 )
            {
                b64putchar( '\n' );
                cols = 0;
            }

            bits        = 0;
            char_count    = 0;
        }
        else
        {
            bits <<= 8;
        }
    }

    // On crypte ici les derniers caractères restants, non traités ci-dessus. On ajoute aussi le marquage
    // de fin de ligne.
    if ( char_count != 0 )
    {
        bits <<= 16 - ( 8 * char_count );
        // JMR-MODIF - Le 14 septembre 2005 - Ajout du masque de bits pour le premier caractère.
//        b64putchar( alphabet[bits >> 18] );
        b64putchar( alphabet[( bits >> 18 ) & 0x3f] );
        b64putchar( alphabet[( bits >> 12 ) & 0x3f] );

        if ( char_count == 1 )
        {
            b64putchar( '=' );
            b64putchar( '=' );
        }
        else
        {
            b64putchar( alphabet[( bits >> 6 ) & 0x3f] );
            b64putchar( '=' );
        }

        if ( cols > 0 )
        {
            b64putchar( '\n' );
        }
    }

    b64putchar( '\0' );
    string tmpret = (char*)outbuf;
    //JMR-MODIF - Le 14 septembre 2005 - Ajouté la ligne permettant le nettoyage des ressources de outbuf.
    delete [] outbuf;

    return tmpret;
}

string base64encode( const unsigned char *pcBuffIn, long nLenIn )
{
    string ret = b64encode( (unsigned char*)pcBuffIn, nLenIn );

    return ret;
}
