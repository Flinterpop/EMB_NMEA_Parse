object Form9: TForm9
  Left = 0
  Top = 0
  Caption = 'Form9'
  ClientHeight = 656
  ClientWidth = 1355
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 29
    Height = 15
    Caption = 'PWD:'
  end
  object Label2: TLabel
    Left = 440
    Top = 51
    Width = 129
    Height = 15
    Caption = 'Message Counts by type'
  end
  object Button1: TButton
    Left = 176
    Top = 448
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object TM_Debug: TMemo
    Left = 8
    Top = 50
    Width = 409
    Height = 392
    Lines.Strings = (
      'TM_Debug')
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object StringGrid1: TStringGrid
    Left = 440
    Top = 72
    Width = 217
    Height = 265
    ColCount = 2
    DefaultColWidth = 100
    RowCount = 8
    TabOrder = 2
    RowHeights = (
      24
      25
      24
      24
      24
      24
      24
      24)
  end
  object StringGrid2: TStringGrid
    Left = 680
    Top = 72
    Width = 417
    Height = 569
    ColCount = 6
    RowCount = 40
    TabOrder = 3
  end
  object TE_PWD: TEdit
    Left = 51
    Top = 8
    Width = 366
    Height = 23
    TabOrder = 4
    Text = '.'
  end
  object CB_Debug: TCheckBox
    Left = 456
    Top = 11
    Width = 73
    Height = 17
    Caption = 'Debug'
    Checked = True
    State = cbChecked
    TabOrder = 5
  end
  object BindingsList1: TBindingsList
    Methods = <>
    OutputConverters = <>
    Left = 60
    Top = 509
  end
end
