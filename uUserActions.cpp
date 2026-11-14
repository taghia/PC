//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uUserActions.h"
#include "uMain.h"
#include "LogTools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmUserActions *frmUserActions;
//---------------------------------------------------------------------------
__fastcall TfrmUserActions::TfrmUserActions(TComponent* Owner)
	: TForm(Owner)
{
	edtFind->RightButton->Visible = false;
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
void __fastcall TfrmUserActions::edtFindChange(TObject *Sender)
{
	text str = edtFind->Text;
	for (int i = 0; i < lbActions->Count; i++) {
		text item = lbActions->Items->Strings[i];
		if(item.contains(str))
		{
			lbActions->ItemIndex = i;
			break;
		}
	}
	edtFind->RightButton->Visible = !str.empty();
}
//---------------------------------------------------------------------------
void __fastcall TfrmUserActions::edtFindRightButtonClick(TObject *Sender)
{
	edtFind->Text = "";
}
//---------------------------------------------------------------------------

