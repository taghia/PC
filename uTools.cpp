//---------------------------------------------------------------------------


#pragma hdrstop

#include "uTools.h"

//---------------------------------------------------------------------------
TIcon *getFileIcon(String path, String *display)
{
	TIcon *icon = new TIcon;
	SHFILEINFOW psfi;
	int uFlag = SHGFI_SMALLICON | SHGFI_ICON;
	if(display) uFlag |= SHGFI_DISPLAYNAME;
	SHGetFileInfoW(path.c_str(), 0, &psfi, 200, uFlag);
	icon->Handle = psfi.hIcon;
	if(display) *display = psfi.szDisplayName;
	return icon;
}
String getDiskQuery()
{
	int count = getDrivesCount();
	String query = "Free Space ";
	//char drvStr[100] = {0};
	//GetLogicalDriveStrings(100, drvStr);
	for (int i=0; i<count; i++) {
		wchar_t drive[] = {getDriveStr(i), ':', 0};
		int type = GetDriveTypeW(drive);
		if(type == DRIVE_FIXED || type == DRIVE_REMOVABLE) {
			query += "[" + String(drive[0]) + " " + formattedSize(DiskFree(drive[0] - 'A' + 1), 10) + "] ";
		}
	}
	query.SetLength(query.Length() - 1);
	return query;

}
String formattedSize(long double size, int digits)
{
	String unit;
	unit = "B";
	long per = 1;
	if (size >= 1024 && size < 1024 * 1024) {
		unit = "KB";
		per = 1024;
	}

	if (size >= 1024 * 1024 && size < 1024 * 1024 * 1024) {
		per = 1024 * 1024;
		unit = "MB";
	}
	if (size >= 1024 * 1024 * 1024) {
		per = 1024 * 1024 * 1024;
		unit = "GB";
	}

	size = size / per;
	size = (__int64)(size * digits);
	size = size / digits;
	return (String)(double)size + " " + unit;
}
#pragma package(smart_init)
