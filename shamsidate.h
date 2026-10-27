//---------------------------------------------------------------------------

#ifndef sdateH
#define sdateH
#include <classes.hpp>
//---------------------------------------------------------------------------
struct CDate
{
	int y;
	int m;
	int d;
};

class TShamsiDate
{
private:
	int mMonthDays(int year, int month);
	int sMonthDays(int year, int month);
	int mYearDays(int year);
	int sYearDays(int year);
	WideString GetShamsiString(bool shortYear=false);
	void SetShamsiString(WideString value);
	WideString GetMiladiString();
	void SetMiladiString(WideString value);
	CDate DateTimeToShamsi(TDateTime dt);
	CDate ShamsiToMiladi(int sYear, int sMonth, int sDay);
	TDateTime ShamsiToDateTime(int sYear, int sMonth, int sDay);
	TDateTime ShamsiToDateTime(CDate date);
	WideString DateTimeToShamsiStr(TDateTime dt, bool shortYear=false);
	int GetShamsiYear();
	int GetShamsiMonth();
	int GetShamsiDay();
	void SetShamsiYear(int value);
	void SetShamsiMonth(int value);
	void SetShamsiDay(int value);
	WideString GetDayName();
	int get_monthDaysCount();
	int get_dayOfWeek();
	WideString GetShamsiYM();
	WideString GetShamsiMD();
	TShamsiDate GetNextMonth();
	TShamsiDate GetShamsiNow();
	String get_asString()
	{
        return GetShamsiString(true);
    }
public:
	//--------------------------------------------------------------------------
	double Val;
	TShamsiDate(int value=0);
	TShamsiDate(char* value);
	TShamsiDate(String value);
	TShamsiDate(TDateTime value);
	int GetShamsiMonthDays(int year, int month);
	CDate AddShamsiMonth(CDate sDate, int count);
	CDate ShamsiStrToDate(String sDate);
	TDateTime ShamsiStrToDateTime(String sDate);
	bool OfThisShamsiMonth(int date);
	bool OfNextShamsiMonth(int date);
	int operator = (int value);
	int operator = (TShamsiDate value);
	int operator = (TDateTime value);
	int operator = (String value);
	int operator - (TShamsiDate value);
	int operator + (TShamsiDate value);
	int operator += (int value);
	int operator ++ (){return Val++;};
	int operator -- (){return Val--;};
	int operator -= (int value);
	void getMonthBounds(TShamsiDate &date1, TShamsiDate &date2);
	bool isLeap(int y);
	operator int ();
	TShamsiDate operator = (char* value);
	__property WideString ShamsiString = {read=GetShamsiString, write=SetShamsiString};
	__property WideString asString = {read=get_asString};
	__property WideString MiladiString = {read=GetMiladiString, write=SetMiladiString};
	__property int ShamsiYear = {read=GetShamsiYear, write=SetShamsiYear};
	__property int ShamsiMonth = {read=GetShamsiMonth, write=SetShamsiMonth};
	__property int ShamsiDay = {read=GetShamsiDay, write=SetShamsiDay};
	__property WideString DayName = {read=GetDayName};
	__property int monthDaysCount = {read=get_monthDaysCount};
	__property int dayOfWeek = {read=get_dayOfWeek};
	__property WideString ShamsiYM = {read=GetShamsiYM};
	__property WideString ShamsiMD = {read=GetShamsiMD};
	__property TShamsiDate NextMonth = {read=GetNextMonth};
	__property TShamsiDate ShamsiNow = {read=GetShamsiNow};
};

#endif
