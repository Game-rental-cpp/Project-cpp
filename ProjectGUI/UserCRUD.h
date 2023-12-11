#pragma once
#include <string>

class UserCRUD {
	public:
		static bool isLogged();
		static void CreateUser(std::string login, std::string password);
		static std::string ReadLogged();
		static void Update_logged(std::string newContent);
		static std::string ReadUser(std::string login);
		static void UpdateUser(std::string login, std::string body);
		static bool DoesExist(std::string login);

};