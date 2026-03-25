#pragma once
/**
 * KLASSE: CDaten
 * ----------------------------------------------------------------
 * Hauptaufgaben:
 * - Dynamische Speicherverwaltung: Verwaltung von Double-Arrays für X- und
 * Y-Koordinaten zur Darstellung komplexer Funktionsverläufe.
 * - Statistische Analyse: Bereitstellung von Methoden zur Ermittlung von
 * Extremwerten (Min/Max) und Mittelwerten innerhalb der Datensätze.
 * - Grafik-Metadaten: Speicherung von Darstellungsparametern wie Linienfarbe,
 * Dicke und Stil 
 * - Datensicherheit: Implementierung eines Kopier-Konstruktors,
 * um Speicherfehler bei der Übergabe von Objekten zu verhindern.
 */

using namespace std;

#include <string>      
#include <afxwin.h>

class CDaten {
protected:
	double* ptrXVal;
	double* ptrYVal;
	int length;
	string name;
	bool pointView;
	int lineStyle;
	int lineWidth;
	COLORREF lineCol;
public:
	CDaten& getModel();
	void setDataValueY(double _value, int _index);
	void setDataValueX(double _value, int _index);
	int getLength(void)const;
	void setPointView(void);
	bool getPointView(void);
	void setName(string _name);
	string getName(void)const;
	double* getXData(void);
	double* getYData(void);
	CDaten(void);
	CDaten(const CDaten& CD);
	CDaten(int _width, int _style, string _name, bool _pointView, int _length);
	double getMinX(void)const;
	double getMaxX(void)const;
	double getMinY(void)const;
	double getMaxY(void)const;
	double getMeanY(void)const;
	int getLineWidth()const;
	int getLineStyle() const;
	void setLineWidth(int _width);
	void setLineStyle(int _style);
	~CDaten(void);
	double Round(double Zahl, int Stellen);
	void setYDataValueFromTo(int start, int end, double val);
	COLORREF getLineCol(void) const;
	void setLineCol(COLORREF _col);
};


