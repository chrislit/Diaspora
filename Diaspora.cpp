/*
 *
 * Copyright 2001 by Christopher C. Little
 *
 */
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("Diaspora.res");
USEFORM("Main.cpp", MainForm);
USEUNIT("thmlpbr.cpp");
USELIB("..\..\sword\lib\libsword.lib");
USELIB("..\..\icu-sword\as_is\borland\icucommon.lib");
USELIB("..\..\icu-sword\as_is\borland\icudatab.lib");
USELIB("..\..\icu-sword\as_is\borland\icui18n.lib");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Diaspora";
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
