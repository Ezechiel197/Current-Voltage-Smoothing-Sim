



#include "pch.h"
#include "CModel.h"
#include <cmath>


CModel::CModel()
{
	// Standardwerte setzen
	fsz = 500;
	Usteuer = 2.5;
	R = 0.86;
	RL = 0.50;
	L = 0.00074;
	C = 0.0004;
	Ud = 5;
	koord_str = new CKoordinatensystem();
	koord_U = new CKoordinatensystem();
	koord_I = new CKoordinatensystem();
	Usz = new CData();
	Uout = new CData();
	Upulse = new CData();
	Ustr_graph = new CData();
	Ipulse = new CData();
	Iout = new CData();
	iR = new CData();
}
CModel::~CModel() {
	delete koord_str; koord_str = nullptr;
	delete koord_U; koord_U = nullptr;
	delete koord_I; koord_I = nullptr;
	delete Usz;        Usz = nullptr;
	delete Uout;       Uout = nullptr;
	delete Upulse;     Upulse = nullptr;
	delete Ustr_graph; Ustr_graph = nullptr;
	delete Ipulse;     Ipulse = nullptr;
	delete Iout;       Iout = nullptr;
	delete iR;         iR = nullptr;
}
// Sägezahn und Steuerspannung
void CModel::saegezahn_U_und_steuer_U() {
	t_ein = Usteuer / (fsz * U_SAEGEZAHN_MAX);
	// Sägezahnspannung
	int Usz_y_min = 0;
	int Usz_y_max = U_SAEGEZAHN_MAX;
	double periode = 0;

	if (fsz > 0) periode = 1 / (double)fsz;
	else periode = 1;

	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		zeit[i] = i * ABTASTSRATE; // Zeitachse füllen
		double zeitInPeriode = fmod(zeit[i], periode);
		if (zeitInPeriode == 0) Usz_y[i] = Usz_y_min;

		else Usz_y[i] = (Usz_y_max - Usz_y_min) * fsz * zeitInPeriode;

	}

	// Steuerspannung
	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		Ustr_y[i] = Usteuer;
	}
}

void CModel::Koordinatensystem() {

	// Koordinatensystem für Steuerelement
	Usz->setName("Usz");
	Usz->setGrau();
	Ustr_graph->setName("Ustr");
	//Ustr_graph.setBlue();
	Usz->setXYdata(zeit, Usz_y, ANZAHL_PUNKTE);
	Ustr_graph->setXYdata(zeit, Ustr_y, ANZAHL_PUNKTE);
	koord_str->ClearData();
	koord_str->addData(*Usz);
	//koord_str.addData(Ustr_graph);
	// Koordinatensystem für Spannungen
	Upulse->setName("Upulse");
	Upulse->setBlack();
	Uout->setName("Uout");
	Uout->setRed();
	Upulse->setXYdata(zeit, pulse_y, ANZAHL_PUNKTE);
	Uout->setXYdata(zeit, Uout_y, ANZAHL_PUNKTE);
	koord_U->ClearData();
	koord_U->addData(*Upulse);
	koord_U->addData(*Uout);
	// Koordinatensystem für Strömen
	Ipulse->setName("Ipulse");
	Ipulse->setBlack();
	Iout->setName("Iout");
	Iout->setRed();
	Ipulse->setXYdata(zeit, Ipulse_y, ANZAHL_PUNKTE);
	Iout->setXYdata(zeit, Iout_y, ANZAHL_PUNKTE);
	koord_I->ClearData();
	koord_I->addData(*Ipulse);
	koord_I->addData(*Iout);
}
// pulsierende- und Ausgangsspannung und No-Filter
void CModel::Pulse_U_und_Uout()
{
	// Rechteckspannung
	double amplitude = Ud;
	double periode = 0;

	if (fsz > 0) periode = 1 / (double)fsz;
	else periode = 1;

	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		//zeit[i] = i * ABTASTSRATE; // Zeitachse füllen

		double zeitInPeriode = fmod(zeit[i], periode);
		TRACE(_T("Der aktuelle Wert ist: %d\n"), t_ein);
		if (zeitInPeriode <= t_ein) {
			pulse_y[i] = amplitude; // HIGH
		}
		else {
			pulse_y[i] = 0;       // LOW 
		}
	}

	// Ausgangsspannung
	double G = 0;
	if ((R + RL) > 0) G = RL / (R + RL);

	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		Uout_y[i] = G * pulse_y[i];
	}
}

// pulsierende- und Ausgangsstrom
void CModel::I_out_und_I_pulse() {

	double G = 0;
	if ((R + RL) > 0) G = 1 / (R + RL);

	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		Iout_y[i] = G * pulse_y[i];
		Ipulse_y[i] = Iout_y[i];

	}
}


void CModel::Kein_filter()
{
	saegezahn_U_und_steuer_U();
	Pulse_U_und_Uout();
	I_out_und_I_pulse();
	Koordinatensystem();

}


