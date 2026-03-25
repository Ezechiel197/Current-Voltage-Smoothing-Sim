#pragma once
/**
 * KLASSE: CLegende
 * ----------------------------------------------------------------
 * Diese View-Klasse dient der Benutzerführung und sorgt für die eindeutige
 * Interpretation der simulierten Kurvenverläufe.
 *
 * Hauptaufgaben:
 * - Statische Visualisierung: Erstellung einer Farblegende für alle im Oszilloskop-
 * Bereich dargestellten Signale (Spannungen und Ströme).
 * - Grafische Zuordnung: Zeichnen von Farbindikatoren (Ellipsen) und der
 * zugehörigen Beschriftungen (TextOut) an fest definierten Koordinaten.
 * - Erhöhung der Übersichtlichkeit: Ermöglicht dem Anwender die schnelle
 * Unterscheidung zwischen Quellgrößen (z.B. Upulse) und geglätteten Ausgangsgrößen (Uout).
 */
#include "AbstractView.h"
class CLegende : public CAbstractView {
public:
	CLegende();
	~CLegende();
	void draw(CDC* _pDC);
};
