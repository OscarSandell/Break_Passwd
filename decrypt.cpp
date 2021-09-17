#include <iostream>
#include <chrono>
#include <string>
#include "key.h"
#include <map>
#include <unordered_map>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <sstream>
using namespace std;

/*
Decrypt funktion
*/
//kanske typ

#define dela_upp_mitten false

 string to_string_from_key(const Key & arg)
    {
        std::stringstream ss{};
        for (int i{0}; i < N; i++)
        {
            ss << arg.bit(i);
        }
        return ss.str();

    }

template <>
struct std::hash<Key>
{
    size_t operator()(const Key & arg)const
    {
        size_t value = std::hash<string>{}(to_string_from_key(arg));

        return value;
    }
   
};



void decrypt(const Key &c, Key *table)
{
    //Vi skapar en map för a som håller koll på a:s nycklar och de hashade lösenorden för de nycklarna
    //std::map<Key, Key> a_saved;

    std::unordered_map<Key, std::vector<Key>> a_saved{};
    std::vector<Key> cracked{};

    Key a{};
    Key b{};
//Vi räknar ut all kopmbinationer för a
//Här är nyckeln 1 4 9 16 25 och elementen är 1 2 3 4 5
    for (int i = 0; i < std::pow(2, static_cast<int>(N / 2)); i++)
    {
        //std::cout << "kombination " << i << "   a\t" << a << std::endl;
        a_saved[subset_sum(a, table)].push_back(a);
        a++;
    }

    std::cout << "a_saved " << a_saved.size() << std::endl;

    //Här vill vi räkna ut kombinationerna för b
    Key minus1lol{};
    minus1lol++;
    std::map<Key, Key> map2;
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

            //std::cout << "kombination " << i << "   b\t" << b << "temp_b " << temp_b << std::endl;
            Key a_hashed = c - subset_sum(temp_b, table);

            auto it = a_saved.find(a_hashed);
            if (it != a_saved.end())
            {
                for (auto const &i : it->second)
                {
                    cracked.push_back(i + temp_b);
                }
            }
            b += a;
        }
    else
    {
        for (int i = 0; i < std::pow(2, static_cast<int>((N / 2) + 1)); i++)

        {

            temp_b = b;
            for (int var = (C / 2) + 1; var < C; var++)
            {
                temp_b.digit[var] = 0;
            }
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

            //std::cout << "kombination " << i << "b\t" << b << "\ttemp_b " << temp_b <<  " Hashed " << subset_sum(temp_b, table) << std::endl;
            Key a_hashed = c - subset_sum(temp_b, table);
            auto it = a_saved.find(a_hashed);
            if (it != a_saved.end())
            {
                for (auto const &i : it->second)
                {
                    cracked.push_back(i + temp_b);
                }
            }

            b += a;
        }
    }
    for (auto &&i : cracked)
    {
        std::cout << i << std::endl;
    }
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
