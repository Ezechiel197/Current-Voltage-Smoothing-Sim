#pragma once
/**
 * KLASSE: CAbstractController
 * ----------------------------------------------------------------
 * Diese Basisklasse definiert das logische Verhalten aller spezialisierten
 * Controller-Typen (horizontal, vertikal, etc.).
 *
 * Hauptaufgaben:
 * - Zustands-Mapping: Umrechnung zwischen physikalischen Werten (z.B. Henry, Farad)
 * und grafischen Bildschirmkoordinaten (Pixel).
 * - Initialisierung: Synchronisation der grafischen Schieberposition beim
 * Programmstart basierend auf den Default-Werten des Modells.
 * - Abstraktion: Bereitstellung einer einheitlichen Schnittstelle für den
 * Haupt-Controller, um verschiedene Steuerungslogiken (Linear, Pilot-Capacitor)
 * polymorph zu behandeln.
 */
#include "Controller.h"

class CAbstractController {
protected:
	CController* pCtr;

public:
	
	CAbstractController(CController* pCtr);
	~CAbstractController();

	virtual double calcController(CPoint _pos, CDC* pDC, CController* ctrfs) = 0;
	void init(void);
};

