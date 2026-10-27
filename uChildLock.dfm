object frmChildLock: TfrmChildLock
  Left = 0
  Top = 0
  AlphaBlend = True
  AlphaBlendValue = 200
  BorderStyle = bsNone
  Caption = 'frmChildLock'
  ClientHeight = 244
  ClientWidth = 430
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  WindowState = wsMaximized
  OnClose = FormClose
  OnShow = FormShow
  DesignSize = (
    430
    244)
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 96
    Top = 48
    Width = 233
    Height = 153
    Anchors = []
    Caption = 'Panel1'
    TabOrder = 0
    object Label1: TLabel
      Left = 64
      Top = 54
      Width = 107
      Height = 24
      Caption = 'Child Lock'
      Font.Charset = ARABIC_CHARSET
      Font.Color = clWhite
      Font.Height = -21
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 27
      Top = 84
      Width = 182
      Height = 24
      Caption = 'Press Ctrl+Alt+Del'
      Font.Charset = ARABIC_CHARSET
      Font.Color = clWhite
      Font.Height = -21
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object Timer: TTimer
    Interval = 700
    OnTimer = TimerTimer
    Left = 344
    Top = 48
  end
end
