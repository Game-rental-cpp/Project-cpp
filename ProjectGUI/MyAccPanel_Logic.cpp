#include "MyAccPanel_Logic.h"

#include "User.h"
#include "UserNormal.h"
#include "UserPremium.h"
#include "json.hpp"
#include "Game.h"

#include "UserCRUD.h"
#include "GameCRUD.h"

User* MyAccPanel_Logic::user = nullptr;

User* MyAccPanel_Logic::GetUser() {
    return MyAccPanel_Logic::user;
}


void MyAccPanel_Logic::SetUser(User* u) {
    MyAccPanel_Logic::user = u;
}

using json = nlohmann::json;

/*
This function creates an object of Game type based on json files
@param string name - the name of a game.json file inside Games directory
@returns Game* game - game model
*/
Game* MyAccPanel_Logic::CreateGameFromJSON(std::string gameName)
{
    std::string name;
    int quantity;
    int nrOfRentals;
    float rate;
    std::map<std::string, int> userRates;

    std::string gameStr = GameCRUD::readGame(gameName);

    json jsonData = json::parse(gameStr);

    name = jsonData["name"];
    quantity = jsonData["quantity"];
    nrOfRentals = jsonData["nrOfRentals"];
    rate = jsonData["rate"];
    userRates = jsonData["userRates"];
        
    Game* game = new Game(name, quantity, nrOfRentals, rate, userRates); 

    return game;
}
