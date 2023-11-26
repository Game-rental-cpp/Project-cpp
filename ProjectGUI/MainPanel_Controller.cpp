#include "MainPanel_Controller.h"
#include "MainPanel_Logic.h"



/*
This function updates game label (and button) 
@param wxCommandEvent& event
@param wxPanel* gamesPanel
@param std::vector<Game> gamesVector
*/
std::vector<Game> MainPanel_Controller::updateGame(wxCommandEvent& event, wxPanel* gamesPanel, std::vector<Game> gamesVector) {
    
    // Take the button that has been clicked
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());
    // Check if it was taken properly
    if (button) {
        //take the unique name of the clicked button
        wxString buttonName = button->GetName();
        //wxLogMessage(buttonName);

        //Search for the corresponding label for the clicked button 
        wxStaticText* correspondingLabel = wxDynamicCast(gamesPanel->FindWindowByName(buttonName + "Lbl"), wxStaticText);
        
        // Take current label text
        wxString labelText = correspondingLabel->GetLabel();

        // Take number (quantity) from label
        int quantity;
        labelText.AfterLast(' ').ToInt(&quantity);

        //In loop the Game object from the vector is updated and then the label is updated
        for (int i = 0; i < gamesVector.size(); i++) {

            //search for the Game which name is the same as the name of clicked button
            if (gamesVector[i].GetName() == buttonName) {

                //wxLogMessage(wxString(gamesVector[i].GetName().c_str()));
                
                //update json file - set the current value of available games (quantity) decreased by one
                gamesVector[i].SetQuantity(gamesVector[i].GetQuantity() - 1);

                wxString newLabelText = labelText.BeforeLast(' ') + wxString::Format(" %ld", gamesVector[i].GetQuantity());
                correspondingLabel->SetLabel(newLabelText);

                //If there are no games available, disable hire button
                if (gamesVector[i].GetQuantity() == 0) {
                    disableButton(button);               
                }
                    

                break; // The game has been found, break the loop
            }

        }

        correspondingLabel->Refresh();
    }
    return gamesVector;
}

void MainPanel_Controller::disableButton(wxButton* button) {
    wxColour backgroundColor(200, 200, 200);  // Kolor t³a
    wxColour textColor(55, 55, 55);        // Kolor tekstu

    button->SetBackgroundColour(backgroundColor);
    button->SetForegroundColour(textColor);
    button->Enable(false);
}
