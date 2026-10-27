//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("uRun.cpp", frmRun);
USEFORM("uAddBtn.cpp", frmAddBtn);
USEFORM("uMain.cpp", frmMain);
USEFORM("uUserActions.cpp", frmUserActions);
USEFORM("uSearch.cpp", frmSearch);
USEFORM("uConsole.cpp", frmConsole);
USEFORM("uRename.cpp", frmRename);
//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
//		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TfrmMain), &frmMain);
		Application->CreateForm(__classid(TfrmRun), &frmRun);
		Application->CreateForm(__classid(TfrmAddBtn), &frmAddBtn);
		Application->CreateForm(__classid(TfrmUserActions), &frmUserActions);
		Application->CreateForm(__classid(TfrmSearch), &frmSearch);
		Application->CreateForm(__classid(TfrmConsole), &frmConsole);
		Application->CreateForm(__classid(TfrmRename), &frmRename);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
