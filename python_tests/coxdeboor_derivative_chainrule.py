import numpy as np
import math as m

#######################################################################
def find_index(u,knots):
    i=0
    while (knots[i]>u) or (knots[i+1]<=u):
        i+=1
    return i
#######################################################################
def deBoor(u, knots, points, weights, deg):

    knot_index=find_index(u,knots)

    c = []
    for i in range(len(points)):
        w=weights[i]
        c.append([points[i][0]*w, points[i][1]*w, points[i][2]*w, w])
    c = np.array(c)

    d=[]
    for j in range(0, deg+1):
        d.append(c[j + knot_index - deg] )
    
    for r in range(1, deg+1):
        for j in range(deg, r-1, -1):
            alpha = (u - knots[j+knot_index-deg]) / (knots[j+1+knot_index-r] - knots[j+knot_index-deg])
            d[j] = (1.0 - alpha) * d[j-1] + alpha * d[j]
        
    return np.array([
        d[deg][0] / d[deg][3],
        d[deg][1] / d[deg][3],
        d[deg][2] / d[deg][3]
    ])
#######################################################################
def deBoor4D(u, knots, points, weights, deg):

    knot_index=find_index(u,knots)

    c = []
    for i in range(len(points)):
        w=weights[i]
        c.append([points[i][0]*w, points[i][1]*w, points[i][2]*w, w])
    c = np.array(c)

    d = [c[j + knot_index - deg] for j in range(0, deg+1)]
    for r in range(1, deg+1):
        for j in range(deg, r-1, -1):
            alpha = (u - knots[j+knot_index-deg]) / (knots[j+1+knot_index-r] - knots[j+knot_index-deg])
            d[j] = (1.0 - alpha) * d[j-1] + alpha * d[j]
        
    return d[deg]
#######################################################################
def deBoorDerivative(u, knots, points, weights, deg): 

    knot_index=find_index(u,knots)

    c = []
    for i in range(len(points)):
        w=weights[i]
        c.append([points[i][0]*w, points[i][1]*w, points[i][2]*w, w])
    c = np.array(c)

    q=[]
    for j in range(0, deg):
        q.append(deg * (c[j+knot_index-deg+1] - c[j+knot_index-deg]) / (knots[j+knot_index+1] - knots[j+knot_index-deg+1]))
                  
    for r in range(1, deg): 
        for j in range(deg-1, r-1, -1):
            right = j+1+knot_index-r
            left = j+knot_index-(deg-1)
            alpha = (u - knots[left]) / (knots[right] - knots[left])
            q[j] = (1.0 - alpha) * q[j-1] + alpha * q[j]

    p4d=deBoor4D(u, knots, points, weights, deg)
    w=p4d[3]
    q=q[deg-1]
    wp=q[3]

    # apply chain rule
    return np.array([
        (q[0]*w-p4d[0]*wp) / (w*w),
        (q[1]*w-p4d[1]*wp) / (w*w),
        (q[2]*w-p4d[2]*wp) / (w*w),
    ])
#######################################################################
def finiteDifferenceDerivative(u, knots, points, weights, deg):
    f = lambda xx : deBoor( xx, knots, points, weights, deg)
    dx = 1e-7
    return (- f(u+2*dx)  + 8*f(u+dx) - 8*f(u-dx) + f(u-2*dx)) / (12*dx)
#######################################################################
def finiteDifferenceDerivative2Val(u, knots, points, weights, deg):
    f = lambda xx : deBoor( xx, knots, points, weights, deg)
    dx = 1e-7
    return (f(u+dx) - f(u-dx)) / (2*dx)
#######################################################################
deg=3
u=0.44
points=[]
for i in range(0, 11):
    points.append([i, m.sin(i / 3.0), m.cos(i / 2)])
points=np.array(points)
weights = [0.3, 0.8, 0.9, 2, 1.25, 1.07, 0.5, 1, 1, 3, 1]
knots = [0, 0, 0, 0, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 1.0, 1.0, 1.0, 1.0]

a = deBoorDerivative(u, knots, points, weights, deg)
b = finiteDifferenceDerivative( u, knots, points, weights, deg)
c = finiteDifferenceDerivative2Val( u, knots, points, weights, deg)

print(f"              deBoorDerivative: {a}")
print(f"    finiteDifferenceDerivative: {b}")
print(f"finiteDifferenceDerivative2val: {c}")