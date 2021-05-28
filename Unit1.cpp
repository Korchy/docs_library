//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//                                     �����
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        // ��� �������� �����
        // ��������� ���������
Settings = new Options();
Settings->File = "Docs.cfg";
if(Settings->Load()==true) {
        Form1->Top = StrToInt(Settings->FindByName("FormTop"));
        Form1->Left = StrToInt(Settings->FindByName("FormLeft"));
        Form1->Width = StrToInt(Settings->FindByName("FormWidth"));
        Form1->Height = StrToInt(Settings->FindByName("FormHeight"));
        switch (StrToInt(Settings->FindByName("FormStyle"))) {
                case 0: Form1->WindowState = wsNormal;
                        break;
                case 1: Form1->WindowState = wsMaximized;
                        break;
                case 2: Form1->WindowState = wsMinimized;
                        break;
                }
        }
        // �������� ������� �������
CurrentDir = GetCurrentDir();
//ShowMessage(CurrentDir);
        // ���������, ����-�� Alias ��� ������� � ������� � ������� ����������
FirstSetup();
        // ��������� ������ ����������
CreateTree();
        // ������������� ����������
DeleteFromTable = false;        // ������� ���� ��� �������� ������� � �������
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
        // ���������� ����� �� ������ ����������
Tree->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
        // ��� �������� �����
        // ��������� ���������
if(Form1->WindowState==wsNormal) {
        Settings->SetByName("FormStyle","0");
        Settings->SetByName("FormTop",IntToStr(Form1->Top));
        Settings->SetByName("FormLeft",IntToStr(Form1->Left));
        Settings->SetByName("FormWidth",IntToStr(Form1->Width));
        Settings->SetByName("FormHeight",IntToStr(Form1->Height));
        }
if(Form1->WindowState==wsMaximized) Settings->SetByName("FormStyle","1");
if(Form1->WindowState==wsMinimized) Settings->SetByName("FormStyle","2");
Settings->Save();
        // ������� ������ � �����������
delete Settings;
        // ���� ���������� ����� - ������� ���� � ����������� ������
if(FileExists(CurrentDir + "\\SearchRez.htm")==true) DeleteFile(CurrentDir + "\\SearchRez.htm");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
        // ��� ������� �������� �����
        // ��������� ������ (�� �� ����� 300 pix)
