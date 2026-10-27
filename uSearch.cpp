//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uSearch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmSearch *frmSearch;
//---------------------------------------------------------------------------
__fastcall TfrmSearch::TfrmSearch(TComponent* Owner)
	: TForm(Owner)
{
	view = new TFileView(Owner);
	view->Parent = this;
	view->Align = alClient;
	view->AlignWithMargins = true;
	view->onSearchNewDir = onSearchNewDir;
	view->onItemFound = onItemFound;
	target = new TStringList;
	onFindTarget = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::FormDestroy(TObject *Sender)
{
	delete target;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::btnStartClick(TObject *Sender)
{
	TSearchParams params;
	params.dir = target->Strings[0];
	TSearchParam *param = params.add();
	param->text = edtStr->Text;

	StatusBar->Panels->Items[0]->Text = "please wait ...";
	btnStop->Enabled = true;
	btnStart->Enabled = false;
	view->search(&params);
	btnStop->Enabled = false;
	btnStart->Enabled = true;
	StatusBar->Panels->Items[1]->Text = "Search complete.";
	StatusBar->Panels->Items[0]->Text = String(view->getFileCount()) + " items found.";
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::btnStopClick(TObject *Sender)
{
	view->stopSearch();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::onSearchNewDir(TObject *Sender, String dir)
{
	StatusBar->Panels->Items[1]->Text = "Searching " + dir;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::onItemFound(TObject *Sender)
{
	StatusBar->Panels->Items[0]->Text = String(view->getFileCount()) + " items found ...";
}

void __fastcall TfrmSearch::FormShow(TObject *Sender)
{
	view->OnDblClick = onFindTarget;
	edtStr->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmSearch::Button1Click(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

