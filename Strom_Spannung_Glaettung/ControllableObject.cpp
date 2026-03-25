#include "pch.h"
#include "ControllableObject.h"


CControllableObject::CControllableObject()
	: minVal(10)
	, maxVal(110)
	, actualVal(50)
	, name("NN")
{
}

CControllableObject::CControllableObject(double _minVal, double _actVal, double _maxVal, string _name)
	: minVal(_minVal)
	, maxVal(_maxVal)
	, actualVal(_actVal)
	, name(_name)
{
}


CControllableObject::~CControllableObject()
{
}


double CControllableObject::getMaxVal() {
	return maxVal;
}

double CControllableObject::getMinVal() {
	return minVal;
}

double CControllableObject::getActualVal() {
	return actualVal;
}
string CControllableObject::getName() {
	return name;
}

void CControllableObject::setActualValue(double _actVal) {
	if ((_actVal >= minVal) && (_actVal <= maxVal)) {
		actualVal = _actVal;
	}
}
