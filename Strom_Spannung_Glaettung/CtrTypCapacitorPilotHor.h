#pragma once
/**
 * KLASSE: CCtrTypCapacitorPilotHor
 * ----------------------------------------------------------------
 * Diese spezialisierte Controller-Logik-Klasse implementiert das Verhalten
 * eines horizontalen Schiebereglers für einen Kondensator.
 *
 * Hauptaufgaben:
 * - Bewegungseinschränkung : Begrenzung der Mausbewegung auf einen
 * definierten Bereich (Min/Max Pixel), um ein "Ausbrechen" des Bauteils zu verhindern.
 * - Lineare Abbildung : Umrechnung der horizontalen Pixel-Position der
 * Maus in den entsprechenden physikalischen Kapazitätswert .
 * - Echtzeit-Synchronisation: Aktualisierung des Datenmodells 
 * und Anstoß der Neu-Berechnung der gesamten Simulation (calcModel).
 */
#include "AbstractController.h"

class CCtrTypCapacitorPilotHor : public CAbstractController
{
public:
    CCtrTypCapacitorPilotHor(CController* _pCtr);
    ~CCtrTypCapacitorPilotHor();
    double calcController(CPoint _pos, CDC* pDC, CController* ctrfs) override;
};