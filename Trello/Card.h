#pragma once
#include<string>
#include"BoardList.h"

class User;

class Card
{

private:
	std::string id;
	std::string name;
	std::string desc;
	User* assignedUser;
	void setId();
	BoardList* list;

public:
	Card();
	Card( std::string name );
	void setName( std::string name );
	void setDesc( std::string desc );
	void setAssignedUser( User* user );
	void setBoardList( BoardList* );

	std::string getId();
	std::string getName();
	std::string getDesc();
	User* getAssignedUser();
	BoardList* getBoardList();

};

