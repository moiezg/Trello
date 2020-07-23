#include <iostream>
#include <vector>
#include <random>
#include <functional>
#include <algorithm>
#include<map>
#include<string>
const int IDLENGTH = 24;

const std::vector<char>charSet = { '0','1','2','3','4',
                                       '5','6','7','8','9',
                                       'a','b','c','d','e','f',
                                       'g','h','i','j','k',
                                       'l','m','n','o','p',
                                       'q','r','s','t','u',
                                       'v','w','x','y','z'
                                  };

class Util
{
    public:
   
        static std::string random_string( size_t length, std::function<char( void )> rand_char )
        {
            std::string str( length, 0 );
            std::generate_n( str.begin(), length, rand_char );
            return str;
        }

        static std::string getNewId()
        {
            const auto ch_set = charSet;
            std::default_random_engine rng( std::random_device {}( ) );
            std::uniform_int_distribution<> dist( 0, ch_set.size() - 1 );
            auto randchar = [ ch_set, &dist, &rng ] ()
            {
                return ch_set[dist( rng )];
            };

            std::string newId = random_string( IDLENGTH, randchar );
            return newId;

        }

};



