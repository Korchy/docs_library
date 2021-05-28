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
//                              СОБЫТИЯ ФОРМЫ
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
        // При создании формы
        // Создать список доступных иконок для каталогов
for(int i=1; i<Form1->ImageList->Count; i+=2) {
        FolderPic->ItemsEx->AddItem("",i,i,-1,-1,NULL);
        FolderPic1->ItemsEx->AddItem("",i-1,i-1,-1,-1,NULL);
        }
        // По умолчанию - №5
        FolderPic->ItemIndex = 18;
        FolderPic1->ItemIndex = 18;

}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormDeactivate(TObject *Sender)
{
        // При потере фокуса формой
Close();
}
//---------------------------------------------------------------------------
//                          ОБРАБОТКА КНОПОК НА ФОРМЕ
//---------------------------------------------------------------------------
void __fastcall TForm2::PathButtonClick(TObject *Sender)
{
        // Кнопка "Указание файла"
//ShowMessage(Form1->CurrentDir+"\\");
if(OpenDialog->Execute()) NewPath->Text = ExtractRelativePath(Form1->CurrentDir+"\\",OpenDialog->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::OkButtonClick(TObject *Sender)
{
        // Кн. "ОК"
if(NewPath->Text!=""&&NewName->Text!="") {
        // Добавить новый документ
        // Проверить, правильно ли указан файл
        if(FileExists(NewPath->Text)==false) {
                ShowMessage("Неправильно указан путь к файлу");
                return;
                }
        // Новый документ добавляем к выделенному каталогу
        int NewRef = 0; // Ничего не выделено - добавим в корень
        if(Form1->Tree->Selected!=NULL) {
                // Если выделен каталог или головной узел - добавить к нему
                if(((TForm1::ItemStruct*)Form1->Tree->Selected->Data)->Path==""||Form1->Tree->Selected==Form1->Tree->Items->Item[0]) NewRef = ((TForm1::ItemStruct*)Form1->Tree->Selected->Data)->No;
                // Если выделен документ - ничего не делать
                else {
                        Close();
                        return;
                        }
                }
        // Получить новый Id
        int NewId = Form1->NewId();
        // Добавим новую строчку в таблицу
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
                MessageBox(NULL,"Ошибка при занесении нового документа в каталог","Error",NULL);
                Form1->TreeTable->Cancel();
                Abort();
                Close();
                return;
                }
        // Пересоздать дерево с документами
        Form1->CreateTree();
        }
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CuncelButtonClick(TObject *Sender)
{
        // Кн. "ОТМЕНА"
Close();
}
//---------------------------------------------------------------------------
//                              ВЫБОР ИКОНОК
//---------------------------------------------------------------------------
void __fastcall TForm2::FolderPicSelect(TObject *Sender)
{
        // При выборе иконки - показать вторую ее часть
FolderPic1->ItemIndex = FolderPic->ItemIndex;
}
//---------------------------------------------------------------------------

