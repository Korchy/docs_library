//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "EditInTable.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::ExitButtonClick(TObject *Sender)
{
        // ����� �� �������������� �������
if(Form1->TreeTable->State==dsEdit) Form1->TreeTable->Post();   // ������������� ���������
Close();
Form1->CreateTree();
}
//---------------------------------------------------------------------------
