//---------------------------------------------------------------------
#include <clx.h>
#pragma hdrstop

#include "about.h"
//--------------------------------------------------------------------- 
#pragma resource "*.xfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::OKButtonClick(TObject *Sender)
{
      Close();        
}
//---------------------------------------------------------------------------


