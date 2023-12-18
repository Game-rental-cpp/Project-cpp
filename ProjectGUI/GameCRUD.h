#pragma once
#include <string>
#include <map>

class GameCRUD {
public:
	static int countGames();
	static std::string readGame(std::string);
    std::map<std::string, int> userRates;  // Dodana mapa userRates
	static void updateGame(std::string name, int quantity, int nrOfLoans, float rate, std::map<std::string, int> userRates);
};