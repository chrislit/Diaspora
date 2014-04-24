/*
 *
 * Copyright 2001 by Christopher C. Little
 *
 */
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "Main.h"
#include <defs.h>
#include <swmgr.h>
#include <versekey.h>
#include <gbfthml.h>
#include <latin1utf8.h>
#include <thmlgbf.h>
#include <thmlolb.h>
#include <thmlplain.h>
#include "thmlpbr.h"

#define _ICU_
#include <utf8transliterator.h>

#include <localemgr.h>
#include <rawtext.h>
#include <rawcom.h>
#include <ztext.h>
#include <zcom.h>
#include <swmodule.h>

#include <systdate.h>
//---------------------------------------------------------------------------
#pragma resource "*.dfm"

using namespace sword;

TMainForm *MainForm;

VerseKey* getVerseBounds (SWModule* mod, VerseKey* key) {
        zCom* zcom;
        RawCom* rawcom;
        zText* ztext;
        RawText* rawtext;

        key->LowerBound(mod->Key());
        key->UpperBound(mod->Key());

        char testament = ((VerseKey*)&mod->Key())->Testament();
        unsigned short otherIndex, index = ((VerseKey*)&mod->Key())->Index();

        long origStart, otherStart;
        unsigned short origSize, otherSize;

        zcom = dynamic_cast<zCom*>(mod);
        if (zcom) {

        zcom->findoffset(testament, index, &origStart, &origSize);
/*
        //work backwards to find first verse outside our block
        otherIndex = index - 1;
        zcom->findoffset(testament, otherIndex, &otherStart, &otherSize);
        while (origSize && otherStart == origStart && otherSize == origSize) {
                otherIndex--;
                zcom->findoffset(testament, otherIndex, &otherStart, &otherSize);
        }
        key->LowerBound() -= (index - otherIndex - 1);
*/
        //work forwards to find first verse outside our block
        otherIndex = index + 1;
        zcom->findoffset(testament, otherIndex, &otherStart, &otherSize);
        while (origSize && otherStart == origStart && otherSize == origSize && index != otherIndex) {
                otherIndex++;
                zcom->findoffset(testament, otherIndex, &otherStart, &otherSize);
        }
        key->UpperBound() += (otherIndex - index - 1);

        }
        else {
                ztext = dynamic_cast<zText*>(mod);
                if (ztext) {

        ztext->findoffset(testament, index, &origStart, &origSize);
/*
        //work backwards to find first verse outside our block
        otherIndex = index - 1;
        ztext->findoffset(testament, otherIndex, &otherStart, &otherSize);
        while (otherStart == origStart && otherSize == origSize) {
                otherIndex--;
                ztext->findoffset(testament, otherIndex, &otherStart, &otherSize);
        }
        key->LowerBound() -= (index - otherIndex - 1);
*/
        //work forwards to find first verse outside our block
        otherIndex = index + 1;
        ztext->findoffset(testament, otherIndex, &otherStart, &otherSize);
        while (origSize && otherStart == origStart && otherSize == origSize && index != otherIndex) {
                otherIndex++;
                ztext->findoffset(testament, otherIndex, &otherStart, &otherSize);
        }
        key->UpperBound() += (otherIndex - index - 1);


                }
                else {
                        rawcom = dynamic_cast<RawCom*>(mod);
                        if (rawcom) {

        rawcom->findoffset(testament, index, &origStart, &origSize);
/*
        //work backwards to find first verse outside our block
        otherIndex = index - 1;
        rawcom->findoffset(testament, otherIndex, &otherStart, &otherSize);
        while (origSize && otherStart == origStart && otherSize == origSize) {
                otherIndex--;
                rawcom->findoffset(testament, otherIndex, &otherStart, &otherSize);
        }
        key->LowerBound() -= (index - otherIndex - 1);
*/
        //work forwards to find first verse outside our block
        otherIndex = index + 1;
        rawcom->findoffset(testament, otherIndex, &otherStart, &otherSize);
        while (origSize && otherStart == origStart && otherSize == origSize) {
                otherIndex++;
                rawcom->findoffset(testament, otherIndex, &otherStart, &otherSize);
        }
        key->UpperBound() += (otherIndex - index - 1);

                        }
                        else {
                                rawtext = dynamic_cast<RawText*>(mod);
                                if (rawtext) {

        rawtext->findoffset(testament, index, &origStart, &origSize);
/*
        //work backwards to find first verse outside our block
        otherIndex = index - 1;
        rawtext->findoffset(testament, otherIndex, &otherStart, &otherSize);
        while (origSize && otherStart == origStart && otherSize == origSize) {
                otherIndex--;
                rawtext->findoffset(testament, otherIndex, &otherStart, &otherSize);
        }
        key->LowerBound() -= (index - otherIndex - 1);
*/
        //work forwards to find first verse outside our block
        otherIndex = index + 1;
        rawtext->findoffset(testament, otherIndex, &otherStart, &otherSize);
        while (origSize && otherStart == origStart && otherSize == origSize) {
                otherIndex++;
                rawtext->findoffset(testament, otherIndex, &otherStart, &otherSize);
        }
        key->UpperBound() += (otherIndex - index - 1);


                                }
                        }
                }
        }
        return key;
}

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
}
//----------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	ModMap::iterator it;
	SWModule *target;
        manager = new SWMgr();

	for (it = manager->Modules.begin(); it != manager->Modules.end(); it++) {
		target = it->second;
		if (!strcmp(target->Type(), "Biblical Texts")) {
                        modlist->Items->Add(target->Name());
//			if (descriptions) *output << target->Description();
		}
	}
	for (it = manager->Modules.begin(); it != manager->Modules.end(); it++) {
		target = it->second;
		if (!strcmp(target->Type(), "Commentaries")) {
                        modlist->Items->Add(target->Name());
//			if (descriptions) *output << target->Description();
		}
	}
	for (it = manager->Modules.begin(); it != manager->Modules.end(); it++) {
		target = it->second;
		if (!strcmp(target->Type(), "Lexicons / Dictionaries")) {
                        modlist->Items->Add(target->Name());
//			if (descriptions) *output << target->Description();
		}
	}
}

