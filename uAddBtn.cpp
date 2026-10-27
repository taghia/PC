//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uAddBtn.h"
#include "text.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmAddBtn *frmAddBtn;
//---------------------------------------------------------------------------
__fastcall TfrmAddBtn::TfrmAddBtn(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
text renderParam(text param, bool exec_prompt = true);
void __fastcall TfrmAddBtn::Button2Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddBtn::edtCmdLineChange(TObject *Sender)
{
    labPreview->Caption = renderParam(edtCmdLine->Text, false);
}
//---------------------------------------------------------------------------

void __fastcall TfrmAddBtn::chSeparatorClick(TObject *Sender)
{
	if(chSeparator->Checked)
	{
		edtName->Text = "Separator";
		edtPath->Text = "";
		edtCmdLine->Text = "";
		shortcut->HotKey = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmAddBtn::FormShow(TObject *Sender)
{
	//edtCmdLine->Hint = renderParam(edtCmdLine->Text, false);
    labPreview->Caption = renderParam(edtCmdLine->Text, false);
}
//---------------------------------------------------------------------------

