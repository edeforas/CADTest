import numpy as np
import matplotlib.pyplot as plt
#####################################################################################
def eval(u,v):
    x=4.*u
    y=4.*v
    z=u*u+v*v-4.
    w=u*u+v*v+4.

    x/=w
    y/=w
    z/=w
    return x,y,z
#####################################################################################
all_x=[]
all_y=[]
all_z=[]

for u in range(-40,40):
    for v in range(-40,40):
        x,y,z=eval(u/20.,v/20.)
     
        all_x.append(x)
        all_y.append(y)
        all_z.append(z)
     
        normp=np.sqrt(x*x+y*y+z*z)
        print(f"x={x} y={y} z={z} normp={normp}")

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
ax.scatter(all_x, all_y, all_z)
plt.show()