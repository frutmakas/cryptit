//---------------------------------------------------------------------------
#ifndef cyptitH
#define cyptitH
//---------------------------------------------------------------------------

#ifndef _KYLIX_
#include <clx.h>
#include <Classes.hpp>
#include <QButtons.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QDialogs.hpp>
#include <QExtCtrls.hpp>
#include <QMenus.hpp>
#include <QStdCtrls.hpp>
#include <QTypes.hpp>
/*#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <QButtons.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QDialogs.hpp>
#include <QExtCtrls.hpp>
#include <QMenus.hpp>
#include <QStdCtrls.hpp>
#include <QTypes.hpp>    */
#else
/*
#include <QButtons.hpp>
#include <QComCtrls.hpp>
#include <QControls.hpp>
#include <QDialogs.hpp>
#include <QExtCtrls.hpp>
#include <QMenus.hpp>
#include <QStdCtrls.hpp>
#include <QTypes.hpp>  */
#endif
//
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TEdit *Edit2;
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label3;
        TGroupBox *GroupBox1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TMainMenu *MainMenu1;
        TMenuItem *Exit1;
        TMenuItem *About1;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TBevel *Bevel1;
        TEdit *Edit3;
        TStatusBar *StatusBar1;
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Edit1KeyPress(TObject *Sender, char &Key);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button1Enter(TObject *Sender);
        void __fastcall Button1Exit(TObject *Sender);
        void __fastcall Button2Enter(TObject *Sender);
        void __fastcall Button2Exit(TObject *Sender);
        void __fastcall Button3Exit(TObject *Sender);
        void __fastcall Button3Enter(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall About1Click(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
        void __fastcall Edit1KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit2KeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall Edit1Exit(TObject *Sender);
        void __fastcall Edit2Exit(TObject *Sender);
        void __fastcall Edit2KeyPress(TObject *Sender, char &Key);
        void __fastcall GroupBox1Enter(TObject *Sender);
        void __fastcall Edit3Enter(TObject *Sender);
private:	// User declarations
        void EnableAll(bool ver);
        void EnableButton1();
        void setFields();
        AnsiString status;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
