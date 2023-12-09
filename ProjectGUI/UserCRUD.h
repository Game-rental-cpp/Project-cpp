#pragma once
#include <string>


class UserCRUD {
	public:
		static bool isLogged();
		static void CreateUser(std::string login, std::string password);
		static std::string ReadLogged();
		static void Update_logged(std::string newContent);
		static bool DoesExist(std::string);

};