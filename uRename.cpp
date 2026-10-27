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
void TfrmRename::applyPattern()
{
	lbPreview->Clear();
	for (int i = 0; i < items.count(); i++) {
		text item, pat;
		pat = edtPat->Text;
		if(pat.wcCompare("*[*,*]*"))
		{
			text start = pat.subfind("[", ",").trim();
			text end = pat.subfind(",", "]").trim();

			if(start[0] == '\'' && end[0] != '\'')
				pat = pat.replace("[", "]", items[i].subfind(start.unQuoted('\''), end.intValue()));
			else if(start[0] != '\'' && end[0] == '\'')
				pat = pat.replace("[", "]", items[i].subfind(start.intValue(), end.unQuoted('\'')));
			else if(start[0] == '\'' && end[0] == '\'')
				pat = pat.replace("[", "]", items[i].subfind(start.unQuoted('\''), end.unQuoted('\'')));
			else if(start[0] != '\'' && end[0] != '\'')
				pat = pat.replace("[", "]", items[i].substr(start.intValue(), end.intValue()));


		}
		item.print(pat, i);
		lbPreview->Items->Add(item);
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

