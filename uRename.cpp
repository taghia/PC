//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uRename.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmRename *frmRename;
//---------------------------------------------------------------------------
__fastcall TfrmRename::TfrmRename(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
#include <JavaScriptEvaluator.h>
//---------------------------------------------------------------------------
void TfrmRename::applyPattern()
{
	JavaScriptEvaluator js;
	if(!js.init())
	{
		ShowMessage("Could not init javascript");
		return;
	}
	lbPreview->Clear();
	for (int i = 0; i < items.count(); i++) {
		text item, pat;
		text script = String(L"var file='") + items[i] + "'";
		if(!js.define(script) || !js.eval(edtPat->Text.c_str()))
		{
			ShowMessage("JavaScript error");
			return;
		}
		lbPreview->Items->Add(js.getResult());
	}
}
//---------------------------------------------------------------------------
void __fastcall TfrmRename::edtPatKeyPress(TObject *Sender, wchar_t &Key)
{
	if(Key == VK_RETURN)
	{
		applyPattern();
		Key = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmRename::btnRenameClick(TObject *Sender)
{
	applyPattern();
	for (int i = 0; i < items.count(); i++) {
		RenameFile(dir + items[i], dir + lbPreview->Items->Strings[i]);
	}
}
//---------------------------------------------------------------------------

