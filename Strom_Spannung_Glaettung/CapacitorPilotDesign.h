#pragma once
/**
 * KLASSE: CCapacitorPilotDesign
 * ----------------------------------------------------------------
 * Diese Klasse ist eine spezialisierte View-Komponente ("Design-Klasse"),
 * die einen Kondensator im Schaltplan visualisiert und gleichzeitig als
 * grafisches Interface fungiert.
 *
 * Hauptaufgaben:
 * - Dynamische Darstellung: Zeichnet das physikalische Symbol eines Kondensators
 * (zwei parallele Platten) mittels der Windows GDI-Bibliothek (CDC).
 * - Interaktives Feedback: Visualisiert die aktuelle Kapazitätseinstellung durch
 * einen "roten Griff", dessen Position sich synchron zur Mausbewegung verändert.
 * - Koordinatentransformation: Rechnet die abstrakten Controller-Daten (Pixel-Werte)
 * in eine konkrete grafische Darstellung auf dem Bildschirm um.
 */
#include "AbstractView.h"

class CCapacitorPilotDesign : public CAbstractView
{
public:
    CCapacitorPilotDesign(CController* _pCtr);
    ~CCapacitorPilotDesign();
    void draw(CDC* _pDC) override;
};
