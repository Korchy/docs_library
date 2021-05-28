//---------------------------------------------------------------------------
#ifndef AddFolderH
#define AddFolderH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Unit1.h"      // Для связи с главной формой
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Folder;
        TBitBtn *OkButton;
        TBitBtn *CuncelButton;
        TComboBoxEx *FolderPic;
        TComboBoxEx *FolderPic1;
        void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall OkButtonClick(TObject *Sender);
        void __fastcall CuncelButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FolderPicSelect(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
