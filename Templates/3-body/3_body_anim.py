import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
    
NUM_OF_VAR = 12
num_of_pts = 0
results = open("3_body_results.txt", "r")
for l in results:
    num_of_pts += 1
results.seek(0, os.SEEK_SET)

t = np.zeros(num_of_pts)
x = np.zeros((num_of_pts, NUM_OF_VAR))

# Assign each column in results to its respective variable
for i, l in enumerate(results):
    if (l != ""):
        var = l.split()
        t[i] = float(var[0])
        for j in range(NUM_OF_VAR):
            x[i, j] = float(var[j+1])

results.close()

fig, ax = plt.subplots()
ax.axhline(c='black')
ax.axvline(c='black')
ax.set_xlim(-1.5, 1.5)
ax.set_ylim(-2, 2)

particle_1 = ax.scatter(x[0,0], x[0,1], c="red", s=25)
particle_2 = ax.scatter(x[0,4], x[0,5], c="green", s=25)
particle_3 = ax.scatter(x[0,8], x[0,9], c="blue", s=25)

def updAnim(frame):
    particle_1.set_offsets((x[frame,0], x[frame,1]))
    particle_2.set_offsets((x[frame,4], x[frame,5]))
    particle_3.set_offsets((x[frame,8], x[frame,9]))

    return (particle_1, particle_2, particle_3)

anim = animation.FuncAnimation(fig, updAnim, np.arange(1, num_of_pts, 1), interval=1/24*1000)
plt.show()