object frmAddBtn: TfrmAddBtn
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Add Button'
  ClientHeight = 306
  ClientWidth = 383
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 149
    Width = 41
    Height = 13
    Caption = 'Shortcut'
  end
  object Label2: TLabel
    Left = 29
    Top = 49
    Width = 22
    Height = 13
    Caption = 'Path'
  end
  object Label3: TLabel
    Left = 16
    Top = 75
    Width = 35
    Height = 13
    Caption = 'Params'
  end
  object Label4: TLabel
    Left = 189
    Top = 21
    Width = 45
    Height = 13
    Caption = 'Category'
  end
  object labPreview: TLabel
    Left = 55
    Top = 99
    Width = 313
    Height = 41
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clGray
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    WordWrap = True
  end
  object Label5: TLabel
    Left = 13
    Top = 99
    Width = 38
    Height = 13
    Caption = 'Preview'
  end
  object edtName: TLabeledEdit
    Left = 55
    Top = 18
    Width = 121
    Height = 21
    EditLabel.Width = 27
    EditLabel.Height = 13
    EditLabel.Caption = 'Name'
    LabelPosition = lpLeft
    TabOrder = 0
  end
  object btnAdd: TButton
    Left = 283
    Top = 269
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 7
  end
  object Button2: TButton
    Left = 202
    Top = 269
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 8
    OnClick = Button2Click
  end
  object shortcut: THotKey
    Left = 53
    Top = 145
    Width = 121
    Height = 21
    HotKey = 32833
    TabOrder = 3
  end
  object edtPath: TComboBox
    Left = 55
    Top = 45
    Width = 313
    Height = 21
    TabOrder = 1
    Items.Strings = (
      '%FLAG_CREATE%'
      '%ADMINTOOLS%'
      '%ALTSTARTUP%'
      '%APPDATA%'
      '%BITBUCKET%'
      '%CDBURN_AREA%'
      '%COMMON_ADMINTOOLS%'
      '%COMMON_ALTSTARTUP%'
      '%COMMON_APPDATA%'
      '%COMMON_DESKTOPDIRECTORY%'
      '%COMMON_DOCUMENTS%'
      '%COMMON_FAVORITES%'
      '%COMMON_MUSIC%'
      '%COMMON_PICTURES%'
      '%COMMON_PROGRAMS%'
      '%COMMON_STARTMENU%'
      '%COMMON_STARTUP%'
      '%COMMON_TEMPLATES%'
      '%COMMON_VIDEO%'
      '%COMPUTERSNEARME%'
      '%CONNECTIONS%'
      '%CONTROLS%'
      '%COOKIES%'
      '%DESKTOP%'
      '%DESKTOPDIRECTORY%'
      '%DRIVES%'
      '%FAVORITES%'
      '%FLAG_DONT_UNEXPAND%'
      '%FLAG_DONT_VERIFY%'
      '%FONTS%'
      '%HISTORY%'
      '%INTERNET%'
      '%INTERNET_CACHE%'
      '%LOCAL_APPDATA%'
      '%MYDOCUMENTS%'
      '%MYMUSIC%'
      '%MYPICTURES%'
      '%MYVIDEO%'
      '%NETHOOD%'
      '%NETWORK%'
      '%PERSONAL%'
      '%PLAYLISTS%'
      '%PRINTERS%'
      '%PRINTHOOD%'
      '%PROFILE%'
      '%PROGRAM_FILES%'
      '%PROGRAM_FILES_COMMON%'
      '%PROGRAMS%'
      '%RECENT%'
      '%RESOURCES%'
      '%SAMPLE_MUSIC%'
      '%SAMPLE_PLAYLISTS%'
      '%SAMPLE_PICTURES%'
      '%SAMPLE_VIDEOS%'
      '%SENDTO%'
      '%STARTMENU%'
      '%STARTUP%'
      '%SYSTEM%'
      '%TEMPLATES%'
      '%WINDOWS%')
  end
  object chAsButton: TCheckBox
    Left = 302
    Top = 148
    Width = 72
    Height = 17
    Caption = 'As Button'
    Checked = True
    State = cbChecked
    TabOrder = 5
  end
  object edtCmdLine: TComboBox
    Left = 55
    Top = 72
    Width = 313
    Height = 21
    AutoComplete = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnChange = edtCmdLineChange
    Items.Strings = (
      '%FILE% -> one file'
      '%FILES(,)% -> selected files width '#39','#39' delimeter'
      '%DIR% -> current directory'
      '%FILE2% -> other side file'
      '%DIR2% -> other side directory'
      '%PROMPT(Caption)% -> get param from user')
  end
  object chSeparator: TCheckBox
    Left = 224
    Top = 148
    Width = 72
    Height = 17
    Caption = 'Separator'
    TabOrder = 4
    Visible = False
    OnClick = chSeparatorClick
  end
  object GroupBox1: TGroupBox
    Left = 53
    Top = 172
    Width = 313
    Height = 83
    Caption = 'Accept'
    TabOrder = 6
    object edtFileType: TLabeledEdit
      Left = 127
      Top = 20
      Width = 89
      Height = 21
      EditLabel.Width = 43
      EditLabel.Height = 13
      EditLabel.Caption = 'File Type'
      LabelPosition = lpLeft
      TabOrder = 1
    end
    object chFile: TCheckBox
      Left = 24
      Top = 24
      Width = 41
      Height = 17
      Caption = 'File'
      TabOrder = 0
    end
    object chFolder: TCheckBox
      Left = 24
      Top = 47
      Width = 97
      Height = 17
      Caption = 'Folder'
      TabOrder = 2
    end
  end
  object cmbCategory: TComboBox
    Left = 240
    Top = 18
    Width = 128
    Height = 21
    TabOrder = 9
  end
end
