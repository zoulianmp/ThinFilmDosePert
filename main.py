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

import sys
import random

import numpy
import pyublas

import Geant4
import g4 

from Geant4 import keV, MeV

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
    #Geant4.gUImanager.ExecuteMacroFile("macros/vis.mac")

    histories, energy, density, thickness = sys.argv[1:5]

    detector_construction.SetFilmProperties(float(density), float(thickness))
    
    #bins = numpy.array(numpy.logspace(-1, numpy.log10(500), 51), dtype=float)
    #bins = numpy.append(0, bins)

    bins = numpy.arange(0, 501).astype(float)

    detector_construction.SetBins(bins)

    detector_construction.SetDimensions(501, 1, 1001)
    detector_construction.SetMinimumCutoff(0, 0, 0)
    detector_construction.SetMaximumCutoff(501, 1, 1001)
    detector_construction.SetResolution(.1, .1, .1)

    primary_generator.SetEnergy(float(energy)*keV)
    Geant4.gRunManager.BeamOn(int(histories))

    data = detector_construction.GetEnergyHistogram()
    numpy.save("output/ene_%s_den_%s_thk_%s_hist_%s" % (energy, density, thickness, histories), data)
    detector_construction.ZeroHistograms()
