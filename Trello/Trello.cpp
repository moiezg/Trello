// Trello.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include "AppController.h"

using  namespace std;

AppController *app = nullptr;

vector<string> UserMenu =
{
   "Create a new User",
   "Show an user",
   "Return to previous menu",  // This option shall always be the last option
};

 vector<string> BoardMenu = 
 {
    "Create a board",
    "Delete a board",
    "Change board privacy",
    "Assign user to board",
    "Remove user from board",
    "Show a board",
    "Show all boards",
    "GetBoardURL",
    "Return to previous menu",  // This option shall always be the last option
};

 vector<string> BoardListMenu =
 {
    "Create a board list",
    "Delete a board list",
    "Show a board list",
    "Show all board lists",
    "Return to previous menu",  // This option shall always be the last option
 };

 vector<string> CardMenu =
 {
     "Create a card",
     "Delete a card",
     "Assign user to card",
     "Remove user from card",
     "Move card within same board",
     "Show a card",
     "Show all cards",
     "Return to previous menu",  // This option shall always be the last option
 };

 vector<string>MainMenu =
 {
     "User Operation",
     "Board operation",
     "Board list operation",
     "Card operation",
     "Exit"

 };

void ShowUserMenu()
 {
     std::cout << " \n --------------- AVAILABLE USER OPTIONS --------------- \n";
     for( int iCnt = 0; iCnt < UserMenu.size(); iCnt++ )
     {
         cout << iCnt + 1 << ". " << UserMenu[iCnt] << std::endl;
     }
}

void ShowBoardMenu()
{
    std::cout << " \n --------------- AVAILABLE BOARD OPTIONS --------------- \n";
    for( int iCnt = 0; iCnt < BoardMenu.size(); iCnt++ )
    {
        cout << iCnt+1 << ". " << BoardMenu[iCnt] << std::endl;
    }
}

void ShowBoardListMenu()
{
    std::cout << " \n --------------- AVAILABLE BOARD LIST OPTIONS --------------- \n";
    for( int iCnt = 0; iCnt < BoardListMenu.size(); iCnt++ )
    {
        cout << iCnt + 1 << ". " << BoardListMenu[iCnt] << std::endl;
    }
}

void ShowCardMenu()
{
    std::cout << " \n --------------- AVAILABLE CARD OPTIONS --------------- \n";
    for( int iCnt = 0; iCnt < CardMenu.size(); iCnt++ )
    {
        cout << iCnt + 1 << ". " << CardMenu[iCnt] << std::endl;
    }
}


void ShowMainMenu()
{
    std::cout << " \n --------------- AVAILABLE MENU OPTIONS --------------- \n";
    for( int iCnt = 0; iCnt < MainMenu.size(); iCnt++ )
    {
        cout << iCnt+1 << ". " << MainMenu[iCnt] << std::endl;
    }
}

/*
*   User related operation
*/
void PerformShowAnUser()
{
    string email;
    cout << "Enter email id: ";
    cin >> email;

    string json =  app->ShowAnUser(email);
    if( !json.empty() )
        cout << json << "\n";
}

void PerformCreateNewUser()
{
    string name, email;
    cout << "Enter name: ";
    cin >> name;

    cout << "Enter email: ";
    cin >> email;

    string userId = app->CreateNewUser( name, email );

    if( !userId.empty() )
    {
        cout << "User " << userId << " created \n";
    }
}

/*
*   Board related operation
*/

void PerformCreateBoard()
{
    string boardName;

    cout << "Enter board name: ";
    cin >> boardName;

    std::string boardId = app->CreateNewBoard( boardName );

    if( !boardId.empty() )
        std::cout << "Board " << boardId << " created" << std::endl;
}

void PerformShowABoard()
{
    string boardId;
    cout << "Show board id: ";
    cin >> boardId;

    string json = app->ShowABoard( boardId );
    if( !json.empty() )
        cout << json << "\n";
}

void PerformShowAllBoards()
{
    string json = app->ShowAllBoards();
    if( !json.empty() )
        cout << json << "\n";
}

