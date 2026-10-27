object frmUserActions: TfrmUserActions
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'User Actions'
  ClientHeight = 299
  ClientWidth = 269
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object btnUp: TSpeedButton
    Left = 186
    Top = 235
    Width = 27
    Height = 25
    Hint = 'Move action up (hold ctrl to skip 5)'
    Caption = '5'
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Webdings'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
  end
  object btnDown: TSpeedButton
    Left = 186
    Top = 266
    Width = 27
    Height = 25
    Hint = 'Move action down (hold ctrl to skip 5)'
    Caption = '6'
    Font.Charset = SYMBOL_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Webdings'
    Font.Style = []
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
  end
  object lbActions: TListBox
    Left = 8
    Top = 8
    Width = 172
    Height = 283
    ItemHeight = 13
    TabOrder = 0
    OnDblClick = lbActionsDblClick
  end
  object btnRemove: TButton
    Left = 186
    Top = 39
    Width = 75
    Height = 25
    Caption = 'Remove'
    TabOrder = 2
  end
  object btnEdit: TButton
    Left = 186
    Top = 70
    Width = 75
    Height = 25
    Caption = 'Edit'
    TabOrder = 3
  end
  object btnClose: TButton
    Left = 186
    Top = 101
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Close'
    TabOrder = 4
    OnClick = btnCloseClick
  end
  object btnRun: TButton
    Left = 186
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Run'
    Default = True
    TabOrder = 1
  end
end
