//---------------------------------------------------------------------------
#ifndef AddFormH
#define AddFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Unit1.h"      // Для связи с главной формой
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TEdit *NewPath;
        TBitBtn *PathButton;
        TEdit *NewName;
        TBitBtn *OkButton;
        TBitBtn *CuncelButton;
        TComboBoxEx *FolderPic;
        TComboBoxEx *FolderPic1;
        TLabel *Label1;
        TLabel *Label2;
        TOpenDialog *OpenDialog;
        void __fastcall PathButtonClick(TObject *Sender);
        void __fastcall OkButtonClick(TObject *Sender);
        void __fastcall CuncelButtonClick(TObject *Sender);
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall FolderPicSelect(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
