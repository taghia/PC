object frmConsole: TfrmConsole
  Left = 0
  Top = 0
  Caption = 'Enter Command'
  ClientHeight = 202
  ClientWidth = 447
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object mCmd: TMemo
    AlignWithMargins = True
    Left = 3
    Top = 40
    Width = 441
    Height = 159
    Align = alBottom
    ScrollBars = ssVertical
    TabOrder = 0
    WordWrap = False
  end
  object btnRun: TButton
    Left = 8
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Run'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object btnCancel: TButton
    Left = 88
    Top = 8
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
end
