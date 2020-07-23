#pragma once
#include<map>
#include<string>
#include"User.h"
#include"Board.h"
#include"BoardList.h"
#include"Card.h"
#include"Util.h"
#include"Error.h"

const std::string protocol = "https:://";
const std::string host = "www.mytrello.com";
const std::string boardEndPoint = "/board";

class AppController
{
private:
	std::map<std::string, Board>boards;
	std::map<std::string, BoardList>boardLists;
	std::map<std::string, Card>cards;
	std::map<std::string, User>users;

	
public:
	AppController()
	{

	}

	
	// User related operations
	std::string  CreateNewUser( std::string name, std::string email );
	std::string ShowAnUser(std::string email);

	// Board related operations
	std::string ShowABoard(std::string boardId);
	std::string ShowAllBoards();
	std::string CreateNewBoard( std::string name );
	RETURN_CODE DeleteBoard( std::string boardId );
	RETURN_CODE AddBoardMember( std::string boardId, std::string email );
	RETURN_CODE RemoveBoardMember( std::string boardId, std::string email );
	RETURN_CODE SetPrivacy( std::string boardId, std::string privacy );
	std::string GetBoardURL( std::string boardId );

	// BoardList related operations
	std::string CreateBoardList( std::string boardId, std::string listName );
	RETURN_CODE DeleteBoardList( std::string boardListId );
	std::string ShowABoardList( std::string boardListId );
	std::string ShowAllBoardLists();

	// Card related operations
	std::string CreateCard( std::string boardListId, std::string name );
	RETURN_CODE DeleteCard( std::string cardId );
	RETURN_CODE AssignUserToCard( std::string email, std::string cardId );
	RETURN_CODE RemoveUserFromCard(std::string cardId );
	RETURN_CODE MoveCard( std::string cardID, std::string fromListId, std::string toListId );    // todo: across list in same board only
	std::string ShowACard( std::string cardId );
	std::string ShowAllCards();

	
	private :

		// User related operations
		bool IsValidUser( std::string email );
		std::map<std::string, User>& getUsers();


		// board related operations
		std::map<std::string, Board>& getBoards();
		bool IsValidBoard( std::string boardId );

		// board list related operations
		bool IsValidBoardList( std::string listId );
		std::map<std::string, BoardList>& getBoardLists();


		// card related operations
		bool IsValidCard( std::string cardId );
		bool IsCardAssignedToUser( std::string cardId );
		std::map<std::string, Card> getCards();

};

