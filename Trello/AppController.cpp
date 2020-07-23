#include "AppController.h"
#include<iostream>
#include"Json.h"

/*
*              User related operation
*/
bool AppController::IsValidUser( std::string email )
{
	return ( users.find( email ) != users.end() );
}

std::string AppController::CreateNewUser( std::string name, std::string email )
{
	if(IsValidUser(email))
	{
		std::cout << "User already exists \n";
		return "";
	}
	User user( name, email );
	users[user.getEmail()] = user;
	return user.getId();
}

std::string AppController::ShowAnUser(std::string email)
{
	
	if( !IsValidUser( email ) )
		return Error::getReturnCodeMessage( RETURN_CODE::INVALID_USER_ID );

	std::string jsonData;

	User& user = users[email];

	std::vector<std::tuple<std::string, std::string, bool>>data;
	std::map<std::string, Card*>assignedCards = user.getAssignedCards();

	std::tuple<std::string, std::string, bool>id = { "id", user.getId() , true };
	std::tuple<std::string, std::string, bool>name = { "name",user.getName(), true };
	
	std::string jsonCardDataInList; 
	int cntCardsAdded = 0;

	jsonCardDataInList.append( "[ " );

	// gather all assigned card details
	for( auto& curCard : assignedCards )
	{
		++cntCardsAdded;
		Card* card = curCard.second;
		jsonCardDataInList.append( ShowACard( card->getId() ) );
		if( cntCardsAdded < assignedCards.size() )
			jsonCardDataInList.append( ", " );
	}
	jsonCardDataInList.append( " ]" );

	std::tuple<std::string, std::string, bool>cards = { "assignedCards", jsonCardDataInList, false };
	data.push_back( id );
	data.push_back( name );
	data.push_back( cards );

	jsonData = Json::getEntityInJson( data );
	return jsonData;
}


/*
*              Board related operation
*/

bool AppController::IsValidBoard( std::string boardId )
{
	return ( boards.find( boardId ) != boards.end() );
}


std::string AppController::ShowABoard( std::string boardId )
{
	if( !IsValidBoard(boardId) )
	{
		return Error::getReturnCodeMessage( RETURN_CODE::INVALID_BOARD_ID );
	}
	std::string jsonData;
	std::vector<std::tuple<std::string, std::string, bool>>data;

	Board& board = boards[boardId];
	std::map<std::string, BoardList*>listOfBoardList = board.getBoardLists();

	std::tuple<std::string, std::string, bool>id = { "id", board.getId() , true };
	std::tuple<std::string, std::string, bool>name = { "name",board.getName(), true };
	std::tuple<std::string, std::string, bool>privacy = { "privacy", board.getPrivacyInString(), true };
	std::tuple<std::string, std::string, bool>url = { "url", GetBoardURL(board.getId()), true };

	int cntBoardListAdded = 0;
	std::string jsonBoardListDataInList;

	jsonBoardListDataInList.append( "[ " );
	for( auto& curList : listOfBoardList )
	{
		++cntBoardListAdded;
		BoardList* list = curList.second;
		jsonBoardListDataInList.append( ShowABoardList( list->getId() ) );

		if( cntBoardListAdded < listOfBoardList.size() )
			jsonBoardListDataInList.append( ", " );
	}
	jsonBoardListDataInList.append( " ]" );

	std::tuple<std::string, std::string, bool>lists = { "lists", jsonBoardListDataInList, false };
	data.push_back( id );
	data.push_back( name );
	data.push_back( privacy );
	data.push_back( url );
	data.push_back( lists );
	
	jsonData = Json::getEntityInJson( data );
	return jsonData;
}

std::string AppController::ShowAllBoards()
{
	std::string json;
	int cntBoardAdded = 0;

	json.append( "[ " );
	for( auto& board : boards )
	{
		++cntBoardAdded;
		json.append( ShowABoard( board.second.getId() ) );
		if( cntBoardAdded < boards.size() )
			json.append( "," );
	}
	json.append( " ]" );

	return json;
}

