object frmSearch: TfrmSearch
  Left = 0
  Top = 0
  Caption = 'Search'
  ClientHeight = 386
  ClientWidth = 613
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object panTop: TPanel
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 607
    Height = 30
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitWidth = 553
    DesignSize = (
      607
      30)
    object edtStr: TLabeledEdit
      Left = 144
      Top = 5
      Width = 215
      Height = 21
      Hint = 
        'Sample : *.mp3 [2mb-3mb] or *.cpp "strcmp" or *.log {2010/1/1-20' +
        '11/1/1} or *.bin <FFA0E800>'
      Anchors = [akLeft, akTop, akRight]
      EditLabel.Width = 129
      EditLabel.Height = 13
      EditLabel.Caption = 'All or part of the file name:'
      LabelPosition = lpLeft
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      ExplicitWidth = 161
    end
    object btnStart: TButton
      Left = 365
      Top = 3
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Start'
      Default = True
      TabOrder = 1
      OnClick = btnStartClick
      ExplicitLeft = 311
    end
    object btnStop: TButton
      Left = 446
      Top = 3
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Stop'
      Enabled = False
      TabOrder = 2
      OnClick = btnStopClick
      ExplicitLeft = 392
    end
    object Button1: TButton
      Left = 527
      Top = 3
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = 'Close'
      TabOrder = 3
      OnClick = Button1Click
      ExplicitLeft = 491
    end
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 367
    Width = 613
    Height = 19
    Panels = <
      item
        Width = 100
      end
      item
        Width = 200
      end>
    ExplicitWidth = 559
  end
end
