object frmRun: TfrmRun
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Run ...'
  ClientHeight = 105
  ClientWidth = 404
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
  object edtApp: TLabeledEdit
    Left = 80
    Top = 16
    Width = 313
    Height = 21
    EditLabel.Width = 52
    EditLabel.Height = 13
    EditLabel.Caption = 'Application'
    LabelPosition = lpLeft
    TabOrder = 1
  end
  object edtArg: TLabeledEdit
    Left = 80
    Top = 43
    Width = 313
    Height = 21
    EditLabel.Width = 55
    EditLabel.Height = 13
    EditLabel.Caption = 'Parameters'
    LabelPosition = lpLeft
    TabOrder = 0
  end
  object btnRun: TButton
    Left = 318
    Top = 70
    Width = 75
    Height = 25
    Caption = 'Run'
    Default = True
    ModalResult = 1
    TabOrder = 2
  end
  object Button2: TButton
    Left = 237
    Top = 70
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = Button2Click
  end
end
