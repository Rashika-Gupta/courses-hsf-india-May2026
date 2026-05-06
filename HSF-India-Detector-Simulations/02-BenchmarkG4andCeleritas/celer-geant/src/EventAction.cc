//------------------------------- -*- C++ -*- -------------------------------//
// Copyright Celeritas contributors: see top-level COPYRIGHT file for details
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file celer-geant/src/EventAction.cc
//---------------------------------------------------------------------------//
#include "EventAction.hh"

#include <G4Event.hh>
#include <corecel/io/Logger.hh>
#include "RunAction.hh"
#include "JsonReader.hh"

//---------------------------------------------------------------------------//
/*!
 * Construct thread-local event action and set up event logging.
 */
EventAction::EventAction() : G4UserEventAction()
{
    auto json = JsonReader::Instance();
    log_progress_ = (json.contains("log_progress"))
                        ? json.at("log_progress").get<size_t>()
                        : 1;
}

//---------------------------------------------------------------------------//
/*!
 * Thread-local begin of event action.
 */
void EventAction::BeginOfEventAction(G4Event const* event)
{
    // Initialise generated photon count for event
    generated_photons_ = 0;

    
}

//---------------------------------------------------------------------------//
/*!
 * Thread-local end of event action.
 */
void EventAction::EndOfEventAction(G4Event const* event)
{
    // Add generated photon count to total for run
    RunAction::AddToTotal(generated_photons_);

}
