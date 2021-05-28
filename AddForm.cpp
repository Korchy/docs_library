//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AddForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//                              ������� �����
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
        // ��� �������� �����
        // ������� ������ ��������� ������ ��� ���������
for(int i=1; i<Form1->ImageList->Count; i+=2) {
        FolderPic->ItemsEx->AddItem("",i,i,-1,-1,NULL);
        FolderPic1->ItemsEx->AddItem("",i-1,i-1,-1,-1,NULL);
        }
        // �� ��������� - �5
        FolderPic->ItemIndex = 18;
        FolderPic1->ItemIndex = 18;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormDeactivate(TObject *Sender)
{
        // ��� ������ ������ ������
Close();
}
//---------------------------------------------------------------------------
//                          ��������� ������ �� �����
//---------------------------------------------------------------------------
void __fastcall TForm2::PathButtonClick(TObject *Sender)
{
        // ������ "�������� �����"
//ShowMessage(Form1->CurrentDir+"\\");
if(OpenDialog->Execute()) NewPath->Text = ExtractRelativePath(Form1->CurrentDir+"\\",OpenDialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::OkButtonClick(TObject *Sender)
{
        // ��. "��"
if(NewPath->Text!=""&&NewName->Text!="") {
        // �������� ����� ��������
        // ���������, ��������� �� ������ ����
        if(FileExists(NewPath->Text)==false) {
                ShowMessage("����������� ������ ���� � �����");
                return;
                }
        // ����� �������� ��������� � ����������� ��������
        int NewRef = 0; // ������ �� �������� - ������� � ������
        if(Form1->Tree->Selected!=NULL) {
                // ���� ������� ������� ��� �������� ���� - �������� � ����
                if(((TForm1::ItemStruct*)Form1->Tree->Selected->Data)->Path==""||Form1->Tree->Selected==Form1->Tree->Items->Item[0]) NewRef = ((TForm1::ItemStruct*)Form1->Tree->Selected->Data)->No;
                // ���� ������� �������� - ������ �� ������
                else {
                        Close();
                        return;
                        }
                }
        // �������� ����� Id
        int NewId = Form1->NewId();
        // ������� ����� ������� � �������
        try {
                Form1->TreeTable->Insert();
                Form1->TreeTable->FieldByName("id")->AsInteger = NewId;
                Form1->TreeTable->FieldByName("Ref")->AsInteger = NewRef;
                Form1->TreeTable->FieldByName("Name")->AsString = NewName->Text;
                Form1->TreeTable->FieldByName("Path")->AsString = NewPath->Text;
                Form1->TreeTable->FieldByName("Icon")->AsInteger = FolderPic->ItemIndex*2+1;
                Form1->TreeTable->Post();
                }
        catch(...) {
                MessageBox(NULL,"������ ��� ��������� ������ ��������� � �������","Error",NULL);
                Form1->TreeTable->Cancel();
                Abort();
                Close();
                return;
                }
        // ����������� ������ � �����������
        Form1->CreateTree();
        }
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CuncelButtonClick(TObject *Sender)
{
        // ��. "������"
Close();
}
//---------------------------------------------------------------------------
//                              ����� ������
//---------------------------------------------------------------------------
void __fastcall TForm2::FolderPicSelect(TObject *Sender)
{
        // ��� ������ ������ - �������� ������ �� �����
FolderPic1->ItemIndex = FolderPic->ItemIndex;
}
//---------------------------------------------------------------------------

