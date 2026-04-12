import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Currently, i have no fucking clue what to do with this file
# Should it be an animation?
# Just a regular plot?
    
num_of_var = int(sys.argv[1])
num_of_pts = int(sys.argv[2])

t = np.zeros(num_of_pts)
x = np.zeros((num_of_pts, num_of_var))

fig, ax = plt.subplots()
ax.axhline(c='black')
ax.axvline(c='black')
log = open("results.txt", "r")

for i, l in enumerate(log):
    if (l != ""):
        val = l.split()
        t[i] = float(val[0])
        for j in range(num_of_var):
            x[i, j] = float(val[j+1])

log.close()

"""
particle1 = ax.plot(x[0, 0], x[0, 1], c="r", label="1")[0]
particle2 = ax.plot(x[0, 4], x[0, 5], c="g", label="2")[0]
particle3 = ax.plot(x[0, 8], x[0, 9] ,c="b", label="3")[0]
"""

particle1 = ax.scatter(x[0,0], x[0,1], c="r", s=50)
particle2 = ax.scatter(x[0,4], x[0,5], c="g", s=50)
particle3 = ax.scatter(x[0,8], x[0,9], c="b", s=50)

def updAnim(frame):
    """
    particle1.set_data(x[:frame,0], x[:frame,1])
    particle2.set_xdata(x[:frame,4], x[:frame,5])    
    particle3.set_xdata(x[:frame,8], x[:frame,9])
    """

    particle1.set_offsets((x[frame,0], x[frame,1]))
    particle2.set_offsets((x[frame,4], x[frame,5]))
    particle3.set_offsets((x[frame,8], x[frame,9]))

    return (particle1, particle2, particle3)

anim = animation.FuncAnimation(fig, updAnim, np.arange(1, num_of_pts, 1), interval=1)
plt.show()