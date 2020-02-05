#
#  Si_fitting.py
# #  This is an example to run ALM in the fitting mode.
#

from alm import ALM
import numpy as np

lavec = [[20.406, 0, 0],
         [0, 20.406, 0],
         [0, 0, 20.406]]
xcoord = [[0.0000000000000000, 0.0000000000000000, 0.0000000000000000],
          [0.0000000000000000, 0.0000000000000000, 0.5000000000000000],
          [0.0000000000000000, 0.2500000000000000, 0.2500000000000000],
          [0.0000000000000000, 0.2500000000000000, 0.7500000000000000],
          [0.0000000000000000, 0.5000000000000000, 0.0000000000000000],
          [0.0000000000000000, 0.5000000000000000, 0.5000000000000000],
          [0.0000000000000000, 0.7500000000000000, 0.2500000000000000],
          [0.0000000000000000, 0.7500000000000000, 0.7500000000000000],
          [0.1250000000000000, 0.1250000000000000, 0.1250000000000000],
          [0.1250000000000000, 0.1250000000000000, 0.6250000000000000],
          [0.1250000000000000, 0.3750000000000000, 0.3750000000000000],
          [0.1250000000000000, 0.3750000000000000, 0.8750000000000000],
          [0.1250000000000000, 0.6250000000000000, 0.1250000000000000],
          [0.1250000000000000, 0.6250000000000000, 0.6250000000000000],
          [0.1250000000000000, 0.8750000000000000, 0.3750000000000000],
          [0.1250000000000000, 0.8750000000000000, 0.8750000000000000],
          [0.2500000000000000, 0.0000000000000000, 0.2500000000000000],
          [0.2500000000000000, 0.0000000000000000, 0.7500000000000000],
          [0.2500000000000000, 0.2500000000000000, 0.0000000000000000],
          [0.2500000000000000, 0.2500000000000000, 0.5000000000000000],
          [0.2500000000000000, 0.5000000000000000, 0.2500000000000000],
          [0.2500000000000000, 0.5000000000000000, 0.7500000000000000],
          [0.2500000000000000, 0.7500000000000000, 0.0000000000000000],
          [0.2500000000000000, 0.7500000000000000, 0.5000000000000000],
          [0.3750000000000000, 0.1250000000000000, 0.3750000000000000],
          [0.3750000000000000, 0.1250000000000000, 0.8750000000000000],
          [0.3750000000000000, 0.3750000000000000, 0.1250000000000000],
          [0.3750000000000000, 0.3750000000000000, 0.6250000000000000],
          [0.3750000000000000, 0.6250000000000000, 0.3750000000000000],
          [0.3750000000000000, 0.6250000000000000, 0.8750000000000000],
          [0.3750000000000000, 0.8750000000000000, 0.1250000000000000],
          [0.3750000000000000, 0.8750000000000000, 0.6250000000000000],
          [0.5000000000000000, 0.0000000000000000, 0.0000000000000000],
          [0.5000000000000000, 0.0000000000000000, 0.5000000000000000],
          [0.5000000000000000, 0.2500000000000000, 0.2500000000000000],
          [0.5000000000000000, 0.2500000000000000, 0.7500000000000000],
          [0.5000000000000000, 0.5000000000000000, 0.0000000000000000],
          [0.5000000000000000, 0.5000000000000000, 0.5000000000000000],
          [0.5000000000000000, 0.7500000000000000, 0.2500000000000000],
          [0.5000000000000000, 0.7500000000000000, 0.7500000000000000],
          [0.6250000000000000, 0.1250000000000000, 0.1250000000000000],
          [0.6250000000000000, 0.1250000000000000, 0.6250000000000000],
          [0.6250000000000000, 0.3750000000000000, 0.3750000000000000],
          [0.6250000000000000, 0.3750000000000000, 0.8750000000000000],
          [0.6250000000000000, 0.6250000000000000, 0.1250000000000000],
          [0.6250000000000000, 0.6250000000000000, 0.6250000000000000],
          [0.6250000000000000, 0.8750000000000000, 0.3750000000000000],
          [0.6250000000000000, 0.8750000000000000, 0.8750000000000000],
          [0.7500000000000000, 0.0000000000000000, 0.2500000000000000],
          [0.7500000000000000, 0.0000000000000000, 0.7500000000000000],
          [0.7500000000000000, 0.2500000000000000, 0.0000000000000000],
          [0.7500000000000000, 0.2500000000000000, 0.5000000000000000],
          [0.7500000000000000, 0.5000000000000000, 0.2500000000000000],
          [0.7500000000000000, 0.5000000000000000, 0.7500000000000000],
          [0.7500000000000000, 0.7500000000000000, 0.0000000000000000],
          [0.7500000000000000, 0.7500000000000000, 0.5000000000000000],
          [0.8750000000000000, 0.1250000000000000, 0.3750000000000000],
          [0.8750000000000000, 0.1250000000000000, 0.8750000000000000],
          [0.8750000000000000, 0.3750000000000000, 0.1250000000000000],
          [0.8750000000000000, 0.3750000000000000, 0.6250000000000000],
          [0.8750000000000000, 0.6250000000000000, 0.3750000000000000],
          [0.8750000000000000, 0.6250000000000000, 0.8750000000000000],
          [0.8750000000000000, 0.8750000000000000, 0.1250000000000000],
          [0.8750000000000000, 0.8750000000000000, 0.6250000000000000]]

kd = [14] * 64

force = np.loadtxt("force.dat").reshape((-1, 64, 3))[[0]]
disp = np.loadtxt("disp.dat").reshape((-1, 64, 3))[[0]]

# alm.alm_new() and alm.alm_delete() are done by 'with' statement
with ALM(lavec, xcoord, kd) as alm:
    alm.define(1)
    alm.displacements = disp
    alm.forces = force
    info = alm.optimize()
    fc_values, elem_indices = alm.get_fc(1, mode='all')
    c = "xyz"
    for (fc, elem) in zip(fc_values, elem_indices):
        v1 = elem[0] // 3
        c1 = elem[0] % 3
        v2 = elem[1] // 3
        c2 = elem[1] % 3
        print("%f %d%s %d%s" % ((fc, v1 + 1, c[c1], v2 + 1, c[c2])))
