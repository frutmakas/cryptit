//----------------------------------------------------------------------------
#ifndef aboutH
#define aboutH
#include <clx.h>
#include <Classes.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QGraphics.hpp>
#include <QStdCtrls.hpp>
/*#include <Classes.hpp>
#include <QControls.hpp>
#include <QExtCtrls.hpp>
#include <QGraphics.hpp>
#include <QStdCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>   */
//----------------------------------------------------------------------------
//#include <clx\QSystem.hpp>
/*
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>*/
//----------------------------------------------------------------------------
class TAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TImage *ProgramIcon;
	TLabel *ProductName;
	TLabel *Copyright;
	TLabel *Comments;
	TButton *OKButton;
        TLabel *Label1;
        void __fastcall OKButtonClick(TObject *Sender);
private:
public:
	virtual __fastcall TAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TAboutBox *AboutBox;
//----------------------------------------------------------------------------
#endif    
