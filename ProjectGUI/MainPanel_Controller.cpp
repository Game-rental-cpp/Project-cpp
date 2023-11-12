#include "MainPanel_Controller.h"
#include <wx/dir.h>
#include <string>


//std::vector<Game> MainPanel_Controller::vec;

std::vector<Game> MainPanel_Controller::updateGame(wxCommandEvent& event, wxPanel* gamesPanel, std::vector<Game> gamesVector) {
    // Pobierz obiekt przycisku, który zosta³ naciœniêty
    wxButton* button = dynamic_cast<wxButton*>(event.GetEventObject());


    // SprawdŸ, czy uda³o siê pobraæ obiekt przycisku
    if (button) {
        //take the unique name of the clicked button
        wxString buttonName = button->GetName();
        //wxLogMessage(buttonName);

        //Search for the corresponding label for the clicked button
        wxStaticText* correspondingLabel = wxDynamicCast(gamesPanel->FindWindowByName(buttonName + "Lbl"), wxStaticText);

        // Pobierz aktualn¹ wartoœæ etykiety
        wxString labelText = correspondingLabel->GetLabel();

        // Pobierz liczbê z tekstu etykiety
        int quantity;
        labelText.AfterLast(' ').ToInt(&quantity);

        //W pêtli jest aktualizowany odpowiedni obiekt Game z wektora, a nastêpnie na tej podstawie aktuazlizowany jest laebl
        for (int i = 0; i < gamesVector.size(); i++) {

            if (gamesVector[i].GetName() == buttonName) {

                //wxLogMessage(wxString(gamesVector[i].GetName().c_str()));
                gamesVector[i].SetQuantity(gamesVector[i].GetQuantity() - 1);

                wxString newLabelText = labelText.BeforeLast(' ') + wxString::Format(" %ld", gamesVector[i].GetQuantity());
                correspondingLabel->SetLabel(newLabelText);

                if (gamesVector[i].GetQuantity() == 0)
                    button->Enable(false);

                break; // Znaleziono grê, przerywamy pêtlê
            }

        }

        correspondingLabel->Refresh();
    }
    return gamesVector;
}