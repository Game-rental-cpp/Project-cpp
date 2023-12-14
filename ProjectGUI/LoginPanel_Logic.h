#pragma once

#include <wx/wx.h>
class LoginPanel_Logic : public wxPanel
{
public:
	static bool loginValidated(std::string loginName, std::string loginPassword, LoginPanel* loginPanel);
	static bool signupValidated(std::string signupName, std::string signupPassword1, std::string signupPassword2, LoginPanel* loginPanel);
};

