#pragma once

#include <wx/wx.h>
class LoginPanel_Logic
{
public:
	static bool LoginValidated(std::string loginName, std::string loginPassword, LoginPanel* loginPanel);
	static bool SignupValidated(std::string signupName, std::string signupPassword1, std::string signupPassword2, LoginPanel* loginPanel);
};

