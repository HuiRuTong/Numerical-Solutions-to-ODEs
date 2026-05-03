import os
import numpy as np
import matplotlib.pyplot as plt

NUM_OF_VAR = 4
num_of_pts = 0
a = 0.5
results = open("finite_well_results.txt", "r")
for l in results:
    num_of_pts += 1
results.seek(0, os.SEEK_SET)

res = np.zeros((num_of_pts, NUM_OF_VAR+1))
l_wall = 0
r_wall = 0

# Assign each column in results to its respective variable
for i, l in enumerate(results):
    if (l != ""):
        var = l.split()
        for j in range(NUM_OF_VAR + 1):
            res[i, j] = float(var[j])

results.close()

sorted = res[res[:, 0].argsort()]
for i in range(num_of_pts):
    # Where to cut off the two psi
    if (sorted[i, 0] == -a):
        l_wall = i
    if (sorted[i, 0] == a):
        r_wall = i

fig, ax = plt.subplots()
ax.axhline(a, c="black")
ax.axvline(-a, c="black")
ax.axvline(a, c="black")
ax.set_xlim(-2, 2)
ax.set_ylim(-1e-3, 1e-2)

ax.plot(sorted[:l_wall+1, 0], pow(sorted[:l_wall+1, 1], 2), c="red")
ax.plot(sorted[l_wall:r_wall+1, 0], pow(sorted[l_wall:r_wall+1, 3], 2),  c="blue")
ax.plot(sorted[r_wall:, 0], pow(sorted[r_wall:, 1], 2), c="red")

plt.show()