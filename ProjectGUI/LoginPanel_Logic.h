#pragma once

#include <wx/wx.h>
class LoginPanel_Logic : public wxPanel
{
public:
	static bool loginValidated(std::string loginName, std::string loginPassword, LoginPanel* loginPanel);

	bool signupNameValidated(std::string signupName, LoginPanel* loginPanel);
	bool signupPasswordValidated(std::string signupPassword1, std::string signupPassword2, LoginPanel* loginPanel);
};

