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

    def knots(self):
        return self._knots

    def set_points(self,points):
        self._points=points
    
    def set_weights(self,weights):
        self._weights=weights

    def weights(self):
        return self._weights

    def set_degree(self,degree):
        self._degree=degree

    def find_knot_span(self,t): #todo dichotomy
        for idx in range(len(self._knots-1)):
             if (t>=self._knots[idx]) and (t<=self._knots[idx+1]) and (self._knots[idx]< self._knots[idx+1]):
                return idx
        assert False,"knot index not found"
        return -1
                             
    def evaluate(self, t):
        degree=self._degree
        knot_index=self.find_knot_span(t)

        points=[]
        weights=[]
        for j in range(0, degree + 1):
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

    def create_from_points(self,points,degree):

        weights=[]
        knots=[]
        nbPoints=len(points)

        for i in range(nbPoints):
            weights.append(1.)

        for i in range(degree+1):
            knots.append(0)

        for i in range(1,nbPoints-degree):
            knots.append(i)

        for i in range(degree+1):
            knots.append(nbPoints-degree)

        self.set_weights(weights)
        self.set_knots(knots)
        self.set_degree(degree)
        self.set_points(points)

#######################################################################################
def plot_nurbs(degree,points,weights,knots,clf=True,title="Nurbs"):
    n=NurbsCurve()
    n.set_knots(knots)
    n.set_points(points)
    n.set_weights(weights)
    n.set_degree(degree)
    x=[]
    y=[]
    nb_eval=100
    for t in np.arange(nb_eval+1):
        r=n.evaluate(t/100)
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
    plt.gca().set_aspect('equal')
    if clf:
        plt.show()
#######################################################################################
def test_simple_segment():
    d=1
    p=np.array([[1,0],[0,1]])
    w=np.array([1, 1])
    k=np.array([0,0,1,1])
    plot_nurbs(d,p,w,k,title="test_simple_segment")
#######################################################################################
def test_quarter_circle():
    d=2
    p=np.array([[1,0],[1,1],[0,1]])
    w=np.array(np.array([1, 1./math.sqrt(2.), 1]))
    k=np.array([0,0,0,1,1,1])
    plot_nurbs(d,p,w,k,title="test_quarter_circle")
#######################################################################################
def test_half_circle_deg3():
    degree=3
    points=np.array([[1,0],[1,2],[-1,2],[-1,0]])
    weights=np.array(np.array([1, 1./3., 1./3., 1]))
    knots=np.array([0,0,0,0,1,1,1,1])
    plot_nurbs(degree,points,weights,knots,title="test_half_circle_deg3")
#######################################################################################
def test_full_circle():
    d=2
    p=np.array([[1,0],[1,1],[0,1],[-1,1],[-1,0],[-1,-1],[0,-1],[1,-1],[1,0]])
    w=np.array([1., 1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.])
    k=np.array([0.,0.,0.,0.25,0.25,0.5,0.5,0.75,0.75,1.,1.,1.])
    plot_nurbs(d,p,w,k,title="test_full_circle")
#######################################################################################
#approximation using cubic NURBS, not rational
# from "Good Approximation of Circles by Curvature-Continuous Bézier curves"
# 0.55 number optimized to 0.5519151 for a lower max error
def test_approx_circle():
    d=3
    p=np.array([[1,0],[1,0.5519151],[0.5519151,1],[0,1]])
    w=np.array([1,1,1,1])
    k=np.array([0,0,0,0,1,1,1,1])
    plot_nurbs(d,p,w,k,title="cubic approximation of quarter circle")
#######################################################################################
def test_deg2_square():
    n=NurbsCurve()
    d=2
    p=np.array([[0,0],[1,0],[1,1],[0,1]])
    n.create_from_points(p,d)
    plot_nurbs(d,p,n.weights(),n.knots(),title="test_deg2_square")
#######################################################################################
def test_square():
    d=1
    p=np.array([[1,-1],[1,1],[-1,1],[-1,-1],[1,-1]])
    w=np.array([1, 1, 1, 1, 1])
    k=np.array([0,0,1,2,3,4,5,5])
    plot_nurbs(d,p,w,k,title="test_square")
#######################################################################################
def test_random_polyline():
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
    plot_nurbs(d,p,w,k,title="test_random_polyline")
#######################################################################################
def test_random_deg2():
    n=NurbsCurve()
    d=2
    nb_ctrl=10
    p=np.random.uniform(-1,1,(nb_ctrl,2))
    n.create_from_points(p,d)
    plot_nurbs(d,p,n.weights(),n.knots(),title="test_random_deg2")
#######################################################################################
def test_random_deg3():
    d=3
    nb_ctrl=10
    p=np.random.uniform(-1,1,(nb_ctrl,2))
    w=np.ones(nb_ctrl)
    k=[]
    k.append(0)
    k.append(0)
    k.append(0)
    for i in range(nb_ctrl):
        k.append(i)
    k.append(nb_ctrl)
    k.append(nb_ctrl)
    k.append(nb_ctrl)
    k.append(nb_ctrl)
    k=np.array(k)
    plot_nurbs(d,p,w,k,title="test_random_deg3")
#######################################################################################
def test_circle_weight():
    d=2
    p=np.array([[1,0],[1,1],[0,1],[-1,1],[-1,0],[-1,-1],[0,-1],[1,-1],[1,0]])
    w=np.array([1., 1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.,1./math.sqrt(2.), 1.])
    k=np.array([0.,0.,0.,0.25,0.25,0.5,0.5,0.75,0.75,1.,1.,1.])
    plt.clf()

    for ww in np.arange(0.,3.,0.2):
        w[1]=ww
        plot_nurbs(d,p,w,k,clf=False,title="circle+weight change")
    plt.show()

test_simple_segment()
test_quarter_circle()
test_half_circle_deg3()
test_full_circle()
test_approx_circle()
test_deg2_square()
test_square()
test_random_polyline()
test_random_deg2()
test_random_deg3()
test_circle_weight()