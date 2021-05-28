//---------------------------------------------------------------------------
#ifndef EditInTableH
#define EditInTableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include "Unit1.h"              // Для связи с главной формой
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TToolBar *ToolBar;
        TBitBtn *ExitButton;
        TToolButton *ToolButton1;
        TDBGrid *EditGrid;
        TDataSource *DataSource;
        TDBMemo *PathEdit;
        void __fastcall ExitButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
