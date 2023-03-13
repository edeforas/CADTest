import numpy as np
import matplotlib.pyplot as plt
import math
##############################################################################
def compute_sphere_uniform(nb_points):
    px=np.random.uniform(-1.,1.,nb_points)
    py=np.random.uniform(-1.,1.,nb_points)
    pz=np.random.uniform(-1.,1.,nb_points)

    norm_p=np.sqrt(px*px+py*py+pz*pz)
    pnx=px/norm_p
    pny=py/norm_p
    pnz=pz/norm_p

    return pnx,pny,pnz
##############################################################################
def compute_sphere_normal(nb_points):
    px=np.random.normal(0.,1.,nb_points)
    py=np.random.normal(0.,1.,nb_points)
    pz=np.random.normal(0.,1.,nb_points)

    norm_p=np.sqrt(px*px+py*py+pz*pz)
    pnx=px/norm_p
    pny=py/norm_p
    pnz=pz/norm_p

    return pnx,pny,pnz
##############################################################################
def compute_sphere_wolfram(nb_points):
    # from https://mathworld.wolfram.com/SpherePointPicking.html
    u=np.random.uniform(0.,1.,nb_points)
    v=np.random.uniform(0.,1.,nb_points)

    theta=u*2.*math.pi
    phi=np.arccos(2.*v-1.)

    x=np.cos(theta)*np.sin(phi)
    y=np.sin(theta)*np.sin(phi)
    z=np.cos(phi)

    return x,y,z
##############################################################################
def angleaxis_to_rotmat(x,y,z,theta):
    # from https://fr.wikipedia.org/wiki/Formule_d%27Euler%E2%80%93Rodrigues
    s=np.sin(theta)
    c=np.cos(theta)    
    c1=1.-c
    r=[ [ x*x*c1+c , x*y*c1-z*s , x*z*c1+y*s] ,  [x*y*c1+z*s, y*y*c1+c, y*z*c1+x*s], [x*z*c1-y*s,y*z*c1+x*s, z*z*c1+c]   ]
    return np.array(r)
##############################################################################
def quat_to_rotmat(q):
    #from https://fr.wikipedia.org/wiki/Quaternions_et_rotation_dans_l%27espace
    a=q[0]
    b=q[1]
    c=q[2]
    d=q[3]
    r=[ [ a*a+b*b-c*c-d*d, 2*b*c-2*a*d, 2*a*c + 2*b*d ],
        [ 2*a*d+2*b*c, a*a-b*b+c*c-d*d ,2*c*d-2*a*b],
        [2*b*d-2*a*c, 2*a*b+2*c*d,a*a-b*b-c*c+d*d] ]
    return np.array(r)
##############################################################################
def angleaxis_to_quat(theta,x,y,z):
    #from https://fr.wikipedia.org/wiki/Quaternions_et_rotation_dans_l%27espace
    s=np.sin(theta/2.)
    c=np.cos(theta/2.)
    r=[c,x*s,y*s,z*s]
    return np.array(r)
##############################################################################
def rotate_point(quat,x,y,z):
    # from https://fr.wikipedia.org/wiki/Quaternions_et_rotation_dans_l%27espace
    a=quat[0]
    b=quat[1]
    c=quat[2]
    d=quat[3]

    t2 =   a*b
    t3 =   a*c
    t4 =   a*d
    t5 =  -b*b
    t6 =   b*c
    t7 =   b*d
    t8 =  -c*c
    t9 =   c*d
    t10 = -d*d
    xnew = 2.*( (t8 + t10)*x + (t6 -  t4)*y + (t3 + t7)*z ) + x
    ynew = 2.*( (t4 +  t6)*x + (t5 + t10)*y + (t9 - t2)*z ) + y
    znew = 2.*( (t7 -  t3)*x + (t2 +  t9)*y + (t5 + t8)*z ) + z
    return xnew,ynew,znew
##############################################################################


x,y,z=compute_sphere_normal(1000)

fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
ax.scatter(x, y, z)
plt.show()