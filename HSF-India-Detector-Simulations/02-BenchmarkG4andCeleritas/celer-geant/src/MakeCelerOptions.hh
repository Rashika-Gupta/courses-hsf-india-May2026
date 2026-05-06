//------------------------------- -*- C++ -*- -------------------------------//
// Copyright Celeritas contributors: see top-level COPYRIGHT file for details
// SPDX-License-Identifier: (Apache-2.0 OR MIT)
//---------------------------------------------------------------------------//
//! \file celer-geant/src/MakeCelerOptions.hh
//---------------------------------------------------------------------------//
#pragma once

#include <G4Electron.hh>
#include <G4Gamma.hh>
#include <G4MuonMinus.hh>
#include <G4MuonPlus.hh>
#include <G4Neutron.hh>
#include <G4Positron.hh>
#include "G4OpticalPhoton.hh"
#include <accel/AlongStepFactory.hh>
#include <accel/SetupOptions.hh>
#include <accel/TrackingManagerConstructor.hh>
#include <celeritas/phys/PDGNumber.hh>
#include <corecel/Assert.hh>


inline celeritas::SetupOptions MakeCelerOptions()
{
    celeritas::SetupOptions opts;

    opts.max_num_tracks = 1024 * 8;
    opts.initializer_capacity = 1024 * 64;

    opts.offload_particles = {
        G4Electron::Definition(),
        G4Positron::Definition(),
        G4Gamma::Definition()//,
      
    };

    opts.ignore_processes = {"CoulombScat"};
    opts.make_along_step = celeritas::UniformAlongStepFactory();

    
    opts.sd.enabled = false;
    celeritas::OpticalSetupOptions optical;
    optical.capacity.generators = 100000;
    optical.capacity.tracks =65536;
    optical.capacity.primaries = 100000;
    opts.optical = optical;
 
    return opts;
}