// Ab hier beginnt der Programmcode für den Teil L-Filter
void CModel::Pulse_U_und_Uout_L() {
	double periode = 0;
	double tau = L / RL;
	double U_start = 0;
	double U_ein_max = 0;

	if (fsz > 0) periode = 1 / (double)fsz;
	else periode = 1;
	U_start = Ud * (1 - exp(-t_ein / tau)) / (1 - exp(-periode / tau)) * exp(-(periode - t_ein) / tau);
	U_ein_max = Ud - (Ud - U_start) * exp(-RL * t_ein / L);
	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		double zeitInPeriode = fmod(zeit[i], periode);

		if (zeitInPeriode <= t_ein) {

			Uout_y[i] = Ud - (Ud - U_start) * exp(-RL * zeitInPeriode / L);
		}
		else {

			Uout_y[i] = U_ein_max * exp(-RL * (zeitInPeriode - t_ein) / L);
		}
	}
}
void CModel::I_out_und_I_pulse_L() {

	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		Iout_y[i] = Uout_y[i] / RL;
		Ipulse_y[i] = Iout_y[i];
	}
}
void CModel::L_filter()
{
	saegezahn_U_und_steuer_U();
	Pulse_U_und_Uout();
	Pulse_U_und_Uout_L();
	I_out_und_I_pulse_L();
	Koordinatensystem();
}


// Ab hier beginnt der Programmcode für den Teil RC-Filter
void CModel::Pulse_U_und_Uout_RC() {
	double periode = 0;
	double tau = R * C;
	double U_aus = 0;
	double U_ein_max = 0;

	if (fsz > 0) periode = 1 / (double)fsz;
	else periode = 1;
	double t_aus = periode - t_ein;

	double U_start = Ud * (1 - exp(-t_ein / tau)) / (1 - exp(-periode / tau)) * exp(-(periode - t_ein) / tau);
	U_ein_max = Ud * (1 - exp(-t_ein / tau)) + U_start * exp(-t_ein / tau);
	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		double zeitInPeriode = fmod(zeit[i], periode);

		if (zeitInPeriode <= t_ein) {

			Uout_y[i] = Ud * (1 - exp(-zeitInPeriode / tau)) + U_start * exp(-zeitInPeriode / tau);
		}
		else {

			Uout_y[i] = U_ein_max * exp(-(zeitInPeriode - t_ein) / tau);
		}
	}
}
void CModel::I_out_und_I_pulse_RC() {

	double periode = 0;
	double tau = R * C;
	double U_aus = 0;
	double U_ein_max = 0;

	if (fsz > 0) periode = 1 / (double)fsz;
	else periode = 1;
	double t_aus = periode - t_ein;
	U_aus = Ud * exp(-t_aus / tau);
	U_ein_max = Ud * (1 - exp(-t_ein / tau)) + U_aus * exp(-t_ein / tau);

	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		double zeitInPeriode = fmod(zeit[i], periode);

		if (zeitInPeriode <= t_ein) {

			Ipulse_y[i] = ((Ud * exp(-zeitInPeriode / tau) / R) - (U_aus * exp(-zeitInPeriode / tau) / R));
			Iout_y[i] = 0;

		}
		else {

			Ipulse_y[i] = (-U_ein_max * exp(-(zeitInPeriode - t_ein) / tau)) / R;
			Iout_y[i] = 0;
		}
	}
}