std::string AppController::CreateNewBoard( std::string name )
{ 
	Board board( name );
	boards[board.getId()] = board;
	return board.getId();
}

RETURN_CODE AppController::DeleteBoard( std::string boardId )
{
	//  Delete all list in the board
	//  then delete board

	if( IsValidBoard( boardId ) )
	{
		return RETURN_CODE::INVALID_BOARD_ID;
	}
	
	Board board = boards[boardId];
	std::map<std::string, BoardList*> boardList = board.getBoardLists();

	for( auto lst = boardList.begin(); lst != boardList.end(); lst++ )
	{
		BoardList* list = lst->second;
		RETURN_CODE error = DeleteBoardList( list->getId() );

		if( RETURN_CODE::SUCCESS != error)
		{
			return RETURN_CODE::ERROR_DELETING_BOARD;
		}
	}
	
	boards.erase( boards.find( board.getId() ) );

	return RETURN_CODE::SUCCESS;
	
}

RETURN_CODE AppController::AddBoardMember( std::string boardId, std::string email )
{
	if( false == IsValidBoard( boardId ) )
	{
		return RETURN_CODE::INVALID_BOARD_ID;
	}

	if( false == IsValidUser( email ) )
	{
		return RETURN_CODE::INVALID_USER_ID;
	}

	Board &board = boards[boardId];
	if( true == board.IsUserAddedInBoard( email ) )
	{
		return RETURN_CODE::USER_ALREADY_ADDED_TO_BOARD;
	}
	else
	{
		board.AddMember( &users[email] );
	}

	return RETURN_CODE::SUCCESS;
}

RETURN_CODE AppController::RemoveBoardMember( std::string boardId, std::string email )
{
	if( false == IsValidBoard( boardId ) )
	{
		return RETURN_CODE::INVALID_BOARD_ID;
	}

	if( false == boards[boardId].IsUserAddedInBoard( email ) )
	{
		return RETURN_CODE::USER_NOT_MEMBER_OF_BOARD;
	}

	boards[boardId].RemoveMember( &users[email] );

	return RETURN_CODE::SUCCESS;
}

RETURN_CODE AppController::SetPrivacy( std::string boardId, std::string privacy )
{
	if( false == IsValidBoard( boardId ) )
	{
		return RETURN_CODE::INVALID_BOARD_ID;
	}

	Privacy newPrivacy;

	if( privacy == "PUBLIC" )
		newPrivacy = Privacy::PUBLIC;
	else if( privacy == "PRIVATE" )
		newPrivacy = Privacy::PRIVATE;
	else
	{
		return RETURN_CODE::INVALID_PRIVACY_TYPE;
	}

	boards[boardId].setPrivacy( newPrivacy );

	return RETURN_CODE::SUCCESS;
}

std::string AppController::GetBoardURL( std::string boardId )
{
	if(!IsValidBoard(boardId))
	{ 
		return Error::getReturnCodeMessage( RETURN_CODE::INVALID_BOARD_ID );
	}
	std::string boardURL;
	boardURL = protocol + host + boardEndPoint + "/" + boards[boardId].getId();
	return boardURL;
}
/*
*              Board list related operation
*/

std::string AppController::CreateBoardList( std::string boardId, std::string listName )
{
	if( false == IsValidBoard( boardId ) )
	{
		std::cout << "Invalid Board Id " << boardId << std::endl;
		return "";
	}

	BoardList list( listName);
	boardLists[list.getId()] = list;

	boards[boardId].AddBoardList( &boardLists[list.getId()] );
	
	return list.getId();
}

RETURN_CODE AppController::DeleteBoardList( std::string boardListId )
{
	// remove all card attached to the list
	// remove list detail from the board
	// remove list entry from boardLists

	if( false == IsValidBoardList( boardListId ) )
	{
		return RETURN_CODE::INVALID_LIST_ID;
	}

	BoardList &list = boardLists[boardListId];
	std::map<std::string, Card*>cards = list.getCards();

	// removing card
	for( auto card = cards.begin(); card != cards.end(); card++ )
	{
		Card* crd = card->second;
		RETURN_CODE error = DeleteCard(crd->getId());

		if(  RETURN_CODE::SUCCESS != error )
			return RETURN_CODE::ERROR_DELETING_LIST;
	}

	// removing list entry from board
	Board* board = list.getBoard();
	board->RemoveBoardList( &list );

	// removing list entry from boardLists
	boardLists.erase( boardLists.find( list.getId() ) );

	return RETURN_CODE::SUCCESS;
}

