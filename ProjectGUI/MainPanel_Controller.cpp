#include "MainPanel_Controller.h"
#include <wx/dir.h>
#include <string>


//std::vector<Game> MainPanel_Controller::vec;

std::vector<Game> MainPanel_Controller::updateGame(wxCommandEvent& event, wxPanel* gamesPanel, std::vector<Game> gamesVector) {
    // Pobierz obiekt przycisku, kt�ry zosta� naci�ni�ty
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());


    // Sprawd�, czy uda�o si� pobra� obiekt przycisku
    if (button) {
        //take the unique name of the clicked button
        wxString buttonName = button->GetName();
        //wxLogMessage(buttonName);

        //Search for the corresponding label for the clicked button
        wxStaticText* correspondingLabel = wxDynamicCast(gamesPanel->FindWindowByName(buttonName + "Lbl"), wxStaticText);

        // Pobierz aktualn� warto�� etykiety
        wxString labelText = correspondingLabel->GetLabel();

        // Pobierz liczb� z tekstu etykiety
        int quantity;
        labelText.AfterLast(' ').ToInt(&quantity);

        //W p�tli jest aktualizowany odpowiedni obiekt Game z wektora, a nast�pnie na tej podstawie aktuazlizowany jest laebl
        for (int i = 0; i < gamesVector.size(); i++) {

            if (gamesVector[i].GetName() == buttonName) {

                //wxLogMessage(wxString(gamesVector[i].GetName().c_str()));
                gamesVector[i].SetQuantity(gamesVector[i].GetQuantity() - 1);

                wxString newLabelText = labelText.BeforeLast(' ') + wxString::Format(" %ld", gamesVector[i].GetQuantity());
                correspondingLabel->SetLabel(newLabelText);

                if (gamesVector[i].GetQuantity() == 0)
                    button->Enable(false);

                break; // Znaleziono gr�, przerywamy p�tl�
            }

        }

        correspondingLabel->Refresh();
    }
    return gamesVector;
}