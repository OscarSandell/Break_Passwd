#include <iostream>
#include <chrono>
#include <string>
#include "key.h"
#include <map>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

/*
Decrypt funktion
*/
//kanske typ

#define dela_upp_mitten false

void decrypt(const Key &c, Key *table)
{
    //Vi skapar en map för a som håller koll på a:s nycklar och de hashade lösenorden för de nycklarna
    std::map<Key, Key> a_saved;
    std::vector<Key> cracked{};
    //std::set<Key> cracked{};
    Key a{};
    Key b{};
//Vi räknar ut all kopmbinationer för a
//Här är nyckeln 1 4 9 16 25 och elementen är 1 2 3 4 5
#if dela_upp_mitten == false
    for (int i = 0; i < std::pow(2, static_cast<int>(N / 2)); i++)
    {
        std::cout << "kombination " << i << "   a\t" << a << std::endl;
        a_saved[subset_sum(a, table)] = a;
        a++;
    }
#else
    for (int i = 0; i < std::pow(2, static_cast<int>(((C / 2) * 5))); i++)
    {
        std::cout << "kombination " << i << "   a\t" << a << std::endl;
        a_saved[subset_sum(a, table)] = a;
        a++;
    }
#endif

    //Här vill vi räkna ut kombinationerna för b
    Key minus1lol{};
    minus1lol++;
    std::map<Key, Key> map2;

    /* 000000000000100000000000 - 1
    000000000000011111111111

    000000000001 000000000000 + 1
    000000000001 000000000001
    ...
    000000000010 000000000000  
    000000000011 000000000000
    000000000100 000000000000
    000000000101 000000000000
    000000000110 000000000000
    000000000111 000000000000
    000000001000 000000000000 */
    int abc{};
    //-----------------------------------testar

    b = a;
    b -= minus1lol;
    Key temp_b{};
    if (N % 2 == 0)
        for (int i = 0; i < std::pow(2, static_cast<int>(N / 2)); i++)
        {

            temp_b = b;
            for (int var = C / 2; var < C; var++)
            {
                temp_b.digit[var] = 0;
            }

            std::cout << "kombination " << i << "   b\t" << b << "temp_b " << temp_b << std::endl;
            //   map2[subset_sum(temp_b, table)] = temp_b;
            Key a_hashed = c - subset_sum(temp_b, table);

            if (subset_sum(a_saved[a_hashed] + temp_b, table) == c)
            {
                std::cout << "Difference betwwen c and b " << a_hashed << std::endl;
                std::cout << "Yeay " << abc++ << std::endl;
                cracked.push_back(a_saved[a_hashed] + temp_b);
                //cracked[a_saved[a_hashed] + temp_b];
                //cracked.insert(a_saved[a_hashed] + temp_b);
            }
            b += a;
        }
    else
    {

#if dela_upp_mitten == false
        for (int i = 0; i < std::pow(2, static_cast<int>((N / 2) + 1)); i++)
#else
        for (int i = 0; i < std::pow(2, static_cast<int>((C / 2) + 1) * 5); i++)
#endif
        {

            temp_b = b;
            for (int var = (C / 2) + 1; var < C; var++)
            {
                temp_b.digit[var] = 0;
            }

#if dela_upp_mitten == false

            switch (temp_b.digit[C / 2])
            {
            case 1:
                temp_b.digit[C / 2] = 0;
                break;
            case 2:
                temp_b.digit[C / 2] = 0;
                break;
            case 3:
                temp_b.digit[C / 2] = 0;
                break;
            case 5:
                temp_b.digit[C / 2] = 4;
                break;
            case 6:
                temp_b.digit[C / 2] = 4;
                break;
            case 7:
                temp_b.digit[C / 2] = 4;
                break;
            case 9:
                temp_b.digit[C / 2] = 8;
                break;
            case 10:
                temp_b.digit[C / 2] = 8;
                break;
            case 11:
                temp_b.digit[C / 2] = 8;
                break;
            case 13:
                temp_b.digit[C / 2] = 12;
                break;
            case 14:
                temp_b.digit[C / 2] = 12;
                break;
            case 15:
                temp_b.digit[C / 2] = 12;
                break;
            case 17:
                temp_b.digit[C / 2] = 16;
                break;
            case 18:
                temp_b.digit[C / 2] = 16;
                break;
            case 19:
                temp_b.digit[C / 2] = 16;
                break;
            case 21:
                temp_b.digit[C / 2] = 20;
                break;
            case 22:
                temp_b.digit[C / 2] = 20;
                break;
            case 23:
                temp_b.digit[C / 2] = 20;
                break;
            case 25:
                temp_b.digit[C / 2] = 24;
                break;
            case 26:
                temp_b.digit[C / 2] = 24;
                break;
            case 27:
                temp_b.digit[C / 2] = 24;
                break;
            case 29:
                temp_b.digit[C / 2] = 28;
                break;
            case 30:
                temp_b.digit[C / 2] = 28;
                break;
            case 31:
                temp_b.digit[C / 2] = 28;
                break;
            default:
                break;
            }
#endif

            //std::cout << "kombination " << i << "b\t" << b << "\ttemp_b " << temp_b << std::endl;
            map2[subset_sum(temp_b, table)] = temp_b;

            Key a_hashed = c - subset_sum(temp_b, table);

            if (subset_sum(a_saved[a_hashed] + temp_b, table) == c)
            //if(a_saved.find(a_hashed) != a_saved.end())
            {
                std::cout << "Yeay " << abc++ << std::endl;
                cracked.push_back(a_saved[a_hashed] + temp_b);
               // std::cout << a_saved[a_hashed] + temp_b << std::endl;
                //cracked.insert(a_saved[a_hashed] + temp_b);
            }
            b += a;
        }
    }

/*
    for (auto const &a_pair : a_saved)
    {
        //njjhd
        // passw
        //b**2 = c**2 - a**2
        Key b_hashed = c - a_pair.first;
        if (subset_sum(map2[b_hashed] + a_pair.second, table) == c)
        {
            //std::cout << "Difference betwwen c and a " << b_hashed << std::endl;
            std::cout << "Yeay " << abc++ << std::endl;
            std::cout << a_pair.second + map2[b_hashed] << std::endl;

            cracked.push_back(a_pair.first + map2[b_hashed]);
            //cracked.insert(a_pair.second + map2[b_hashed]);
        }
    }*/

    /*
    for (auto &&i : a_saved)
    {
            Key b_hashed = c - i.first;

            if (subset_sum(a_saved[a_hashed] + i.second, table) == c)
            {
                std::cout << "Yeay " << abc++ << std::endl;
                cracked.insert(a_saved[a_hashed] + i.second);
            } 
    }
    */

    /*
  passwd  15  0 18 18 22  3   011110000010010100101011000011
 1 emqvwg   4 12 16 21 22  6   001000110010000101011011000110
 2 klpepn  10 11 15  4 15 13   010100101101111001000111101101
 3 dinngo   3  8 13 13  6 14   000110100001101011010011001110
 4 cynvra   2 24 13 21 17  0   000101100001101101011000100000
10 oxfmpz  14 23  5 12 15 25   011101011100101011000111111001
13 wtjusd  22 19  9 20 18  3   101101001101001101001001000011
15 ogzvlt  14  6 25 21 11 19   011100011011001101010101110011
18 eboepp   4  1 14  4 15 15   001000000101110001000111101111
20 kodqwt  10 14  3 16 22 19   010100111000011100001011010011
22 bgojvq   1  6 14  9 21 16   000010011001110010011010110000
23 ummbgd  20 12 12  1  6  3   101000110001100000010011000011
28 xmlsaf  23 12 11 18  0  5   101110110001011100100000000101
29 jdkyyg   9  3 10 24 24  6   010010001101010110001100000110
   m2f4eq  12 28  5 30  4 16   011001110000101111100010010000


koaofbmx  10 14  0 14  5  1 12 23   0101001110000000111000101000010110010111
password  15  0 18 18 22 14 17  3   0111100000100101001010110011101000100011
xvbyofnz  23 21  1 24 14  5 13 25   1011110101000011100001110001010110111001
1p1ngsgg  27 15 27 13  6 18  6  6   1101101111110110110100110100100011000110



*/
    //------------------------------------
/*
    std::cout << "\n\n\n";

    std::sort(cracked.begin(), cracked.end());
    std::unique(cracked.begin(), cracked.end());*/
    for (auto &&i : cracked)
    {
        std::cout << i << std::endl;
    }
    /*

    passw 15  0 18 18 22 01111 00000 10010 10010 10110
    p3csw 15 29  2 18 22 01111 11101 00010 10010 10110
    p35cw 15 29 31  2 22 01111 11101 11111 00010 10110
    p355g 15 29 31 31  6 01111 11101 11111 11111 00110
    2dcsw 28  3  2 18 22 11100 00011 00010 10010 10110
    2d5cw 28  3 31  2 22 11100 00011 11111 00010 10110
    2d55g 28  3 31 31  6 11100 00011 11111 11111 00110
    2qssw 28 16 18 18 22 11100 10000 10010 10010 10110
    **/
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "Usage:" << endl;
        cout << argv[0] << " <hashed password> < rand8.txt" << endl;
        return 1;
    }

    // Hashed password.
    Key hashed{argv[1]};

    // Table.
    Key table[N];

    // Read table.
    for (int i{0}; i < N; i++)
    {
        string buffer;
        if (!(cin >> buffer))
        {
            cerr << "Too short table!" << endl;
            return 1;
        }
        table[i] = Key{buffer.c_str()};
    }

    std::cout << "Det hashade: \n"
              << hashed << std::endl;
    auto begin = chrono::high_resolution_clock::now();

    // Find all possible passwords that hash to 'hashed' and print them.
    //------------------------------------------------------------------

    decrypt(hashed, table);

    //------------------------------------------------------------------
    auto end = chrono::high_resolution_clock::now();
    cout << "Decryption took "
         << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
         << " seconds." << endl;

    return 0;
}
