<<<<<<< HEAD
import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
    
NUM_OF_VAR = 4
num_of_pts = 0
results = open("double_pendulum_results.txt", "r")
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
ax.set_xlim(-2.5, 2.5)
ax.set_ylim(-0.5, 4.5)

pos_1 = [np.sin(x[0,0]), 2-np.cos(x[0,0])]
pos_2 = [pos_1[0]+np.sin(x[0,1]), pos_1[1]-np.cos(x[0,1])]

particle_1 = ax.scatter(pos_1[0], pos_1[1], c="red", s=25, zorder=10)
particle_2 = ax.scatter(pos_2[0], pos_2[1], c="blue", s=25, zorder=10)
line_1, = ax.plot([0, pos_1[0]], [2, pos_1[1]], c="black", zorder=3)
line_2, =  ax.plot([pos_1[0], pos_2[0]], [pos_1[1], pos_2[1]], c="black", zorder=5)

def updAnim(frame):
    pos_1[0] = np.sin(x[frame,0])
    pos_1[1] = 2-np.cos(x[frame,0])
    pos_2[0] = pos_1[0] + np.sin(x[frame,1])
    pos_2[1] = pos_1[1] - np.cos(x[frame,1])

    line_1.set_data([0, pos_1[0]], [2, pos_1[1]])
    particle_1.set_offsets(pos_1)
    line_2.set_data([pos_1[0], pos_2[0]], [pos_1[1], pos_2[1]])
    particle_2.set_offsets(pos_2)

    return (line_1, particle_1, line_2, particle_2)

anim = animation.FuncAnimation(fig, updAnim, np.arange(1, num_of_pts, 1), interval=1/12*1000)
=======
import os
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
    
NUM_OF_VAR = 4
num_of_pts = 0
results = open("double_pendulum_results.txt", "r")
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
ax.set_xlim(-2.5, 2.5)
ax.set_ylim(-0.5, 4.5)

pos_1 = [np.sin(x[0,0]), 2-np.cos(x[0,0])]
pos_2 = [pos_1[0]+np.sin(x[0,1]), pos_1[1]-np.cos(x[0,1])]

particle_1 = ax.scatter(pos_1[0], pos_1[1], c="red", s=25, zorder=10)
particle_2 = ax.scatter(pos_2[0], pos_2[1], c="blue", s=25, zorder=10)
line_1, = ax.plot([0, pos_1[0]], [2, pos_1[1]], c="black", zorder=3)
line_2, =  ax.plot([pos_1[0], pos_2[0]], [pos_1[1], pos_2[1]], c="black", zorder=5)

def updAnim(frame):
    pos_1[0] = np.sin(x[frame,0])
    pos_1[1] = 2-np.cos(x[frame,0])
    pos_2[0] = pos_1[0] + np.sin(x[frame,1])
    pos_2[1] = pos_1[1] - np.cos(x[frame,1])

    line_1.set_data([0, pos_1[0]], [2, pos_1[1]])
    particle_1.set_offsets(pos_1)
    line_2.set_data([pos_1[0], pos_2[0]], [pos_1[1], pos_2[1]])
    particle_2.set_offsets(pos_2)

    return (line_1, particle_1, line_2, particle_2)

anim = animation.FuncAnimation(fig, updAnim, np.arange(1, num_of_pts, 1), interval=1/12*1000)
>>>>>>> 2ca30074244f8b1eda8281c39e136514c49b519e
plt.show()