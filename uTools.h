//---------------------------------------------------------------------------

#ifndef uToolsH
#define uToolsH
//---------------------------------------------------------------------------
#include "vcl.h"
String formattedSize(long double size, int digits);
//---------------------------------------------------------------------------
String mapPath(String path)
{
	return ExtractFilePath(Application->ExeName) + path;
}
TIcon *getShellIcon(int index);
String getFolderPath(int clsid);
int getDrivesCount()
{
	DWORD drives = GetLogicalDrives();
	int n=0;
	for(int t=0; t<32; t++)
		n += (bool)(drives & (2 << t));
	return n;
}
//---------------------------------------------------------------------------
char getDriveStr(int index)
{
	TStringList *list= new TStringList;
	char buf[100];
	GetLogicalDriveStrings(100, buf);
	int count = getDrivesCount();
	char drive[3];
	for(int t=0; t<count; t++)
	{
		drive[0] = buf[t*4]; drive[1] = buf[t*4 + 1]; drive[2] = 0;
		if(GetDriveType(drive) != DRIVE_CDROM)
			list->Add(drive);
	}
	for(int t=0; t<count; t++)
	{
		drive[0] = buf[t*4]; drive[1] = buf[t*4 + 1]; drive[2] = 0;
		if(GetDriveType(drive) == DRIVE_CDROM)
			list->Add(drive);
	}
	char retval = list->Strings[index][1];
	delete list;
	return retval;
}
//---------------------------------------------------------------------------
TIcon *getShellIcon(int index)
{
	TIcon *icon = new TIcon;
	HICON hIcon;
	ExtractIconEx("shell32.dll", index, NULL, &hIcon, 1);
	icon->Handle = hIcon;
	return icon;
}
//---------------------------------------------------------------------------
int getDriveIconIndex(char* drive)
{
	int type = GetDriveType(drive);
	if(type == DRIVE_RAMDISK)
		return 12;
	if(type == DRIVE_FIXED)
		return 8;
	if(type == DRIVE_CDROM)
		return 11;
	if(type == DRIVE_REMOVABLE)
	{
		if(drive[0] != 'A')
			return 12;
		return 6;
	}
	if(type == DRIVE_REMOTE)
		return 9;
	return 53;
}
//---------------------------------------------------------------------------
String getDiskQuery();
TIcon *getFileIcon(String path, String *display = NULL);
//---------------------------------------------------------------------------
#endif
