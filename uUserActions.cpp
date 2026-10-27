//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uUserActions.h"
#include "uMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmUserActions *frmUserActions;
//---------------------------------------------------------------------------
__fastcall TfrmUserActions::TfrmUserActions(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmUserActions::btnCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmUserActions::lbActionsDblClick(TObject *Sender)
{
	btnRun->Click();
}
//---------------------------------------------------------------------------


