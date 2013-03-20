//////////////////////////////////////////////////////////////////////////
// License & Copyright
// ===================
// 
// Copyright 2012 Christopher M Poole <mail@christopherpoole.net>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////


#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "SensitiveDetector.hh"

// GEANT4 //
#include "G4VUserDetectorConstruction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"

#include "boost/python.hpp"
#include "pyublas/numpy.hpp"


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();
    void MakeMaterials();

    void SetFilmDensity(G4double density) {
        film_density = density;
    };

    void SetFilmThickness(G4double thickness) {
        film_thickness = thickness;
    }

    pyublas::numpy_vector<float> GetEnergyHistogram() {
        return detector->energy_histogram;
    }

    pyublas::numpy_vector<float> GetCountsHistogram() {
        return detector->counts_histogram;
    }

    void SetDimensions(G4int x, G4int y, G4int z) {
        this->detector->SetDimensions(x, y, z);
    };

    void SetMinimumCutoff(G4int x, G4int y, G4int z) {
        this->detector->SetMinimumCutoff(x, y, z);
    };

    void SetMaximumCutoff(G4int x, G4int y, G4int z) {
        this->detector->SetMaximumCutoff(x, y, z);
    };

    void SetResolution(G4float x, G4float y, G4float z) {
        this->detector->SetResolution(x, y, z);
    };

  private:
    SensitiveDetector* detector;

    G4Box* world_solid;
    G4LogicalVolume* world_logical;
    G4VPhysicalVolume* world_physical;

    G4Box* phantom_solid;
    G4LogicalVolume* phantom_logical;
    G4VPhysicalVolume* phantom_physical;

    G4Box* film_solid;
    G4LogicalVolume* film_logical;
    G4VPhysicalVolume* film_physical;

    G4double phantom_size;
    G4double film_thickness;

    G4Material* air;
    G4Material* water;
    G4Material* dense_water;
    G4double film_density;
};

#endif

