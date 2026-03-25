#pragma once
/**
 * KLASSE: CSchaltfrequenzDesign
 * ----------------------------------------------------------------
 * Diese View-Klasse ist für die grafische Darstellung des Stellglieds der
 * Schaltfrequenz (fsz) verantwortlich.
 *
 * Hauptaufgaben:
 * - Komplexe Formzeichnung: Erstellung eines spezifischen Interaktionssymbols
 * unter Verwendung der GDI-Path-Funktionen.
 * - Dynamische Positionierung: Das Symbol folgt präzise der aktuellen
 * Mauskoordinate (act), um dem Benutzer visuelles Feedback bei der
 * Frequenzänderung zu geben.
 * - Pfad-basierte Grafik: Kombination von Linien- und Fülloperationen zur
 * Erzeugung eines markanten grafischen Indikators.
 */
#include "AbstractView.h"
class CSchaltfrequenzDesign : public CAbstractView {
public:
	CSchaltfrequenzDesign(CController* _pCtr);
	~CSchaltfrequenzDesign();
	void draw(CDC* _pDC);
};
