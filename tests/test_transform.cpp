#include "Transform.h"

#include <string>
#include <iostream>
using namespace std;

void test(bool b, string s="")
{
	if (b == false)
	{
		cout << "condition: [" << s << "] is not realized!" << endl;
		exit(-1);
	}
}

void test_near(double a, double ref, double epsilon = 1.e-10, const string& sMessage = "")
{
	if ((a > ref + epsilon) || (a < ref - epsilon))
	{
		cerr << "Test Error: " << sMessage.c_str() << "value=" << a << " ref=" << ref << endl;
		exit(-1);
	}
}
///////////////////////////////////////////////////////////////////////////
void test_euler_angles()
{
	Point3 p1(10., 20., 30.);
	RotationEulerAngles re(4, 5, 6);
	re.apply(p1);

	test(p1.x() != 10.,"");
	test(p1.y() != 20.,"");
	test(p1.z() != 30.,"");
}
///////////////////////////////////////////////////////////////////////////
void test_quaternion()
{
	Point3 p1(10., 20., 30.);
	RotationQuaternion rq;
	Point3 axis(-16, 58, 92);
	axis.normalize();
	rq.from_angle_axis(37, axis);
	rq.apply(p1);

	test(p1.x() != 10.);
	test(p1.y() != 20.);
	test(p1.z() != 30.);

	rq.from_angle_axis(-37, axis);
	rq.apply(p1);

	test_near(p1.x(), 10.);
	test_near(p1.y(), 20.);
	test_near(p1.z(), 30.);
}
///////////////////////////////////////////////////////////////////////////
void test_quaternion_120deg()
{
	Point3 p1(10., 20., 30.);
	RotationQuaternion rq;
	Point3 axis(-16, 58, 92);
	axis.normalize();
	rq.from_angle_axis(120., axis);
	rq.apply(p1);

	test(p1.x() != 10.);
	test(p1.y() != 20.);
	test(p1.z() != 30.);

	rq.apply(p1);

	test(p1.x() != 10.);
	test(p1.y() != 20.);
	test(p1.z() != 30.);

	rq.apply(p1);

	test_near(p1.x(), 10.);
	test_near(p1.y(), 20.);
	test_near(p1.z(), 30.);
}
///////////////////////////////////////////////////////////////////////////
void test_rotation_matrix()
{
	Point3 p1(10., 20., 30.);
	RotationMatrix rm;
	Point3 axis(-16, 58, 92);
	axis.normalize();
	rm.from_angle_axis(37, axis);
	rm.apply(p1);

	test(p1.x() != 10.);
	test(p1.y() != 20.);
	test(p1.z() != 30.);

	rm.from_angle_axis(-37, axis);
	rm.apply(p1);

	test_near(p1.x(), 10.);
	test_near(p1.y(), 20.);
	test_near(p1.z(), 30.);
}
///////////////////////////////////////////////////////////////////////////
void test_rotation_matrix_120deg()
{
	Point3 p1(10., 20., 30.);
	RotationMatrix rm;
	Point3 axis(-16, 58, 92);
	axis.normalize();
	rm.from_angle_axis(120., axis);
	rm.apply(p1);

	test(p1.x() != 10.);
	test(p1.y() != 20.);
	test(p1.z() != 30.);

	rm.apply(p1);

	test(p1.x() != 10.);
	test(p1.y() != 20.);
	test(p1.z() != 30.);

	rm.apply(p1);

	test_near(p1.x(), 10.);
	test_near(p1.y(), 20.);
	test_near(p1.z(), 30.);
}
///////////////////////////////////////////////////////////////////////////
void test_angle_axis()
{
	Point3 p1(10., 20., 30.);
	RotationAngleAxis rq;
	Point3 axis(-16, 58, 92);
	axis.normalize();
	rq.from_angle_axis(37, axis);
	rq.apply(p1);

	test(p1.x() != 10.);
	test(p1.y() != 20.);
	test(p1.z() != 30.);

	rq.from_angle_axis(-37, axis);
	rq.apply(p1);

	test_near(p1.x(), 10.);
	test_near(p1.y(), 20.);
	test_near(p1.z(), 30.);
}
///////////////////////////////////////////////////////////////////////////
void test_angle_axis_120deg()
{
	Point3 p1(10., 20., 30.);
	RotationAngleAxis rq;
	Point3 axis(-16, 58, 92);
	axis.normalize();
	rq.from_angle_axis(120., axis);
	rq.apply(p1);

	test(p1.x() != 10.);
	test(p1.y() != 20.);
	test(p1.z() != 30.);

	rq.apply(p1);

	test(p1.x() != 10.);
	test(p1.y() != 20.);
	test(p1.z() != 30.);

	rq.apply(p1);

	test_near(p1.x(), 10.);
	test_near(p1.y(), 20.);
	test_near(p1.z(), 30.);
}
///////////////////////////////////////////////////////////////////////////

int main()
{
	cout << "Tests start..." << endl;
	
	test_euler_angles();
	test_quaternion();
	test_quaternion_120deg();
	test_rotation_matrix();
	test_rotation_matrix_120deg();
	test_angle_axis();
	test_angle_axis_120deg();

	cout << "Tests finished." << endl;
	return 0;
}