short palmbooks[67] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 190, 220, 230, 240, 250, 260, 290, 300, 310, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730};
char* palmbooknames[67] = {"", "GEN", "EXO", "LEV", "NUM", "DEU", "JOS", "JUG", "RUT", "1SA", "2SA", "1KI", "2KI", "1CH", "2CH", "EZR", "NEH", "EST", "JOB", "PS", "PRO", "ECC", "SON", "ISA", "JER", "LAM", "EZE", "DAN", "HOS", "JOE", "AMO", "OBA", "JON", "MIC", "NAH", "HAB", "ZEP", "HAG", "ZEC", "MAL", "MAT", "MAK", "LUK", "JHN", "ACT", "ROM", "1CO", "2CO", "GAL", "EPH", "PHL", "COL", "1TS", "2TS", "1TI", "2TI", "TIT", "MON", "HEB", "JAS", "1PE", "2PE", "1JN", "2JN", "3JN", "JUD", "REV"};
enum {ThML, OLB, GBF, PBR, Plain};

void __fastcall TMainForm::outputClick(TObject *Sender)
{
        static GBFThML gbffilter;
        static Latin1UTF8 latin1filter;
        static ThMLOLB olboutputfilter;
        static ThMLGBF gbfoutputfilter;
        static ThMLPlain plainoutputfilter;
        static ThMLPBR pbroutputfilter;

        static UTF8Transliterator romantransliterator;

        static TDateTime startTotal, startModule;
        startTotal = TDateTime::CurrentDateTime();

        int format;
        if (fmtOLB->Checked) format = OLB;
        else if (fmtGBF->Checked) format = GBF;
        else if (fmtPalm->Checked) format = PBR;
        else if (fmtPlain->Checked) format = Plain;
        else format = ThML;

        unsigned long topicnr = 0;

        if (optFootnotes->Checked)
                manager->setGlobalOption("Footnotes","On");
        else
                manager->setGlobalOption("Footnotes","Off");

        if (optHeadings->Checked)
        	manager->setGlobalOption("Headings","On");
        else
               	manager->setGlobalOption("Headings","Off");

        if (optStrongs->Checked)
        	manager->setGlobalOption("Strong's Numbers","On");
        else
        	manager->setGlobalOption("Strong's Numbers","Off");

        if (optMorph->Checked)
                manager->setGlobalOption("Morphological Tags","On");
        else
                manager->setGlobalOption("Morphological Tags","Off");

        if (optHCant->Checked)
                manager->setGlobalOption("Hebrew Cantillation","On");
        else
                manager->setGlobalOption("Hebrew Cantillation","Off");

        if (optHVowels->Checked)
        	manager->setGlobalOption("Hebrew Vowel Points","On");
        else
                manager->setGlobalOption("Hebrew Vowel Points","Off");

        if (optGAccents->Checked)
        	manager->setGlobalOption("Greek Accents","On");
        else
        	manager->setGlobalOption("Greek Accents","Off");

        if (format == OLB)
        	manager->setGlobalOption("Headings","Off");

        for (int i = 0; i < modlist->Items->Count; i++) {
                if (modlist->Checked[i]) {
                        startModule = TDateTime::CurrentDateTime();
                        if (feedback->Lines->Count > 30000) {
                                feedback->Lines->Clear();
                        }
                        AnsiString path;
                        if (format == OLB)
                                path = outputpath->Text + "\\" + modlist->Items->Strings[i] + ".exp";
                        else if (format == GBF)
                                path = outputpath->Text + "\\" + modlist->Items->Strings[i] + ".gbf";
                        else if (format == ThML)
                                path = outputpath->Text + "\\" + modlist->Items->Strings[i] + ".thml";
                        else
                                path = outputpath->Text + "\\" + modlist->Items->Strings[i] + ".txt";

                	ModMap::iterator it = manager->Modules.find(modlist->Items->Strings[i].c_str());
                	SectionMap::iterator sit;
                	ConfigEntMap::iterator eit;
                	SWModule *mod = it->second;
                        FILE *ofile = fopen(path.c_str(), "w");
                        VerseKey* vkey, vkey3;
                        SWKey* key;
                        char* version;
                        char* lang;
                        bool rtl;

                        const char* text;
                                                
                        ListKey listkey;
                        long listi;
                        bool listfinished, isAtomic;
                        VerseKey* vkey2;

                        static unsigned char testament, book, chapter, verse, verse2;
                        static bool t, b, c, v;
                        static char ldsect[3] = {0, 0, 0};

                        testament = book = chapter = verse = t = b = c = v = 0;

                       	if ((sit = manager->config->Sections.find((*it).second->Name())) != manager->config->Sections.end()) {
                		if ((eit = (*sit).second.find("SourceType")) != (*sit).second.end()) {
                			if (!stricmp((char *)(*eit).second.c_str(), "GBF")) {
                        		        mod->AddRenderFilter(&gbffilter);
                                        }
                                        else {
                                                mod->RemoveRenderFilter(&gbffilter);
                                        }
                		}

                                if ((eit = (*sit).second.find("Version")) != (*sit).second.end()) {
                                        version = (char *)(*eit).second.c_str();
                                }
                                else {
                                        version = "1.0";
                                }

                       		if ((eit = (*sit).second.find("Encoding")) == (*sit).second.end() || stricmp((char *)(*eit).second.c_str(), "UTF-8")) {
                                        if (eit == (*sit).second.end()) {
                                                mod->AddRenderFilter(&latin1filter);
                                        }
                                        else {
                                                mod->RemoveRenderFilter(&latin1filter);
                                        }
                                }

                                if ((eit = (*sit).second.find("Lang")) != (*sit).second.end()) {
                                        lang = (char *)(*eit).second.c_str();
                                }
                                else {
                                        lang = "en";
                                }
                                if (optRoman->Checked) {
/*
                                        if (xlitFmt->ItemIndex == 1 && (!stricmp(lang, "grc") || !stricmp(lang, "el"))){
                                                manager->setGlobalOption("Transliteration", "BGreek");
                                                romantransliterator.setOptionValue("BGreek");
                                        }
                                        else if (xlitFmt->ItemIndex == 2 && (!stricmp(lang, "grc") || !stricmp(lang, "el"))){
                                                manager->setGlobalOption("Transliteration", "BETA");
                                                romantransliterator.setOptionValue("BETA");
                                        }
                                        else if (xlitFmt->ItemIndex == 2 && (!stricmp(lang, "he"))){
                                                manager->setGlobalOption("Transliteration", "MCHebrew");
                                                romantransliterator.setOptionValue("MCHebrew");
                                        }
                                        else if (xlitFmt->ItemIndex == 2 && (!stricmp(lang, "syr"))){
                                                manager->setGlobalOption("Transliteration", "MCSyriac");
                                                romantransliterator.setOptionValue("MCSyriac");
                                        }
                                        else*/{
                                                manager->setGlobalOption("Transliteration", "Latin");
                                                romantransliterator.setOptionValue("Latin");
                                        }
                                        mod->AddRenderFilter(&romantransliterator);

                                }
                                else {
                                        manager->setGlobalOption("Transliteration", "None");
                                        mod->RemoveRenderFilter(&romantransliterator);
                                }

                                if ((eit = (*sit).second.find("Direction")) != (*sit).second.end()) {
                                        rtl = !stricmp((char *)(*eit).second.c_str(), "RtoL");
                                }
                                else {
                                        rtl = false;
                                }

                	}




                        if (format == ThML) {
                                LocaleMgr::systemLocaleMgr.setDefaultLocaleName("en");
                                fprintf(ofile, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!DOCTYPE ThML PUBLIC \"-\/\/CCEL\/\/DTD Theological Markup Language\/\/EN\" \"dtd\/ThML.dtd\">\n<ThML>\n<ThML.head>\n");
                                fprintf(ofile, "<electronicEdInfo>\n<publisherID>crosswire</publisherID>\n<authorID></authorID>\n<bookID>%s</bookID>\n<version>%s</version>\n<series></series>\n", modlist->Items->Strings[i].LowerCase().c_str(), version);
                                fprintf(ofile, "<DC>\n<DC.Title>%s<\/DC.Title>\n<DC.Language>%s<\/DC.Language>\n<\/DC>\n<\/electronicEdInfo>\n<\/ThML.head>\n<ThML.body>\n", (char*)mod->Description(), lang);

                                if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                        fprintf (ofile, "<scripContext version=\"%s\" \/>\n", (char*)mod->Name());
                                        key = (*mod);
                                       	vkey = (VerseKey*)key;
                                        vkey->Headings(1);
                                        vkey->Persist(1);
                                        vkey->setLocale("en");

                                        listfinished = false;
                                        if (!range->Text.IsEmpty()) {
                                             listkey = vkey->ParseVerseList(range->Text.c_str(), "Gen 1:1", true);
                                             listi = 0;
                                        }
                                }
                                else if (!strcmp(mod->Type(), "Lexicons / Dictionaries")) {
                                        fprintf (ofile, "<glossary>\n");
                                }

                                (*mod) = TOP;
                                if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                        if (listkey.Count() > listi) {
                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                if (!vkey) {
                                                        isAtomic = true;
                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                }
                                                else {
                                                        isAtomic = false;
                                                }
                                                mod->SetKey(vkey);
                                        }
                                        else {
                                                isAtomic = false;
                                        }
                                }


                                bool div1, div2, div3;
                                div1 = div2 = div3 = 0;


                                while (!mod->Error() && !listfinished) {
                                        if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                                text = (const char*)(*mod);
                                                if (!listkey.Count() && !strlen(text)) {
                                                        (*mod)++;
                                                        continue;
                                                }
                                                getVerseBounds(mod, &vkey3);
                                                verse2 = vkey3.UpperBound().Verse();
                                                VerseKey* vkey2 = (VerseKey*)(SWKey*)(*mod);
                                                t = vkey2->Testament() != testament;
                                                testament = vkey2->Testament();
                                                b = vkey2->Book() != book || t;
                                                book = vkey2->Book();
                                                c = vkey2->Chapter() != chapter || b;
                                                chapter = vkey2->Chapter();
                                                v = vkey2->Verse() != verse || c;
                                                verse = vkey2->Verse();

                                                if (testament) {
                                                        if (b && book) {
                                                                feedback->Lines->Add(modlist->Items->Strings[i] + "  -  " + vkey2->books[testament - 1][book - 1].name);
                                                        }

                                                        if (t || !div1) {
                                                                if (div1) {
                                                                        fprintf (ofile, "<\/div3>\n<\/div2>\n<\/div1>\n");
                                                                        div3 = false;
                                                                        div2 = false;
                                                                }
                                                                if (testament == 1) {
                                                                        fprintf (ofile, "<div1 title=\"Old Testament\" class=\"testament\" n=\"1\">\n");
                                                                        div1 = true;
                                                                }
                                                                else if (testament == 2) {
                                                                        fprintf (ofile, "<div1 title=\"New Testament\" class=\"testament\" n=\"2\">\n");
                                                                        div1 = true;
                                                                }
                                                        }
                                                        if ((b || !div2) && book) {
                                                                if (div2) {
                                                                        fprintf (ofile, "<\/div3>\n<\/div2>\n");
                                                                        div3 = false;
                                                                }
                                                                fprintf (ofile, "<div2 title=\"%s\" class=\"book\" n=\"%d\">\n<scripContext passage=\"%s\" \/>\n", vkey2->books[testament - 1][book - 1].name, book, vkey2->books[testament - 1][book - 1].name);
                                                                div2 = true;
                                                        }
                                                        if ((c || !div3) && chapter) {
                                                                if (div3) {
                                                                        fprintf (ofile, "<\/div3>\n");
                                                                }
                                                                fprintf (ofile, "<div3 title=\"Chapter %d\" class=\"chapter\" n=\"%d\">\n<scripContext passage=\"%s %d\" \/>\n",  chapter, chapter, vkey2->books[testament - 1][book - 1].name,  chapter);
                                                                div3 = true;
                                                        }
                                                }

                                                if (!strcmp(mod->Type(), "Biblical Texts")) {
                                                        if (verse == verse2 || !verse)
                                                                fprintf (ofile, "<scripture passage=\"%s\">%s<\/scripture>\n", (char*)mod->KeyText(), text);
                                                        else
                                                                fprintf (ofile, "<scripture passage=\"%s-%d\">%s<\/scripture>\n", (char*)mod->KeyText(), verse2, text);
                                                }
                                                else if (!strcmp(mod->Type(), "Commentaries")) {
                                                        if (verse == verse2 || !verse)
                                                                fprintf (ofile, "<scripCom passage=\"%s\">%s<\/scripCom>\n", (char*)mod->KeyText(), text);
                                                        else
                                                                fprintf (ofile, "<scripCom passage=\"%s-%d\">%s<\/scripCom>\n", (char*)mod->KeyText(), verse2, text);
                                                }

                                                if (isAtomic || mod->Key() >= vkey->UpperBound()) {
                                                        listi++;
                                                        if (listkey.Count() > listi) {
                                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                if (!vkey) {
                                                                        isAtomic = true;
                                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                                }
                                                                else {
                                                                        isAtomic = false;
                                                                }
                                                                mod->SetKey(vkey);
                                                        }
                                                        else {
                                                                listfinished = true;
                                                        }
                                                }
                                                else {
                                                        (*mod)++;
                                                        if (mod->Key() > vkey->UpperBound()) {
                                                                listi++;
                                                                if (listkey.Count() > listi) {
                                                                        vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                        if (!vkey) {
                                                                                isAtomic = true;
                                                                                vkey = (VerseKey*)listkey.GetElement(listi);
                                                                        }
                                                                        else {
                                                                                isAtomic = false;
                                                                        }
                                                                        mod->SetKey(vkey);
                                                                }
                                                                else {
                                                                        listfinished = true;
                                                                }
                                                        }
                                                }

                                        }
                                        else if (!strcmp(mod->Type(), "Lexicons / Dictionaries")) {
                                                fprintf (ofile, "<term>%s<\/term><def>%s<\/def>\n", (char*)mod->KeyText(), (const char*)(*mod));
                                                (*mod)++;
                                                if (ldsect[0] != *((char*)mod->KeyText()) || ldsect[1] != *((char*)mod->KeyText() + 1)) {
                                                        ldsect[0] = *((char*)mod->KeyText());
                                                        ldsect[1] = *((char*)mod->KeyText() + 1);
                                                        feedback->Lines->Add(modlist->Items->Strings[i] + "  -  " + ldsect);
                                                }
                                        }
                                }

                                if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                        fprintf (ofile, "<\/div3>\n<\/div2>\n<\/div1>\n");
                                }
                                else if (!strcmp(mod->Type(), "Lexicons / Dictionaries")) {
                                        fprintf (ofile, "<\/glossary>\n");
                                }
                                fprintf(ofile, "<\/ThML.body>\n<\/ThML>\n");
                        }
                        else if (format == Plain) {
                                mod->AddRenderFilter(&plainoutputfilter);
                                LocaleMgr::systemLocaleMgr.setDefaultLocaleName("en");
                                fprintf (ofile, "﻿");  // UTF-8 BOM -- a BOM is stupid for an 8-bit encoding, but this does serve to signal that this is UTF-8 and not ANSI

                                if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                        key = (*mod);
                                       	vkey = (VerseKey*)key;
                                        vkey->Headings(1);
                                        vkey->Persist(1);
                                        vkey->setLocale("en");

                                        listfinished = false;
                                        if (!range->Text.IsEmpty()) {
                                             listkey = vkey->ParseVerseList(range->Text.c_str(), "Gen 1:1", true);
                                             listi = 0;
                                        }
                                }

                                (*mod) = TOP;

                                if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                        if (listkey.Count() > listi) {
                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                if (!vkey) {
                                                        isAtomic = true;
                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                }
                                                else {
                                                        isAtomic = false;
                                                }
                                                mod->SetKey(vkey);
                                        }
                                        else {
                                                isAtomic = false;
                                        }
                                }

                                while (!mod->Error() && !listfinished) {
                                        if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                                text = (const char*)(*mod);
                                                if (!listkey.Count() && !strlen(text)) {
                                                        (*mod)++;
                                                        continue;
                                                }
                                                getVerseBounds(mod, &vkey3);
                                                verse2 = vkey3.UpperBound().Verse();
                                                VerseKey* vkey2 = (VerseKey*)(SWKey*)(*mod);
                                                testament = vkey2->Testament();
                                                b = vkey2->Book() != book;
                                                book = vkey2->Book();
                                                verse = vkey2->Verse();

                                                if (b) {
                                                        feedback->Lines->Add(modlist->Items->Strings[i] + "  -  " + vkey2->books[testament - 1][book - 1].name);
                                                }

                                                if (verse2 == verse || !verse)
                                                        fprintf (ofile, "%s %s\n", (char*)mod->KeyText(), text);
                                                else
                                                        fprintf (ofile, "%s-%d %s\n", (char*)mod->KeyText(), verse2, text);

                                                if (isAtomic || mod->Key() >= vkey->UpperBound()) {
                                                        listi++;
                                                        if (listkey.Count() > listi) {
                                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                if (!vkey) {
                                                                        isAtomic = true;
                                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                                }
                                                                else {
                                                                        isAtomic = false;
                                                                }
                                                                mod->SetKey(vkey);
                                                        }
                                                        else {
                                                                listfinished = true;
                                                        }
                                                }
                                                else {
                                                        (*mod)++;
                                                        if (mod->Key() > vkey->UpperBound()) {
                                                                listi++;
                                                                if (listkey.Count() > listi) {
                                                                        vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                        if (!vkey) {
                                                                                isAtomic = true;
                                                                                vkey = (VerseKey*)listkey.GetElement(listi);
                                                                        }
                                                                        else {
                                                                                isAtomic = false;
                                                                        }
                                                                        mod->SetKey(vkey);
                                                                }
                                                                else {
                                                                        listfinished = true;
                                                                }
                                                        }
                                                }
                                        }
                                        else if (!strcmp(mod->Type(), "Lexicons / Dictionaries")) {
                                                fprintf (ofile, "%s\n%s\n\n", (char*)mod->KeyText(), (const char*)(*mod));
                                                (*mod)++;
                                                if (ldsect[0] != *((char*)mod->KeyText()) || ldsect[1] != *((char*)mod->KeyText() + 1)) {
                                                        ldsect[0] = *((char*)mod->KeyText());
                                                        ldsect[1] = *((char*)mod->KeyText() + 1);
                                                        feedback->Lines->Add(modlist->Items->Strings[i] + "  -  " + ldsect);
                                                }
                                        }
                                }
                                mod->RemoveRenderFilter(&plainoutputfilter);
                        }
                        else if (format == OLB) {
                                mod->AddRenderFilter(&olboutputfilter);
                                LocaleMgr::systemLocaleMgr.setDefaultLocaleName("olb");

                                if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                        key = (*mod);
                                       	vkey = (VerseKey*)key;
                                        vkey->Headings(0);
                                        vkey->Persist(1);
                                        vkey->setLocale("olb");

                                        listfinished = false;
                                        if (!range->Text.IsEmpty()) {
                                             listkey = vkey->ParseVerseList(range->Text.c_str(), "Gen 1:1", true);
                                             listi = 0;
                                        }
                                }

                                (*mod) = TOP;

                                if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                        if (listkey.Count() > listi) {
                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                if (!vkey) {
                                                        isAtomic = true;
                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                }
                                                else {
                                                        isAtomic = false;
                                                }
                                                mod->SetKey(vkey);
                                        }
                                        else {
                                                isAtomic = false;
                                        }
                                }

                                while (!mod->Error() && !listfinished) {
                                        if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                                text = (const char*)(*mod);
                                                if (!listkey.Count() && !strlen(text)) {
                                                        (*mod)++;
                                                        continue;
                                                }
                                                VerseKey* vkey2 = (VerseKey*)(SWKey*)(*mod);
                                                testament = vkey2->Testament();
                                                b = vkey2->Book() != book;
                                                book = vkey2->Book();

                                                if (b) {
                                                        feedback->Lines->Add(modlist->Items->Strings[i] + "  -  " + vkey2->books[testament - 1][book - 1].name);
                                                }

                                                if (!strcmp(mod->Type(), "Biblical Texts"))
                                                        fprintf (ofile, "$$$ %s\n%s\n", (char*)mod->KeyText(), text);
                                                else
                                                        fprintf (ofile, "$$$ %s\n%s\n", (char*)mod->KeyText(), text);

                                                if (isAtomic || mod->Key() >= vkey->UpperBound()) {
                                                        listi++;
                                                        if (listkey.Count() > listi) {
                                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                if (!vkey) {
                                                                        isAtomic = true;
                                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                                }
                                                                else {
                                                                        isAtomic = false;
                                                                }
                                                                mod->SetKey(vkey);
                                                        }
                                                        else {
                                                                listfinished = true;
                                                        }
                                                }
                                                else {
                                                        (*mod)++;
                                                        if (mod->Key() > vkey->UpperBound()) {
                                                                listi++;
                                                                if (listkey.Count() > listi) {
                                                                        vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                        if (!vkey) {
                                                                                isAtomic = true;
                                                                                vkey = (VerseKey*)listkey.GetElement(listi);
                                                                        }
                                                                        else {
                                                                                isAtomic = false;
                                                                        }
                                                                        mod->SetKey(vkey);
                                                                }
                                                                else {
                                                                        listfinished = true;
                                                                }
                                                        }
                                                }
                                        }
                                        else if (!strcmp(mod->Type(), "Lexicons / Dictionaries")) {
                                                fprintf (ofile, "$$$ T%d\n\\\\%s\\\\\n%s\n", topicnr++, (char*)mod->KeyText(), text);
                                                (*mod)++;
                                                if (ldsect[0] != *((char*)mod->KeyText()) || ldsect[1] != *((char*)mod->KeyText() + 1)) {
                                                        ldsect[0] = *((char*)mod->KeyText());
                                                        ldsect[1] = *((char*)mod->KeyText() + 1);
                                                        feedback->Lines->Add(modlist->Items->Strings[i] + "  -  " + ldsect);
                                                }
                                        }
                                }
                                mod->RemoveRenderFilter(&olboutputfilter);
                        }
                        else if (format == GBF) {
                                if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                        mod->AddRenderFilter(&gbfoutputfilter);
                                        LocaleMgr::systemLocaleMgr.setDefaultLocaleName("en");
                                        fprintf(ofile, "<H000>\n<H1>%s\n<H2>%s\n", (char*)mod->Description(), (char*)mod->Name());
                                        key = (*mod);
                                       	vkey = (VerseKey*)key;
                                        vkey->Headings(0);
                                        vkey->Persist(1);
                                        vkey->setLocale("en");

                                        listfinished = false;
                                        if (!range->Text.IsEmpty()) {
                                             listkey = vkey->ParseVerseList(range->Text.c_str(), "Gen 1:1", true);
                                             listi = 0;
                                        }

                                        (*mod) = TOP;

                                        if (listkey.Count() > listi) {
                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                if (!vkey) {
                                                        isAtomic = true;
                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                }
                                                else {
                                                        isAtomic = false;
                                                }
                                                mod->SetKey(vkey);
                                        }
                                        else {
                                                isAtomic = false;
                                        }

                                        while (!mod->Error() && !listfinished) {
                                                text = (const char*)(*mod);
                                                if (!listkey.Count() && !strlen(text)) {
                                                        (*mod)++;
                                                        continue;
                                                }
                                                VerseKey* vkey2 = (VerseKey*)(SWKey*)(*mod);
                                                t = vkey2->Testament() != testament;
                                                testament = vkey2->Testament();
                                                b = vkey2->Book() != book || t;
                                                book = vkey2->Book();
                                                c = vkey2->Chapter() != chapter || b;
                                                chapter = vkey2->Chapter();
                                                v = vkey2->Verse() != verse || v;
                                                verse = vkey2->Verse();

                                                if (b) {
                                                        feedback->Lines->Add(modlist->Items->Strings[i] + "  -  " + vkey2->books[testament - 1][book - 1].name);
                                                }

                                                if (t) {
                                                        if (testament == 1) {
                                                                fprintf (ofile, "<BO><CM>\n");
                                                        }
                                                        else if (testament == 2) {
                                                                fprintf (ofile, "<BN><CM>\n");
                                                        }

                                                        fprintf (ofile, "<SB%d><TT>%s<CM><Tt>\n", book, vkey2->books[testament - 1][book - 1].name);
                                                        fprintf (ofile, "<SC%d>\n", chapter);
                                                        if (rtl)
                                                                fprintf (ofile, "<DR>\n");
                                                }
                                                else if (b) {
                                                        fprintf (ofile, "<SB%d><TT>%s<CM><Tt>\n", book, vkey2->books[testament - 1][book - 1].name);
                                                        fprintf (ofile, "<SC%d>\n", chapter);
                                                        if (rtl)
                                                                fprintf (ofile, "<DR>\n");
                                                }
                                                else if (c) {
                                                        fprintf (ofile, "<SC%d>\n", chapter);
                                                        if (rtl)
                                                                fprintf (ofile, "<DR>\n");
                                                }

                                                fprintf (ofile, "<SV%d>%s\n", verse, text);

                                                if (isAtomic || mod->Key() >= vkey->UpperBound()) {
                                                        listi++;
                                                        if (listkey.Count() > listi) {
                                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                if (!vkey) {
                                                                        isAtomic = true;
                                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                                }
                                                                else {
                                                                        isAtomic = false;
                                                                }
                                                                mod->SetKey(vkey);
                                                        }
                                                        else {
                                                                listfinished = true;
                                                        }
                                                }
                                                else {
                                                        (*mod)++;
                                                        if (mod->Key() > vkey->UpperBound()) {
                                                                listi++;
                                                                if (listkey.Count() > listi) {
                                                                        vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                        if (!vkey) {
                                                                                isAtomic = true;
                                                                                vkey = (VerseKey*)listkey.GetElement(listi);
                                                                        }
                                                                        else {
                                                                                isAtomic = false;
                                                                        }
                                                                        mod->SetKey(vkey);
                                                                }
                                                                else {
                                                                        listfinished = true;
                                                                }
                                                        }
                                                }
                                        }
                                        fprintf(ofile, "<ZZ>\n");
                                        mod->RemoveRenderFilter(&gbfoutputfilter);
                                }
                        }
                        else if (format == PBR) {
                                if (!strcmp(mod->Type(), "Biblical Texts") || !strcmp(mod->Type(), "Commentaries")) {
                                        mod->AddRenderFilter(&pbroutputfilter);
                                        LocaleMgr::systemLocaleMgr.setDefaultLocaleName(lang);
                                        fprintf(ofile, "<PARSERINFO DECODE=\"UTF8\" ENCODE=\"iso-8859-1\" WORDTYPE=\"SPCSEP\">\n\n");
                                        fprintf(ofile, "<BIBLE NAME=\"%s\" INFO=\"%s\" ALIGN=\"%s\">\n", (char*)mod->Name(), (char*)mod->Description(), rtl ? "RIGHT" : "LEFT");
                                        key = (*mod);
                                       	vkey = (VerseKey*)key;
                                        vkey->Headings(0);
                                        vkey->Persist(1);
                                        vkey->setLocale(lang);

                                        listfinished = false;
                                        if (!range->Text.IsEmpty()) {
                                             listkey = vkey->ParseVerseList(range->Text.c_str(), "Gen 1:1", true);
                                             listi = 0;
                                        }                                        

                                        (*mod) = TOP;

                                        if (listkey.Count() > listi) {
                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                if (!vkey) {
                                                        isAtomic = true;
                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                }
                                                else {
                                                        isAtomic = false;
                                                }
                                                mod->SetKey(vkey);
                                        }
                                        else {
                                                isAtomic = false;
                                        }

                                        bool div1, div2;
                                        div1 = div2 = 0;

                                        while (!mod->Error() && !listfinished) {
                                                text = (const char*)(*mod);                                        
                                                if (!listkey.Count() && !strlen(text)) {
                                                        (*mod)++;
                                                        continue;
                                                }
                                                unsigned char chapter2 = chapter;
                                                verse2 = verse;
                                                VerseKey* vkey2 = (VerseKey*)(SWKey*)(*mod);
                                                t = vkey2->Testament() != testament;
                                                testament = vkey2->Testament();
                                                b = vkey2->Book() != book || t;
                                                book = vkey2->Book();
                                                c = vkey2->Chapter() != chapter || b;
                                                chapter = vkey2->Chapter();
                                                v = vkey2->Verse() != verse || v;
                                                verse = vkey2->Verse();

                                                if (testament) {
                                                        if (b) {
                                                                feedback->Lines->Add(modlist->Items->Strings[i] + "  -  " + vkey2->books[testament - 1][book - 1].name);
                                                        }

                                                        if (b || !div1) {
                                                                if (div1) {
                                                                        fprintf(ofile, "<\/CHAPTER>\n<\/BOOK>\n");
                                                                        div2 = false;
                                                                }

                                                                int len = 2 * strlen(vkey2->books[testament - 1][book - 1].name);
                                                                char* localname = new char[len];
                                                                strcpy (localname, vkey2->books[testament - 1][book - 1].name);
                                                                latin1filter.ProcessText(localname, len, NULL);

                                                                fprintf (ofile, "<BOOK NAME=\"%s\" NUMBER=\"%d\" SHORTCUT=\"%s\">\n", localname, palmbooks[book + (39 * (testament - 1))], palmbooknames[book + (39 * (testament - 1))]);
                                                                delete localname;

                                                                div1 = true;
                                                                b = true;
                                                        }
                                                        if (c || !div2) {
                                                                if (div2) {
                                                                        fprintf(ofile, "<\/CHAPTER>\n");
                                                                }
                                                                while (chapter - chapter2 - 1 > 0) {
                                                                        fprintf (ofile, "<CHAPTER><\/CHAPTER>\n");
                                                                        chapter2++;
                                                                }
                                                                fprintf (ofile, "<CHAPTER>\n");
                                                                div2 = true;
                                                                c = true;
                                                        }
                                                }

                                                for (int j = 0; j < (verse - verse2 - 1); j++) {
                                                        fprintf (ofile, "<VERSE><\/VERSE>\n");
                                                }                                                

                                                fprintf (ofile, "<VERSE>");
                                                if (c) {
                                                        if (b) {
                                                                int len = 2 * strlen(vkey->books[testament - 1][book - 1].name);
                                                                char* localname = new char[len];
                                                                strcpy (localname, vkey->books[testament - 1][book - 1].name);
                                                                latin1filter.ProcessText(localname, len, NULL);

                                                                fprintf(ofile, "<BOOKTEXT>%s", localname);

                                                                delete localname;
                                                        }
                                                        fprintf (ofile, "<CHAPTEXT>Chapter %d", chapter);
                                                }
                                                fprintf (ofile, "%s<\/VERSE>\n", text);

                                                if (isAtomic || mod->Key() >= vkey->UpperBound()) {
                                                        listi++;
                                                        if (listkey.Count() > listi) {
                                                                vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                if (!vkey) {
                                                                        isAtomic = true;
                                                                        vkey = (VerseKey*)listkey.GetElement(listi);
                                                                }
                                                                else {
                                                                        isAtomic = false;
                                                                }
                                                                mod->SetKey(vkey);
                                                        }
                                                        else {
                                                                listfinished = true;
                                                        }
                                                }
                                                else {
                                                        (*mod)++;
                                                        if (mod->Key() > vkey->UpperBound()) {
                                                                listi++;
                                                                if (listkey.Count() > listi) {
                                                                        vkey = SWDYNAMIC_CAST(VerseKey, listkey.GetElement(listi));
                                                                        if (!vkey) {
                                                                                isAtomic = true;
                                                                                vkey = (VerseKey*)listkey.GetElement(listi);
                                                                        }
                                                                        else {
                                                                                isAtomic = false;
                                                                        }
                                                                        mod->SetKey(vkey);
                                                                }
                                                                else {
                                                                        listfinished = true;
                                                                }
                                                        }
                                                }

                                        }

                                        fprintf(ofile, "<\/CHAPTER>\n<\/BOOK>\n<\/BIBLE>\n");
                                        mod->RemoveRenderFilter(&pbroutputfilter);
                                }
                        }

                        fclose(ofile);
                        feedback->Lines->Add(modlist->Items->Strings[i] + "  -  Complete");
                        feedback->Lines->Add("Processing time: " + (TDateTime::CurrentDateTime() - startModule).FormatString("n:ss") + " min.");
                }
        }
        feedback->Lines->Add("Cleaning up...");
        delete manager;
        manager = new SWMgr();
        feedback->Lines->Add("Finished");
        feedback->Lines->Add("Total time: " + (TDateTime::CurrentDateTime() - startTotal).FormatString("n:ss") + " min.");
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::optRomanClick(TObject *Sender)
{
xlitFmt->Enabled = optRoman->Checked;
}
//---------------------------------------------------------------------------

