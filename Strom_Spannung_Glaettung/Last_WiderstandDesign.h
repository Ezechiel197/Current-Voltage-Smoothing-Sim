#pragma once
/**
 * KLASSE: CLast_WiderstandDesign
 * ----------------------------------------------------------------
 * Diese View-Klasse realisiert die grafische Darstellung des Lastwiderstands (RL)
 * als vertikales Schieberegler-Modul innerhalb des Schaltplans.
 *
 * Hauptaufgaben:
 * - Vertikale Visualisierung: Zeichnet den Widerstandskörper als rechteckiges
 * Element, dessen Länge sich dynamisch entlang der Y-Achse anpasst.
 * - Interaktives Feedback: Ein roter Kontaktbalken (Abgriff) visualisiert die
 * aktuelle Position der Benutzereingabe und damit den eingestellten Widerstandswert.
 * - Dynamisches Beschneiden: Sorgt dafür, dass die grafische Verbindung zwischen dem
 * Ursprungspunkt (org) und der aktuellen Mausposition (act) korrekt dargestellt wird.
 * - Kennzeichnung: Automatische Beschriftung des Bauteils mit dem Symbol "RL".
 */
#include "AbstractView.h"
class CLast_WiderstandDesign : public CAbstractView {
public:
	CLast_WiderstandDesign(CController* _pCtr);
	~CLast_WiderstandDesign();
	void draw(CDC* _pDC);
};


