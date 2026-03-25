
#pragma once/**
 * KLASSE: CCtrTypVert
 * ----------------------------------------------------------------
 * Diese Klasse implementiert die Steuerungslogik für vertikale Interaktionselemente.
 * Sie spezialisiert das Verhalten des Controllers auf die vertikale Achse (Y-Richtung).
 *
 * Hauptaufgaben:
 * - Vertikale Wertberechnung: Transformation von vertikalen Mausbewegungen
 * (Y-Pixel) in physikalische Parameter.
 * - Koordinaten-Invertierung: Berücksichtigung der GDI-Koordinatenlogik (Y nimmt nach
 * unten hin zu), um eine intuitive "Schieben-nach-oben"-Steuerung zu ermöglichen.
 * - Bereichsschutz: Sicherstellung, dass der vertikale Schieber die definierten
 * grafischen Grenzen nicht überschreitet.
 * */
#include "Controller.h"
#include "AbstractController.h"
class CCtrTypVert : public CAbstractController {
public:
	CCtrTypVert(CController* pCtr);
	~CCtrTypVert();
	double calcController(CPoint _pos, CDC* pDC, CController* ctrfs);
};