void PerformDeleteBoard()
{
    string boardId;
    cout << "Enter board id: ";
    cin >> boardId;

    RETURN_CODE code = app->DeleteBoard( boardId );
   
    cout << Error::getReturnCodeMessage( code ) << "\n";
}


void PerformAddBoardMember()
{
    string email, boardId;

    cout << "Enter board id: ";
    cin >> boardId;

    cout << "Enter email id: ";
    cin >> email;

    RETURN_CODE code = app->AddBoardMember( boardId, email );

    cout << Error::getReturnCodeMessage( code ) << "\n";
}

void PerformRemoveBoardMember()
{
    string email, boardId;

    cout << "Enter board id: ";
    cin >> boardId;

    cout << "Enter email id: ";
    cin >> email;

    RETURN_CODE code = app->RemoveBoardMember( boardId, email );
    cout << Error::getReturnCodeMessage( code ) << "\n";
}

void PerformChangeBoardPrivacy()
{
    string boardId, privacy;

    cout << "Enter board id: ";
    cin >> boardId;

    cout << "Enter privacy type [ PUBLIC , PRIVATE ]: ";
    cin >> privacy;

    RETURN_CODE code = app->SetPrivacy( boardId, privacy );
    cout << Error::getReturnCodeMessage( code ) << "\n";
}

void PerformGetBoardURL()
{
    string boardId;
    cout << "Enter board id: ";
    cin >> boardId;

    string url = app->GetBoardURL( boardId );
    cout << url << std::endl;
}

/*
*   Board list related operation
*/
void PerformShowABoardList()
{
    string boardListId;
    cout << "Enter list id: ";
    cin >> boardListId;

    std::string json = app->ShowABoardList( boardListId );
    if( !json.empty() )
        cout << json << "\n";
}

void PerformShowAllBoardLists()
{
    string json = app->ShowAllBoardLists();
    if( !json.empty() )
        cout << json << "\n";
}

void PerformCreateBoardList()
{
    string boardListName, boardId, boardListId;
    
 
    cout << "Enter board id: ";
    cin >> boardId;

    cout << "Enter board list name: ";
    cin >> boardListName;

    boardListId = app->CreateBoardList( boardId, boardListName );

    if(!boardListId.empty())
        std::cout << "Board list " << boardListId << " created" << std::endl;
}

void PerformDeleteBoardList()
{
    string boardListId;
    cout << "Enter board list id: ";
    cin >> boardListId;

    RETURN_CODE code = app->DeleteBoardList( boardListId );
    cout << Error::getReturnCodeMessage( code ) << "\n";
}

/*
*   Card related operation
*/


void PerformShowACard()
{
    string cardId;
    cout << "Enter card id: ";
    cin >> cardId;

    std::string json = app->ShowACard( cardId );

    if( !json.empty() )
        cout << json << "\n";
}

void PerformShowAllCards()
{
    string json = app->ShowAllCards();
    if( !json.empty() )
        cout << json << "\n";
}

void PerformCreateCard()
{
    string boardListId, cardName;

    cout << "Enter board list id: ";
    cin >> boardListId;

    cout << "Enter card name: ";
    cin >> cardName;

    string cardId = app->CreateCard( boardListId, cardName );
    if( !cardId.empty() )
    {
        cout << "Card " << cardId << " created \n";
    }
}

void PerformDeleteCard()
{
    string carId;
    cout << "Enter card id: ";
    cin >> carId;

    RETURN_CODE code = app->DeleteCard( carId );

    cout << Error::getReturnCodeMessage( code ) << "\n";
}

void PerformAssignUserToCard()
{
    string cardId, email;

    cout << "Enter email id: ";
    cin >> email;

    cout << "Enter card id: ";
    cin >> cardId;

    RETURN_CODE code = app->AssignUserToCard( email, cardId );
   
    cout << Error::getReturnCodeMessage( code ) << "\n";
}


void PerformUnAssignCard()
{
    string cardId;
    cout << "Enter card id: ";
    cin >> cardId;

    RETURN_CODE code = app->RemoveUserFromCard( cardId );
    cout << Error::getReturnCodeMessage( code ) << "\n";
}

