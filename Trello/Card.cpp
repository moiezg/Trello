#include "Card.h"
#include"User.h"
#include"Util.h"

Card::Card()
{

}

Card::Card(std::string name)
{
	setName( name );
	setId();
	setAssignedUser( NULL );
}

void Card::setId()
{
	this->id = Util::getNewId();
}

void Card::setName( std::string name )
{
	this->name = name;
}

void Card::setDesc( std::string desc )
{
	this->desc = desc;
}

void Card::setAssignedUser( User* user )
{
	this->assignedUser = user;	// todo : also update the user that this card is assigned to him
}

void Card::setBoardList( BoardList* list)
{
	this->list = list;
}

std::string Card::getId()
{
	return id;
}

std::string Card::getName()
{
	return name;
}

std::string Card::getDesc()
{
	return desc;
}

User* Card::getAssignedUser()
{
	return assignedUser;
}

BoardList* Card::getBoardList()
{
	return list;
}