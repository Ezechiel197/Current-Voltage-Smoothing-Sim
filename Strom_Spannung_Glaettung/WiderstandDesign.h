#pragma once
/**
 * KLASSE: CWiderstandDesign
 * ----------------------------------------------------------------
 * Diese View-Klasse übernimmt die grafische Darstellung eines ohmschen
 * Widerstands (R) im interaktiven Schaltplan.
 *
 * Hauptaufgaben:
 * - Symbolik-Zeichnung: Darstellung des Widerstands als genormtes Rechteck
 * gemäß elektrotechnischer Standards.
 * - Dynamische Längenanpassung: Visualisierung des Widerstandswerts durch
 * proportionale Änderung der Rechteckbreite in Abhängigkeit der Mausposition.
 * - Benutzerführung: Zeichnen eines roten Interaktions-Handles, das dem
 * Anwender signalisiert, an welcher Stelle der Parameter verändert werden kann.
 * - Konsistente UI: Platzierung des Labels "R" zur eindeutigen Identifizierung
 * des Bauteils innerhalb der Simulationsumgebung.
 */
#include "AbstractView.h"
class CWiderstandDesign : public CAbstractView {
public:
	CWiderstandDesign(CController* _pCtr);
	~CWiderstandDesign();
	void draw(CDC* _pDC);
};

