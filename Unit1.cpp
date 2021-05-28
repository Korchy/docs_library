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
//                                     ФОРМА
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        // При создании формы
        // Загрузить настройки
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
        // Получить текущий каталог
CurrentDir = GetCurrentDir();
//ShowMessage(CurrentDir);
        // Проверить, есть-ли Alias для доступа к таблице с деревом документов
FirstSetup();
        // Загрузить дерево документов
CreateTree();
        // Инициализация переменных
DeleteFromTable = false;        // Удалять узлы без удаления записей в таблице
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
        // Установить фокус на дерево документов
Tree->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
        // При закрытии формы
        // Сохранить настройки
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
        // Удалить объект с настройками
delete Settings;
        // Если проводился поиск - удалить файл с результатми поиска
if(FileExists(CurrentDir + "\\SearchRez.htm")==true) DeleteFile(CurrentDir + "\\SearchRez.htm");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormResize(TObject *Sender)
{
        // При измении размеров формы
        // Увеличить дерево (но не более 300 pix)
Tree->Width = Form1->Width/3;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TreeDeletion(TObject *Sender, TTreeNode *Node)
{
        // При удалении узла в дереве документов. Если событие было вызвано
        // через кнопку удаления - удалить и записи в таблице
        // Если нужно - удалить запись в таблице
if(DeleteFromTable==true) {
        TLocateOptions SearchOptions;   // Найдем удаляемую строку в таблице
        TreeTable->Locate("id",((ItemStruct*)Node->Data)->No,SearchOptions<<loCaseInsensitive);
        TreeTable->Delete();
        }
        // Удалить струтктуру, связанную с узлом
delete Node->Data;
}
//---------------------------------------------------------------------------
//                                      МЕНЮ
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
        // Кн. "Выход"
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N6Click(TObject *Sender)
{
        // Кн. "Обновить документы"
CreateTree();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N17Click(TObject *Sender)
{
        // Редактировать структуру документов в таблице
Application->CreateForm(__classid(TForm4),&Form4);
Form4->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N5Click(TObject *Sender)
{
        // Кн. "О программе"
TAboutBox *Abox = new TAboutBox(this);
Abox->Caption = "Документация  v. 1.04";
Abox->ProgramName->Caption = "Документация";
Abox->ProgramVer->Caption = "ver. 1.04 build 030704";
Abox->ProgramImage->Picture = AboutBoxImage->Picture;
Abox->Visible = true;
}
//---------------------------------------------------------------------------
//                                  BUTTON МЕНЮ
//---------------------------------------------------------------------------
void __fastcall TForm1::AddButtonClick(TObject *Sender)
{
        // Кнопка "Добавить"
Application->CreateForm(__classid(TForm2),&Form2);
Form2->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AddFolderButtonClick(TObject *Sender)
{
        // Кнопка "Добавить каталог"
Application->CreateForm(__classid(TForm3),&Form3);
Form3->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RemoveButtonClick(TObject *Sender)
{
        // Кнопка "Удалить"
if(Application->MessageBox("Удалить объект из каталога?\nБудут удалены и все подчиненные объекты!","Удаление",MB_YESNO+MB_ICONWARNING)==IDYES) {
        // Если что-то выделено
        if(Tree->Selected!=NULL) {
                // Удалить узел и по событию, связанному с удалением,записи в таблице. Событие сработает для всех узлов
                DeleteFromTable = true;
                Tree->Items->Delete(Tree->Selected);
                DeleteFromTable = false;
                }
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BackButtonClick(TObject *Sender)
{
        // Кнопка "Назад"
Doc->GoBack();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ForwardButtonClick(TObject *Sender)
{
        // Кнопка "Вперед"
Doc->GoForward();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RefreshButtonClick(TObject *Sender)
{
        // Кнопка "Обновить"
Doc->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PrintButtonClick(TObject *Sender)
{
        // Кнопка "Печать"
        // Получить путь к файлу, который просматривается  данный момент
AnsiString FilePath = CurrentDir+"\\"+((ItemStruct*)(Tree->Selected)->Data)->Path;
        // Отправить документ на печать средствами приложения, используемого для его просмотра
ShellExecute(Handle,"print",FilePath.c_str(),NULL,NULL,SW_HIDE);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FindButtonClick(TObject *Sender)
{
        // Кнопка "Поиск"
if(SearchText->Text!="") {
        // Создать файл для результатов поиска
        TStringList* SearchRez = new TStringList();
        SearchRez->Add("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">");
        SearchRez->Add("<HTML>");
        SearchRez->Add("<HEAD>");
        SearchRez->Add("<TITLE>Документация</TITLE>");
        SearchRez->Add("</HEAD>");
        SearchRez->Add("<BODY BGCOLOR=bfbdbd>");
        SearchRez->Add("<CENTER>");
        SearchRez->Add("<FONT SIZE=3><B><I>РЕЗУЛЬТАТЫ ПОИСКА</I></B></FONT><BR>");
        SearchRez->Add("<I>поиск ведется только по текстовым файлам *.txt,*.htm</I>");
        SearchRez->Add("</CENTER>");
        SearchRez->Add("<P>");
        // Провести поиск по всем документам дерева и занести разультаты в файл
        for(int i=0; i<Tree->Items->Count; i++) {
                if(FileExists(CurrentDir+"\\"+((ItemStruct*)Tree->Items->Item[i]->Data)->Path)) {

                        }
                }
        // Сохранить файл
        SearchRez->Add("</BODY>");
        SearchRez->Add("</HTML>");
        SearchRez->SaveToFile("SearchRez.htm");
        delete SearchRez;
        //  Отобразить файл с результатми поиска
        Doc->Navigate(WideString(CurrentDir+"\\SearchRez.htm"));
        }
}
//---------------------------------------------------------------------------
//                                 ОБЩИЕ ФУНКЦИИ
//---------------------------------------------------------------------------
void TForm1::FirstSetup()
{
        // Проверяет, есть ли в системе ODBC Alias для доступа к таблице с
        // документами, если нет - создает его. Должно срабатывать только при
        // первом запуске программы
        // Получить системный каталог и каталог WINDOWS
char SystemDirTmp[MAX_PATH];
GetSystemDirectory(SystemDirTmp,MAX_PATH);
AnsiString SystemDir = AnsiString(SystemDirTmp);
char WindowsDirTmp[MAX_PATH];
GetWindowsDirectory(WindowsDirTmp,MAX_PATH);
AnsiString WindowsDir = AnsiString(WindowsDirTmp);
        // Нужно ли будет перезагружаться после настройки
bool Restart = false;
        // Если в системном каталоге нет файла vfpodbc.dll - установить ODBC-драйвер
if(FileExists(SystemDir + "\\vfpodbc.dll")==false) {
        // Перезагрузка нужна
        Restart = true;
        // Скопировать файл
        CopyFile("Vfpodbc.dll",(SystemDir+"\\vfpodbc.dll").c_str(),true);
        // Изменить ini-файл и реестр
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
        // Если нужна перезагрузка - перезагрузиться
if(Restart==true) {
        ShowMessage("Была проведена установка драйвера. Сейчас компьютер будет перезагружен!");
        ExitWindowsEx(EWX_REBOOT,NULL);
        return;
        }
        // Если в ODBC отсутствует Alias "DOCS" - создать его
if(FileExists(WindowsDir+"\\odbc.ini")==false) {
        // т.к. в некоторых Windows XP вообще нет этого файла - создать его
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
        AliasReg->WriteString("Description","ДОКУМЕНТАЦИЯ");
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
        // Если нужна перезагрузка - перезагрузиться
if(Restart==true) {
        ShowMessage("Была проведена настройка драйвера. Сейчас компьютер будет перезагружен!");
        ExitWindowsEx(EWX_REBOOT,NULL);
        }
}
//---------------------------------------------------------------------------
void TForm1::CreateTree()
{
        // Создание дерева с документами
        // Очистить окно
Tree->Items->Clear();
        // Головной узел
TreeTable->Active = true;
ItemInfo = new ItemStruct();
ItemInfo->No = 0;
ItemInfo->Path = "Docs\\Home.htm";
TLocateOptions SearchOptions;   // Найдем его в таблице
TreeTable->Locate("id",ItemInfo->No,SearchOptions<<loCaseInsensitive);
Tree->Items->AddObject(NULL,Trim(TreeTable->FieldByName("name")->AsString),ItemInfo);  // Добавление головного узла с индексом 0
Tree->Items->Item[0]->ImageIndex = TreeTable->FieldByName("icon")->AsInteger;
Tree->Items->Item[0]->SelectedIndex = Tree->Items->Item[0]->ImageIndex;
        // Узлы с документами - берем из таблицы
TreeTable->First();
while(!TreeTable->Eof) {
        // Вставляем в дерево элементы из таблицы
        AddTreeNode();
        TreeTable->Next();
        }
        // Провести сортировку
Tree->AlphaSort(true);
        // Раскрыть головной узел
Tree->Items->Item[0]->Expanded = true;
}
//---------------------------------------------------------------------------
TTreeNode* TForm1::AddTreeNode()
{
        // Вставляет в дерево документов очередной элемент
        // Проверить, не был ли вставлен данный элемент ранее и есть ли элемент-хозяин для вставляемого элемента
TTreeNode* Parent = NULL;
int ItemNo = TreeTable->FieldByName("id")->AsInteger;          // Номер очередного элемента
int ItemRef = TreeTable->FieldByName("ref")->AsInteger;        // Какому элементу он подчиняется
for(int i=0; i<Tree->Items->Count; i++) {
        if(((ItemStruct*)Tree->Items->Item[i]->Data)->No==ItemNo) return NULL;  // Этот элемент уже есть - возврат
        if(((ItemStruct*)Tree->Items->Item[i]->Data)->No==ItemRef) Parent = Tree->Items->Item[i]; // Есть-ли хозяин?
        }
if(Parent==NULL) {
                // Если даже хозяин еще не вставлен - повторить все для хозяина
        TBookmark SaveNo = TreeTable->GetBookmark();    // Сохраняем местоположение т.к. оно измениться при добавлении верхнего элемента
        TLocateOptions SearchOptions;
        TreeTable->Locate("id",ItemRef,SearchOptions<<loCaseInsensitive);
        Parent = AddTreeNode();
        TreeTable->GotoBookmark(SaveNo);
        TreeTable->FreeBookmark(SaveNo);
        }
        // Если хозяин есть - добавить новый элемент
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
        // При свертывании узла
        // Поменять картинку на закрытую
Node->ImageIndex = Node->ImageIndex + 1;
Node->SelectedIndex = Node->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TreeExpanded(TObject *Sender, TTreeNode *Node)
{
        // При развертывании узла
        // Поменять картинку на открытую
Node->ImageIndex = Node->ImageIndex - 1;
Node->SelectedIndex = Node->ImageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TreeChange(TObject *Sender, TTreeNode *Node)
{
        // При выборе документа из дерева
        // Отобразить его в окне
if(((ItemStruct*)Node->Data)->Path!="") {
        // Если есть путь - открыть документ по этому пути
        Doc->Navigate(WideString(CurrentDir+"\\"+((ItemStruct*)Node->Data)->Path));
        }
else {
        // если нет (папка) - если свернута - развернуть, если развернута - свернуть
        if(Node->Expanded!=true) Node->Expanded = true;
        else Node->Expanded = false;
        }
}
//---------------------------------------------------------------------------
int TForm1::NewId()
{
        // Получить новый Id для добавляемого документа или каталога
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
        // Обрабочик события сортировки документов в дереве
        // Сортировка: сначала папки, далее по алфавиту
        // По папкам
Compare = 1;
if(((ItemStruct*)Node1->Data)->Icon<((ItemStruct*)Node2->Data)->Icon) Compare = -1;
        // Если папки одинаковы - по алфавиту
if(((ItemStruct*)Node1->Data)->Icon==((ItemStruct*)Node2->Data)->Icon) {
        Compare = AnsiStrIComp(Node1->Text.c_str(),Node2->Text.c_str());
        }
}
//---------------------------------------------------------------------------

