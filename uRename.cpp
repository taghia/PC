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
	text item, pat, fil;
	JavaScriptEvaluator js;
	if(!js.init())
	{
		ShowMessage("Could not init javascript");
		return;
	}
	lbPreview->Clear();
	js.define(L"function pad(n, len) {var s = String(n);while (s.length < len)s = '0' + s;return s;}");
	for (int i = 0; i < items.count(); i++) {
		text script = "var i=[]; var file='[]'; ext='[]'; fil='[]'";
		item = items[i];
		if(item.contains("."))
			fil = item.substr(0, item.rfind("."));
		else
			fil = item;
		script = script << i << item << ExtractFileExt(item) << fil;
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
void __fastcall TfrmRename::btnPreviewClick(TObject *Sender)
{
	applyPattern();
}
//---------------------------------------------------------------------------