Tree->Width = Form1->Width/3;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TreeDeletion(TObject *Sender, TTreeNode *Node)
{
        // ��� �������� ���� � ������ ����������. ���� ������� ���� �������
        // ����� ������ �������� - ������� � ������ � �������
        // ���� ����� - ������� ������ � �������
if(DeleteFromTable==true) {
        TLocateOptions SearchOptions;   // ������ ��������� ������ � �������
        TreeTable->Locate("id",((ItemStruct*)Node->Data)->No,SearchOptions<<loCaseInsensitive);
        TreeTable->Delete();
        }
        // ������� ����������, ��������� � �����
delete Node->Data;
}
//---------------------------------------------------------------------------
//                                      ����
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
        // ��. "�����"
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N6Click(TObject *Sender)
{
        // ��. "�������� ���������"
CreateTree();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N17Click(TObject *Sender)
{
        // ������������� ��������� ���������� � �������
Application->CreateForm(__classid(TForm4),&Form4);
Form4->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N5Click(TObject *Sender)
{
        // ��. "� ���������"
TAboutBox *Abox = new TAboutBox(this);
Abox->Caption = "������������  v. 1.04";
Abox->ProgramName->Caption = "������������";
Abox->ProgramVer->Caption = "ver. 1.04 build 030704";
Abox->ProgramImage->Picture = AboutBoxImage->Picture;
Abox->Visible = true;
}
//---------------------------------------------------------------------------
//                                  BUTTON ����
//---------------------------------------------------------------------------
void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
        // ������ "��������"
Application->CreateForm(__classid(TForm2),&Form2);
Form2->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddFolderButtonClick(TObject *Sender)
{
        // ������ "�������� �������"
Application->CreateForm(__classid(TForm3),&Form3);
Form3->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RemoveButtonClick(TObject *Sender)
{
        // ������ "�������"
if(Application->MessageBox("������� ������ �� ��������?\n����� ������� � ��� ����������� �������!","��������",MB_YESNO+MB_ICONWARNING)==IDYES) {
        // ���� ���-�� ��������
        if(Tree->Selected!=NULL) {
                // ������� ���� � �� �������, ���������� � ���������,������ � �������. ������� ��������� ��� ���� �����
                DeleteFromTable = true;
                Tree->Items->Delete(Tree->Selected);
                DeleteFromTable = false;
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BackButtonClick(TObject *Sender)
{
        // ������ "�����"
Doc->GoBack();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ForwardButtonClick(TObject *Sender)
{
        // ������ "������"
Doc->GoForward();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RefreshButtonClick(TObject *Sender)
{
        // ������ "��������"
Doc->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PrintButtonClick(TObject *Sender)
{
        // ������ "������"
        // �������� ���� � �����, ������� ���������������  ������ ������
AnsiString FilePath = CurrentDir+"\\"+((ItemStruct*)(Tree->Selected)->Data)->Path;
        // ��������� �������� �� ������ ���������� ����������, ������������� ��� ��� ���������
ShellExecute(Handle,"print",FilePath.c_str(),NULL,NULL,SW_HIDE);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FindButtonClick(TObject *Sender)
{
        // ������ "�����"
if(SearchText->Text!="") {
        // ������� ���� ��� ����������� ������
        TStringList* SearchRez = new TStringList();
        SearchRez->Add("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">");
        SearchRez->Add("<HTML>");
        SearchRez->Add("<HEAD>");
        SearchRez->Add("<TITLE>������������</TITLE>");
        SearchRez->Add("</HEAD>");
        SearchRez->Add("<BODY BGCOLOR=bfbdbd>");
        SearchRez->Add("<CENTER>");
        SearchRez->Add("<FONT SIZE=3><B><I>���������� ������</I></B></FONT><BR>");
        SearchRez->Add("<I>����� ������� ������ �� ��������� ������ *.txt,*.htm</I>");
        SearchRez->Add("</CENTER>");
        SearchRez->Add("<P>");
        // �������� ����� �� ���� ���������� ������ � ������� ���������� � ����
        for(int i=0; i<Tree->Items->Count; i++) {
                if(FileExists(CurrentDir+"\\"+((ItemStruct*)Tree->Items->Item[i]->Data)->Path)) {

                        }
                }
        // ��������� ����
        SearchRez->Add("</BODY>");
        SearchRez->Add("</HTML>");
        SearchRez->SaveToFile("SearchRez.htm");
        delete SearchRez;
        //  ���������� ���� � ����������� ������
        Doc->Navigate(WideString(CurrentDir+"\\SearchRez.htm"));
        }
}
//---------------------------------------------------------------------------
//                                 ����� �������
//---------------------------------------------------------------------------
void TForm1::FirstSetup()
{
        // ���������, ���� �� � ������� ODBC Alias ��� ������� � ������� �
        // �����������, ���� ��� - ������� ���. ������ ����������� ������ ���
        // ������ ������� ���������
        // �������� ��������� ������� � ������� WINDOWS
char SystemDirTmp[MAX_PATH];
GetSystemDirectory(SystemDirTmp,MAX_PATH);
AnsiString SystemDir = AnsiString(SystemDirTmp);
char WindowsDirTmp[MAX_PATH];
GetWindowsDirectory(WindowsDirTmp,MAX_PATH);
AnsiString WindowsDir = AnsiString(WindowsDirTmp);
        // ����� �� ����� ��������������� ����� ���������
bool Restart = false;
        // ���� � ��������� �������� ��� ����� vfpodbc.dll - ���������� ODBC-�������
if(FileExists(SystemDir + "\\vfpodbc.dll")==false) {
        // ������������ �����
        Restart = true;
        // ����������� ����
        CopyFile("Vfpodbc.dll",(SystemDir+"\\vfpodbc.dll").c_str(),true);
        // �������� ini-���� � ������
        TStringList* DriverIni = new TStringList();
        DriverIni->LoadFromFile(WindowsDir+"\\odbcinst.ini");
        if(DriverIni->IndexOf("Microsoft Visual FoxPro Driver (32 bit)=Installed")==-1) {
                int Poz = DriverIni->IndexOf("[ODBC 32 bit Drivers]")+1;
                DriverIni->Insert(Poz,"Microsoft Visual FoxPro Driver (32 bit)=Installed");
                DriverIni->Add("[Microsoft Visual FoxPro Driver (32 bit)]");
                DriverIni->Add("Driver="+SystemDir+"\\vfpodbc.dll");
                DriverIni->Add("Setup="+SystemDir+"\\vfpodbc.dll");
                DriverIni->Add("32Bit=1");
                DriverIni->SaveToFile(WindowsDir+"\\odbcinst.ini");
                TRegistry* DriverReg = new TRegistry();
                DriverReg->RootKey = HKEY_LOCAL_MACHINE;
                DriverReg->OpenKey("\\Software\\ODBC\\ODBCINST.INI\\Microsoft Visual FoxPro Driver",true);
                DriverReg->WriteString("Driver",SystemDir+"\\vfpodbc.dll");
                DriverReg->WriteString("Setup",SystemDir+"\\vfpodbc.dll");
                DriverReg->WriteInteger("UsageCount",1);
                DriverReg->OpenKey("\\Software\\ODBC\\ODBCINST.INI\\ODBC Drivers",true);
                DriverReg->WriteString("Microsoft Visual FoxPro Driver","Installed");
                delete DriverReg;
                }
        delete DriverIni;
        }
        // ���� ����� ������������ - ���������������
if(Restart==true) {
        ShowMessage("���� ��������� ��������� ��������. ������ ��������� ����� ������������!");
        ExitWindowsEx(EWX_REBOOT,NULL);
        return;
        }
        // ���� � ODBC ����������� Alias "DOCS" - ������� ���
if(FileExists(WindowsDir+"\\odbc.ini")==false) {
        // �.�. � ��������� Windows XP ������ ��� ����� ����� - ������� ���
        FILE *F;
        F = fopen((WindowsDir+"\\odbc.ini").c_str(),"w");
        fclose(F);
        }
TStringList* AliasIni = new TStringList();
AliasIni->LoadFromFile(WindowsDir+"\\odbc.ini");
if(AliasIni->IndexOf("[DOCS]")==-1) {
        int Poz = AliasIni->IndexOf("[ODBC 32 bit Data Sources]")+1;
        AliasIni->Insert(Poz,"DOCS=Microsoft Visual FoxPro Driver (32 bit)");
        AliasIni->Add("[DOCS]");
        AliasIni->Add("Driver32="+SystemDir+"\\vfpodbc.dll");
        AliasIni->Add("");
        AliasIni->SaveToFile(WindowsDir+"\\odbc.ini");
        TRegistry* AliasReg = new TRegistry();
        AliasReg->RootKey =  HKEY_CURRENT_USER;
        AliasReg->OpenKey("\\SOFTWARE\\ODBC\\ODBC.INI\\DOCS",true);
        AliasReg->WriteString("BackgroundFetch","Yes");
        AliasReg->WriteString("Collate","Machine");
        AliasReg->WriteString("Deleted","Yes");
        AliasReg->WriteString("Description","������������");
        AliasReg->WriteString("Driver",SystemDir+"\\vfpodbc.dll");
        AliasReg->WriteString("Exclusive","No");
        AliasReg->WriteString("Null","Yes");
        AliasReg->WriteString("SetNoCountOn","No");
        AliasReg->WriteString("SourceDB",CurrentDir);
        AliasReg->WriteString("SourceType","DBF");
        AliasReg->OpenKey("\\SOFTWARE\\ODBC\\ODBC.INI\\ODBC Data Sources",true);
        AliasReg->WriteString("DOCS","Microsoft Visual FoxPro Driver");
        delete AliasReg;
        }
delete AliasIni;
        // ���� ����� ������������ - ���������������
if(Restart==true) {
        ShowMessage("���� ��������� ��������� ��������. ������ ��������� ����� ������������!");
        ExitWindowsEx(EWX_REBOOT,NULL);
        }
}
//---------------------------------------------------------------------------
void TForm1::CreateTree()
{
        // �������� ������ � �����������
        // �������� ����
Tree->Items->Clear();
        // �������� ����
TreeTable->Active = true;
ItemInfo = new ItemStruct();
ItemInfo->No = 0;
ItemInfo->Path = "Docs\\Home.htm";
TLocateOptions SearchOptions;   // ������ ��� � �������
TreeTable->Locate("id",ItemInfo->No,SearchOptions<<loCaseInsensitive);
Tree->Items->AddObject(NULL,Trim(TreeTable->FieldByName("name")->AsString),ItemInfo);  // ���������� ��������� ���� � �������� 0
Tree->Items->Item[0]->ImageIndex = TreeTable->FieldByName("icon")->AsInteger;
Tree->Items->Item[0]->SelectedIndex = Tree->Items->Item[0]->ImageIndex;
        // ���� � ����������� - ����� �� �������
TreeTable->First();
while(!TreeTable->Eof) {
        // ��������� � ������ �������� �� �������
        AddTreeNode();
        TreeTable->Next();
        }
        // �������� ����������
Tree->AlphaSort(true);
        // �������� �������� ����
Tree->Items->Item[0]->Expanded = true;
}
//---------------------------------------------------------------------------
TTreeNode* TForm1::AddTreeNode()
{
        // ��������� � ������ ���������� ��������� �������
        // ���������, �� ��� �� �������� ������ ������� ����� � ���� �� �������-������ ��� ������������ ��������
TTreeNode* Parent = NULL;
int ItemNo = TreeTable->FieldByName("id")->AsInteger;          // ����� ���������� ��������
int ItemRef = TreeTable->FieldByName("ref")->AsInteger;        // ������ �������� �� �����������
for(int i=0; i<Tree->Items->Count; i++) {
        if(((ItemStruct*)Tree->Items->Item[i]->Data)->No==ItemNo) return NULL;  // ���� ������� ��� ���� - �������
        if(((ItemStruct*)Tree->Items->Item[i]->Data)->No==ItemRef) Parent = Tree->Items->Item[i]; // ����-�� ������?
        }
if(Parent==NULL) {
                // ���� ���� ������ ��� �� �������� - ��������� ��� ��� �������
        TBookmark SaveNo = TreeTable->GetBookmark();    // ��������� �������������� �.�. ��� ���������� ��� ���������� �������� ��������
        TLocateOptions SearchOptions;
        TreeTable->Locate("id",ItemRef,SearchOptions<<loCaseInsensitive);
        Parent = AddTreeNode();
        TreeTable->GotoBookmark(SaveNo);
        TreeTable->FreeBookmark(SaveNo);
        }
        // ���� ������ ���� - �������� ����� �������
ItemInfo = new ItemStruct();
ItemInfo->No = ItemNo;
ItemInfo->Path = Trim(TreeTable->FieldByName("path")->AsString);
ItemInfo->Icon = TreeTable->FieldByName("icon")->AsInteger;
TTreeNode* Rez = Tree->Items->AddChildObject(Parent,Trim(TreeTable->FieldByName("name")->AsString),ItemInfo);
Rez->ImageIndex = ItemInfo->Icon;
Rez->SelectedIndex = Rez->ImageIndex;
return Rez;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TreeCollapsed(TObject *Sender, TTreeNode *Node)
{
        // ��� ����������� ����
        // �������� �������� �� ��������
Node->ImageIndex = Node->ImageIndex + 1;
Node->SelectedIndex = Node->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TreeExpanded(TObject *Sender, TTreeNode *Node)
{
        // ��� ������������� ����
        // �������� �������� �� ��������
Node->ImageIndex = Node->ImageIndex - 1;
Node->SelectedIndex = Node->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TreeChange(TObject *Sender, TTreeNode *Node)
{
        // ��� ������ ��������� �� ������
        // ���������� ��� � ����
if(((ItemStruct*)Node->Data)->Path!="") {
        // ���� ���� ���� - ������� �������� �� ����� ����
        Doc->Navigate(WideString(CurrentDir+"\\"+((ItemStruct*)Node->Data)->Path));
        }
else {
        // ���� ��� (�����) - ���� �������� - ����������, ���� ���������� - ��������
        if(Node->Expanded!=true) Node->Expanded = true;
        else Node->Expanded = false;
        }
}
//---------------------------------------------------------------------------
int TForm1::NewId()
{
        // �������� ����� Id ��� ������������ ��������� ��� ��������
int NewId = 0;
TreeTable->First();
while(!TreeTable->Eof) {
        int TmpId = TreeTable->FieldByName("id")->AsInteger;
        if(NewId<TmpId) NewId = TmpId;
        TreeTable->Next();
        }
NewId += 1;
return NewId;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TreeCompare(TObject *Sender, TTreeNode *Node1,
      TTreeNode *Node2, int Data, int &Compare)
{
        // ��������� ������� ���������� ���������� � ������
        // ����������: ������� �����, ����� �� ��������
        // �� ������
Compare = 1;
if(((ItemStruct*)Node1->Data)->Icon<((ItemStruct*)Node2->Data)->Icon) Compare = -1;
        // ���� ����� ��������� - �� ��������
if(((ItemStruct*)Node1->Data)->Icon==((ItemStruct*)Node2->Data)->Icon) {
        Compare = AnsiStrIComp(Node1->Text.c_str(),Node2->Text.c_str());
        }
}
//---------------------------------------------------------------------------

