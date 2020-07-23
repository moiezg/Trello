#pragma once

#include<map>
#include<string>
enum class RETURN_CODE
{
    SUCCESS,
    UNKNOWN_ERROR,
    INVALID_USER_ID,
    INVALID_BOARD_ID,
    INVALID_LIST_ID,
    INVALID_CARD_ID,
    INVALID_PRIVACY_TYPE,
    USER_ALREADY_EXISTS,
    ERROR_DELETING_CARD,
    ERROR_DELETING_LIST,
    ERROR_DELETING_BOARD,
    USER_ALREADY_ADDED_TO_BOARD,
    USER_NOT_MEMBER_OF_BOARD,
    USER_NOT_ASSIGNED_TO_CARD,
    INVALID_CARD_MOVE_OPERATION
};

static std::map<RETURN_CODE, std::string>errorsList = {

        {RETURN_CODE::SUCCESS,                        "Operation completed successfully"},
        {RETURN_CODE::UNKNOWN_ERROR,                  "ERROR: Unknown error occurred"},
        {RETURN_CODE::INVALID_USER_ID ,               "Error: Invalid email id "},
        {RETURN_CODE::INVALID_BOARD_ID,               "Error: Invalid board id"},
        {RETURN_CODE::INVALID_LIST_ID,                "Error: Invalid list id"},
        {RETURN_CODE::INVALID_CARD_ID,                "Error: Invalid card id"},
        {RETURN_CODE::INVALID_PRIVACY_TYPE,           "Error: Invalid privacy type"},
        {RETURN_CODE::USER_ALREADY_EXISTS,            "Error: User already exists"},
        {RETURN_CODE::ERROR_DELETING_CARD,            "Error: Unexpected error while deleting card "},
        {RETURN_CODE::ERROR_DELETING_LIST,            "Error: Unexpected error while deleting list "},
        {RETURN_CODE::ERROR_DELETING_BOARD,           "Error: Unexpected error while deleting board "},
        {RETURN_CODE::USER_ALREADY_ADDED_TO_BOARD,    "Error: User already added to board "},
        {RETURN_CODE::USER_NOT_MEMBER_OF_BOARD,       "Error: User not member of board "},
        {RETURN_CODE::USER_NOT_ASSIGNED_TO_CARD,      "Error: No user assigned to card "},
        {RETURN_CODE::INVALID_CARD_MOVE_OPERATION,    "Error: Invalid card move operation. Card can be moved within same board only "}

};

class Error
{
public :

    static std::string getReturnCodeMessage( RETURN_CODE error )
    {
        if( errorsList.find( error ) == errorsList.end() )
        {
            return errorsList[RETURN_CODE::UNKNOWN_ERROR];
        }
        else
        {
            return errorsList[error];
        }
    }

};