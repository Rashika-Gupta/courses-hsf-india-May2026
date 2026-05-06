//------------------------------- -*- C++ -*- -------------------------------//
// Copyright Celeritas contributors: see top-level COPYRIGHT file for details
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file celer-geant/src/ActionInitialization.cc
//---------------------------------------------------------------------------//
#include "ActionInitialization.hh"

#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "StackingAction.hh"
#include "SteppingAction.hh"

//---------------------------------------------------------------------------//
/*!
 * Initialize Celeritas offload on master thread.
 */
void ActionInitialization::BuildForMaster() const
{
    this->SetUserAction(new RunAction());
}

//---------------------------------------------------------------------------//
/*!
 * Set up all worker thread user-actions and Celeritas offload interface.
 */
void ActionInitialization::Build() const
{
    this->SetUserAction(new RunAction());
    this->SetUserAction(new PrimaryGeneratorAction());
    auto* event_action = new EventAction();
    this->SetUserAction(event_action);
    this->SetUserAction(new SteppingAction(event_action));
    this->SetUserAction(new StackingAction());

}
