#pragma once
/**
 * KLASSE: CAbstractModel
 * ----------------------------------------------------------------
 * Diese abstrakte Basisklasse bildet das fundamentale Rückgrat der Softwarearchitektur
 * nach dem Model-View-Controller (MVC) Entwurfsmuster.
 *
 * Hauptaufgaben:
 * - Verwaltung der aktiven Controller und Views in dynamischen Listen (Vektoren).
 * - Steuerung des Datenflusses: Benachrichtigung der Views bei Modelländerungen .
 * - Schnittstelle für die Interaktion: Identifikation von aktiven Controllern bei Mausereignissen.
 */
class CAbstractView;
class CController;
class CModell;
#include "Daten.h"
#include "vector"

class CAbstractModel {
protected:
	vector <CAbstractView*> viewListe;
	vector <CController*> controllerListe;
public:
	CAbstractModel();
	virtual ~CAbstractModel();
	void addView(CAbstractView* _pV);
	
	void notifyViews(CDC* pDC);
	virtual void calcModel(CDC* pDC);
	void addCtr(CController* _pM);
	void removeCtr(CController* _pC);

	bool controllerCheck(CPoint _pos);
	CController* getCtrPtr(CPoint _pos);

	virtual CDaten* getDaten(void) = 0;
};

