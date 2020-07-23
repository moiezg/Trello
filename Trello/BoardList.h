#pragma once
#include<string>
#include <map>
//#include"Board.h"
//#include"Card.h"

class Card;
class Board;
class BoardList
{

	private:
		std::string id;
		std::string name;
		Board* board;
		std::map<std::string, Card*>cards;
		bool IsCardAssignedToList( Card* card );

	public:

		BoardList();
		BoardList(std::string name);
		std::map<std::string, Card*> getCards();
	
		// setters
		void setId();
		void setName( std::string name );
		void setBoard( Board* board );

		// getters
		std::string getId();
		std::string getName();
		Board* getBoard();

		void AddCard( Card* card );
		void RemoveCard( Card* card );
	
};

