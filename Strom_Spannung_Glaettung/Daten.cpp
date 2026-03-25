#include "pch.h"
#include "Daten.h"

CDaten::CDaten(void) {					//Standard-Konstruktor
	name = "";
	pointView = 0;
	lineStyle = 1; // 1 == PS_SOLID
	lineWidth = 1;
	lineCol = RGB(0, 0, 255);
	length = 361;
	ptrXVal = new double[length];
	ptrYVal = new double[length];
	for (int i = 0; i < length; i++) {
		*(ptrXVal + i) = i * 1;
		*(ptrYVal + i) = 0;
	}

}

CDaten::~CDaten(void) {
	delete[] ptrXVal;
	delete[] ptrYVal;
}

CDaten::CDaten(int _width, int _style, string _name, bool _pointView, int _length) {
	lineWidth = _width;
	lineStyle = _style;
	name = _name;
	length = _length;
	ptrXVal = new double[length];
	ptrYVal = new double[length];
}

CDaten::CDaten(const CDaten& CD) {			//Kopier-Konstruktor
	length = CD.length;
	pointView = CD.pointView;
	lineStyle = CD.lineStyle;
	lineWidth = CD.lineWidth;
	ptrXVal = new double[length];
	ptrYVal = new double[length];
	for (int i = 0; i < length; i++)
	{
		ptrXVal[i] = CD.ptrXVal[i];
	}
	for (int i = 0; i < length; i++)
	{
		ptrYVal[i] = CD.ptrYVal[i];
	}
	name = CD.name;
}

void CDaten::setPointView(void) {
	pointView = 1;
}

void CDaten::setName(string _name) {
	name = _name;
}
bool CDaten::getPointView(void) {
	return pointView;
}
double* CDaten::getXData(void) {
	return ptrXVal;
}
double* CDaten::getYData(void) {
	return ptrYVal;
}
string CDaten::getName(void) const {
	return name;
}
int CDaten::getLength(void) const {
	return length;
}
CDaten& CDaten::getModel() {
	return *this;
}


double CDaten::getMaxY(void) const {
	double max = *ptrYVal;
	for (int i = 1; i < length; i++) {
		if (*(ptrYVal + i) > max)
			max = *(ptrYVal + i);
	}
	return max;
}

double CDaten::getMinY(void) const {
	double min = *ptrYVal;
	for (int i = 1; i < length; i++) {
		if (*(ptrYVal + i) < min)
			min = *(ptrYVal + i);
	}
	return min;
}

double CDaten::getMaxX(void) const {
	double max = *ptrXVal;
	for (int i = 1; i < length; i++) {
		if (*(ptrXVal + i) > max)
			max = *(ptrXVal + i);
	}
	return max;
}

double CDaten::getMinX(void) const {
	double min = *ptrXVal;
	for (int i = 1; i < length; i++) {
		if (*(ptrXVal + i) < min)
			min = *(ptrXVal + i);
	}
	return min;
}

double CDaten::getMeanY(void) const {
	double mean = 0;
	for (int i = 0; i < length; i++)
		mean += *(ptrYVal + i);
	mean /= length;
	return mean;
}

int CDaten::getLineWidth() const {
	return lineWidth;
}
int CDaten::getLineStyle() const {
	return lineStyle;
}
void CDaten::setLineWidth(int _width) {
	lineWidth = _width;
}

void CDaten::setLineStyle(int _style) {
	lineStyle = _style;
}

double CDaten::Round(double Zahl, int Stellen) {
	return floor(Zahl * pow(10.0, Stellen) + 0.5) * pow(10.0, -Stellen);
}

// setzt den Y-Wert
void CDaten::setDataValueY(double _value, int _index) {
	if (_index < this->length) {
		ptrYVal[_index] = _value;
	}
}

// setzt den X-Wert
void CDaten::setDataValueX(double _value, int _index) {
	if (_index < this->length) {
		ptrXVal[_index] = _value;
	}
}

void CDaten::setYDataValueFromTo(int start, int end, double val) {
	for (int k = start; k < end; k++)
		ptrYVal[k] = val;
}

COLORREF CDaten::getLineCol(void) const {
	return lineCol;
}

void CDaten::setLineCol(COLORREF _col) {
	lineCol = _col;
}


