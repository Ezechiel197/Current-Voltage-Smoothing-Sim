#pragma once
/**
 * KLASSE: CControllableObject
 * ----------------------------------------------------------------
 * Diese Klasse fungiert als Datenmodell für alle veränderbaren Parameter
 * der Simulation (z.B. Widerstandswerte, Induktivitäten, Frequenzen).
 *
 * Hauptaufgaben:
 * - Werte-Kapselung: Speicherung von Minimal-, Maximal- und aktuellen Werten
 * eines physikalischen Parameters.
 * - Validierung: Sicherstellung der Datenintegrität durch Bereichsprüfung
 *  bei Wertänderungen.
 * - Abstraktion: Trennung der physikalischen Größe von ihrer grafischen
 * Repräsentation im User Interface.
 */
#include "AbstractModel.h"
class CControllableObject {
protected:
	double minVal;
	double maxVal;
	string name;
	double actualVal;
public:
	CControllableObject();
	CControllableObject(double _minVal, double _actVal, double _maxVal, string _name);
	virtual ~CControllableObject();
	double getMaxVal();
	double getMinVal();
	double getActualVal();
	string getName();
	void setActualValue(double _actVal);
};


