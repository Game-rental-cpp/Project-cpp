#pragma once
#include <string>

class GameCRUD {
public:
	static int countGames();
	static std::string readGame(std::string);
	static void updateGame(std::string name, int quantity, int nrOfLoans);
};