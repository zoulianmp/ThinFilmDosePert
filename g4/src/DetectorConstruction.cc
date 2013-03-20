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


// USER //
#include "DetectorConstruction.hh"

// GEANT4 //
#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4UIcommand.hh"
#include "G4UserLimits.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

DetectorConstruction::DetectorConstruction()
{
    phantom_size = 10*cm;
    film_thickness = 0.1*mm;
    film_density = 1.1*g/cm3;

    MakeMaterials();
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

    world_solid = new G4Box("world_solid", 1*m, 1*m, 1*m);
    world_logical = new G4LogicalVolume(world_solid, air, "world_logical", 0, 0, 0);
    world_physical = new G4PVPlacement(0, G4ThreeVector(), world_logical, 
                                      "world_physical", 0, false, 0);
    world_logical->SetVisAttributes(G4VisAttributes::Invisible);

    phantom_solid = new G4Box("phantom_solid", phantom_size/2.,
                                               phantom_size/2.,
                                               phantom_size/2.);
    phantom_logical = new G4LogicalVolume(phantom_solid, water, "phantom_logical", 0, 0, 0);
    phantom_physical = new G4PVPlacement(0, G4ThreeVector(), phantom_logical, 
                                         "phantom_physical", world_logical, false, 0);

    film_solid = new G4Box("film_solid", phantom_size/2.,
                                         phantom_size/2.,
                                         film_thickness/2.);
    film_logical = new G4LogicalVolume(film_solid, water, "film_logical", 0, 0, 0);
    G4ThreeVector film_position = G4ThreeVector(0, 0, phantom_size/2. + film_thickness/2.);
    film_physical = new G4PVPlacement(0, film_position, film_logical, 
                                         "film_physical", world_logical, false, 0);

    detector = new SensitiveDetector("phantom_detector");

    G4SDManager* sd_manager = G4SDManager::GetSDMpointer();
    sd_manager->AddNewDetector(detector);
    phantom_logical->SetSensitiveDetector(detector);
    
    return world_physical;
}

void DetectorConstruction::MakeMaterials() {
    G4NistManager* nist_manager = G4NistManager::Instance();
    air = nist_manager->FindOrBuildMaterial("G4_Galactic");
    water = nist_manager->FindOrBuildMaterial("G4_WATER");

    G4String material_name = "G4_WATER" + G4UIcommand::ConvertToString(film_density);
    dense_water = nist_manager->BuildMaterialWithNewDensity(material_name,
                                                            "G4_WATER", 
                                                            film_density);
}
