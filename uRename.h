//---------------------------------------------------------------------------

#ifndef uRenameH
#define uRenameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "text.h"
//---------------------------------------------------------------------------
class TfrmRename : public TForm
{
__published:	// IDE-managed Components
	TListBox *lbPreview;
	TButton *btnRename;
	TButton *btnCancel;
	TLabel *Label1;
	TEdit *edtPat;
	void __fastcall edtPatKeyPress(TObject *Sender, wchar_t &Key);
	void __fastcall btnRenameClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmRename(TComponent* Owner);
	void applyPattern();
	array items;
	text dir;
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRename *frmRename;
//---------------------------------------------------------------------------
#endif
