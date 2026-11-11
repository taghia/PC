object frmRename: TfrmRename
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Group Rename'
  ClientHeight = 236
  ClientWidth = 268
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  ShowHint = True
  DesignSize = (
    268
    236)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    AlignWithMargins = True
    Left = 5
    Top = 3
    Width = 260
    Height = 13
    Margins.Left = 5
    Margins.Bottom = 0
    Align = alTop
    Caption = 'Rename Preview'
    ExplicitWidth = 80
  end
  object lbPreview: TListBox
    AlignWithMargins = True
    Left = 3
    Top = 19
    Width = 262
    Height = 154
    Margins.Bottom = 0
    Align = alTop
    ItemHeight = 13
    TabOrder = 0
    ExplicitWidth = 395
  end
  object btnRename: TButton
    Left = 97
    Top = 203
    Width = 75
    Height = 25
    Anchors = [akTop]
    Caption = 'Rename'
    ModalResult = 1
    TabOrder = 1
    OnClick = btnRenameClick
  end
  object btnCancel: TButton
    Left = 178
    Top = 203
    Width = 75
    Height = 25
    Anchors = [akTop]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object edtPat: TComboBox
    Left = 3
    Top = 176
    Width = 262
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 3
    Text = 'file'
    TextHint = 'enter javascript'
    OnKeyPress = edtPatKeyPress
    Items.Strings = (
      '-> fil'
      '-> file'
      '-> "image " + pad(i+1, 3)+ ext'
      '-> file.toLowerCase()')
    ExplicitWidth = 395
  end
  object btnPreview: TButton
    Left = 16
    Top = 203
    Width = 75
    Height = 25
    Anchors = [akTop]
    Caption = 'Preview'
    TabOrder = 4
    OnClick = btnPreviewClick
  end
end
