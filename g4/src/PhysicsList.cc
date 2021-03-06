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


// USER//
#include "PhysicsList.hh"

// GEANT4 //
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmDNAPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"


PhysicsList::PhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics_option1());
    //RegisterPhysics(new G4EmStandardPhysics_option2());
    //RegisterPhysics(new G4EmStandardPhysics_option3());
    //RegisterPhysics(new G4EmLivermorePhysics());
    //RegisterPhysics(new G4EmPenelopePhysics());
}

PhysicsList::~PhysicsList()
{;}

void PhysicsList::ConstructParticle()
{
    G4VModularPhysicsList::ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    G4VModularPhysicsList::ConstructProcess();
}


void PhysicsList::SetCuts()
{
    SetCutValue(0.05*mm, "gamma");
    SetCutValue(0.05*mm, "e-");
    SetCutValue(0.05*mm, "e+");
}

