#pragma once
/**
 * KLASSE: CAbstractView
 * ----------------------------------------------------------------
 * Diese abstrakte Basisklasse definiert das Grundgerüst für alle grafischen
 * Elemente der Benutzeroberfläche (Schaltpläne, Bauteile, Skalen).
 *
 * Hauptaufgaben:
 * - Bereitstellung einer einheitlichen Schnittstelle für den Zeichenvorgang (draw).
 * - Kapselung der Verbindung zum zugehörigen Controller (pCtr), um
 * Benutzereingaben (z.B. Slider-Bewegungen) grafisch umzusetzen.
 * - Trennung der rein visuellen Logik von der mathematischen Simulation.
 */
#include "Controller.h"
class CAbstractView {
protected:
	CController* pCtr;
public:
	CAbstractView();
	~CAbstractView();
	virtual void draw(CDC* _pDC) = 0;
};

