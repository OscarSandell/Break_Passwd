#include <iostream>
#include <chrono>
#include <string>
#include "key.h"
#include <map>
#include <math.h>
#include <vector>
using namespace std;

/*
Decrypt funktion
*/
//kanske typ
void decrypt(const Key &c, Key *table)
{
    //Vi skapar en map för a som håller koll på a:s nycklar och de hashade lösenorden för de nycklarna
    std::map<Key, Key> saved;
    std::vector<Key> cracked{};

    Key a{};
    Key b{};

    std::cout << "a\t" << a << std::endl;
    std::cout << "b\t" << b << "\n"
              << std::endl;
    //Vi räknar ut all kopmbinationer för a
    for (int i = 0; i < std::pow(2, static_cast<int>(N / 2)); i++)
    {
        std::cout << "kombination " << i << "   a\t" << a << std::endl;
        saved[a] = subset_sum(a, table);
        a++;
    }

    /*
    for (auto &&i : saved)
    {
        std::cout << "Nyckeln " << i.first << "\nhashade " << i.second << "\n\n";
    }
    */
    //Här vill vi räkna ut kombinationerna för b
    Key minus1lol{};
    minus1lol++;
    std::map<Key, Key> map2;
    b = a;
    Key temp_b{};
    if (N % 2 == 0)
        for (int i = 0; i < std::pow(2, static_cast<int>(N / 2)); i++)
        {

            b += (saved.rbegin()->first - minus1lol);
            temp_b = b;
            for (int i = 0; i < C / 2; i++)
            {
                temp_b.digit[i] = 0;
            }

            std::cout << "kombination " << i << "   b\t" << b << "temp_b" << temp_b << std::endl;
            map2[b] = subset_sum(b, table);

           // map2[subset_sum(b, table)] = b;
        }
    else
    {
        for (int i = 0; i < std::pow(2, static_cast<int>(N / 2) + 1); i++)
        {

            b += (saved.rbegin()->first - minus1lol);
            temp_b = b;
            for (int i = (C/2)+1; i < C; i++)
            {
                temp_b.digit[i] = 0;
            }
            switch (temp_b.digit[C/2])
            {
            case 1 :
                temp_b.digit[C/2] = 0;
                break;
            case 2 :
                temp_b.digit[C/2] = 0;
                break;
            case 3 :
                temp_b.digit[C/2] = 0;
                break;
            case 5 :
                temp_b.digit[C/2] = 4;
                break;
            case 6 :
                temp_b.digit[C/2] = 4;
                break;
            case 7 :
                temp_b.digit[C/2] = 4;
                break;
            case 9 :
                temp_b.digit[C/2] = 8;
                break;
            case 10 :
                temp_b.digit[C/2] = 8;
                break;
            case 11 :
                temp_b.digit[C/2] = 8;
                break;
            case 13 :
                temp_b.digit[C/2] = 12;
                break;
            case 14 :
                temp_b.digit[C/2] = 12;
                break;
            case 15 :
                temp_b.digit[C/2] = 12;
                break;
            case 17 :
                temp_b.digit[C/2] = 16;
                break;
            case 18 :
                temp_b.digit[C/2] = 16;
                break;
            case 19 :
                temp_b.digit[C/2] = 16;
                break;
            case 21 :
                temp_b.digit[C/2] = 20;
                break;
            case 22 :
                temp_b.digit[C/2] = 20;
                break;
            case 23 :
                temp_b.digit[C/2] = 20;
                break;
            case 25 :
                temp_b.digit[C/2] = 24;
                break;
            case 26 :
                temp_b.digit[C/2] = 24;
                break;
            case 27 :
                temp_b.digit[C/2] = 24;
                break;
            case 29 :
                temp_b.digit[C/2] = 28;
                break;
            case 30 :
                temp_b.digit[C/2] = 28;
                break;
            case 31 :
                temp_b.digit[C/2] = 28;
                break;
            default:
                break;
            }

            //temp_b.digit[C/2] = 
         //   std::cout << "kombination " << i << "   b\t" << b << std::endl;
              std::cout << "kombination " << i << "   b\t" << b << "\t temp_b" << temp_b << std::endl;
            map2[b] = subset_sum(b, table);
            //map2[subset_sum(b, table)] = ;
        }
    }
    //11111 11111 11 | 101 01010 10101 
    std::cout << "sista i a " << saved.rbegin()->first << std::endl;
    std::cout << saved.rbegin()->first + minus1lol << std::endl;
    std::cout << saved.rbegin()->first + minus1lol + saved.rbegin()->first << std::endl;

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

    /*     else
    {
        for (int i = static_cast<int>((N / 2)); i < std::pow(2, static_cast<int>(N); i++)
        {
            std::cout << "kombination " << i << "   a\t" << a++ << std::endl;
            saved[a] = subset_sum(a, table);
        }
    } */
    //Här vill vi kolla om a:s nyckel + b:nyckel hashat blir c där vi använder map2 för att  spara b:s hashade lösenord som nyckel och det ohasade som elementet
    int abc{};
    for (auto &&i : saved)
    {
        //njjhd
        // passw
        Key diffrence_between_c_and_a = c - i.second;

        if (subset_sum(i.first + map2[diffrence_between_c_and_a], table) == c)
        {
            std::cout << "Yeay " << abc++ << std::endl;
        }
    }

    // c - a
    /*
    0->12   12->25

    25-a = b

a  = (00000000000)0000000000000
b =   000000000000(0000000000000)
c - a = b
    

    0000
    0001
    0010
    0011
    0100
    1000
    1100
*/

    /* for (int i{0}; i < N; i++)
        to << hashed.bit(i);
     */
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
