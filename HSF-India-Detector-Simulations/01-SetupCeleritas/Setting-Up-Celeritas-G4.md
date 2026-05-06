## Step 1: Access the Environment

Open the Binder environment using the link below, then open a terminal:

https://binderhub.ssl-hep.org/v2/gh/research-software-collaborations/courses-hsf-india-April2026/dune?gpuModel=&gpuCount=1&cudaMajor=undefined&cudaMinor=undefined&site=nrp&memory=4.0&cpu=1&qos=Guaranteed

#Open the terminal

---

## Step 2: Set Up Geant4
Source the framework to make Geant4, CMake, and Ninja available:

`source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh`

Then load the required packages:

```
setup geant4 v4_11_2_p02 -q e26:prof
setup cmake v3_27_4
setup ninja v1_11_1
```
In case, setup does not work check which versions are available

`ups list -aK+ geant4`

Verify the installation (optional):
```
echo "$Geant4_DIR"
echo "$Geant4_DIR"
cmake --version
```     
## Step 3: Download Celeritas using Github

Navigate to your working directory : `cd /data/YourName/`

```
git clone https://github.com/celeritas-project/celeritas.git
cd celeritas
```

Option A: Simple Build

```
mkdir build
cd build
cmake ..
make -j 64
```

Make sure that ` CELERITAS_CORE_GEO               ORANGE`

Option B: Build with Custom Flags

Configure with specific options
```
cmake -S . -B build -G Ninja   -DCMAKE_INSTALL_PREFIX=/data/rashika/opt/celeritas   -DGeant4_DIR="$Geant4_DIR"   -DCELERITAS_USE_Geant4=ON   -DCELERITAS_USE_VecGeom=OFF   -DCELERITAS_USE_ROOT=OFF   -DCELERITAS_USE_HepMC3=OFF   -DCELERITAS_USE_MPI=OFF   -DCELERITAS_BUILD_TESTS=OFF   -DCELERITAS_BUILD_DOCS=OFF   -DCELERITAS_BUILTIN_CLI11=ON   -DCELERITAS_BUILTIN_nlohmann_json=ON
```

Build the files 
```
cmake --build build -j
```

## Step 4: Verify the build

```
cd build/bin
./celer-g4 --help
```
If you see the help output, Celeritas is successfully built!

## Step 5: Run an example
Explore the `celer-geant` example and read its README for guidance on running a simulation.

## Glossary
Quick Command Reference
|Command            |        Description     |
|-------------------|-----------------------|
| `git clone <url>`	| Downloads a copy of a remote repository to your local machine |
| `CMake` | A cross-platform build system generator — it doesn't compile code itself, but produces the files (Makefiles, Ninja files, etc.) that a compiler uses to build the project |
| `CMakeLists.txt` | The configuration file CMake reads — it defines the project name, source files, dependencies, compiler options, and build targets |
| `cmake ..`	| Reads the project's CMakeLists.txt and generates build files |
| `cmake -S . -B build -G Ninja -D...`	| Configures the build with custom options/flags before compiling |
| `cmake --build build -j`	| Compiles the source code using all available CPU cores |
| `make -j 64`	| Compiles using make with 64 parallel jobs to speed up the build |
| `source <file>`    | Loads environment variables and settings from a script into your current shell |
| `setup <package>`    | Activates a specific software package in the DUNE/UPS environment |
