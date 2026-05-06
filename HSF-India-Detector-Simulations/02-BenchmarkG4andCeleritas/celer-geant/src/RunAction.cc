//------------------------------- -*- C++ -*- -------------------------------//
// Copyright Celeritas contributors: see top-level COPYRIGHT file for details
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file celer-geant/src/RunAction.cc
//---------------------------------------------------------------------------//
#include "RunAction.hh"

#include <G4Threading.hh>
#include <accel/ExceptionConverter.hh>
#include <accel/TrackingManagerIntegration.hh>
#include <celeritas/global/CoreParams.hh>
#include <corecel/io/Logger.hh>
#include <corecel/io/OutputRegistry.hh>
#include <CeleritasG4.hh>

#include <accel/detail/IntegrationSingleton.hh>
#include <celeritas/optical/CoreState.hh>
#include <celeritas/optical/OpticalCollector.hh>
#include "EventAction.hh"

std::atomic<size_t> RunAction::total_generated_{0};
std::atomic<size_t> RunAction::total_celeritas_generated_{0};
 
//---------------------------------------------------------------------------//
/*!
 * Initialize master and worker threads in Celeritas.
 */
void RunAction::BeginOfRunAction(G4Run const* run)
{
 
    celeritas::TrackingManagerIntegration::Instance().BeginOfRunAction(run);

    
}

//---------------------------------------------------------------------------//
/*!
 * Write thread-local ROOT file and return Celeritas to an invalid state.
 */
void RunAction::EndOfRunAction(G4Run const* run)
{
    using Mode = celeritas::OffloadMode;
    auto& integration = celeritas::detail::IntegrationSingleton::instance();

    
    auto& tmi = celeritas::TrackingManagerIntegration::Instance();
    
    if (integration.mode() == Mode::enabled && G4Threading::IsWorkerThread())
    {
        auto& local
            = dynamic_cast<celeritas::LocalTransporter&>(integration.local_offload());
        auto const& optical_collector
            = integration.shared_params().problem_loaded().optical_collector;
        auto const& accum
            = optical_collector->optical_state(local.GetState()).accum();
           total_celeritas_generated_.fetch_add(accum.steps);
    
    }
    
    if (G4Threading::IsMasterThread())
    {
        std::cout << "[Celeritas] Total optical photons generated: "
            << total_celeritas_generated_.load() << "\n";
    
        std::cout << "[Geant4]    Total optical photons generated: "
                  << total_generated_.load() << std::endl;              
    }

    // Return Celeritas to an invalid state
    tmi.EndOfRunAction(run);
}
