/*
 *
 * Copyright 2001 by Christopher C. Little
 *
 */
//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <vcl\sysutils.hpp>
#include <vcl\windows.hpp>
#include <vcl\messages.hpp>
#include <vcl\sysutils.hpp>
#include <vcl\classes.hpp>
#include <vcl\graphics.hpp>
#include <vcl\controls.hpp>
#include <vcl\forms.hpp>
#include <vcl\dialogs.hpp>
#include <vcl\stdctrls.hpp>
#include <vcl\buttons.hpp>
#include <vcl\extctrls.hpp>
#include <vcl\menus.hpp>
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <CheckLst.hpp>
#include <StdCtrls.hpp>
#include <encfiltmgr.h>
using namespace sword;
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:
        TCheckListBox *modlist;
        TPanel *Panel1;
        TLabel *Label1;
        TEdit *outputpath;
        TButton *output;
        TMemo *feedback;
        TRadioGroup *RadioGroup1;
        TRadioButton *fmtThML;
        TRadioButton *fmtOLB;
        TRadioButton *fmtGBF;
        TRadioButton *fmtPalm;
        TRadioButton *fmtPlain;
        TCheckBox *optFootnotes;
        TCheckBox *optStrongs;
        TCheckBox *optHeadings;
        TCheckBox *optMorph;
        TCheckBox *optGAccents;
        TCheckBox *optHCant;
        TCheckBox *optHVowels;
        TCheckBox *optRoman;
        TEdit *range;
        TLabel *label;
        TRadioGroup *xlitFmt;
	void __fastcall FormCreate(TObject *Sender);
        void __fastcall outputClick(TObject *Sender);
        void __fastcall optRomanClick(TObject *Sender);
private:        // private user declarations
        SWMgr* manager;
public:         // public user declarations
	virtual __fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
