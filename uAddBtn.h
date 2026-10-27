//---------------------------------------------------------------------------

#ifndef uAddBtnH
#define uAddBtnH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmAddBtn : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *edtName;
	TButton *btnAdd;
	TButton *Button2;
	THotKey *shortcut;
	TLabel *Label1;
	TComboBox *edtPath;
	TLabel *Label2;
	TCheckBox *chAsButton;
	TComboBox *edtCmdLine;
	TLabel *Label3;
	TCheckBox *chSeparator;
	TGroupBox *GroupBox1;
	TLabeledEdit *edtFileType;
	TCheckBox *chFile;
	TCheckBox *chFolder;
	TComboBox *cmbCategory;
	TLabel *Label4;
	TLabel *labPreview;
	TLabel *Label5;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall edtCmdLineChange(TObject *Sender);
	void __fastcall chSeparatorClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmAddBtn(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmAddBtn *frmAddBtn;
//---------------------------------------------------------------------------
#endif
