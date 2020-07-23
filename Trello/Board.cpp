#include "Board.h"
#include"User.h"
#include"Util.h"


Board::Board()
{
	setPrivacy( Privacy::PUBLIC );
}

Board::Board( std::string name )
{
	setName( name );
	setId();
	setPrivacy( Privacy::PUBLIC );
}

void Board::setId()
{
	this->id = Util::getNewId();
}

void Board::setName( std::string name )
{
	this->name = name;
}

void Board::setPrivacy( Privacy privacy )
{
	this->privacy = privacy;
}

void Board::AddMember( User* user )
{
	members[user->getEmail()] = user;
}

void Board::RemoveMember( User* user )
{	
	//if(IsUserAddedInBoard(user->getEmail()))
		members.erase( members.find( user->getEmail() ) );
}

void Board::AddBoardList( BoardList* list )
{
	boardList[list->getId()] = list;
	list->setBoard( this );
}

void Board::RemoveBoardList( BoardList* list )
{
	boardList.erase( boardList.find( list->getId() ) );
}

bool Board::IsUserAddedInBoard( std::string email )
{
	return ( members.find( email ) != members.end() );
}

std::string Board::getId()
{
	return id;
}

std::string Board::getName()
{
	return name;
}

Privacy Board::getPrivacy()
{
	return privacy;
}

std::map<std::string, BoardList*> Board::getBoardLists()
{
	return boardList;
}

std::string Board:: getPrivacyInString()
{
	Privacy privacy = getPrivacy();
	if( privacy == Privacy::PRIVATE )
		return "PRIVATE";
	else if( privacy == Privacy::PUBLIC )
		return "PUBLIC";
	else
		return "INVALID_PRIVACY";	// this code should never run
}