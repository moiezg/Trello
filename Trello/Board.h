#pragma once
#include<string>
#include <map>
//#include "User.h"
#include"BoardList.h"
class User;

enum class Privacy
{
	PUBLIC,
	PRIVATE
};

class Board
{
	private:
		std::string id;
		std::string name;
		Privacy privacy;
		std::map<std::string, User*>members;
		std::map<std::string, BoardList*>boardList;

	public:

		Board();
		Board( std::string name );
		void setId();
		void setName( std::string name );
		void setPrivacy( Privacy privacy );
	

		std::string getId();
		std::string getName();
		std::map<std::string, BoardList*> getBoardLists();
		
		Privacy getPrivacy();

		void AddMember( User* user );
		void RemoveMember( User* user );
		void AddBoardList( BoardList* boarList );
		void RemoveBoardList( BoardList* boarList );
		bool IsUserAddedInBoard( std::string email );
		std::string getPrivacyInString( );
};

