//---------------------------------------------------------------------------


#pragma hdrstop

#include "shamsidate.h"

//---------------------------------------------------------------------------
void miladi_to_shamsi(int  g_y, int  g_m, int  g_d,
	int *j_y, int *j_m, int *j_d);
void shamsi_to_miladi(int  j_y, int  j_m, int  j_d,
	int *g_y, int *g_m, int *g_d);

//---------------------------------------------------------------------------
TShamsiDate::TShamsiDate(int value)
{
	Val = value;
}
//---------------------------------------------------------------------------
TShamsiDate::TShamsiDate(char* value)
{
	operator = (value);
}
//---------------------------------------------------------------------------
TShamsiDate::TShamsiDate(String value)
{
	operator = (value);
}
//---------------------------------------------------------------------------
TShamsiDate::TShamsiDate(TDateTime value)
{
	Val = value.Val;
}
//---------------------------------------------------------------------------
int TShamsiDate::mMonthDays(int year, int month)
{
	static int mDaysCount[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(month == 2 && !((year - 2000)%4))
		return 29;
	return mDaysCount[month - 1];
}
//--------------------------------------------------------------------------
int TShamsiDate::sMonthDays(int year, int month)
{
	static int sDaysCount[] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
	if(month == 12 && !((year - 1379)%4))
		return 30;
	return sDaysCount[month - 1];
}
//--------------------------------------------------------------------------
int TShamsiDate::mYearDays(int year)
{
	int days = 0;
	for(int t=1; t<=12; t++)
		days += mMonthDays(year, t);
	return days;
}
//--------------------------------------------------------------------------
int TShamsiDate::sYearDays(int year)
{
	int days = 0;
	for(int t=1; t<=12; t++)
		days += sMonthDays(year, t);
	return days;
}
//--------------------------------------------------------------------------
WideString TShamsiDate::GetShamsiString(bool shortYear)
{
	if(Val == 0) return WideString("");
	return DateTimeToShamsiStr(Val, shortYear);
}
void TShamsiDate::SetShamsiString(WideString value)
{
	Val = ShamsiStrToDateTime(value);
}
//--------------------------------------------------------------------------
WideString TShamsiDate::GetMiladiString()
{
	return String(TDateTime(Val).DateTimeString());
}
//---------------------------------------------------------------------------
void TShamsiDate::SetMiladiString(WideString value)
{
	CDate date = ShamsiStrToDate(value);
	Val = EncodeDate(date.y, date.m, date.d);
}
//---------------------------------------------------------------------------
TDateTime TShamsiDate::ShamsiToDateTime(int sYear, int sMonth, int sDay)
{
	int y, m, d;
	shamsi_to_miladi(sYear, sMonth, sDay, &y, &m, &d);
	return EncodeDate(y, m, d);
}
//---------------------------------------------------------------------------
TDateTime TShamsiDate::ShamsiToDateTime(CDate date)
{
	return ShamsiToDateTime(date.y, date.m, date.d);
}
//---------------------------------------------------------------------------
CDate TShamsiDate::DateTimeToShamsi(TDateTime dt)
{
	unsigned short y, m, d;
	int sy, sm, sd;
	dt.DecodeDate(&y, &m, &d);
	miladi_to_shamsi(y, m, d, &sy, &sm, &sd);
	CDate date = {sy, sm, sd};
	return date;
}
//---------------------------------------------------------------------------
WideString TShamsiDate::DateTimeToShamsiStr(TDateTime dt, bool shortYear)
{
	unsigned short y, m, d;
	dt.DecodeDate(&y, &m, &d);
	int jy, jm, jd;
	miladi_to_shamsi(y, m, d, &jy, &jm, &jd);
	String sy, sm, sd;
	sy = jy;
	sm = jm;
	if(sm.Length() == 1) sm = "0" + sm;
	sd = jd;
	if(sd.Length() == 1) sd = "0" + sd;
	String year = sy;
	if(shortYear) year = year.SubString(3, 2);
	WideString result = year + WideString("/") +
		WideString(sm) + WideString("/") + WideString(sd);
	return result;
}
//---------------------------------------------------------------------------
int TShamsiDate::GetShamsiMonthDays(int year, int month)
{
	return sMonthDays(year, month);
}
//---------------------------------------------------------------------------
CDate TShamsiDate::AddShamsiMonth(CDate sDate, int count)
{
	sDate.m += count;
	while(sDate.m > 12)
	{
		sDate.y ++;
		sDate.m -= 12;
	}
	while(sDate.m < 1)
	{
		sDate.y --;
		sDate.m += 12;
	}
	return sDate;
}
//---------------------------------------------------------------------------
CDate TShamsiDate::ShamsiStrToDate(String sDate)
{
	CDate result = {0};
	int pos1 = sDate.Pos("/");
	if(pos1)
	{
		result.y = sDate.SubString(1, pos1 - 1).ToInt();
		if(result.y < 100) result.y += 1300;
		sDate[pos1] = '*';
	}
	int pos2 = sDate.Pos("/");
	if(pos2)
	{
		result.m = sDate.SubString(pos1 + 1, pos2 - pos1 - 1).ToInt();
		result.d = sDate.SubString(pos2 + 1, 2).ToInt();
	}
	return result;
}
//---------------------------------------------------------------------------
TDateTime TShamsiDate::ShamsiStrToDateTime(String sDate)
{
	if(sDate.Length() == 0) return 0;
	CDate date = ShamsiStrToDate(sDate);
	return ShamsiToDateTime(date.y, date.m, date.d);
}
//---------------------------------------------------------------------------
bool TShamsiDate::OfThisShamsiMonth(int date)
{
	TDateTime now = Now();
	CDate sDate = DateTimeToShamsi(now);
	CDate d1 = {sDate.y, sDate.m, 1};
	CDate d2 = AddShamsiMonth(d1, 1);
	int a = ShamsiToDateTime(d1);
	int b = ShamsiToDateTime(d2);
	return date >= a && date < b;
}
//---------------------------------------------------------------------------
bool TShamsiDate::OfNextShamsiMonth(int date)
{
	TDateTime now = Now();
	CDate sDate = DateTimeToShamsi(now);
	CDate d1 = {sDate.y, sDate.m, 1};
	d1 = AddShamsiMonth(d1, 1);
	CDate d2 = AddShamsiMonth(d1, 1);
	int a = ShamsiToDateTime(d1);
	int b = ShamsiToDateTime(d2);
	return date >= a && date < b;
}
//---------------------------------------------------------------------------
int TShamsiDate::operator = (int value)
{
	return Val = value;
}
//---------------------------------------------------------------------------
int TShamsiDate::operator = (TShamsiDate value)
{
	return Val = value.Val;
}
//---------------------------------------------------------------------------
TShamsiDate::operator int ()
{
	return Val;
}
//---------------------------------------------------------------------------
int TShamsiDate::operator += (int value)
{
	return Val += value;
}
//---------------------------------------------------------------------------
int TShamsiDate::operator -= (int value)
{
	return Val -= value;
}
//---------------------------------------------------------------------------
int TShamsiDate::GetShamsiYear()
{
	CDate sDate = DateTimeToShamsi(Val);
	return sDate.y;
}
//---------------------------------------------------------------------------
int TShamsiDate::GetShamsiMonth()
{
	CDate sDate = DateTimeToShamsi(Val);
	return sDate.m;
}
//---------------------------------------------------------------------------
int TShamsiDate::GetShamsiDay()
{
	CDate sDate = DateTimeToShamsi(Val);
	return sDate.d;
}
//---------------------------------------------------------------------------
void TShamsiDate::SetShamsiYear(int value)
{
	CDate sDate = DateTimeToShamsi(Val);
	sDate.y = value;
	Val = ShamsiToDateTime(sDate);
}
//---------------------------------------------------------------------------
void TShamsiDate::SetShamsiMonth(int value)
{
	CDate sDate = DateTimeToShamsi(Val);
	sDate.m = value;
	while(sDate.m > 12)
	{
		sDate.y += 1;
		sDate.m -= 12;
	}
	while(sDate.m < 1)
	{
		sDate.y -= 1;
		sDate.m += 12;
	}
	Val = ShamsiToDateTime(sDate);
}
//---------------------------------------------------------------------------
void TShamsiDate::SetShamsiDay(int value)
{
	CDate sDate = DateTimeToShamsi(Val);
	sDate.d = value;
	Val = ShamsiToDateTime(sDate);
}
//---------------------------------------------------------------------------
WideString TShamsiDate::GetDayName()
{
	int day = DayOfWeek(Val);
	WideString result;
	switch (day)
	{
		case 1: result = WideString(L"íßÔäÈå");
		break;
		case 2: result = WideString(L"ÏæÔäÈå");
		break;
		case 3: result = WideString(L"ÓåÔäÈå");
		break;
		case 4: result = WideString(L"åÇÑÔäÈå");
		break;
		case 5: result = WideString(L"äÌÔäÈå");
		break;
		case 6: result = WideString(L"ÌãÚå");
		break;
		case 7: result = WideString(L"ÔäÈå");
		break;
	}
	return result;
}
//---------------------------------------------------------------------------
static int g_days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int j_days_in_month[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};
//---------------------------------------------------------------------------
void miladi_to_shamsi(int  g_y, int  g_m, int  g_d,
	int *j_y, int *j_m, int *j_d)
{
   int gy, gm, gd;
   int jy, jm, jd;
   long g_day_no, j_day_no;
   int j_np;
 
   int i;

   gy = g_y-1600;
   gm = g_m-1;
   gd = g_d-1;
 
   g_day_no = 365*gy+(gy+3)/4-(gy+99)/100+(gy+399)/400;
   for (i=0;i<gm;++i)
      g_day_no += g_days_in_month[i];
   if (gm>1 && ((gy%4==0 && gy%100!=0) || (gy%400==0)))
      /* leap and after Feb */
      ++g_day_no;
   g_day_no += gd;
 
   j_day_no = g_day_no-79;
 
   j_np = j_day_no / 12053;
   j_day_no %= 12053;
 
   jy = 979+33*j_np+4*(j_day_no/1461);
   j_day_no %= 1461;
 
   if (j_day_no >= 366) {
      jy += (j_day_no-1)/365;
      j_day_no = (j_day_no-1)%365;
   }
 
   for (i = 0; i < 11 && j_day_no >= j_days_in_month[i]; ++i) {
      j_day_no -= j_days_in_month[i];
   }
   jm = i+1;
   jd = j_day_no+1;
   *j_y = jy;
   *j_m = jm;
   *j_d = jd;
}
//---------------------------------------------------------------------------
void shamsi_to_miladi(int  j_y, int  j_m, int  j_d,
	int *g_y, int *g_m, int *g_d)
{
	int gy, gm, gd;
	int jy, jm, jd;
	long g_day_no, j_day_no;
	int leap;

	int i;

	jy = j_y-979;
	jm = j_m-1;
	jd = j_d-1;

	j_day_no = 365*jy + (jy/33)*8 + (jy%33+3)/4;
	for (i=0; i < jm; ++i)
	  j_day_no += j_days_in_month[i];

	j_day_no += jd;

	g_day_no = j_day_no+79;

	gy = 1600 + 400*(g_day_no/146097); /* 146097 = 365*400 + 400/4 - 400/100 + 400/400 */
	g_day_no = g_day_no % 146097;

	leap = 1;
	if (g_day_no >= 36525) /* 36525 = 365*100 + 100/4 */
	{
	  g_day_no--;
	  gy += 100*(g_day_no/36524); /* 36524 = 365*100 + 100/4 - 100/100 */
	  g_day_no = g_day_no % 36524;
      
	  if (g_day_no >= 365)
		 g_day_no++;
	  else
		 leap = 0;
	}

	gy += 4*(g_day_no/1461); /* 1461 = 365*4 + 4/4 */
	g_day_no %= 1461;

	if (g_day_no >= 366) {
	  leap = 0;

	  g_day_no--;
	  gy += g_day_no/365;
	  g_day_no = g_day_no % 365;
	}

	for (i = 0; g_day_no >= g_days_in_month[i] + (i == 1 && leap); i++)
	  g_day_no -= g_days_in_month[i] + (i == 1 && leap);
	gm = i+1;
	gd = g_day_no+1;

	*g_y = gy;
	*g_m = gm;
	*g_d = gd;
}

//---------------------------------------------------------------------------
void TShamsiDate::getMonthBounds(TShamsiDate &date1, TShamsiDate &date2)
{
	unsigned short y, m, d;
	int my, mm, md;
	int sy, sm, sd;
	DecodeDate(Val, y, m, d);
	miladi_to_shamsi(y, m, d, &sy, &sm, &sd);
	shamsi_to_miladi(sy, sm, 1, &my, &mm, &md);
	date1 = (int)EncodeDate(my, mm, md);
	sm ++;
	if(sm==13)
	{
		sm = 1;
		sy ++;
	}
	shamsi_to_miladi(sy, sm, 1, &my, &mm, &md);
	date2 = (int)EncodeDate(my, mm, md) - 1;
}
//---------------------------------------------------------------------------
TShamsiDate TShamsiDate::operator = (char* value)
{
	ShamsiString = value;
	return Val;
}
//---------------------------------------------------------------------------
int TShamsiDate::operator - (TShamsiDate value)
{
	return Val - value.Val;
}
//---------------------------------------------------------------------------
int TShamsiDate::operator + (TShamsiDate value)
{
	return Val + value.Val;
}
//---------------------------------------------------------------------------
int TShamsiDate::get_monthDaysCount()
{
	TShamsiDate date1, date2;
	getMonthBounds(date1, date2);
	return date2 - date1 + 1;
}
//---------------------------------------------------------------------------
int TShamsiDate::get_dayOfWeek()
{
	return DayOfWeek(Val);
}
//---------------------------------------------------------------------------
int TShamsiDate::operator = (TDateTime value)
{
	return Val = value.Val;
}
//---------------------------------------------------------------------------
int TShamsiDate::operator = (String value)
{
	if(value.ToIntDef(-1) == -1)
		ShamsiString = value;
	else
		Val = value.ToInt();
	return Val;
}
//---------------------------------------------------------------------------
WideString TShamsiDate::GetShamsiYM()
{
	wchar_t month[3];
	wsprintfW(month, L"%.2d", ShamsiMonth);
	return String(ShamsiYear) + "/" + String(month);
}
//---------------------------------------------------------------------------
TShamsiDate TShamsiDate::GetNextMonth()
{
	TShamsiDate result = Val;
	if(result.ShamsiMonth == 6 && result.ShamsiDay == 31) result.ShamsiDay --;
	result.ShamsiMonth ++;
	return result;
}
//---------------------------------------------------------------------------
TShamsiDate TShamsiDate::GetShamsiNow()
{
	return TShamsiDate(Now().Val);
}
//---------------------------------------------------------------------------
WideString TShamsiDate::GetShamsiMD()
{
	return String(ShamsiMonth) + "/" + String(ShamsiDay);
}
//---------------------------------------------------------------------------

#pragma package(smart_init)
