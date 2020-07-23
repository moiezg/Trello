#pragma once
#include<string>
#include<map>

class Card;

class User
{
	private:
		std::string id;
		std::string name;
		std::string email;
		std::map<std::string, Card*>assignedCards; // cardId - > card

	public:
		User(); 
		User( std::string name, std::string email );
		void setId();
		void setName( std::string name );
		void setEmail( std::string email );

		std::string getId();
		std::string getName();
		std::string getEmail();

		std::map<std::string, Card*>getAssignedCards();
		void RemoveAssignedCard( Card* card);
		void AddAssignedCard( Card* card );
		bool IsCardAssignedToMe( Card* card );

};

