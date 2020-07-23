#include "User.h"
#include"Util.h"
#include"Card.h"

User::User()
{

}

User::User( std::string name, std::string email )
{
	setName( name );
	setEmail( email );
	setId();
}

void User::setId( )
{
	this->id = Util::getNewId();
}

void User::setName( std::string name )
{
	this->name = name;
}

void User::setEmail( std::string email )
{
	this->email = email;
}

std::string User::getId()
{
	return id;
}

std::string User::getName()
{
	return name;
}

std::string User::getEmail()
{
	return email;
}

std::map<std::string, Card*> User::getAssignedCards()
{
	return assignedCards;
}

bool User::IsCardAssignedToMe( Card* card )
{
	return ( assignedCards.find( card->getId() ) != assignedCards.end() );
}

void User::AddAssignedCard( Card* card )
{
	assignedCards[card->getId()] = card;
}

void User::RemoveAssignedCard( Card* card )
{
	if(IsCardAssignedToMe(card))
		assignedCards.erase( assignedCards.find( card->getId() ) );
}