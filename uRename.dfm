object frmRename: TfrmRename
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Group Rename'
  ClientHeight = 239
  ClientWidth = 401
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
    401
    239)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    AlignWithMargins = True
    Left = 5
    Top = 3
    Width = 393
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
    Width = 395
    Height = 154
    Margins.Bottom = 0
    Align = alTop
    ItemHeight = 13
    TabOrder = 0
  end
  object btnRename: TButton
    Left = 119
    Top = 206
    Width = 75
    Height = 25
    Anchors = [akTop]
    Caption = 'Rename'
    ModalResult = 1
    TabOrder = 1
    OnClick = btnRenameClick
  end
  object btnCancel: TButton
    Left = 206
    Top = 206
    Width = 75
    Height = 25
    Anchors = [akTop]
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 2
  end
  object edtPat: TEdit
    AlignWithMargins = True
    Left = 3
    Top = 176
    Width = 395
    Height = 21
    Hint = 'Example: [1,] ; [3, '#39'.'#39'].bmp ; ['#39'm'#39', '#39'x'#39'].ps ; image %i.jpg'
    Align = alTop
    TabOrder = 3
    Text = 'file %i'
    OnKeyPress = edtPatKeyPress
  end
end
