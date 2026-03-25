#pragma once
/**
 * KLASSE: CInduktorDesign
 * ----------------------------------------------------------------
 * Diese View-Klasse ist für die grafische Darstellung der Induktivität (L)
 * innerhalb des Schaltplans verantwortlich.
 *
 * Hauptaufgaben:
 * - Symbolische Darstellung: Zeichnet das physikalische Symbol einer Spule
 *  mittels GDI-Funktionen.
 * - Interaktive Anzeige: Visualisiert den veränderbaren Teil der Induktivität
 * durch einen roten Stellgriff, der die aktuelle Benutzerinteraktion widerspiegelt.
 * - Dynamische Skalierung: Berechnet die Breite des Bauteils in Echtzeit basierend
 * auf der Mausposition (act.x), um eine intuitive Längenänderung zu simulieren.
 * - Labelling: Platzierung der Bauteilbezeichnung "L" an einer fest definierten
 * Position im User Interface.
 */
#include "AbstractView.h"
class CInduktorDesign : public CAbstractView {
public:
	CInduktorDesign(CController* _pCtr);
	~CInduktorDesign();
	void draw(CDC* _pDC);
};

