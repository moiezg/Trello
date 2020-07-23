#pragma once

/*

Author: Ravi Shankar
Description: This is an utility class used by the app to convert array of key values data pairs into json format.

*/
#include<vector>
#include<string>
#include<utility>

const char entityOpenBracket = '{';
const char entityCloseBracket = '}';
const char listOpenBacket = '[';
const char listCloseBacket = ']';

class Json
{
    private:
        
        
       
    public:
    
        Json()
        {
             
        }

        /*
         *   This method converts key value into quoted format. 
         *   The value is enclosed within double quotes only if parameter 'isValueToBeInsideQuote' is tuue.
         *    
        */
            
       static std::string getPropInString( const std::string &key, const std::string &value , bool isValueToBeInsideQuote )
        {
            std::string str;
            if( isValueToBeInsideQuote )
                str = " \"" + key + "\": " + "\"" + value + "\"";
            else
                str = " \"" + key + "\": "  + value ;

            return str;
        }


       /*
        *    This method accepts a tuple of 3 members. The 1st tuple element member denotes key, 2nd denotes value and 3rd member of tuple
        *    is a boolean value. The boolen value if is true then the 2nd member of tuple will be enclosed inside double quotes else not.
        *    For eaxmple. let the tuple be:
        *    < name , John , true >
        *    Then the return string from this function will be as
        *    {"name": "John"}
        *
        *    If tuple is as:
        *    <name, John, false>
        *    Then the return string from this function will be as
        *    {"name": John}
        *
        *    Note: In json, key (ie, name ) will always be enclosed within double quotes, but whether value will be enclosed or not will be decided by 
        *    3rd tuple member
        *
       */
        static std::string getEntityInJson( const std::vector< std::tuple<std::string, std::string, bool>>&data )
        {
            int propAddedCnt = 0;
            std::string json;

            if( data.size() <= 0 )
                return json;

            json += entityOpenBracket;

            for( auto &prop : data )
            {
                ++propAddedCnt ;
                std::string key = std::get<0>(prop);
                std::string val = std::get<1>( prop );
                bool isValueToBeInsideQuote = std::get<2>( prop );
                json.append( getPropInString( key, val , isValueToBeInsideQuote) );

                // to not add ',' after last prop item
                if(propAddedCnt < data.size())
                    json.append( ", " );
            }

            json += entityCloseBracket;

            return json;
        }
       
};
