object MainForm: TMainForm
  Left = 365
  Top = 111
  Width = 631
  Height = 527
  Caption = 'Diaspora'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  ShowHint = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object modlist: TCheckListBox
    Left = 0
    Top = 0
    Width = 153
    Height = 500
    Align = alLeft
    Constraints.MinHeight = 204
    Constraints.MinWidth = 153
    ItemHeight = 13
    TabOrder = 0
  end
  object Panel1: TPanel
    Left = 153
    Top = 0
    Width = 470
    Height = 500
    Align = alClient
    BevelOuter = bvNone
    Constraints.MinHeight = 500
    Constraints.MinWidth = 470
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 60
      Height = 13
      Caption = 'Output Path:'
    end
    object label: TLabel
      Left = 8
      Top = 40
      Width = 65
      Height = 13
      Caption = 'Verse Range:'
    end
    object outputpath: TEdit
      Left = 88
      Top = 8
      Width = 377
      Height = 21
      TabOrder = 0
      Text = '.\'
    end
    object output: TButton
      Left = 368
      Top = 40
      Width = 97
      Height = 25
      Caption = 'Output Files'
      TabOrder = 7
      OnClick = outputClick
    end
    object feedback: TMemo
      Left = 0
      Top = 216
      Width = 470
      Height = 284
      Align = alBottom
      Anchors = [akLeft, akTop, akRight, akBottom]
      Lines.Strings = (
        'Diaspora: The SWORD Project Module Exporter'
        'Copyright 2001 by the CrossWire Bible Society'
        'http://www.crosswire.org'
        'Released under the GNU General Public License version 2.0'
        
          'You can read this licese here: http://www.gnu.org/licenses/gpl.h' +
          'tml'
        'Send bug reports to sword-bugs@crosswire.org.'
        ''
        
          'Select the modules you which to export from the list on the left' +
          ', enter the '
        
          'path where you want the exported files to be written, and choose' +
          ' the format '
        'you desire.  Then click Output Files.'
        ''
        'Note that OLB, GBF, and Palm Bible Reader export support are '
        'experimental.'
        ''
        'For more information on formats:'
        'ThML: http://www.ccel.org/ThML'
        'GBF: http://www.ebible.org/bible/gbf.htm'
        'Palm Bible Reader: http://palmbible.sourceforge.net/convert.htm'
        ''
        'Please remember to respect copyright holders'#39' rights & wishes.')
      ScrollBars = ssVertical
      TabOrder = 11
    end
    object RadioGroup1: TRadioGroup
      Left = 8
      Top = 72
      Width = 457
      Height = 41
      Caption = 'Format'
      TabOrder = 1
    end
    object fmtThML: TRadioButton
      Left = 16
      Top = 88
      Width = 81
      Height = 17
      Caption = 'ThML'
      Checked = True
      TabOrder = 2
      TabStop = True
    end
    object fmtOLB: TRadioButton
      Left = 104
      Top = 88
      Width = 49
      Height = 17
      Caption = 'OLB'
      TabOrder = 3
    end
    object fmtGBF: TRadioButton
      Left = 216
      Top = 88
      Width = 49
      Height = 17
      Caption = 'GBF'
      TabOrder = 4
    end
    object fmtPalm: TRadioButton
      Left = 320
      Top = 88
      Width = 41
      Height = 17
      Caption = 'PBR'
      TabOrder = 5
    end
    object fmtPlain: TRadioButton
      Left = 408
      Top = 88
      Width = 41
      Height = 17
      Caption = 'Plain'
      TabOrder = 6
    end
    object optFootnotes: TCheckBox
      Left = 240
      Top = 120
      Width = 81
      Height = 17
      Caption = 'Footnotes'
      Checked = True
      State = cbChecked
      TabOrder = 8
    end
    object optStrongs: TCheckBox
      Left = 8
      Top = 120
      Width = 105
      Height = 17
      Caption = 'Strong'#39's Numbers'
      Checked = True
      State = cbChecked
      TabOrder = 9
    end
    object optHeadings: TCheckBox
      Left = 344
      Top = 120
      Width = 105
      Height = 17
      Caption = 'Section Headings'
      Checked = True
      State = cbChecked
      TabOrder = 10
    end
    object optMorph: TCheckBox
      Left = 128
      Top = 120
      Width = 73
      Height = 17
      Caption = 'Morphology'
      Checked = True
      State = cbChecked
      TabOrder = 12
    end
    object optGAccents: TCheckBox
      Left = 344
      Top = 144
      Width = 97
      Height = 17
      Caption = 'Greek Accents'
      Checked = True
      State = cbChecked
      TabOrder = 13
    end
    object optHCant: TCheckBox
      Left = 128
      Top = 144
      Width = 113
      Height = 17
      Caption = 'Hebrew Cantillation'
      Checked = True
      State = cbChecked
      TabOrder = 14
    end
    object optHVowels: TCheckBox
      Left = 240
      Top = 144
      Width = 97
      Height = 17
      Caption = 'Hebrew Vowels'
      Checked = True
      State = cbChecked
      TabOrder = 15
    end
    object optRoman: TCheckBox
      Left = 8
      Top = 144
      Width = 113
      Height = 17
      Caption = 'Roman Transliterate'
      TabOrder = 16
      OnClick = optRomanClick
    end
    object range: TEdit
      Left = 88
      Top = 40
      Width = 265
      Height = 21
      TabOrder = 17
    end
    object xlitFmt: TRadioGroup
      Tag = 1
      Left = 8
      Top = 168
      Width = 457
      Height = 41
      Caption = 'Transliteration Format'
      Columns = 3
      Enabled = False
      ItemIndex = 0
      Items.Strings = (
        'Standard Scheme'
        'B-Greek'
        'BETA/Michigan-Claremont')
      TabOrder = 18
    end
  end
end
