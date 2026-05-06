//------------------------------- -*- C++ -*- -------------------------------//
// Copyright Celeritas contributors: see top-level COPYRIGHT file for details
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file celer-geant/src/RunAction.hh
//---------------------------------------------------------------------------//
#pragma once

#include <G4UserRunAction.hh>
#include <atomic>
#include <chrono>

//---------------------------------------------------------------------------//
/*!
 * Manage Celeritas offloading interface at beginning/end of run.
 */
class RunAction : public G4UserRunAction
{
  public:
    //! Construct empty
    RunAction() = default;

//    void Accumulate(size_t n) { total_generated_ += n; }
    static void AddToTotal(size_t n)
    {
        total_generated_.fetch_add(n);
    }
       //! Add to this worker's local count (called from EventAction)
  //  void AddThreadPhotons(size_t n) { thread_photons_ += n; }
  //  size_t thread_photons() const { return thread_photons_; }
    //! Initialize I/O and Celeritas offloading interface
    void BeginOfRunAction(G4Run const* run) final;

    //! Finalize I/O and Celeritas offloading interface
    void EndOfRunAction(G4Run const* run) final;
  private:
    static std::atomic<size_t> total_generated_;
    static std::chrono::steady_clock::time_point transport_start_;
    static std::atomic<size_t> total_celeritas_generated_;
    // Per-worker-thread accumulators (non-static: each RunAction instance
    // is thread-local in Geant4 MT)
    //size_t thread_photons_{0};
    //std::chrono::steady_clock::time_point worker_start_{};

};
