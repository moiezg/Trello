
#include"Util.h"
#include "BoardList.h"
#include"Card.h"
BoardList::BoardList()
{

}

BoardList::BoardList(std::string name)
{
	setName( name );
	setId();
}

void BoardList::setId()
{
	this->id = Util::getNewId();
}

void BoardList::setName( std::string name )
{
	this->name = name;
}

void BoardList::setBoard( Board* board )
{
	this->board = board;
}

std::string BoardList::getId()
{
	return id;
}

std::string BoardList::getName()
{
	return name;
}

Board* BoardList::getBoard()
{
	return board;
}

std::map<std::string, Card*> BoardList::getCards()
{
	return cards;
}

bool BoardList::IsCardAssignedToList( Card* card )
{
	return ( cards.find( card->getId() ) != cards.end() );
}

void BoardList::AddCard( Card* card)
{
	cards[card->getId()] = card;
	card->setBoardList( this );
}

void BoardList::RemoveCard( Card* card )
{
	if(IsCardAssignedToList(card))
		cards.erase( cards.find( card->getId() ) );
}