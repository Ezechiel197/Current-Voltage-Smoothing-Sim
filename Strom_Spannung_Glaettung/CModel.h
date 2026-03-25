#pragma once
/**
 * KLASSE: CModel
 * ----------------------------------------------------------------
 * Diese Klasse bildet das Herzstück der Anwendung und repräsentiert das "Model"
 * im MVC-Entwurfsmuster. Sie enthält die gesamte physikalische Logik und
 * die mathematischen Berechnungsmodelle der verschiedenen Filterschaltungen.
 *
 * Hauptaufgaben:
 * - Parameterverwaltung: Speicherung elektrotechnischer Kennwerte (R, L, C, fsz, Ud).
 * - Simulationslogik: Berechnung von Zeitverläufen für Sägezahn-, Puls- und
 * geglättete Ausgangsspannungen sowie Ströme.
 * - Datenaufbereitung: Verwaltung von Datencontainern (CData) und Koordinatensystemen
 * für die grafische Ausgabe in den Views.
 * - Filtertypen: Implementierung spezifischer Algorithmen für L-, RC- und LC-Filter
 * sowie deren Verhalten unter Last.
 */

#include "Koordinatensystem.h" 
#include "math.h"
#include "AbstractModel.h"
#include "ControllableObject.h"

class CControllableObject;
// Konstanten definieren
#define ANZAHL_PUNKTE 1000
#define ABTASTSRATE 0.00001 
#define U_SAEGEZAHN_MAX 5

class CModel :public CAbstractModel {
private:

	CDaten mDaten;
	// Membervariablen
	double L = 0, C = 0, RL = 0, R = 0;
	double Usteuer = 0, Ud = 0;
	double fsz = 0, f0 = 0; // Frequenz
	double t_ein = 0;

	// Kurven
	CData* Usz = nullptr;
	CData* Uout = nullptr;
	CData* Upulse = nullptr;
	CData* Ustr_graph = nullptr;
	CData* Ipulse = nullptr;
	CData* iR = nullptr;
	CData* Iout = nullptr;

	// Kurven Achsen

	double zeit[ANZAHL_PUNKTE] = { 0 };
	double pulse_y[ANZAHL_PUNKTE] = { 0 };
	double Uout_y[ANZAHL_PUNKTE] = { 0 };
	double Usz_y[ANZAHL_PUNKTE] = { 0 };
	double Ustr_y[ANZAHL_PUNKTE] = { 0 };
	double Iout_y[ANZAHL_PUNKTE] = { 0 };
	double Ipulse_y[ANZAHL_PUNKTE] = { 0 };
	// Variable für den L-Filter
	double UL_y[ANZAHL_PUNKTE] = { 0 };
	double IL_y[ANZAHL_PUNKTE] = { 0 };


public:
	CControllableObject* pL = nullptr;
	CControllableObject* pRL = nullptr;
	CControllableObject* pC = nullptr;
	CControllableObject* pR = nullptr;
	CControllableObject* pUstr = nullptr;
	CControllableObject* pfs = nullptr;


	CDaten* getDaten() override { return &mDaten; }
	// Koordinatensystem 
	CKoordinatensystem* koord_str = nullptr;
	CKoordinatensystem* koord_U = nullptr;
	CKoordinatensystem* koord_I = nullptr;


public:
	CModel();
	~CModel();
	// Set Methoden
	void set_induktivitaet(double l) { L = l; }
	void set_Kapazitaet(double c) { C = c; }
	void set_widerstand(double r) { R = r; } // Widerstand der die Induktivität bei bei No-Filter und RC-Filter ersetzt
	void set_Lastwiderstand(double rL) { RL = rL; }// Lastwiderstand
	void set_steuers_spannung(double Ustr) { Usteuer = Ustr; }
	void set_dreieck_frequenz(double f) { fsz = f; }
	void set_resonanz_frequenz(double f) { f0 = f; }

	// Get Methoden 
	double get_induktivitaet() const { return L; }
	double get_Kapazitaet() { return C; }
	double get_widerstand() { return R; }
	double get_Lastwiderstand() { return RL; }
	double get_steuers_spannung() { return Usteuer; }
	double get_dreieck_frequenz() { return fsz; }
	double get_resonanz_frequenz() { return f0; }
	double get_Tastgrad() { return Usteuer / Ud; }


	CKoordinatensystem* GetDataKoord_U() { return koord_U; }
	CKoordinatensystem* GetDataKoord_str() { return koord_str; }
	CKoordinatensystem* GetDataKoord_I() { return koord_I; }

	void Koordinatensystem();

	void Pulse_U_und_Uout();
	void saegezahn_U_und_steuer_U();
	void I_out_und_I_pulse();
	void Kein_filter();

	// Methode für den L-Filter
	void L_filter();
	void Pulse_U_und_Uout_L();
	void I_out_und_I_pulse_L();

	// Methode für den RC-Filter
	void RC_filter();
	void Pulse_U_und_Uout_RC();
	void I_out_und_I_pulse_RC();

	// Methode für den RC-Filter
	void LC_filter();
	void Pulse_U_und_Uout_LC();
	void I_out_und_I_pulse_LC();
	// Methode für den RC-Filter&Load
	void Pulse_U_und_Uout_RC_und_Load();
	void RC_und_Load_filter();
	void I_out_und_I_pulse_RC_und_Load();
};
