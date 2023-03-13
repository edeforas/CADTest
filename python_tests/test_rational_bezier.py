import numpy as np
import math
import matplotlib.pyplot as plt

#bernstein polynoms of deg2 and 3
def B02(t):
    return (1-t)**2
def B12(t):
    return 2*t*(1-t)
def B22(t):
    return t**2
def B03(t):
    return (1-t)**3
def B13(t):
    return 3*t*((1-t)**2)
def B23(t):
    return 3*(t**2)*(1-t)
def B33(t):
    return t**3

#elevate a degreee 2 bezier to a degree 3 bezier
# from https://pages.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/Bezier/bezier-elev.html

# rational elevation from: http://www.cad.zju.edu.cn/home/hwlin/pdf_files/A-simple-method-for-approximating-rational-Bezier-curve-using-Bezier-curves.pdf

def degree_elevation(P2,W2):
    n=2
    P3=[]
    P3.append(P2[0]*W2[0])
    P3.append(P2[0]*W2[0]*1/(n+1)+P2[1]*W2[1]*(1-1/(n+1)))
    P3.append(P2[1]*W2[1]*2/(n+1)+P2[2]*W2[2]*(1-2/(n+1)))
    P3.append(P2[2]*W2[2])

    W3=[]
    W3.append(W2[0])
    W3.append(W2[0]*1/(n+1)+W2[1]*(1-1/(n+1)))
    W3.append(W2[1]*2/(n+1)+W2[2]*(1-2/(n+1)))
    W3.append(W2[n])

    P3[0]/=W3[0]
    P3[1]/=W3[1]
    P3[2]/=W3[2]
    P3[3]/=W3[3]

    return P3,W3

def rational_bezier_deg2(t,P,W=None):
    
    if W is None:
        return (B02(t)*P[0]+B12(t)*P[1]+B22(t)*P[2])

    numerator=(B02(t)*P[0]*W[0]+B12(t)*P[1]*W[1]+B22(t)*P[2]*W[2])
    denumerator=(B02(t)*W[0]+B12(t)*W[1]+B22(t)*W[2])
    return numerator/denumerator

def rational_bezier_deg3(t,P,W=None):

    if W is None:
        return (B03(t)*P[0]+B13(t)*P[1]+B23(t)*P[2]+B33(t)*P[3])

    numerator=(B03(t)*P[0]*W[0]+B13(t)*P[1]*W[1]+B23(t)*P[2]*W[2]+B33(t)*P[3]*W[3])
    denumerator=(B03(t)*W[0]+B13(t)*W[1]+B23(t)*W[2]+B33(t)*W[3])
    return numerator/denumerator

def bezier_patch_deg2(u,v,P):
    #tensor product
    P1=[P[0],P[1],P[2]]
    P2=[P[3],P[4],P[5]]
    P3=[P[6],P[7],P[8]]
    
    P1u=rational_bezier_deg2(u,P1)
    P2u=rational_bezier_deg2(u,P2)
    P3u=rational_bezier_deg2(u,P3)

    return rational_bezier_deg2(v,[P1u,P2u,P3u])

def parametric_circle(t):
    return (1-t**2)/(1+t**2),(2*t)/(1+t**2)
    
#reference circle
t=np.arange(0,math.pi/2,0.01)
x=np.cos(t)
y=np.sin(t)
#plt.plot(x,y,label='ref_circle')
norm=np.sqrt(x**2+y**2)
print(f"trigonometric circle max_norm={norm.max()} min_norm={norm.min()}")

#circle parametrization test
t=np.arange(0,1,0.01)
x,y=parametric_circle(t)
#plt.plot(x,y,label='parametric_circle')
norm=np.sqrt(x**2+y**2)
print(f"parametric circle max_norm={norm.max()} min_norm={norm.min()}")

#rational bezier deg 2 fit test
px=[1,1,0]
py=[0,1,1]

w=[1,math.sqrt(2)/2,1]# works
w=[1,1,2] # works also and is simpler (computed by hand equalizing Re(P),Im(P))

x=rational_bezier_deg2(t,px,w)
y=rational_bezier_deg2(t,py,w)
#plt.plot(x,y,label='rational_bezier_deg2')
norm=np.sqrt(x**2+y**2)
print(f"deg2 max_norm={norm.max()} min_norm={norm.min()}")

#convert a deg2 rational bezier to a deg3 rational bezier
px3,w3=degree_elevation(px,w)
py3,w3=degree_elevation(py,w)
x=rational_bezier_deg3(t,px3,w3)
y=rational_bezier_deg3(t,py3,w3)
#plt.plot(x,y,label='rational_bezier_deg3')
norm=np.sqrt(x**2+y**2)
print(f"deg3 max_norm={norm.max()} min_norm={norm.min()}")

#approximation using cubic bezier, not rational
# from "Good Approximation of Circles by Curvature-Continuous Bézier curves"
# 0.55 number optimized to 0.5519151 for a lower max error
px=[1,1,0.5519151,0]
py=[0,0.5519151,1,1]
x=rational_bezier_deg3(t,px,None)
y=rational_bezier_deg3(t,py,None)
#plt.plot(x,y,label='cubic approximation_bezier_deg3')
norm=np.sqrt(x**2+y**2)
print(f"cubic approximation max_norm={norm.max()} min_norm={norm.min()}")

# plt.grid()
# plt.legend()
# plt.show()

#now in 3d
Px=[0,10,20, 0,10,20, 0,10,20]
Py=[0,0,0, 10,10,10, 20,20,20]
Pz=[0,10,0, 20,0,-10, 0,-10,0]

all_x=[]
all_y=[]
all_z=[]
for u in range(0,20):
    for v in range(0,20):
        all_x.append(bezier_patch_deg2(u/20,v/20,Px))
        all_y.append(bezier_patch_deg2(u/20,v/20,Py))
        all_z.append(bezier_patch_deg2(u/20,v/20,Pz))

fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(all_x,all_y,all_z)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.title("Rational Bezier patch deg2")
plt.show()