void PerformMoveCard()
{
    string cardId, fromBoardListId, toBoardListId;
    cout << "Enter card id to move: ";
    cin >> cardId;

    cout << "Enter source board id ";
    cin >> fromBoardListId;

    cout << "Enter target board id ";
    cin >> fromBoardListId;

    RETURN_CODE code = app->MoveCard( cardId, fromBoardListId, toBoardListId );
    cout << Error::getReturnCodeMessage( code ) <<"\n";
}

void UserOperation()
{
    int userChoice;
    do
    {
        ShowUserMenu();
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch( userChoice )
        {
            case 1:
            {
                PerformCreateNewUser();
                break;
            }
            case 2:
            {
                PerformShowAnUser();
                break;
            }
            case 3:
            {
                break;
            }
            default:
            {
                cout << "Invalid option. Enter [1:" << UserMenu.size() << "]" << std::endl;
                break;
            }
        }
    } while( userChoice != UserMenu.size() );
}

void BoardOperation()
{
    int userChoice;

    do
    {
        ShowBoardMenu();
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch( userChoice )
        {
            case 1:
            {
                PerformCreateBoard();
                break;
            }

            case 2:
            {
                PerformDeleteBoard();
                break;
            }

            case 3:
            {
                PerformChangeBoardPrivacy();
                break;
            }

            case 4:
            {
                PerformAddBoardMember();
                break;
            }

            case 5:
            {
                PerformRemoveBoardMember();
                break;
            }

            case 6:
            {
                PerformShowABoard();
                break;
            }

            case 7:
            {
                PerformShowAllBoards();
                break;
            }

            case 8:
            {
                PerformGetBoardURL();
                break;
            }
            case 9:
            {
                break;
            }
            default:
            {
                cout << "Invalid option. Enter [1:" << BoardMenu.size() << "]" << std::endl;
                break;
            }
        }

    } while( userChoice != BoardMenu.size() );
}

void BoardListOperation()
{
    int userChoice;
    do
    {
        ShowBoardListMenu();
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch( userChoice )
        {
            case 1:
            {
                PerformCreateBoardList();
                break;
            }
            case 2:
            {
                PerformDeleteBoardList();
                break;
            }
            case 3:
            {
                PerformShowABoardList();
                break;
            }
            case 4 :
            {
                PerformShowAllBoardLists();
                break;
            }
            case 5:
            {
                break;
            }
            default:
            {
                cout << "Invalid option. Enter [1:" << BoardListMenu.size() << "]" << std::endl;
                break;
            }
       }
    } while( userChoice != BoardListMenu.size() );
}


void CardOperation()
{
    int userChoice;
    do
    {
        ShowCardMenu();
        cout << "Enter your choice: ";
        cin >> userChoice;

        switch( userChoice )
        {
            case 1:
            {
                PerformCreateCard();
                break;
            }
            case 2:
            {
                PerformDeleteCard();
                break;
            }
            case 3:
            {
                PerformAssignUserToCard();
                break;
            }
            case 4:
            {
                PerformUnAssignCard();
                break;
            }
            case 5:
            {
                PerformMoveCard();
                break;
            }
            case 6:
            {
                PerformShowACard();
                break;
            }
            case 7:
            {
                PerformShowAllCards();
                break;
            }
            case 8:
            {
                break;
            }
            default:
            {
                cout << "Invalid option. Enter [1:" << CardMenu.size() << "]" << std::endl;
                break;
            }
        }
    } while( userChoice != CardMenu.size() );
}

int main()
{
        
    app = new AppController();

    int userOption;
    do
    {
        ShowMainMenu();
        cout << "Enter your option: ";
        cin >> userOption;

        switch( userOption )
        {
            case 1:
            {
                UserOperation();
                break;
            }
            case 2:
            {
                BoardOperation();
                break;

            }
            case 3:
            {
                BoardListOperation();
                break;
            }
            case 4:
            {
                CardOperation();
                break;
            }
            case 5:
            {
                break;
            }
            default:
            {
                cout << "Invalid option. Enter [1:" << MainMenu.size() << "]" << std::endl;
                break;
            }
        }
    } while( userOption != MainMenu.size() );

    delete app;
}
