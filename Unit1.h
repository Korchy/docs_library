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
#include "D:\Programms\Cpp\include\Options\Options.h"    // ��� ������� "���������"
#include <ADODB.hpp>
#include <DB.hpp>
#include <ImgList.hpp>
#include <ExtCtrls.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <Buttons.hpp>          // ��� ������ � �����������
#include "AddForm.h"            // ��� ����� � ������ ���������� ����� ����������
#include "AddFolder.h"          // ��� ����� � ������ �������� ����� �����
#include "ShellApi.h"           // ��� ������������� ������ ���������� ����������, ������� ��������� ��������������� ��������
#include "registry.hpp"         // ��� ������ � �������� ��� ���������
#include "D:\Programms\Cpp\include\AboutBox\ABox.h"      // ��� ���� "� ���������"
#include <Graphics.hpp>
#include "EditInTable.h"        // ��� ����� � ������ "�������������� ���������� � �������"
#include <stdio.h>              // ��� �������� ������
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
        // ����������
        Options* Settings;      // ��������� ���������
        AnsiString CurrentDir;  // ������� �������
        bool DeleteFromTable;   // ���� ��� �������� ���� � ������ = true - ������� � ������ � ������� 

        struct ItemStruct {             // ��������� � ������� �� ������� ����
                int No;                 // ����� ����
                AnsiString Path;        // ���� � ��������� ����
                int Icon;               // ����� ������ ����
                };
        ItemStruct *ItemInfo;

        // �������
        void CreateTree();              // �������� ������ � �����������
        void FirstSetup();              // ���������, ���� �� � ������� ODBC Alias ��� ������� � ������� � �����������, ���� ��� - ������� ���
        TTreeNode* AddTreeNode();       // ��������� � ������ ���������� ��������� �������
        int NewId();                    // �������� ����� id ��� ����������� ����������

        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
