from os import system
import numpy


cmd = "qsub -q batch -v histories=%i,energy=%f,density=%f,thickness=%f /media/nfsroot/software/ThinFilmDosePert/job.sh"

histories = 10000000
for energy in range(100, 1500, 100):
    for density in numpy.arange(0.5, 2.5, 0.5):
        for thickness in numpy.arange(0.1, 0.6, 0.1):
            system(cmd % (histories, energy, density, thickness))

