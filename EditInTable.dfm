object Form4: TForm4
  Left = 218
  Top = 155
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1089#1090#1088#1091#1082#1090#1091#1088#1099' '#1076#1086#1082#1091#1084#1077#1085#1090#1086#1074
  ClientHeight = 273
  ClientWidth = 492
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Times New Roman'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 14
  object ToolBar: TToolBar
    Left = 0
    Top = 0
    Width = 492
    Height = 29
    Caption = 'ToolBar'
    EdgeBorders = [ebTop, ebBottom]
    TabOrder = 0
    object ToolButton1: TToolButton
      Left = 0
      Top = 2
      Width = 2
      Caption = 'ToolButton1'
      Style = tbsSeparator
    end
    object ExitButton: TBitBtn
      Left = 2
      Top = 2
      Width = 22
      Height = 22
      TabOrder = 0
      OnClick = ExitButtonClick
      Glyph.Data = {
        26040000424D2604000000000000360000002800000012000000120000000100
        180000000000F0030000C40E0000C40E000000000000000000000000FF0000FF
        0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
        FF0000FF0000FF0000FF0000FF0000FF00000000FF0000FF0000FF0000FF0000
        FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
        00FF0000FF0000FF00000000FF0000FF0000FF0000FF0000FF0000FF0000FF00
        00FF0000FF0000FF0000FF0000FF0000FF9090900000FF0000FF0000FF0000FF
        00000000FF0000FF0000FF0000FF0000FF9090909090900000FF0000FF0000FF
        0000FF0000FF9090909090909090900000FF0000FF0000FF00000000FF0000FF
        0000FF0000FF0000FF9090906060609090900000FF0000FF0000FF9090903030
        300000009090909090900000FF0000FF00000000FF0000FF0000FF0000FF9090
        9060606000000090909090909030303090909030303090909040400020200090
        90909090900000FF00000000FF0000FF0000FF0000FF90909090909000000030
        3030C0C0C0909090303030909090C0C0C04040008080002020009090900000FF
        00000000FF0000FF0000FF909090606060C0C0C0000000000000303030606060
        C0C0C0C0C0C09090907F7F006060008080006060600000FF00000000FF0000FF
        0000FF9090909090906F6F307F7F00000000909090C0C0C0C0C0C0606060BFBF
        00FFFF00BFBF006060000000000000FF00000000FF0000FF9090906060609090
        90BFBF00FFFF00000000C0C0C06060607F7F00FFFF00FFFF00FFFF00FFFF00BF
        BF000000000000FF00000000FF0000FF909090606060BFBF00FFFF00FFFF007F
        7F003F3F00FFFF00FFFF00FFFF00FFFF00BFBF003F3F000000000000000000FF
        00000000FF9090906060606F6F30FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00
        FFFF00BFBF003F3F000000000000FF0000FF0000FF0000FF00000000FF606060
        3F3F00FFFF00FFFF00FFFF00FFFF00FFFF00FFFF00BFBF003F3F000000000000
        000000FF0000FF0000FF0000FF0000FF00000000FF303030FFFF00FFFF00FFFF
        00FFFF00FFFF00FFFF00FFFF00FFFF007F7F000000000000000000FF0000FF00
        00FF0000FF0000FF00000000FF3F3F007F7F007F7F007F7F007F7F007F7F007F
        7F007F7F007F7F007F7F003F3F000000000000FF0000FF0000FF0000FF0000FF
        00000000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF
        0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00000000FF0000FF
        0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000
        FF0000FF0000FF0000FF0000FF0000FF00000000FF0000FF0000FF0000FF0000
        FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF0000FF00
        00FF0000FF0000FF0000}
    end
  end
  object EditGrid: TDBGrid
    Left = 0
    Top = 29
    Width = 492
    Height = 222
    Align = alClient
    DataSource = DataSource
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    TitleFont.Charset = ANSI_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Times New Roman'
    TitleFont.Style = []
  end
  object PathEdit: TDBMemo
    Left = 0
    Top = 251
    Width = 492
    Height = 22
    Align = alBottom
    DataField = 'path'
    DataSource = DataSource
    TabOrder = 2
    WantReturns = False
  end
  object DataSource: TDataSource
    DataSet = Form1.TreeTable
    Left = 456
    Top = 8
  end
end