std::string AppController::ShowABoardList( std::string boardListId )
{
	if( !IsValidBoardList( boardListId ) )
		return Error::getReturnCodeMessage( RETURN_CODE::INVALID_LIST_ID );

	
	std::string jsonData;
	std::vector<std::tuple<std::string, std::string, bool>>data;

	BoardList &list = boardLists[boardListId];
	std::map<std::string, Card*>listOfcards = list.getCards();

	std::tuple<std::string, std::string, bool>id = { "id", list.getId() , true};
	std::tuple<std::string, std::string, bool>name = { "name",list.getName(), true };


	std::string jsonCardDataInList;
	int cntCardsAdded = 0;

	jsonCardDataInList.append( "[" );
	// gather all card details
	for( auto& curCard : listOfcards )
	{
		++cntCardsAdded;
		Card* card = curCard.second;
		jsonCardDataInList.append( ShowACard( card->getId() ) );
		if( cntCardsAdded < listOfcards.size() )
			jsonCardDataInList.append( ", " );
	}
	jsonCardDataInList.append( "]" );

	std::tuple<std::string, std::string, bool>cards = { "cards", jsonCardDataInList, false};

	data.push_back( id );
	data.push_back( name );
	data.push_back( cards );

	jsonData = Json::getEntityInJson( data );
	return jsonData;
}

std::string AppController::ShowAllBoardLists()
{
	std::string json;

	int cntBoardListsAdded = 0;

	json.append( "[" );
	for( auto& list : boardLists )
	{
		++cntBoardListsAdded;
		json.append( ShowABoardList( list.second.getId() ) );
		if( cntBoardListsAdded < boardLists.size() )
			json.append( "," );
	}
	json.append( "]" );

	return json;
}

bool AppController::IsValidBoardList( std::string listId )
{
	return ( boardLists.find( listId ) != boardLists.end() );
}

/*
*              Card related operation
*/

bool AppController::IsValidCard( std::string cardId )
{
	return ( cards.find( cardId ) != cards.end() );
}

std::string AppController::CreateCard( std::string boardListId, std::string name )
{
	if( false == IsValidBoardList( boardListId ) )
	{
		std::cout << "Invalid list id " << boardListId << std::endl;
		return "";
	}

	Card card( name );
	cards[card.getId()] = card;

	boardLists[boardListId].AddCard( &cards[card.getId()] );
	return card.getId();

}


bool AppController::IsCardAssignedToUser( std::string cardId )
{
	return ( NULL != cards[cardId].getAssignedUser());
}

RETURN_CODE AppController::DeleteCard( std::string cardId )
{
	// remove entry of card from assigned user
	// remove entry of card from assigned boardList
	// remove card entry from cards
	
	if( false == IsValidCard( cardId ) )
	{
		return RETURN_CODE::INVALID_CARD_ID;
	}

	Card &card = cards[cardId];

	// check if this card is assigned to user, if yes then remove entry of this card from that user's assigned card list
	if( IsCardAssignedToUser(cardId))
	{
		
		User* user = card.getAssignedUser();
		if(user->IsCardAssignedToMe(&card))
			user->RemoveAssignedCard( &card );

	}

	// Remove card entry form the BoardList
	BoardList* list = cards[cardId].getBoardList();
	list->RemoveCard( &card );
		
	// Remove the card from the cards list
	cards.erase( cards.find( cardId ) );

	return RETURN_CODE::SUCCESS;
}