void CModel::RC_filter()
{
	saegezahn_U_und_steuer_U();
	Pulse_U_und_Uout();
	Pulse_U_und_Uout_RC();
	I_out_und_I_pulse_RC();
	Koordinatensystem();
}
// Ab hier beginnt der Programmcode für den Teil LC-Filter
void CModel::Pulse_U_und_Uout_LC() {
	double periode = 0;
	double delta = 1 / (2 * RL * C);
	double omega = 1 / sqrt(L * C);
	double omega_d = 0;
	//double omega = 2*PI*fsz;

	double Unter_Wurzel = omega * omega - delta * delta;
	if (Unter_Wurzel <= 0) omega_d = 0.000001;
	else omega_d = sqrt(Unter_Wurzel);

	double U_ein_max = 0;
	double U_aus_min = 0;
	if (fsz > 0) periode = 1 / (double)fsz;
	else periode = 1;

	U_ein_max = Ud + (Usteuer - Ud) * exp(-delta * t_ein) * (cos(omega_d * t_ein) + delta / omega_d * sin(omega_d * t_ein));
	U_aus_min = U_ein_max * exp(-delta * (periode - t_ein)) * (cos(omega_d * (periode - t_ein)) + delta / omega_d * sin(omega_d * (periode - t_ein)));

	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		double zeitIn_P = fmod(zeit[i], periode);
		//Uout_y[i] = Usteuer + (0 - Usteuer) * exp(-delta * zeit[i]) * (cos(omega_d * zeit[i]) + delta / omega_d * sin(omega_d * zeit[i]));
		if (zeitIn_P <= t_ein) {

			Uout_y[i] = Ud + (U_aus_min - Ud) * exp(-delta * zeitIn_P) * (cos(omega_d * zeitIn_P) + delta / omega_d * sin(omega_d * zeitIn_P));
		}
		else {
			double U_ein_max = Uout_y[(int)(t_ein / ABTASTSRATE)];
			Uout_y[i] = U_ein_max * exp(-delta * (zeitIn_P - t_ein)) * (cos(omega_d * (zeitIn_P - t_ein)) + delta / omega_d * sin(omega_d * (zeitIn_P - t_ein)));

		}

	}
}
void CModel::I_out_und_I_pulse_LC() {

	double periode = 0;
	double delta = 1 / (2 * RL * C);
	double omega = 1 / sqrt(L * C);
	//double omega = 2*PI*fsz;
	double omega_d = 0;
	double Unter_Wurzel = omega * omega - delta * delta;
	double U_ein_max = 0;
	double U_aus_min = 0;
	double I_current = 0;

	if (Unter_Wurzel <= 0) omega_d = 0.000001;
	else omega_d = sqrt(Unter_Wurzel);


	if (fsz > 0) periode = 1 / (double)fsz;
	else periode = 1;
	double t_aus = periode - t_ein;

	U_ein_max = Ud + (Usteuer - Ud) * exp(-delta * t_ein) * (cos(omega_d * t_ein) + delta / omega_d * sin(omega_d * t_ein));
	U_aus_min = U_ein_max * exp(-delta * (periode - t_ein)) * (cos(omega_d * (periode - t_ein)) + delta / omega_d * sin(omega_d * (periode - t_ein)));
	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		double zeitInPeriode = fmod(zeit[i], periode);

		if (zeitInPeriode <= t_ein) {

			Ipulse_y[i] = (Ud - Uout_y[i]) * zeitInPeriode / L + U_aus_min / R;
			Iout_y[i] = Uout_y[i] / R;
			I_current = Ipulse_y[i];
		}
		else {
			Ipulse_y[i] = -Uout_y[i] * (zeitInPeriode - t_ein) / L + I_current;
			Iout_y[i] = Uout_y[i] / R;
		}
	}
}
void CModel::LC_filter()
{
	saegezahn_U_und_steuer_U();
	Pulse_U_und_Uout();
	Pulse_U_und_Uout_LC();
	I_out_und_I_pulse_LC();
	Koordinatensystem();
}
// Ab hier beginnt der Programmcode für den Teil RC-Filter und Load
void CModel::Pulse_U_und_Uout_RC_und_Load() {
	double periode = 0;
	double lamda = -(1 + (RL / R)) / (RL * C);
	double U_aus = 0;
	double U_ein_max = 0;
	double K = R / (RL + R);
	double U_peak_current = 0;


	if (fsz > 0) periode = 1 / (double)fsz;
	else periode = 1;
	double t_aus = periode - t_ein;
	double U_start = K * Ud * (1 - exp(lamda * t_ein)) / (1 - exp(lamda * periode)) * exp(-(periode - t_ein) / (K * RL * C));

	U_ein_max = K * Ud * (1 - exp(lamda * t_ein)) + U_start * exp(lamda * t_ein);
	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		double zeitInPeriode = fmod(zeit[i], periode);

		if (zeitInPeriode <= t_ein) {

			Uout_y[i] = K * Ud * (1 - exp(lamda * zeitInPeriode)) + U_start * exp(lamda * zeitInPeriode);
			U_peak_current = Uout_y[i];
		}
		else {

			Uout_y[i] = U_peak_current * exp(-(zeitInPeriode - t_ein) / (K * RL * C));
		}
	}
}
void CModel::I_out_und_I_pulse_RC_und_Load() {

	double periode = 0;
	double K = R / (RL + R);
	double lamda = -(1 + (RL / R)) / (RL * C);
	double U_peak_current = 0;

	if (fsz > 0) periode = 1 / (double)fsz;
	else periode = 1;
	double t_aus = periode - t_ein;
	double U_start = K * Ud * (1 - exp(lamda * t_ein)) / (1 - exp(lamda * periode)) * exp(-(periode - t_ein) / (K * RL * C));
	for (int i = 0; i < ANZAHL_PUNKTE; i++) {
		double zeitInPeriode = fmod(zeit[i], periode);

		if (zeitInPeriode <= t_ein) {
			Iout_y[i] = Uout_y[i] / R;
			Ipulse_y[i] = C * (K * Ud * (-lamda * exp(lamda * zeitInPeriode)) + U_start * lamda * exp(lamda * zeitInPeriode)) + Iout_y[i];
			U_peak_current = Uout_y[i];
		}
		else {

			Iout_y[i] = Uout_y[i] / R;
			Ipulse_y[i] = -U_peak_current * exp(-(zeitInPeriode - t_ein) / (K * RL * C)) / (RL * K) + Iout_y[i];
		}
	}
}

void CModel::RC_und_Load_filter()
{
	saegezahn_U_und_steuer_U();
	Pulse_U_und_Uout();
	Pulse_U_und_Uout_RC_und_Load();
	I_out_und_I_pulse_RC_und_Load();
	Koordinatensystem();
}