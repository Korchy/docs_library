//---------------------------------------------------------------------------
#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include "D:\Programms\Cpp\include\Options\Options.h"    // Для объекта "Настройки"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <Buttons.hpp>          // Для работы с настройками
#include "AddForm.h"            // Для связи с формой добавления новых документов
#include "AddFolder.h"          // Для связи с формой создания новой папки
#include "ShellApi.h"           // Для осуществления печати средствами приложения, которое открывает просматриваемый документ
#include "registry.hpp"         // Для работы с реестром при установке
#include "D:\Programms\Cpp\include\AboutBox\ABox.h"      // Для окна "О программе"
#include <Graphics.hpp>
#include "EditInTable.h"        // Для связи с фориой "Редактирование документов в таблице"
#include <stdio.h>              // Для создания файлов
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TToolBar *ToolBar;
        TTreeView *Tree;
        TADOTable *TreeTable;
        TImageList *ImageList;
        TPanel *DocPanel;
        TCppWebBrowser *Doc;
        TBitBtn *AddButton;
        TToolButton *ToolButton1;
        TBitBtn *RemoveButton;
        TToolButton *ToolButton2;
        TBitBtn *BackButton;
        TBitBtn *ForwardButton;
        TBitBtn *RefreshButton;
        TBitBtn *PrintButton;
        TToolButton *ToolButton3;
        TBitBtn *AddFolderButton;
        TEdit *SearchText;
        TBitBtn *FindButton;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TMenuItem *N4;
        TMenuItem *N5;
        TImage *AboutBoxImage;
        TMenuItem *N6;
        TMenuItem *N7;
        TMenuItem *N8;
        TMenuItem *N9;
        TMenuItem *N10;
        TMenuItem *N11;
        TMenuItem *N12;
        TMenuItem *N13;
        TMenuItem *N14;
        TMenuItem *N15;
        TMenuItem *N16;
        TMenuItem *N17;
        void __fastcall N3Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall TreeChange(TObject *Sender, TTreeNode *Node);
        void __fastcall TreeCollapsed(TObject *Sender, TTreeNode *Node);
        void __fastcall TreeExpanded(TObject *Sender, TTreeNode *Node);
        void __fastcall AddButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall RemoveButtonClick(TObject *Sender);
        void __fastcall BackButtonClick(TObject *Sender);
        void __fastcall ForwardButtonClick(TObject *Sender);
        void __fastcall RefreshButtonClick(TObject *Sender);
        void __fastcall PrintButtonClick(TObject *Sender);
        void __fastcall AddFolderButtonClick(TObject *Sender);
        void __fastcall TreeDeletion(TObject *Sender, TTreeNode *Node);
        void __fastcall FindButtonClick(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall TreeCompare(TObject *Sender, TTreeNode *Node1,
          TTreeNode *Node2, int Data, int &Compare);
        void __fastcall N17Click(TObject *Sender);
private:	// User declarations

public:		// User declarations
        // Переменные
        Options* Settings;      // Настройки программы
        AnsiString CurrentDir;  // Текущий каталог
        bool DeleteFromTable;   // Если при удалении узла в дереве = true - удалить и запись в таблице 

        struct ItemStruct {             // Структура с данными по каждому узлу
                int No;                 // Номер узла
                AnsiString Path;        // Путь к документу узла
                int Icon;               // Номер иконки узла
                };
        ItemStruct *ItemInfo;

        // Функции
        void CreateTree();              // Создание дерева с документами
        void FirstSetup();              // Проверяет, есть ди в системе ODBC Alias для доступа к таблице с документами, если нет - создает его
        TTreeNode* AddTreeNode();       // Вставляет в дерево документов очередной элемент
        int NewId();                    // Получить новый id для добавляемых документов

        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
