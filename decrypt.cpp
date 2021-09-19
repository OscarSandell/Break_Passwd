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

string to_string_from_key(const Key &arg)
{
    std::stringstream ss{};
    for (int i{0}; i < N; i++)
    {
        ss << arg.bit(i);
    }
    return ss.str();
}




 #include <thread>
 #include <bitset>
template <>
struct std::hash<Key>
{
    /*size_t operator()(const Key &arg) const
    {
        return std::hash<string>{}(to_string_from_key(arg));
    }*/
    /*
    size_t operator()(const Key &arg) const
    {
        size_t value{};
        for (int i = 0; i < C; i++)
        {
            value = value + (arg.digit[i] + 1) * 3;
        }
        value = value % static_cast<size_t>(std::pow(2, N / 2.0)*1.3);
        return value;
    }
    */
  
  
    size_t operator()(const Key &arg) const
    {   
        

        size_t value{};
        for (int i = 0; i < N; i++)
        {
            if (arg.bit(i) == 1)
            {   
                        
                value += i << i;
              //  value += i << 1;
                
            }
            //else
           // {
             //   value += i << 0;
            //}

                                  // std::cout << std::bitset<16>(value) << std::endl;


        }
        //std::this_thread::sleep_for (std::chrono::seconds(2));
        return value;
    }
     /*size_t operator()(const Key &arg) const
    {   
        

        size_t value{};
        for (int i = 1; i < C+1; i++)
        {
            for (int a{1}; a < C+1; a++)
            {
                if(arg.bit(a*i))
                value += value << 1;
                else
                value += value << 0;
            }
            
                                 //  std::cout << std::bitset<16>(value) << std::endl;


        }
        //std::this_thread::sleep_for (std::chrono::seconds(2));
        return value;
    }*/
};

void decrypt(const Key &c, Key *table)
{
    //Vi skapar en map för a som håller koll på a:s nycklar och de hashade lösenorden för de nycklarna

    std::unordered_map<Key, std::vector<Key>> a_saved{};
    std::vector<Key> cracked{};

    Key a{};
    Key b{};
    //Vi räknar ut all kopmbinationer för a
    //Här är nyckeln 1 4 9 16 25 och elementen är 1 2 3 4 5
    for (int i = 0; i < static_cast<int>(std::pow(2, std::floor(N / 2.0))); i++)
    {
        //std::cout << "kombination " << i << "   a\t" << a << std::endl;
        a_saved[subset_sum(a, table)].push_back(a);
        a++;
    }

    //Räkna antalet kollisioner

    //Här vill vi räkna ut kombinationerna för b
    std::map<Key, Key> map2;
    //-----------------------------------testar

    for (int i = 0; i < static_cast<int>(std::pow(2, std::ceil(N / 2.0))); i++)
    {
        //std::cout << "kombination " << i << "   b\t" << b << std::endl;
        Key a_hashed = c - subset_sum(b, table);

        auto it = a_saved.find(a_hashed);
        if (it != a_saved.end())
        {
            for (auto const &i : it->second)
            {
                cracked.push_back(i + b);
            }
        }
        b += a;
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
