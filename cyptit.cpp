//---------------------------------------------------------------------------
#include <clx.h>
#pragma hdrstop

#include "cyptit.h"
#include "cryptcore.h"
#include "fileversion.h"
#include "about.h"
#include <SysUtils.hpp>
//#include <FileCtrl.hpp>
#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.xfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        status = "Ready";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
     OpenDialog1->Filter = "Archive Files (*.zip; *.tar; *.gz; *.rar; *.ace; *.arj; *.exe) | *.zip; *.tar; *.gz; *.rar; *.ace; *.arj; *.exe | CryptIt Files (*.cry) | *.cry | All Files (*.*) | *.*";

     Cursor=crHourGlass;
     if (OpenDialog1->Execute()){
        Edit1->Font->Color=clWindowText;
        Edit1->Text=OpenDialog1->FileName;
        EnableButton1();
//        Button1->Enabled=Edit1->Text!="" && Edit2->Text!="" && Edit3->Text!="";
        Edit1->Hint=Edit1->Text;
        Edit2->SetFocus();
        setFields();
     } else Edit1->SetFocus();

     Cursor=crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
     AnsiString Edit1_Text(Edit1->Text);
     AnsiString Edit2_Text(Edit2->Text);

     setFields();
     Cursor=crHourGlass;
     if (DirectoryExists(ExtractFilePath(Edit1_Text))) SaveDialog1->InitialDir=ExtractFilePath(Edit1_Text);
     if (!Edit1_Text.IsEmpty() && !DirectoryExists(ExtractFilePath(Edit1_Text))) {
         status="Source File does not exist!";
         StatusBar1->SimpleText=status;
         return;
     }
     if (ExtractFileExt(Edit1_Text).AnsiCompareIC(".cry")==0){
        SaveDialog1->FilterIndex=1;
        SaveDialog1->FileName=ExtractFileName(Edit2_Text);
     }else {
          SaveDialog1->FilterIndex=2;
          SaveDialog1->FileName=ChangeFileExt(ExtractFileName(Edit1_Text),".cry");
     }
     if (SaveDialog1->Execute()){
        Edit2->Font->Color=clWindowText;
        Edit2->Text=SaveDialog1->FileName;
        if (ExtractFileExt(Edit2_Text).AnsiCompare(".")==0 && SaveDialog1->FilterIndex==2)
           Edit2->Text=ChangeFileExt(Edit2_Text,".cry");
        RadioButton1->Checked = SaveDialog1->FilterIndex==2 && OpenDialog1->FilterIndex==1;
        RadioButton2->Checked != RadioButton1->Checked;
        EnableButton1();
        Edit2->Hint=Edit2_Text;
     }
     Cursor=crDefault;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
     Edit1->Text="";
     Edit2->Text="";
     Edit3->Text="";
     EnableButton1();
     //Button1->Enabled=Edit1->Text!="" && Edit2->Text!="" && Edit3->Text!="";
     Edit1->Hint="Enter the name of the file to be encrypted or decrypted";
     Edit2->Hint="Enter the name of the file to be saved as";
     status = "Ready";
     Edit1->Font->Color=clWindowText;
     Edit2->Font->Color=clWindowText;
     StatusBar1->SimpleText=status;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1KeyPress(TObject *Sender, char &Key)
{
//     Button1->Enabled=Edit1->Text!="" && Edit2->Text!="" && Edit3->Text!="";
       Edit1->Font->Color=clWindowText;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
     Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Enter(TObject *Sender)
{
     Button1->Font->Color=clBlue;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Exit(TObject *Sender)
{
     Button1->Font->Color=clWindowText;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Enter(TObject *Sender)
{
     Button2->Font->Color=clHighlight;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Exit(TObject *Sender)
{
     Button2->Font->Color=clWindowText;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Exit(TObject *Sender)
{
     Button3->Font->Color=clWindowText;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Enter(TObject *Sender)
{
     Button3->Font->Color=clHighlight;
}
//---------------------------------------------------------------------------
void TForm1::EnableAll(bool mode){
     Edit1->Enabled=mode;
     Edit2->Enabled=mode;
     Edit3->Enabled=mode;
     Button2->Enabled=mode;
     Button3->Enabled=mode;
     SpeedButton1->Enabled=mode;
     SpeedButton2->Enabled=mode;
     AnsiString Edit1_Text(Edit1->Text);
     AnsiString Edit2_Text(Edit2->Text);
     AnsiString Edit3_Text(Edit3->Text);

     Button1->Enabled = mode ? Edit1_Text!="" && Edit2_Text!="" && Edit3_Text!="": false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
     bool err = false;
     EnableAll(false);
     AnsiString Edit1_Text(Edit1->Text);
     AnsiString Edit2_Text(Edit2->Text);
     AnsiString Edit3_Text(Edit3->Text);

     Cursor=crHourGlass;
     Edit2->Font->Color=clWindowText;
     if (Edit1_Text.AnsiCompareIC(Edit2_Text)==0){
        status = "Error : Source and target file name are identique";
        StatusBar1->SimpleText=status;
        Edit2->Text="";
        Edit3->Text="";
        EnableAll(true);
        Cursor=crDefault;
        return;
     }
     if (RadioButton1->Checked){
           status = "Encrypting. Please wait.";
           StatusBar1->SimpleText= status;
           if (!cryptFile(Edit1_Text.c_str(),Edit2_Text.c_str(),Edit3_Text.c_str(), strlen(Edit3_Text.c_str()))){
              err=true;
           }
     } else {
            status="Decrypting. Please wait.";
           StatusBar1->SimpleText=status;
           if (!decryptFile(Edit1_Text.c_str(),Edit2_Text.c_str(),Edit3_Text.c_str(), strlen(Edit3_Text.c_str()))){
              err=true;
           }
     }
     EnableAll(true);
     Cursor=crDefault;
     if (err) status="Error : "+AnsiString(getErrorMesg());
     else status="Done. Waiting for orders.";
     StatusBar1->SimpleText=status;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::About1Click(TObject *Sender)
{
     AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Exit1Click(TObject *Sender)
{
     Application->Terminate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if (AnsiString(Edit1->Text) ==""){
        Edit1->Hint="Enter the name of the file to be encrypted or decrypted";
     }else Edit1->Hint=Edit1->Text;
     EnableButton1();
//     Button1->Enabled=Edit1->Text!="" && Edit2->Text!="" && Edit3->Text!="";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit2KeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
     if (AnsiString(Edit2->Text) ==""){
       Edit2->Hint="Enter the name of the file to be saved as";
     }else Edit2->Hint=Edit2->Text;
      EnableButton1();
//     Button1->Enabled=Edit1->Text!="" && Edit2->Text!="" && Edit3->Text!="";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
     StatusBar1->SimpleText=status;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
     StatusBar1->SimpleText=status;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Exit(TObject *Sender)
{
     setFields();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Exit(TObject *Sender)
{
     AnsiString Edit2_Text(Edit2->Text);

     if (Edit2_Text.IsEmpty() || DirectoryExists(ExtractFilePath(Edit2_Text))) {
        Edit2->Font->Color=clWindowText;
        status="";
     }
     else {
         Edit2->Font->Color=clRed;
         status="Target path does not exist!";
     }
     StatusBar1->SimpleText=status;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2KeyPress(TObject *Sender, char &Key)
{
     Edit2->Font->Color=clWindowText;
}
//---------------------------------------------------------------------------

void TForm1::setFields(){
    Cursor=crHourGlass;
    AnsiString Edit1_Text(Edit1->Text);

    FILE *f=NULL;
     if (!FileExists(Edit1_Text)) {
         Edit1->Font->Color=clRed;
         status="Source File does not exist!";
     }
     else {
         Edit1->Font->Color=clWindowText;
         f=fopen(Edit1_Text.c_str(),"rb");
         if (f != NULL){
            CryptVersion cv = readVersion(&f);
            if (cv.MajorVersion>=1 && cv.MinorVersion>=1){
               fileInformation fi={"","",0,""};
               readFileInfo(f,&fi);
//               fileInformationCopy(&fi,readFileInfo(f));
               if (crcCompare(fi.crc)) {
                  Edit2->Text = ExtractFilePath(Edit1_Text)+AnsiString(fi.name);
                  Edit2->Font->Color=clBlue;
                  RadioButton2->Checked=true;
               }
            }
         }
         fclose(f);
     }
     StatusBar1->SimpleText=status;
     Cursor=crDefault;
}
void __fastcall TForm1::GroupBox1Enter(TObject *Sender)
{
     if (Edit2->Font->Color!=clRed)
        Edit2->Font->Color=clWindowText;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit3Enter(TObject *Sender)
{
     if (Edit2->Font->Color!=clRed)
        Edit2->Font->Color=clWindowText;
}
//---------------------------------------------------------------------------

void TForm1::EnableButton1(){
        Button1->Enabled=!Edit1->Text.IsEmpty() && !Edit2->Text.IsEmpty() && !Edit3->Text.IsEmpty();
}

