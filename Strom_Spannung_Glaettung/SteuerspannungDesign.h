#pragma once
/**
 * KLASSE: CSteuerspannungDesign
 * ----------------------------------------------------------------
 * Diese Klasse visualisiert die Steuerspannung (Usteuer) 
 *  und dient gleichzeitig als interaktiver vertikaler Slider.
 *
 * Hauptaufgaben:
 * - Signal-Indikator: Zeichnet eine horizontale blaue Linie , welche das
 * Spannungsniveau der Steuerspannung im Verhältnis zum Sägezahnsignal darstellt.
 * - Interaktives Handle: Erstellt ein komplexes, rotes Navigationssymbol (Pfad-Grafik),
 * das genau an der aktuellen vertikalen Mausposition (act.y) verankert ist.
 * - PWM-Feedback: Durch die vertikale Verschiebung dieser Komponente sieht der Nutzer
 * sofort, wie sich der Schnittpunkt mit dem Sägezahn und damit das Tastverhältnis ändert.
 * - Pfad-basierte Symbolik: Nutzung von BeginPath/EndPath zur Erzeugung eines
 * markanten Icons, das die präzise Justierung der Spannung ermöglicht.
 */
#include "AbstractView.h"
class CSteuerspannungDesign : public CAbstractView {
public:
	CSteuerspannungDesign(CController* _pCtr);
	~CSteuerspannungDesign();
	void draw(CDC* _pDC);
};
