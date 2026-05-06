// SteppingAction.cc

#include "SteppingAction.hh"

#include <G4ProcessManager.hh>
#include <G4Step.hh>
#include <G4SystemOfUnits.hh>
#include <G4Track.hh>
#include <G4VProcess.hh>

#include "EventAction.hh"

SteppingAction::SteppingAction(EventAction* event_action)
    : event_action_(event_action)
{
}


void SteppingAction::UserSteppingAction(G4Step const* step)
{
    auto* track = step->GetTrack();

    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
    {
        
        if (track->GetParentID() > 0)
        {
            event_action_->AddGeneratedPhoton();
        }
    }
}