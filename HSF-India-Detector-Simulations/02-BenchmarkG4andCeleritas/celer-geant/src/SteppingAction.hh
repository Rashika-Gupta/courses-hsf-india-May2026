// SteppingAction.hh
#pragma once

#include <set>
#include <unordered_map>
#include <vector>
#include <G4OpBoundaryProcess.hh>
#include <G4OpticalPhoton.hh>
#include <G4UserSteppingAction.hh>

class EventAction;

class SteppingAction : public G4UserSteppingAction
{
  public:
    explicit SteppingAction(EventAction* event_action);

    void UserSteppingAction(G4Step const* step) override;

  private:
    EventAction* event_action_;
};