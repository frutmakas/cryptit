//---------------------------------------------------------------------------

#include <clx.h>
#pragma hdrstop
USEFORM("about.cpp", AboutBox);
USEFORM("cyptit.cpp", Form1);
#define CLX_USE_LIBQT 
//---------------------------------------------------------------------------
int main(void)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "CryptIt 1.10b 2002 For Linux";
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch(...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch(Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
