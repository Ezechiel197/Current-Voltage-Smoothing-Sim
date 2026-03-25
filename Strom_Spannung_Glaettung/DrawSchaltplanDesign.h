
#pragma once
/**
 * KLASSE: CDrawSchaltplanDesign
 * ----------------------------------------------------------------
 * Diese Klasse ist die zentrale grafische Komponente für die Darstellung
 * des interaktiven Schaltplans. Sie fungiert als "Container-View".
 *
 * Hauptaufgaben:
 * - Topologie-Zeichnung: Konstruktion des gesamten Stromkreises (Leitungen,
 * Knotenpunkte, Rahmen) unter Verwendung der Windows GDI.
 * - Dynamische Schalterzustände: Visualisierung der Schaltzustände (S1/S2)
 * in Abhängigkeit der Benutzereingabe (offen/geschlossen).
 * - PWM-Visualisierung: Grafische Darstellung des DC-DC-Wandlers inklusive
 * Symbolen für Rechtecksignale und Spannungspfeile.
 * - Intelligente Leitungsführung: Automatische Anpassung der Verbindungsdrähte
 * an die aktuelle Position der Schieberegler (z.B. Widerstand RL oder Kondensator C).
 */
#include "AbstractView.h"

class CDrawSchaltplanDesign :public CAbstractView {

	CPoint org;
	CPoint orgC;
	bool m_bS1Closed;
	bool m_bS2Closed;
	CController* ctrC;
	CController* ctrRL;

public:

	CDrawSchaltplanDesign();
	CDrawSchaltplanDesign(CPoint _org, CPoint _orgC, bool _m_bS1Closed, bool _m_bS2Closed, CController* _ctrC, CController* _ctrRL);
	~CDrawSchaltplanDesign();
	void draw(CDC* pDC);
	void DrawSwitchV(CDC* pDC, int x, int y1, int y2, bool closed, int r = 4);
	void DrawSwitchH(CDC* pDC, int x1, int x2, int y, bool closed, int r = 4);

	void set_m_bS1Closed(bool _m_bS1Closed) { m_bS1Closed = _m_bS1Closed; }
	void set_m_bS2Closed(bool _m_bS2Closed) { m_bS2Closed = _m_bS2Closed; }
	bool get_m_bS1Closed() {return  m_bS1Closed ; }
	bool get_m_bS2Closed() { return  m_bS2Closed; }

};