RETURN_CODE AppController::AssignUserToCard( std::string email, std::string cardId )
{
	// check if valid email;
	// check if card was assigned to some othe user, if yes, remove card details from that user
	// assign card to new user


	if( false == IsValidCard( cardId ) )
	{
		return RETURN_CODE::INVALID_CARD_ID;
	}

	if( false == IsValidUser( email ) )
	{
		return RETURN_CODE::INVALID_USER_ID;
	}

	Card &card = cards[cardId];
	User* user = card.getAssignedUser();

	if( NULL != user )		// card was assigned to some user
	{
		user->RemoveAssignedCard(&card);
	}
	
	User &newUser = users[email];
	card.setAssignedUser( &newUser );

	return RETURN_CODE::SUCCESS;
}

RETURN_CODE AppController::RemoveUserFromCard( std::string cardId )
{
	// remove card details from user card list
	// assign card to null

	if( false == IsValidCard( cardId ) )
	{
		return RETURN_CODE::INVALID_CARD_ID;
	}

	Card& card = cards[cardId];
	User* user = card.getAssignedUser();
	if( NULL == user )
	{
		return RETURN_CODE::USER_NOT_ASSIGNED_TO_CARD;
	}
	else
	{
		user->RemoveAssignedCard( &card );
	}

	return RETURN_CODE::SUCCESS;
}

std::string AppController::ShowACard( std::string cardId )
{
	if( !IsValidCard( cardId ) )
	{
		return  Error::getReturnCodeMessage( RETURN_CODE::INVALID_CARD_ID);
	}

	Card &card = cards[cardId];
	std::string email = ( card.getAssignedUser() != NULL ? card.getAssignedUser()->getEmail() : "" );
	std::string listId = card.getBoardList()->getId();

	std::string jsonData;
	std::vector< std::tuple<std::string, std::string, bool>>data;

	std::tuple<std::string, std::string, bool>id = {"id",card.getId(), true};
	std::tuple<std::string, std::string, bool>name = { "name",card.getName() , true};
	std::tuple<std::string, std::string, bool>desc = { "desc",card.getDesc(), true };
	std::tuple<std::string, std::string, bool>assignedUser = { "assignedUser",email, true };
	

	data.push_back( id );
	data.push_back( name );
	data.push_back( desc );
	data.push_back( assignedUser );
	
	jsonData = Json::getEntityInJson( data );
	return jsonData;
}

std::string AppController:: ShowAllCards()
{
	std::string json;
	
	int cntCardListAdded = 0;

	json.append( "[ " );
	for( auto& card : cards )
	{
		++cntCardListAdded;
		json.append( ShowACard(card.second.getId()) );
		if( cntCardListAdded < cards.size() )
			json.append( "," );
	}
	json.append( " ]" );

	return json;
}

RETURN_CODE AppController::MoveCard( std::string cardId, std::string fromListId, std::string toListId )
{
	// check if all list id and card id are valid or not
	// check if both src list and dest list are from same board.

	if( !IsValidCard( cardId ) )
		return RETURN_CODE::INVALID_CARD_ID;

	if( !IsValidBoardList( fromListId ) || !IsValidBoardList( toListId ) )
		return RETURN_CODE::INVALID_LIST_ID;

	Board* fromBoard = boardLists[fromListId].getBoard();
	Board* toBoard = boardLists[fromListId].getBoard();

	if( fromBoard->getId() != toBoard->getId() and (fromListId == toListId))
	{
		return RETURN_CODE::INVALID_CARD_MOVE_OPERATION;
	}

	// remove card detail from source list
	// add card detail to dest list
	BoardList &fromBoardList = boardLists[fromListId];
	BoardList& toBoardList = boardLists[toListId];

	Card& card = cards[cardId];
	fromBoardList.RemoveCard( &card );
	toBoardList.AddCard( &card );

	return RETURN_CODE::SUCCESS;
}

std::map<std::string, User>& AppController::getUsers()
{
	return users;
}

std::map<std::string, Board>& AppController::getBoards()
{
	return boards;
}

std::map<std::string, BoardList>& AppController::getBoardLists()
{
	return boardLists;
}

std::map<std::string, Card> AppController::getCards()
{
	return cards;
}