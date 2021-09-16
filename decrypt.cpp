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
        std::cout << "kombination " << i << "   a\t" << a++ << std::endl;
        saved[a] = subset_sum(a, table);
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
    if (N % 2 == 0)
        for (int i = 0; i < std::pow(2, static_cast<int>(N / 2)); i++)
        {

            b += (saved.rbegin()->first-minus1lol);
            std::cout << "kombination " << i << "   b\t" << b << std::endl;
            map2[b] = subset_sum(b, table);
        }
    else
    {
        for (int i = 0; i < std::pow(2, static_cast<int>(N / 2)+1); i++)
        {

            b += (saved.rbegin()->first-minus1lol);
            std::cout << "kombination " << i << "   b\t" << b << std::endl;
            map2[b] = subset_sum(b, table);
        }
    }
    std::cout << "sista i a " << saved.rbegin()->first << std::endl;


    

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
        Key temp = c - i.second;

        if (subset_sum(i.first + map2[temp], table) == c)
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
