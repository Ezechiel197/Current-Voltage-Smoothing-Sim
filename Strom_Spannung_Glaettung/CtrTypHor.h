#pragma once
/**
 * KLASSE: CCtrTypHor
 * ----------------------------------------------------------------
 * Diese Klasse implementiert die Steuerungslogik für horizontale Interaktionselemente.
 * Sie berechnet die Transformation von Mauskoordinaten in physikalische Einheiten.
 *
 * Hauptaufgaben:
 * - Lineares Mapping: Umrechnung der X-Position der Maus in Bauteilwerte (z.B. Ohm).
 * - Sonderlogik für Schaltfrequenz: Implementierung einer spezifischen
 * Berechnungsformel für die Frequenzsteuerung (fsz).
 * - Begrenzungslogik: Sicherstellung, dass der Schieberegler innerhalb der
 * visuellen Grenzen (MinPx/MaxPx) bleibt.
 * - Simulations-Trigger: Automatischer Aufruf der Modellberechnung bei jeder
 * Wertänderung, um Echtzeit-Feedback in den Graphen zu ermöglichen.
 */
#include "Controller.h"
#include "AbstractController.h"
class CCtrTypHor : public CAbstractController {
public:
	CCtrTypHor(CController* pCtr);
	~CCtrTypHor();
	double calcController(CPoint _pos, CDC* pDC, CController* ctrfs);
};
