# License & Copyright
# ===================
#
# Copyright 2012 Christopher M Poole <mail@christopherpoole.net>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import random

import numpy
import pylab
import pyublas

import Geant4
import g4 


if __name__ == "__main__":
    seed = long(random.randint(0, 2**32))
    rand_engine = Geant4.Ranlux64Engine()
    Geant4.HepRandom.setTheEngine(rand_engine)
    Geant4.HepRandom.setTheSeed(seed)

    detector_construction = g4.DetectorConstruction()
    Geant4.gRunManager.SetUserInitialization(detector_construction)

    physics_list = g4.PhysicsList()
    Geant4.gRunManager.SetUserInitialization(physics_list)

    primary_generator = g4.PrimaryGeneratorAction()
    Geant4.gRunManager.SetUserAction(primary_generator)

    stepping_action = g4.SteppingAction()
    Geant4.gRunManager.SetUserAction(stepping_action)

    Geant4.gRunManager.Initialize()
    Geant4.gUImanager.ExecuteMacroFile("macros/vis.mac")

    detector_construction.SetDimensions(32, 32, 32)
    detector_construction.SetMinimumCutoff(0, 0, 0)
    detector_construction.SetMaximumCutoff(32, 32, 32)
    detector_construction.SetResolution(0.1, 0.1, 0.1)

    Geant4.gRunManager.BeamOn(1000000)

    energy = detector_construction.GetEnergyHistogram()
#    pylab.matshow(numpy.log(energy[:,250,:]))
#    pylab.show()
    numpy.save("output", energy)
