# Celeritas-Geant4 Offloading App — LHCb RICH Validation

This application demonstrates **GPU-accelerated particle transport** using Celeritas as a Geant4 offload backend. We offload **electrons** and **optical photons** to Celeritas. The geometry is a simplified **LHCb RICH detector** (`lhcb-rich-simplified-geometry.gdml`, located at the project root).

## Simulation Setup

- **Primary particle**: electron, 10 GeV kinetic energy, shot along the z-axis from the origin
- **Physics**: FTFP_BERT + `G4OpticalPhysics` (Cherenkov emission enabled)
- **Offloaded to Celeritas**: electrons and optical photons
- **Geometry**: simplified LHCb RICH detector — `lhcb-rich-simplified-geometry.gdml` (project root)

The 10 GeV positron traverses the RICH radiator medium, emitting Cherenkov optical photons which are then tracked by Celeritas.

---

## Dependencies
In the current example, we use the instructions on setting up Celeritas in `setting-up-instructions.md`
- Geant4 v11+ with `GEANT4_USE_GDML=ON` and `GEANT4_BUILD_MULTITHREADED=ON`
- Celeritas v0.6+ with `CELERITAS_USE_Geant4=ON`
- ROOT
- nlohmann_json

---

## Build and Run

```sh
mkdir build && cd build
cmake ..
make
./celer-geant ../example-input.json
```

## To Link Celeritas 
make sure that this is added in the `CMakeLists.txt`

```
# Point CMake to your Celeritas installation
set(Celeritas_DIR "/path/to/celeritas/build/lib/cmake/Celeritas")
find_package(Celeritas 0.7 REQUIRED)

# Check Geant4 support is enabled
if(NOT CELERITAS_USE_Geant4)
  message(SEND_ERROR "Celeritas must be built with Geant4 support")
endif()

# Link against Celeritas — use celeritas_target_link_libraries (not plain target_link_libraries)
celeritas_target_link_libraries(celer-geant
  Celeritas::celeritas
  Celeritas::G4
  ${Geant4_LIBRARIES}
  ...
)
```