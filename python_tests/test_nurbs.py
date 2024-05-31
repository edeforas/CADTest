import matplotlib.pyplot as plt
import math
import numpy as np

#from: https://nurbscalculator.wordpress.com/2018/06/03/nurbs-important-and-basic-points/
#also : #https://nurbscalculator.in/

class NurbsCurve:

    def set_knots(self,knots):
        min_knot=np.min(knots)
        max_knot=np.max(knots)
        self._knots=(knots-min_knot)/(max_knot-min_knot) # normalize knots
        
    def set_points(self,points):
        self._points=points
    
    def set_weights(self,weights):
        self._weights=weights
    
    def set_degree(self,degree):
        self._degree=degree

    def find_knot_span(self,t): #todo dichotomy
        for idx in range(len(self._knots-1)):
             if (t>=self._knots[idx]) and (t<=self._knots[idx+1]) and (self._knots[idx]< self._knots[idx+1]):
                return idx
        return -1
                             
    def evaluate(self, t):
        degree=self._degree
        knot_index=self.find_knot_span(t)
        if knot_index==-1:
            return [0,0]

        points=[]
        weights=[]
        for j in range(0, degree + 1):
            #idx=min(j + knot_index - degree,len(self._weights)-1) # todo check
            idx= j + knot_index - degree
            if idx > len(self._points)-1:
                idx=len(self._points)-1
            
            w=self._weights[idx]
            p=self._points[idx]
            weights.append(w)
            points.append(p*w)

        for r in range(1, degree + 1):
            for j in range(degree, r - 1, -1):
                alpha = (t - self._knots[j + knot_index - degree]) / (self._knots[j + 1 + knot_index - r] - self._knots[j + knot_index - degree]) 
                points[j] = (1.0 - alpha) * points[j - 1] + alpha * points[j]
                weights[j] = (1.0 - alpha) * weights[j - 1] + alpha * weights[j]

        return points[degree]/weights[degree]

#######################################################################################
def plot_nurbs(degree,points,weights,knots,clf=True,title="Nurbs"):
    n=NurbsCurve()
    n.set_knots(knots)
    n.set_points(points)
    n.set_weights(weights)
    n.set_degree(degree)
    x=[]
    y=[]
    for t in np.arange(0,1,0.01):
        r=n.evaluate(t)
        x.append(r[0])
        y.append(r[1])

    if clf:
        plt.clf()
    
    plt.plot(points[:,0],points[:,1])
    plt.plot(x,y,'.')
    plt.plot(x,y)
    plt.xlim(-1.5,1.5)
    plt.ylim(-1.5,1.5)
    plt.title(title)
    plt.grid()
    if clf:
        plt.show()
#######################################################################################

# #test simple segment
n=NurbsCurve()
d=1
p=np.array([[1,0],[0,1]])
w=np.array([1, 1])
k=np.array([0,0,1,1])
plot_nurbs(d,p,w,k,title="simple segment")

#test quarter circle
n=NurbsCurve()
d=2
p=np.array([[1,0],[1,1],[0,1]])
w=np.array(np.array([1, 1./math.sqrt(2.), 1]))
k=np.array([0,0,0,1,1,1])
plot_nurbs(d,p,w,k,title="quarter circle")

#test full circle
d=2
p=np.array([[1,0],[1,1],[0,1],[-1,1],[-1,0],[-1,-1],[0,-1],[1,-1],[1,0]])
w=np.array([1., 1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.])
k=np.array([0.,0.,0.,0.25,0.25,0.5,0.5,0.75,0.75,1.,1.,1.])
plot_nurbs(d,p,w,k,title="circle")

#approximation using cubic NURBS, not rational
# from "Good Approximation of Circles by Curvature-Continuous Bézier curves"
# 0.55 number optimized to 0.5519151 for a lower max error
d=3
p=np.array([[1,0],[1,0.5519151],[0.5519151,1],[0,1]])
w=np.array([1,1,1,1])
k=np.array([0,0,0,0,1,1,1,1])
plot_nurbs(d,p,w,k,title="cubic approximation of quarter circle")

# #test square
d=1
p=np.array([[1,-1],[1,1],[-1,1],[-1,-1],[1,-1]])
w=np.array([1, 1, 1, 1, 1])
k=np.array([0,0,1,2,3,4,5,5])
plot_nurbs(d,p,w,k,title="square")

#test random polyline
d=1
nb_ctrl=10
p=np.random.uniform(-1,1,(nb_ctrl,2))
w=np.ones(nb_ctrl)
k=[]
k.append(0)
for i in range(nb_ctrl):
    k.append(i)
k.append(nb_ctrl)
k.append(nb_ctrl)
k=np.array(k)
plot_nurbs(d,p,w,k,title="random polyline")

#test random points deg2
d=2
nb_ctrl=10
p=np.random.uniform(-1,1,(nb_ctrl,2))
w=np.ones(nb_ctrl)
k=[]
k.append(0)
k.append(0)
for i in range(nb_ctrl):
    k.append(i)
k.append(nb_ctrl)
k.append(nb_ctrl)
k.append(nb_ctrl)
k=np.array(k)
plot_nurbs(d,p,w,k,title="random smooth")

#test weight in case of circle
d=2
p=np.array([[1,0],[1,1],[0,1],[-1,1],[-1,0],[-1,-1],[0,-1],[1,-1],[1,0]])
w=np.array([1., 1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.])
k=np.array([0.,0.,0.,0.25,0.25,0.5,0.5,0.75,0.75,1.,1.,1.])
plt.clf()

for ww in np.arange(0.,3.,0.2):
    w[1]=ww
    plot_nurbs(d,p,w,k,clf=False,title="circle+weight change")
plt.show()

