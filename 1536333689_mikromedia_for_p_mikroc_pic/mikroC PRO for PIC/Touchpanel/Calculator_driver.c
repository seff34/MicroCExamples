#include "Calculator_objects.h"
#include "Calculator_resources.h"

// TFT module connections
char TFT_DataPort at PORTE;
char TFT_DataPort_Direction at TRISE;
sbit TFT_RST at LATH3_bit;
sbit TFT_BLED at LATG4_bit;
sbit TFT_RS at LATG3_bit;
sbit TFT_CS at LATF2_bit;
sbit TFT_RD at LATG0_bit;
sbit TFT_WR at LATG1_bit;
sbit TFT_RST_Direction at TRISH3_bit;
sbit TFT_BLED_Direction at TRISG4_bit;
sbit TFT_RS_Direction at TRISG3_bit;
sbit TFT_CS_Direction at TRISF2_bit;
sbit TFT_RD_Direction at TRISG0_bit;
sbit TFT_WR_Direction at TRISG1_bit;
// End TFT module connections

// Touch Panel module connections
sbit DriveX_Left at LATD3_bit;
sbit DriveX_Right at LATD1_bit;
sbit DriveY_Up at LATD4_bit;
sbit DriveY_Down at LATD2_bit;
sbit DriveX_Left_Direction at TRISD3_bit;
sbit DriveX_Right_Direction at TRISD1_bit;
sbit DriveY_Up_Direction at TRISD4_bit;
sbit DriveY_Down_Direction at TRISD2_bit;

// Global variables
unsigned int Xcoord, Ycoord;
char PenDown;
void *PressedObject;
int PressedObjectType;
unsigned int caption_length, caption_height;
unsigned int display_width, display_height;

// Set ADC threshold
const ADC_Threshold = 700;

static void InitializeTouchPanel() {
  TFT_BLED_Direction = 0;
  TFT_BLED = 0;

  Delay_ms(150);
  ANSELA = 0;
  ANSELB = 0;
  ANSELD = 0;
  ANSELE = 0;
  ANSELF = 0;
  ANSELG = 0;

  ADC_Init();
  TFT_Set_Default_Mode();
  TFT_Init_ILI9341_8bit(320, 240);

  TP_TFT_Init(320, 240, 27, 26);                 // Initialize touch panel
  TP_TFT_Set_ADC_Threshold(ADC_Threshold);     // Set touch panel ADC threshold
  TFT_BLED = 1;

  PenDown = 0;
  PressedObject = 0;
  PressedObjectType = -1;
}

void Calibrate() {
  TFT_Set_Font(&Tahoma13x13, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("Touch Panel Calibration...", 85, 110);
  Delay_ms(2000);
  TFT_Fill_Screen(0);

  TFT_Set_Font(&Tahoma13x13, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("Touch Bottom Left Corner...", 85, 110);
  Delay_ms(1000);

  TFT_Set_Pen(CL_WHITE, 3);
  TFT_Line(0, 239, 0, 235);
  TFT_Line(0, 239, 5, 239);
  TFT_Line(0, 239, 10, 229);
  
  TP_TFT_Calibrate_Max();                      // Calibration of bottom left corner
  Delay_ms(500);

  TFT_Set_Pen(CL_BLACK, 3);
  TFT_Line(0, 239, 0, 235);
  TFT_Line(0, 239, 5, 239);
  TFT_Line(0, 239, 10, 229);
  TFT_Fill_Screen(0);
  
  TFT_Set_Font(&Tahoma13x13, CL_WHITE, FO_HORIZONTAL);
  TFT_Write_Text("Touch Upper Right Corner...", 85, 110);
  Delay_ms(1000);

  TFT_Set_Pen(CL_WHITE, 3);
  TFT_Line(315, 1, 319, 1);
  TFT_Line(310, 10, 319, 1);
  TFT_Line(319, 5, 319, 1);
  
  TP_TFT_Calibrate_Min();                      // Calibration of bottom left corner
  Delay_ms(500);

  TFT_Set_Pen(CL_BLACK, 3);
  TFT_Line(315, 1, 319, 1);
  TFT_Line(310, 10, 319, 1);
  TFT_Line(319, 5, 319, 1);

  Delay_ms(500);
}

/////////////////////////
  TScreen *CurrentScreen;

  TScreen                Screen1;
  TButton                Button19;
  char Button19_Caption[2] = "7";

  TButton                Button1;
  char Button1_Caption[2] = "4";

  TButton                Button5;
  char Button5_Caption[2] = "1";

  TButton                Button6;
  char Button6_Caption[2] = "0";

  TButton                Button7;
  char Button7_Caption[2] = "8";

  TButton                Button2;
  char Button2_Caption[2] = "5";

  TButton                Button3;
  char Button3_Caption[2] = "2";

  TButton                Button4;
  char Button4_Caption[4] = "+/-";

  TButton                Button8;
  char Button8_Caption[2] = "9";

  TButton                Button9;
  char Button9_Caption[2] = "6";

  TButton                Button10;
  char Button10_Caption[2] = "3";

  TButton                Button12;
  char Button12_Caption[2] = "/";

  TButton                Button13;
  char Button13_Caption[2] = "*";

  TButton                Button14;
  char Button14_Caption[2] = "-";

  TButton                Button15;
  char Button15_Caption[2] = "+";

  TBox                   Box3;
  TButton                Button16;
  char Button16_Caption[4] = "DEL";

  TButton                Button17;
  char Button17_Caption[2] = "C";

  TButton                Button18;
  char Button18_Caption[2] = "=";

  TBox                   Box1;
  TLabel                 Label1;
  char Label1_Caption[20] = " ";

  TLabel                 Label2;
  char Label2_Caption[3] = " +";

  TLabel                 Label3;
  char Label3_Caption[20] = " ";

  TLabel                 Label4;
  char Label4_Caption[2] = "=";

  TLabel                 Label5;
  char Label5_Caption[14] = "mE Calculator";

  TLabel                 Label6;
  char Label6_Caption[18] = " ";

  TButton                *Screen0_Buttons[18];
  TLabel                 *Screen0_Labels[6];
  TBox                   *Screen0_Boxes[2];

  TScreen                Screen2;
  TLabel                 Label7;
  char Label7_Caption[23] = "mikroE Calculator Demo";

  TLabel                 Label8;
  char Label8_Caption[50] = "This is a simple version of calculator. Feel free";

  TButton_Round          ButtonRound1;
  char ButtonRound1_Caption[26] = "Continue to mE Calculator";

  TLabel                 Label9;
  char Label9_Caption[48] = "to try it out. Note that input values should be";

  TLabel                 Label10;
  char Label10_Caption[51] = "within int/integer values (from -32768 to +32767).";

  TButton_Round          *Screen1_Buttons_Round[1];
  TLabel                 *Screen1_Labels[4];

static void InitializeObjects() {
  Screen1.Color                     = 0x0000;
  Screen1.Width                     = 240;
  Screen1.Height                    = 320;
  Screen1.ButtonsCount              = 18;
  Screen1.Buttons                   = Screen0_Buttons;
  Screen1.Buttons_RoundCount        = 0;
  Screen1.LabelsCount               = 6;
  Screen1.Labels                    = Screen0_Labels;
  Screen1.BoxesCount                = 2;
  Screen1.Boxes                     = Screen0_Boxes;
  Screen1.ObjectsCount              = 26;
  Screen0_Buttons[0]                = &Button19;
  Screen0_Buttons[1]                = &Button1;
  Screen0_Buttons[2]                = &Button5;
  Screen0_Buttons[3]                = &Button6;
  Screen0_Buttons[4]                = &Button7;
  Screen0_Buttons[5]                = &Button2;
  Screen0_Buttons[6]                = &Button3;
  Screen0_Buttons[7]                = &Button4;
  Screen0_Buttons[8]                = &Button8;
  Screen0_Buttons[9]                = &Button9;
  Screen0_Buttons[10]                = &Button10;
  Screen0_Buttons[11]                = &Button12;
  Screen0_Buttons[12]                = &Button13;
  Screen0_Buttons[13]                = &Button14;
  Screen0_Buttons[14]                = &Button15;
  Screen0_Boxes[0]                  = &Box3;
  Screen0_Buttons[15]                = &Button16;
  Screen0_Buttons[16]                = &Button17;
  Screen0_Buttons[17]                = &Button18;
  Screen0_Boxes[1]                  = &Box1;
  Screen0_Labels[0]                 = &Label1;
  Screen0_Labels[1]                 = &Label2;
  Screen0_Labels[2]                 = &Label3;
  Screen0_Labels[3]                 = &Label4;
  Screen0_Labels[4]                 = &Label5;
  Screen0_Labels[5]                 = &Label6;

  Screen2.Color                     = 0x0000;
  Screen2.Width                     = 320;
  Screen2.Height                    = 240;
  Screen2.ButtonsCount              = 0;
  Screen2.Buttons_RoundCount        = 1;
  Screen2.Buttons_Round             = Screen1_Buttons_Round;
  Screen2.LabelsCount               = 4;
  Screen2.Labels                    = Screen1_Labels;
  Screen2.BoxesCount                = 0;
  Screen2.ObjectsCount              = 5;
  Screen1_Labels[0]                 = &Label7;
  Screen1_Labels[1]                 = &Label8;
  Screen1_Buttons_Round[0]          = &ButtonRound1;
  Screen1_Labels[2]                 = &Label9;
  Screen1_Labels[3]                 = &Label10;


  Button19.OwnerScreen     = &Screen1;
  Button19.Order           = 0;
  Button19.Left            = 0;
  Button19.Top             = 162;
  Button19.Width           = 60;
  Button19.Height          = 40;
  Button19.Pen_Width       = 1;
  Button19.Pen_Color       = 0x0000;
  Button19.Visible         = 1;
  Button19.Active          = 1;
  Button19.Transparent     = 1;
  Button19.Caption         = Button19_Caption;
  Button19.FontName        = Arial21x24;
  Button19.Font_Color      = 0xFFFF;
  Button19.Gradient        = 1;
  Button19.Gradient_Orientation    = 0;
  Button19.Gradient_Start_Color    = 0x9492;
  Button19.Gradient_End_Color      = 0x0000;
  Button19.Color           = 0xC618;
  Button19.PressColEnabled = 1;
  Button19.Press_Color     = 0xC618;
  Button19.OnUpPtr        = 0;
  Button19.OnDownPtr      = 0;
  Button19.OnClickPtr     = Button19Click;
  Button19.OnPressPtr     = 0;

  Button1.OwnerScreen     = &Screen1;
  Button1.Order           = 1;
  Button1.Left            = 0;
  Button1.Top             = 202;
  Button1.Width           = 60;
  Button1.Height          = 40;
  Button1.Pen_Width       = 1;
  Button1.Pen_Color       = 0x0000;
  Button1.Visible         = 1;
  Button1.Active          = 1;
  Button1.Transparent     = 1;
  Button1.Caption         = Button1_Caption;
  Button1.FontName        = Arial21x24;
  Button1.Font_Color      = 0xFFFF;
  Button1.Gradient        = 1;
  Button1.Gradient_Orientation    = 0;
  Button1.Gradient_Start_Color    = 0x9492;
  Button1.Gradient_End_Color      = 0x0000;
  Button1.Color           = 0xC618;
  Button1.PressColEnabled = 1;
  Button1.Press_Color     = 0xC618;
  Button1.OnUpPtr        = 0;
  Button1.OnDownPtr      = 0;
  Button1.OnClickPtr     = Button1Click;
  Button1.OnPressPtr     = 0;

  Button5.OwnerScreen     = &Screen1;
  Button5.Order           = 2;
  Button5.Left            = 0;
  Button5.Top             = 242;
  Button5.Width           = 60;
  Button5.Height          = 40;
  Button5.Pen_Width       = 1;
  Button5.Pen_Color       = 0x0000;
  Button5.Visible         = 1;
  Button5.Active          = 1;
  Button5.Transparent     = 1;
  Button5.Caption         = Button5_Caption;
  Button5.FontName        = Arial21x24;
  Button5.Font_Color      = 0xFFFF;
  Button5.Gradient        = 1;
  Button5.Gradient_Orientation    = 0;
  Button5.Gradient_Start_Color    = 0x9492;
  Button5.Gradient_End_Color      = 0x0000;
  Button5.Color           = 0xC618;
  Button5.PressColEnabled = 1;
  Button5.Press_Color     = 0xC618;
  Button5.OnUpPtr        = 0;
  Button5.OnDownPtr      = 0;
  Button5.OnClickPtr     = Button5Click;
  Button5.OnPressPtr     = 0;

  Button6.OwnerScreen     = &Screen1;
  Button6.Order           = 3;
  Button6.Left            = 0;
  Button6.Top             = 282;
  Button6.Width           = 120;
  Button6.Height          = 40;
  Button6.Pen_Width       = 1;
  Button6.Pen_Color       = 0x0000;
  Button6.Visible         = 1;
  Button6.Active          = 1;
  Button6.Transparent     = 1;
  Button6.Caption         = Button6_Caption;
  Button6.FontName        = Arial21x24;
  Button6.Font_Color      = 0xFFFF;
  Button6.Gradient        = 1;
  Button6.Gradient_Orientation    = 0;
  Button6.Gradient_Start_Color    = 0x9492;
  Button6.Gradient_End_Color      = 0x0000;
  Button6.Color           = 0xC618;
  Button6.PressColEnabled = 1;
  Button6.Press_Color     = 0xC618;
  Button6.OnUpPtr        = 0;
  Button6.OnDownPtr      = 0;
  Button6.OnClickPtr     = Button6Click;
  Button6.OnPressPtr     = 0;

  Button7.OwnerScreen     = &Screen1;
  Button7.Order           = 4;
  Button7.Left            = 60;
  Button7.Top             = 162;
  Button7.Width           = 60;
  Button7.Height          = 40;
  Button7.Pen_Width       = 1;
  Button7.Pen_Color       = 0x0000;
  Button7.Visible         = 1;
  Button7.Active          = 1;
  Button7.Transparent     = 1;
  Button7.Caption         = Button7_Caption;
  Button7.FontName        = Arial21x24;
  Button7.Font_Color      = 0xFFFF;
  Button7.Gradient        = 1;
  Button7.Gradient_Orientation    = 0;
  Button7.Gradient_Start_Color    = 0x9492;
  Button7.Gradient_End_Color      = 0x0000;
  Button7.Color           = 0xC618;
  Button7.PressColEnabled = 1;
  Button7.Press_Color     = 0xC618;
  Button7.OnUpPtr        = 0;
  Button7.OnDownPtr      = 0;
  Button7.OnClickPtr     = Button7Click;
  Button7.OnPressPtr     = 0;

  Button2.OwnerScreen     = &Screen1;
  Button2.Order           = 5;
  Button2.Left            = 60;
  Button2.Top             = 202;
  Button2.Width           = 60;
  Button2.Height          = 40;
  Button2.Pen_Width       = 1;
  Button2.Pen_Color       = 0x0000;
  Button2.Visible         = 1;
  Button2.Active          = 1;
  Button2.Transparent     = 1;
  Button2.Caption         = Button2_Caption;
  Button2.FontName        = Arial21x24;
  Button2.Font_Color      = 0xFFFF;
  Button2.Gradient        = 1;
  Button2.Gradient_Orientation    = 0;
  Button2.Gradient_Start_Color    = 0x9492;
  Button2.Gradient_End_Color      = 0x0000;
  Button2.Color           = 0xC618;
  Button2.PressColEnabled = 1;
  Button2.Press_Color     = 0xC618;
  Button2.OnUpPtr        = 0;
  Button2.OnDownPtr      = 0;
  Button2.OnClickPtr     = Button2Click;
  Button2.OnPressPtr     = 0;

  Button3.OwnerScreen     = &Screen1;
  Button3.Order           = 6;
  Button3.Left            = 60;
  Button3.Top             = 242;
  Button3.Width           = 60;
  Button3.Height          = 40;
  Button3.Pen_Width       = 1;
  Button3.Pen_Color       = 0x0000;
  Button3.Visible         = 1;
  Button3.Active          = 1;
  Button3.Transparent     = 1;
  Button3.Caption         = Button3_Caption;
  Button3.FontName        = Arial21x24;
  Button3.Font_Color      = 0xFFFF;
  Button3.Gradient        = 1;
  Button3.Gradient_Orientation    = 0;
  Button3.Gradient_Start_Color    = 0x9492;
  Button3.Gradient_End_Color      = 0x0000;
  Button3.Color           = 0xC618;
  Button3.PressColEnabled = 1;
  Button3.Press_Color     = 0xC618;
  Button3.OnUpPtr        = 0;
  Button3.OnDownPtr      = 0;
  Button3.OnClickPtr     = Button3Click;
  Button3.OnPressPtr     = 0;

  Button4.OwnerScreen     = &Screen1;
  Button4.Order           = 7;
  Button4.Left            = 120;
  Button4.Top             = 282;
  Button4.Width           = 60;
  Button4.Height          = 40;
  Button4.Pen_Width       = 1;
  Button4.Pen_Color       = 0x0000;
  Button4.Visible         = 1;
  Button4.Active          = 1;
  Button4.Transparent     = 1;
  Button4.Caption         = Button4_Caption;
  Button4.FontName        = Arial21x24;
  Button4.Font_Color      = 0xFFFF;
  Button4.Gradient        = 1;
  Button4.Gradient_Orientation    = 0;
  Button4.Gradient_Start_Color    = 0x9492;
  Button4.Gradient_End_Color      = 0x0000;
  Button4.Color           = 0xC618;
  Button4.PressColEnabled = 1;
  Button4.Press_Color     = 0xC618;
  Button4.OnUpPtr        = 0;
  Button4.OnDownPtr      = 0;
  Button4.OnClickPtr     = Button4Click;
  Button4.OnPressPtr     = 0;

  Button8.OwnerScreen     = &Screen1;
  Button8.Order           = 8;
  Button8.Left            = 120;
  Button8.Top             = 162;
  Button8.Width           = 60;
  Button8.Height          = 40;
  Button8.Pen_Width       = 1;
  Button8.Pen_Color       = 0x0000;
  Button8.Visible         = 1;
  Button8.Active          = 1;
  Button8.Transparent     = 1;
  Button8.Caption         = Button8_Caption;
  Button8.FontName        = Arial21x24;
  Button8.Font_Color      = 0xFFFF;
  Button8.Gradient        = 1;
  Button8.Gradient_Orientation    = 0;
  Button8.Gradient_Start_Color    = 0x9492;
  Button8.Gradient_End_Color      = 0x0000;
  Button8.Color           = 0xC618;
  Button8.PressColEnabled = 1;
  Button8.Press_Color     = 0xC618;
  Button8.OnUpPtr        = 0;
  Button8.OnDownPtr      = 0;
  Button8.OnClickPtr     = Button8Click;
  Button8.OnPressPtr     = 0;

  Button9.OwnerScreen     = &Screen1;
  Button9.Order           = 9;
  Button9.Left            = 120;
  Button9.Top             = 202;
  Button9.Width           = 60;
  Button9.Height          = 40;
  Button9.Pen_Width       = 1;
  Button9.Pen_Color       = 0x0000;
  Button9.Visible         = 1;
  Button9.Active          = 1;
  Button9.Transparent     = 1;
  Button9.Caption         = Button9_Caption;
  Button9.FontName        = Arial21x24;
  Button9.Font_Color      = 0xFFFF;
  Button9.Gradient        = 1;
  Button9.Gradient_Orientation    = 0;
  Button9.Gradient_Start_Color    = 0x9492;
  Button9.Gradient_End_Color      = 0x0000;
  Button9.Color           = 0xC618;
  Button9.PressColEnabled = 1;
  Button9.Press_Color     = 0xC618;
  Button9.OnUpPtr        = 0;
  Button9.OnDownPtr      = 0;
  Button9.OnClickPtr     = Button9Click;
  Button9.OnPressPtr     = 0;

  Button10.OwnerScreen     = &Screen1;
  Button10.Order           = 10;
  Button10.Left            = 121;
  Button10.Top             = 242;
  Button10.Width           = 60;
  Button10.Height          = 40;
  Button10.Pen_Width       = 1;
  Button10.Pen_Color       = 0x0000;
  Button10.Visible         = 1;
  Button10.Active          = 1;
  Button10.Transparent     = 1;
  Button10.Caption         = Button10_Caption;
  Button10.FontName        = Arial21x24;
  Button10.Font_Color      = 0xFFFF;
  Button10.Gradient        = 1;
  Button10.Gradient_Orientation    = 0;
  Button10.Gradient_Start_Color    = 0x9492;
  Button10.Gradient_End_Color      = 0x0000;
  Button10.Color           = 0xC618;
  Button10.PressColEnabled = 1;
  Button10.Press_Color     = 0xC618;
  Button10.OnUpPtr        = 0;
  Button10.OnDownPtr      = 0;
  Button10.OnClickPtr     = Button10Click;
  Button10.OnPressPtr     = 0;

  Button12.OwnerScreen     = &Screen1;
  Button12.Order           = 11;
  Button12.Left            = 120;
  Button12.Top             = 123;
  Button12.Width           = 60;
  Button12.Height          = 40;
  Button12.Pen_Width       = 1;
  Button12.Pen_Color       = 0x0000;
  Button12.Visible         = 1;
  Button12.Active          = 1;
  Button12.Transparent     = 1;
  Button12.Caption         = Button12_Caption;
  Button12.FontName        = Arial21x24;
  Button12.Font_Color      = 0xFFFF;
  Button12.Gradient        = 1;
  Button12.Gradient_Orientation    = 0;
  Button12.Gradient_Start_Color    = 0x9492;
  Button12.Gradient_End_Color      = 0x0000;
  Button12.Color           = 0xC618;
  Button12.PressColEnabled = 1;
  Button12.Press_Color     = 0xC618;
  Button12.OnUpPtr        = 0;
  Button12.OnDownPtr      = 0;
  Button12.OnClickPtr     = Button12Click;
  Button12.OnPressPtr     = 0;

  Button13.OwnerScreen     = &Screen1;
  Button13.Order           = 12;
  Button13.Left            = 180;
  Button13.Top             = 123;
  Button13.Width           = 60;
  Button13.Height          = 40;
  Button13.Pen_Width       = 1;
  Button13.Pen_Color       = 0x0000;
  Button13.Visible         = 1;
  Button13.Active          = 1;
  Button13.Transparent     = 1;
  Button13.Caption         = Button13_Caption;
  Button13.FontName        = Arial21x24;
  Button13.Font_Color      = 0xFFFF;
  Button13.Gradient        = 1;
  Button13.Gradient_Orientation    = 0;
  Button13.Gradient_Start_Color    = 0x9492;
  Button13.Gradient_End_Color      = 0x0000;
  Button13.Color           = 0xC618;
  Button13.PressColEnabled = 1;
  Button13.Press_Color     = 0xC618;
  Button13.OnUpPtr        = 0;
  Button13.OnDownPtr      = 0;
  Button13.OnClickPtr     = Button13Click;
  Button13.OnPressPtr     = 0;

  Button14.OwnerScreen     = &Screen1;
  Button14.Order           = 13;
  Button14.Left            = 180;
  Button14.Top             = 162;
  Button14.Width           = 60;
  Button14.Height          = 40;
  Button14.Pen_Width       = 1;
  Button14.Pen_Color       = 0x0000;
  Button14.Visible         = 1;
  Button14.Active          = 1;
  Button14.Transparent     = 1;
  Button14.Caption         = Button14_Caption;
  Button14.FontName        = Arial21x24;
  Button14.Font_Color      = 0xFFFF;
  Button14.Gradient        = 1;
  Button14.Gradient_Orientation    = 0;
  Button14.Gradient_Start_Color    = 0x9492;
  Button14.Gradient_End_Color      = 0x0000;
  Button14.Color           = 0xC618;
  Button14.PressColEnabled = 1;
  Button14.Press_Color     = 0xC618;
  Button14.OnUpPtr        = 0;
  Button14.OnDownPtr      = 0;
  Button14.OnClickPtr     = Button14Click;
  Button14.OnPressPtr     = 0;

  Button15.OwnerScreen     = &Screen1;
  Button15.Order           = 14;
  Button15.Left            = 180;
  Button15.Top             = 202;
  Button15.Width           = 60;
  Button15.Height          = 40;
  Button15.Pen_Width       = 1;
  Button15.Pen_Color       = 0x0000;
  Button15.Visible         = 1;
  Button15.Active          = 1;
  Button15.Transparent     = 1;
  Button15.Caption         = Button15_Caption;
  Button15.FontName        = Arial21x24;
  Button15.Font_Color      = 0xFFFF;
  Button15.Gradient        = 1;
  Button15.Gradient_Orientation    = 0;
  Button15.Gradient_Start_Color    = 0x9492;
  Button15.Gradient_End_Color      = 0x0000;
  Button15.Color           = 0xC618;
  Button15.PressColEnabled = 1;
  Button15.Press_Color     = 0xC618;
  Button15.OnUpPtr        = 0;
  Button15.OnDownPtr      = 0;
  Button15.OnClickPtr     = Button15Click;
  Button15.OnPressPtr     = 0;

  Box3.OwnerScreen     = &Screen1;
  Box3.Order           = 15;
  Box3.Left            = 0;
  Box3.Top             = 26;
  Box3.Width           = 240;
  Box3.Height          = 97;
  Box3.Pen_Width       = 0;
  Box3.Pen_Color       = 0x0000;
  Box3.Visible         = 1;
  Box3.Active          = 1;
  Box3.Transparent     = 1;
  Box3.Gradient        = 0;
  Box3.Gradient_Orientation    = 0;
  Box3.Gradient_Start_Color    = 0x07E0;
  Box3.Gradient_End_Color      = 0x0540;
  Box3.Color           = 0x07E8;
  Box3.PressColEnabled = 1;
  Box3.Press_Color     = 0x8410;
  Box3.OnUpPtr        = 0;
  Box3.OnDownPtr      = 0;
  Box3.OnClickPtr     = 0;
  Box3.OnPressPtr     = 0;

  Button16.OwnerScreen     = &Screen1;
  Button16.Order           = 16;
  Button16.Left            = 0;
  Button16.Top             = 123;
  Button16.Width           = 60;
  Button16.Height          = 40;
  Button16.Pen_Width       = 1;
  Button16.Pen_Color       = 0x0000;
  Button16.Visible         = 1;
  Button16.Active          = 1;
  Button16.Transparent     = 1;
  Button16.Caption         = Button16_Caption;
  Button16.FontName        = Arial21x24;
  Button16.Font_Color      = 0xFFFF;
  Button16.Gradient        = 1;
  Button16.Gradient_Orientation    = 0;
  Button16.Gradient_Start_Color    = 0x9492;
  Button16.Gradient_End_Color      = 0x0000;
  Button16.Color           = 0xC618;
  Button16.PressColEnabled = 1;
  Button16.Press_Color     = 0xC618;
  Button16.OnUpPtr        = 0;
  Button16.OnDownPtr      = 0;
  Button16.OnClickPtr     = Button16Click;
  Button16.OnPressPtr     = 0;

  Button17.OwnerScreen     = &Screen1;
  Button17.Order           = 17;
  Button17.Left            = 60;
  Button17.Top             = 123;
  Button17.Width           = 60;
  Button17.Height          = 40;
  Button17.Pen_Width       = 1;
  Button17.Pen_Color       = 0x0000;
  Button17.Visible         = 1;
  Button17.Active          = 1;
  Button17.Transparent     = 1;
  Button17.Caption         = Button17_Caption;
  Button17.FontName        = Arial21x24;
  Button17.Font_Color      = 0xFFFF;
  Button17.Gradient        = 1;
  Button17.Gradient_Orientation    = 0;
  Button17.Gradient_Start_Color    = 0x9492;
  Button17.Gradient_End_Color      = 0x0000;
  Button17.Color           = 0xC618;
  Button17.PressColEnabled = 1;
  Button17.Press_Color     = 0xC618;
  Button17.OnUpPtr        = 0;
  Button17.OnDownPtr      = 0;
  Button17.OnClickPtr     = Button17Click;
  Button17.OnPressPtr     = 0;

  Button18.OwnerScreen     = &Screen1;
  Button18.Order           = 18;
  Button18.Left            = 180;
  Button18.Top             = 242;
  Button18.Width           = 60;
  Button18.Height          = 80;
  Button18.Pen_Width       = 1;
  Button18.Pen_Color       = 0x0000;
  Button18.Visible         = 1;
  Button18.Active          = 1;
  Button18.Transparent     = 1;
  Button18.Caption         = Button18_Caption;
  Button18.FontName        = Arial21x24;
  Button18.Font_Color      = 0xFFFF;
  Button18.Gradient        = 1;
  Button18.Gradient_Orientation    = 0;
  Button18.Gradient_Start_Color    = 0x9492;
  Button18.Gradient_End_Color      = 0x0000;
  Button18.Color           = 0xC618;
  Button18.PressColEnabled = 1;
  Button18.Press_Color     = 0xC618;
  Button18.OnUpPtr        = 0;
  Button18.OnDownPtr      = 0;
  Button18.OnClickPtr     = Button18Click;
  Button18.OnPressPtr     = 0;

  Box1.OwnerScreen     = &Screen1;
  Box1.Order           = 19;
  Box1.Left            = 0;
  Box1.Top             = 0;
  Box1.Width           = 240;
  Box1.Height          = 26;
  Box1.Pen_Width       = 1;
  Box1.Pen_Color       = 0x0000;
  Box1.Visible         = 1;
  Box1.Active          = 1;
  Box1.Transparent     = 1;
  Box1.Gradient        = 1;
  Box1.Gradient_Orientation    = 0;
  Box1.Gradient_Start_Color    = 0x9492;
  Box1.Gradient_End_Color      = 0x0000;
  Box1.Color           = 0xC618;
  Box1.PressColEnabled = 1;
  Box1.Press_Color     = 0x8410;
  Box1.OnUpPtr        = 0;
  Box1.OnDownPtr      = 0;
  Box1.OnClickPtr     = 0;
  Box1.OnPressPtr     = 0;

  Label1.OwnerScreen    = &Screen1;
  Label1.Order          = 20;
  Label1.Left           = 4;
  Label1.Top            = 34;
  Label1.Width          = 21;
  Label1.Height         = 22;
  Label1.Visible        = 1;
  Label1.Active         = 1;
  Label1.Caption        = Label1_Caption;
  Label1.FontName       = Courier_New12x23;
  Label1.Font_Pos_Ver   = 32;
  Label1.Font_Color     = 0x0000;
  Label1.OnUpPtr        = 0;
  Label1.OnDownPtr      = 0;
  Label1.OnClickPtr     = 0;
  Label1.OnPressPtr     = 0;

  Label2.OwnerScreen    = &Screen1;
  Label2.Order          = 21;
  Label2.Left           = 4;
  Label2.Top            = 55;
  Label2.Width          = 34;
  Label2.Height         = 22;
  Label2.Visible        = 1;
  Label2.Active         = 1;
  Label2.Caption        = Label2_Caption;
  Label2.FontName       = Courier_New12x23;
  Label2.Font_Pos_Ver   = 53;
  Label2.Font_Color     = 0x0000;
  Label2.OnUpPtr        = 0;
  Label2.OnDownPtr      = 0;
  Label2.OnClickPtr     = 0;
  Label2.OnPressPtr     = 0;

  Label3.OwnerScreen    = &Screen1;
  Label3.Order          = 22;
  Label3.Left           = 4;
  Label3.Top            = 75;
  Label3.Width          = 21;
  Label3.Height         = 22;
  Label3.Visible        = 1;
  Label3.Active         = 1;
  Label3.Caption        = Label3_Caption;
  Label3.FontName       = Courier_New12x23;
  Label3.Font_Pos_Ver   = 73;
  Label3.Font_Color     = 0x0000;
  Label3.OnUpPtr        = 0;
  Label3.OnDownPtr      = 0;
  Label3.OnClickPtr     = 0;
  Label3.OnPressPtr     = 0;

  Label4.OwnerScreen    = &Screen1;
  Label4.Order          = 23;
  Label4.Left           = 4;
  Label4.Top            = 96;
  Label4.Width          = 21;
  Label4.Height         = 22;
  Label4.Visible        = 1;
  Label4.Active         = 1;
  Label4.Caption        = Label4_Caption;
  Label4.FontName       = Courier_New12x23;
  Label4.Font_Pos_Ver   = 94;
  Label4.Font_Color     = 0x0000;
  Label4.OnUpPtr        = 0;
  Label4.OnDownPtr      = 0;
  Label4.OnClickPtr     = 0;
  Label4.OnPressPtr     = 0;

  Label5.OwnerScreen    = &Screen1;
  Label5.Order          = 24;
  Label5.Left           = 56;
  Label5.Top            = 5;
  Label5.Width          = 123;
  Label5.Height         = 18;
  Label5.Visible        = 1;
  Label5.Active         = 1;
  Label5.Caption        = Label5_Caption;
  Label5.FontName       = Arial16x19;
  Label5.Font_Pos_Ver   = 3;
  Label5.Font_Color     = 0xFFFF;
  Label5.OnUpPtr        = 0;
  Label5.OnDownPtr      = 0;
  Label5.OnClickPtr     = 0;
  Label5.OnPressPtr     = 0;

  Label6.OwnerScreen    = &Screen1;
  Label6.Order          = 25;
  Label6.Left           = 28;
  Label6.Top            = 96;
  Label6.Width          = 21;
  Label6.Height         = 22;
  Label6.Visible        = 1;
  Label6.Active         = 1;
  Label6.Caption        = Label6_Caption;
  Label6.FontName       = Courier_New12x23;
  Label6.Font_Pos_Ver   = 94;
  Label6.Font_Color     = 0x0000;
  Label6.OnUpPtr        = 0;
  Label6.OnDownPtr      = 0;
  Label6.OnClickPtr     = 0;
  Label6.OnPressPtr     = 0;

  Label7.OwnerScreen    = &Screen2;
  Label7.Order          = 0;
  Label7.Left           = 24;
  Label7.Top            = 27;
  Label7.Width          = 276;
  Label7.Height         = 24;
  Label7.Visible        = 1;
  Label7.Active         = 1;
  Label7.Caption        = Label7_Caption;
  Label7.FontName       = Arial21x24;
  Label7.Font_Pos_Ver   = 25;
  Label7.Font_Color     = 0xF800;
  Label7.OnUpPtr        = 0;
  Label7.OnDownPtr      = 0;
  Label7.OnClickPtr     = 0;
  Label7.OnPressPtr     = 0;

  Label8.OwnerScreen    = &Screen2;
  Label8.Order          = 1;
  Label8.Left           = 20;
  Label8.Top            = 74;
  Label8.Width          = 289;
  Label8.Height         = 15;
  Label8.Visible        = 1;
  Label8.Active         = 1;
  Label8.Caption        = Label8_Caption;
  Label8.FontName       = Tahoma13x16;
  Label8.Font_Pos_Ver   = 72;
  Label8.Font_Color     = 0x07FF;
  Label8.OnUpPtr        = 0;
  Label8.OnDownPtr      = 0;
  Label8.OnClickPtr     = 0;
  Label8.OnPressPtr     = 0;

  ButtonRound1.OwnerScreen     = &Screen2;
  ButtonRound1.Order           = 2;
  ButtonRound1.Left            = 149;
  ButtonRound1.Top             = 180;
  ButtonRound1.Width           = 150;
  ButtonRound1.Height          = 38;
  ButtonRound1.Pen_Width       = 1;
  ButtonRound1.Pen_Color       = 0x0000;
  ButtonRound1.Visible         = 1;
  ButtonRound1.Active          = 1;
  ButtonRound1.Transparent     = 1;
  ButtonRound1.Caption         = ButtonRound1_Caption;
  ButtonRound1.FontName        = Tahoma13x13;
  ButtonRound1.Font_Color      = 0x0000;
  ButtonRound1.Gradient        = 1;
  ButtonRound1.Gradient_Orientation    = 0;
  ButtonRound1.Gradient_Start_Color    = 0xFFFF;
  ButtonRound1.Gradient_End_Color      = 0x8410;
  ButtonRound1.Color           = 0x8410;
  ButtonRound1.PressColEnabled = 1;
  ButtonRound1.Press_Color     = 0x8410;
  ButtonRound1.OnUpPtr        = 0;
  ButtonRound1.OnDownPtr      = 0;
  ButtonRound1.OnClickPtr     = ButtonRound1Click;
  ButtonRound1.OnPressPtr     = 0;

  Label9.OwnerScreen    = &Screen2;
  Label9.Order          = 3;
  Label9.Left           = 20;
  Label9.Top            = 94;
  Label9.Width          = 284;
  Label9.Height         = 15;
  Label9.Visible        = 1;
  Label9.Active         = 1;
  Label9.Caption        = Label9_Caption;
  Label9.FontName       = Tahoma13x16;
  Label9.Font_Pos_Ver   = 92;
  Label9.Font_Color     = 0x07FF;
  Label9.OnUpPtr        = 0;
  Label9.OnDownPtr      = 0;
  Label9.OnClickPtr     = 0;
  Label9.OnPressPtr     = 0;

  Label10.OwnerScreen    = &Screen2;
  Label10.Order          = 4;
  Label10.Left           = 22;
  Label10.Top            = 116;
  Label10.Width          = 270;
  Label10.Height         = 15;
  Label10.Visible        = 1;
  Label10.Active         = 1;
  Label10.Caption        = Label10_Caption;
  Label10.FontName       = Tahoma13x16;
  Label10.Font_Pos_Ver   = 114;
  Label10.Font_Color     = 0x07FF;
  Label10.OnUpPtr        = 0;
  Label10.OnDownPtr      = 0;
  Label10.OnClickPtr     = 0;
  Label10.OnPressPtr     = 0;
}

static char IsInsideObject (unsigned int X, unsigned int Y, unsigned int Left, unsigned int Top, unsigned int Width, unsigned int Height) { // static
  if ( (Left<= X) && (Left+ Width - 1 >= X) &&
       (Top <= Y)  && (Top + Height - 1 >= Y) )
    return 1;
  else
    return 0;
}


#define GetButton(index)              CurrentScreen->Buttons[index]
#define GetRoundButton(index)         CurrentScreen->Buttons_Round[index]
#define GetLabel(index)               CurrentScreen->Labels[index]
#define GetBox(index)                 CurrentScreen->Boxes[index]


void DrawButton(TButton *Abutton) {
  if (Abutton->Visible == 1) {
    TFT_Set_Brush(Abutton->Transparent, Abutton->Color, Abutton->Gradient, Abutton->Gradient_Orientation, Abutton->Gradient_Start_Color, Abutton->Gradient_End_Color);
    TFT_Set_Pen(Abutton->Pen_Color, Abutton->Pen_Width);
    TFT_Rectangle(Abutton->Left, Abutton->Top, Abutton->Left + Abutton->Width - 1, Abutton->Top + Abutton->Height - 1);
    TFT_Set_Font(Abutton->FontName, Abutton->Font_Color, FO_HORIZONTAL);
    TFT_Write_Text_Return_Pos(Abutton->Caption, Abutton->Left, Abutton->Top);
    TFT_Write_Text(Abutton->Caption, (Abutton->Left + ((Abutton->Width - caption_length) / 2)), (Abutton->Top + ((Abutton->Height - caption_height) / 2)));
  }
}

static void DrawButtons() {
  int i;
  TButton *local_button;

  for ( i = 0 ; i < CurrentScreen->ButtonsCount ; i++ ) {
    local_button = GetButton(i);
    DrawButton(local_button);
  }
}


void DrawRoundButton(TButton_Round *Around_button) {
    if (Around_button->Visible == 1) {
      TFT_Set_Brush(Around_button->Transparent, Around_button->Color, Around_button->Gradient, Around_button->Gradient_Orientation,
                    Around_button->Gradient_Start_Color, Around_button->Gradient_End_Color);
      TFT_Set_Pen(Around_button->Pen_Color, Around_button->Pen_Width);
      if (Around_button->Height > Around_button->Width) {
        TFT_Rectangle_Round_Edges(Around_button->Left + 1, Around_button->Top + 1,
          Around_button->Left + Around_button->Width - 2,
          Around_button->Top + Around_button->Height - 2, (Around_button->Width/4));
      }
      else
        if (Around_button->Width > Around_button->Height) {
          TFT_Rectangle_Round_Edges(Around_button->Left + 1, Around_button->Top + 1,
            Around_button->Left + Around_button->Width - 2,
            Around_button->Top + Around_button->Height - 2, (Around_button->Height/4));
        }
      TFT_Set_Font(Around_button->FontName, Around_button->Font_Color, FO_HORIZONTAL);
      TFT_Write_Text_Return_Pos(Around_button->Caption, Around_button->Left, Around_button->Top);
      TFT_Write_Text(Around_button->Caption, (Around_button->Left + ((Around_button->Width - caption_length) / 2)),
                    (Around_button->Top + ((Around_button->Height - caption_height) / 2)));
    }
}

static void DrawRoundButtons() {
  int i;
  TButton_Round *local_round_button;

  for ( i = 0 ; i < CurrentScreen->Buttons_RoundCount ; i++ ) {
    local_round_button = GetRoundButton(i);
    DrawRoundButton(local_round_button);
  }
}


void DrawLabel(TLabel *Alabel) {
  if (Alabel->Visible == 1) {
    TFT_Set_Font(Alabel->FontName, Alabel->Font_Color, FO_HORIZONTAL);
    TFT_Write_Text(Alabel->Caption, Alabel->Left, Alabel->Top);
  }
}

static void DrawLabels() {
  int i;
  TLabel *local_label;

  for ( i = 0 ; i < CurrentScreen->LabelsCount ; i++ ) {
    local_label = GetLabel(i);
    DrawLabel(local_label);
  }
}


void DrawBox(TBox *ABox) {
  if (ABox->Visible == 1) {
    TFT_Set_Brush(ABox->Transparent, ABox->Color, ABox->Gradient, ABox->Gradient_Orientation, ABox->Gradient_Start_Color, ABox->Gradient_End_Color);
    TFT_Set_Pen(ABox->Pen_Color, ABox->Pen_Width);
    TFT_Rectangle(ABox->Left, ABox->Top, ABox->Left + ABox->Width - 1, ABox->Top + ABox->Height - 1);
  }
}

static void DrawBoxes() {
  int i;
  TBox *local_box;

  for ( i = 0 ; i < CurrentScreen->BoxesCount ; i++ ) {
    local_box = GetBox(i);
    DrawBox(local_box);
  }
}

void DrawScreen(TScreen *aScreen) {
  unsigned short order;
  unsigned short button_idx;
  TButton *local_button;
  unsigned short round_button_idx;
  TButton_Round *local_round_button;
  unsigned short label_idx;
  TLabel *local_label;
  unsigned short box_idx;
  TBox *local_box;
  order = 0;
  button_idx = 0;
  round_button_idx = 0;
  label_idx = 0;
  box_idx = 0;

  if ((display_width != aScreen->Width) || (display_height != aScreen->Height)) {
    TFT_BLED_Direction = 0;
    TFT_BLED           = 0;
    TFT_Init_ILI9341_8bit(aScreen->Width, aScreen->Height);
    TP_TFT_Init(aScreen->Width, aScreen->Height, 27, 26);    // Initialize touch panel
    TP_TFT_Set_ADC_Threshold(ADC_Threshold);               // Set touch panel ADC threshold
    TFT_Fill_Screen(aScreen->Color);
    display_width = aScreen->Width;
    display_height = aScreen->Height;
    TFT_BLED           = 1;
  }
  else
    TFT_Fill_Screen(aScreen->Color);

  CurrentScreen = aScreen;


  while (order < CurrentScreen->ObjectsCount) {
    if (button_idx < CurrentScreen->ButtonsCount) {
      local_button = GetButton(button_idx);
      if (order == local_button->Order) {
        button_idx++;
        order++;
        DrawButton(local_button);
      }
    }

    if (round_button_idx < CurrentScreen->Buttons_RoundCount) {
      local_round_button = GetRoundButton(round_button_idx);
      if (order == local_round_button->Order) {
        order++;
        round_button_idx++;
        DrawRoundButton(local_round_button);
      }
    }

    if (label_idx < CurrentScreen->LabelsCount) {
      local_label = GetLabel(label_idx);
      if (order == local_label->Order) {
        label_idx++;
        order++;
        DrawLabel(local_label);
      }
    }

    if (box_idx < CurrentScreen->BoxesCount) {
      local_box = GetBox(box_idx);
      if (order == local_box->Order) {
        box_idx++;
        order++;
        DrawBox(local_box);
      }
    }

  }
}

static void Process_TP_Press(unsigned int X, unsigned int Y) {
  int i;
  TButton *local_button;
  TButton *exec_button;
  short button_order;
  TButton_Round *local_round_button;
  TButton_Round *exec_round_button;
  short round_button_order;
  TLabel *local_label;
  TLabel *exec_label;
  short label_order;
  TBox *local_box;
  TBox *exec_box;
  short box_order;

  button_order        = -1;
  round_button_order  = -1;
  label_order         = -1;
  box_order           = -1;

  // Buttons
  for ( i = 0 ; i < CurrentScreen->ButtonsCount ; i++ ) {
    local_button = GetButton(i);
    if (local_button->Active == 1) {
      if (IsInsideObject(X, Y, local_button->Left, local_button->Top,
                         local_button->Width, local_button->Height) == 1) {
        button_order = local_button->Order;
        exec_button = local_button;
      }
    }
  }

  // Buttons with Round Edges
  for ( i = 0 ; i < CurrentScreen->Buttons_RoundCount ; i++ ) {
    local_round_button = GetRoundButton(i);
    if (local_round_button->Active == 1) {
      if (IsInsideObject(X, Y, local_round_button->Left, local_round_button->Top,
                         local_round_button->Width, local_round_button->Height) == 1) {
        round_button_order = local_round_button->Order;
        exec_round_button = local_round_button;
      }
    }
  }

  // Labels
  for ( i = 0 ; i < CurrentScreen->LabelsCount ; i++ ) {
    local_label = GetLabel(i);
    if (local_label->Active == 1) {
      if (IsInsideObject(X, Y, local_label->Left, local_label->Top,
                         local_label->Width, local_label->Height) == 1) {
        label_order = local_label->Order;
        exec_label = local_label;
      }
    }
  }

  // Boxes
  for ( i = 0 ; i < CurrentScreen->BoxesCount ; i++ ) {
    local_box = GetBox(i);
    if (local_box->Active == 1) {
      if (IsInsideObject(X, Y, local_box->Left, local_box->Top,
                         local_box->Width, local_box->Height) == 1) {
        box_order = local_box->Order;
        exec_box = local_box;
      }
    }
  }

  i = -1;
  if (button_order > i)
    i = button_order;
  if (round_button_order > i)
    i = round_button_order;
  if (label_order > i)
    i = label_order;
  if (box_order > i)
    i = box_order;

  if (i != -1) {
    if (i == button_order) {
      if (exec_button->Active == 1) {
        if (exec_button->OnPressPtr != 0) {
          exec_button->OnPressPtr();
          return;
        }
      }
    }

    if (i == round_button_order) {
      if (exec_round_button->Active == 1) {
        if (exec_round_button->OnPressPtr != 0) {
          exec_round_button->OnPressPtr();
          return;
        }
      }
    }

    if (i == label_order) {
      if (exec_label->Active == 1) {
        if (exec_label->OnPressPtr != 0) {
          exec_label->OnPressPtr();
          return;
        }
      }
    }

    if (i == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->OnPressPtr != 0) {
          exec_box->OnPressPtr();
          return;
        }
      }
    }

  }
}

static void Process_TP_Up(unsigned int X, unsigned int Y) {
  int i;
  TButton *local_button;
  TButton *exec_button;
  short button_order;
  TButton_Round *local_round_button;
  TButton_Round *exec_round_button;
  short round_button_order;
  TLabel *local_label;
  TLabel *exec_label;
  short label_order;
  TBox *local_box;
  TBox *exec_box;
  short box_order;

  switch (PressedObjectType) {
    // Button
    case 0: {
      if (PressedObject != 0) {
        exec_button = (TButton*)PressedObject;
        if (exec_button->PressColEnabled == 1) {
          TFT_Set_Brush(exec_button->Transparent, exec_button->Color, exec_button->Gradient, exec_button->Gradient_Orientation, exec_button->Gradient_Start_Color, exec_button->Gradient_End_Color);
          TFT_Set_Pen(exec_button->Pen_Color, exec_button->Pen_Width);
          TFT_Rectangle(exec_button->Left, exec_button->Top, exec_button->Left + exec_button->Width - 1, exec_button->Top + exec_button->Height - 1);
          TFT_Set_Font(exec_button->FontName, exec_button->Font_Color, FO_HORIZONTAL);
          TFT_Write_Text_Return_Pos(exec_button->Caption, exec_button->Left, exec_button->Top);
          TFT_Write_Text(exec_button->Caption, (exec_button->Left + ((exec_button->Width - caption_length) / 2)), (exec_button->Top + ((exec_button->Height - caption_height) / 2)));
        }
        break;
      }
      break;
    }
    // Round Button
    case 1: {
      if (PressedObject != 0) {
        exec_round_button = (TButton_Round*)PressedObject;
        if (exec_round_button->PressColEnabled == 1) {
          TFT_Set_Brush(exec_round_button->Transparent, exec_round_button->Color, exec_round_button->Gradient, exec_round_button->Gradient_Orientation,
                        exec_round_button->Gradient_Start_Color, exec_round_button->Gradient_End_Color);
          TFT_Set_Pen(exec_round_button->Pen_Color, exec_round_button->Pen_Width);
          if (exec_round_button->Height > exec_round_button->Width)
            TFT_Rectangle_Round_Edges(exec_round_button->Left + 1, exec_round_button->Top + 1,
                                      exec_round_button->Left + exec_round_button->Width - 2,
                                      exec_round_button->Top + exec_round_button->Height - 2, (exec_round_button->Width / 4));
          else if (exec_round_button->Width > exec_round_button->Height)
            TFT_Rectangle_Round_Edges(exec_round_button->Left + 1, exec_round_button->Top + 1,
                                      exec_round_button->Left + exec_round_button->Width - 2,
                                      exec_round_button->Top + exec_round_button->Height - 2, (exec_round_button->Height / 4));
          TFT_Set_Font(exec_round_button->FontName, exec_round_button->Font_Color, FO_HORIZONTAL);
          TFT_Write_Text_Return_Pos(exec_round_button->Caption, exec_round_button->Left, exec_round_button->Top);
          TFT_Write_Text(exec_round_button->Caption, (exec_round_button->Left + ((exec_round_button->Width - caption_length) / 2)),
                        (exec_round_button->Top + ((exec_round_button->Height - caption_height) / 2)));
        }
        break;
      }
      break;
    }
    // Box
    case 6: {
      if (PressedObject != 0) {
        exec_box = (TBox*)PressedObject;
        if (exec_box->PressColEnabled == 1) {
          TFT_Set_Brush(exec_box->Transparent, exec_box->Color, exec_box->Gradient, exec_box->Gradient_Orientation, exec_box->Gradient_Start_Color, exec_box->Gradient_End_Color);
          TFT_Set_Pen(exec_box->Pen_Color, exec_box->Pen_Width);
          TFT_Rectangle(exec_box->Left, exec_box->Top, exec_box->Left + exec_box->Width - 1, exec_box->Top + exec_box->Height - 1);
        }
        break;
      }
      break;
    }
  }

  button_order        = -1;
  round_button_order  = -1;
  label_order         = -1;
  box_order           = -1;

  // Buttons
  for ( i = 0 ; i < CurrentScreen->ButtonsCount ; i++ ) {
    local_button = GetButton(i);
    if (local_button->Active == 1) {
      if (IsInsideObject(X, Y, local_button->Left, local_button->Top,
                         local_button->Width, local_button->Height) == 1) {
        button_order = local_button->Order;
        exec_button = local_button;
      }
    }
  }

  // Buttons with Round Edges
  for ( i = 0 ; i < CurrentScreen->Buttons_RoundCount ; i++ ) {
    local_round_button = GetRoundButton(i);
    if (local_round_button->Active == 1) {
      if (IsInsideObject(X, Y, local_round_button->Left, local_round_button->Top,
                         local_round_button->Width, local_round_button->Height) == 1) {
        round_button_order = local_round_button->Order;
        exec_round_button = local_round_button;
      }
    }
  }

  // Labels
  for ( i = 0 ; i < CurrentScreen->LabelsCount ; i++ ) {
    local_label = GetLabel(i);
    if (local_label->Active == 1) {
      if (IsInsideObject(X, Y, local_label->Left, local_label->Top,
                         local_label->Width, local_label->Height) == 1) {
        label_order = local_label->Order;
        exec_label = local_label;
      }
    }
  }

  // Boxes
  for ( i = 0 ; i < CurrentScreen->BoxesCount ; i++ ) {
    local_box = GetBox(i);
    if (local_box->Active == 1) {
      if (IsInsideObject(X, Y, local_box->Left, local_box->Top,
                         local_box->Width, local_box->Height) == 1) {
        box_order = local_box->Order;
        exec_box = local_box;
      }
    }
  }

  i = -1;
  if (button_order > i)
    i = button_order;
  if (round_button_order > i)
    i = round_button_order;
  if (label_order > i)
    i = label_order;
  if (box_order > i)
    i = box_order;

  if (i != -1) {
  // Buttons
    if (i == button_order) {
      if (exec_button->Active == 1) {
        if (exec_button->OnUpPtr != 0)
          exec_button->OnUpPtr();
        if (PressedObject == (void *)exec_button)
          if (exec_button->OnClickPtr != 0)
            exec_button->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  // Buttons with Round Edges
    if (i == round_button_order) {
      if (exec_round_button->Active == 1) {
        if (exec_round_button->OnUpPtr != 0)
          exec_round_button->OnUpPtr();
        if (PressedObject == (void *)exec_round_button)
          if (exec_round_button->OnClickPtr != 0)
            exec_round_button->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  // Labels
    if (i == label_order) {
      if (exec_label->Active == 1) {
        if (exec_label->OnUpPtr != 0)
          exec_label->OnUpPtr();
        if (PressedObject == (void *)exec_label)
          if (exec_label->OnClickPtr != 0)
            exec_label->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  // Boxes
    if (i == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->OnUpPtr != 0)
          exec_box->OnUpPtr();
        if (PressedObject == (void *)exec_box)
          if (exec_box->OnClickPtr != 0)
            exec_box->OnClickPtr();
        PressedObject = 0;
        PressedObjectType = -1;
        return;
      }
    }

  }
  PressedObject = 0;
  PressedObjectType = -1;
}

static void Process_TP_Down(unsigned int X, unsigned int Y) {
  int i;
  TButton *local_button;
  TButton *exec_button;
  short button_order;
  TButton_Round *local_round_button;
  TButton_Round *exec_round_button;
  short round_button_order;
  TLabel *local_label;
  TLabel *exec_label;
  short label_order;
  TBox *local_box;
  TBox *exec_box;
  short box_order;

  button_order        = -1;
  round_button_order  = -1;
  label_order         = -1;
  box_order           = -1;

  // Buttons
  for ( i = 0 ; i < CurrentScreen->ButtonsCount ; i++ ) {
    local_button = GetButton(i);
    if (local_button->Active == 1) {
      if (IsInsideObject(X, Y, local_button->Left, local_button->Top,
                         local_button->Width, local_button->Height) == 1) {
        button_order = local_button->Order;
        exec_button = local_button;
      }
    }
  }

  // Buttons with Round Edges
  for ( i = 0 ; i < CurrentScreen->Buttons_RoundCount ; i++ ) {
    local_round_button = GetRoundButton(i);
    if (local_round_button->Active == 1) {
      if (IsInsideObject(X, Y, local_round_button->Left, local_round_button->Top,
                         local_round_button->Width, local_round_button->Height) == 1) {
        round_button_order = local_round_button->Order;
        exec_round_button = local_round_button;
      }
    }
  }

  // Labels
  for ( i = 0 ; i < CurrentScreen->LabelsCount ; i++ ) {
    local_label = GetLabel(i);
    if (local_label->Active == 1) {
      if (IsInsideObject(X, Y, local_label->Left, local_label->Top,
                         local_label->Width, local_label->Height) == 1) {
        label_order = local_label->Order;
        exec_label = local_label;
      }
    }
  }

  // Boxes
  for ( i = 0 ; i < CurrentScreen->BoxesCount ; i++ ) {
    local_box = GetBox(i);
    if (local_box->Active == 1) {
      if (IsInsideObject(X, Y, local_box->Left, local_box->Top,
                         local_box->Width, local_box->Height) == 1) {
        box_order = local_box->Order;
        exec_box = local_box;
      }
    }
  }

  i = -1;
  if (button_order > i)
    i = button_order;
  if (round_button_order > i)
    i = round_button_order;
  if (label_order > i)
    i = label_order;
  if (box_order > i)
    i = box_order;
  if (i != -1) {
    if (i == button_order) {
      if (exec_button->Active == 1) {
        if (exec_button->PressColEnabled == 1) {
          TFT_Set_Brush(exec_button->Transparent, exec_button->Press_Color, exec_button->Gradient, exec_button->Gradient_Orientation, exec_button->Gradient_End_Color, exec_button->Gradient_Start_Color);
          TFT_Set_Pen(exec_button->Pen_Color, exec_button->Pen_Width);
          TFT_Rectangle(exec_button->Left, exec_button->Top, exec_button->Left + exec_button->Width - 1, exec_button->Top + exec_button->Height - 1);
          TFT_Set_Font(exec_button->FontName, exec_button->Font_Color, FO_HORIZONTAL);
          TFT_Write_Text_Return_Pos(exec_button->Caption, exec_button->Left, exec_button->Top);
          TFT_Write_Text(exec_button->Caption, (exec_button->Left + ((exec_button->Width - caption_length) / 2)), (exec_button->Top + ((exec_button->Height - caption_height) / 2)));
        }
        PressedObject = (void *)exec_button;
        PressedObjectType = 0;
        if (exec_button->OnDownPtr != 0) {
          exec_button->OnDownPtr();
          return;
        }
      }
    }

    if (i == round_button_order) {
      if (exec_round_button->Active == 1) {
        if (exec_round_button->PressColEnabled == 1) {
          TFT_Set_Brush(exec_round_button->Transparent, exec_round_button->Press_Color, exec_round_button->Gradient, exec_round_button->Gradient_Orientation,
                        exec_round_button->Gradient_End_Color, exec_round_button->Gradient_Start_Color);
          TFT_Set_Pen(exec_round_button->Pen_Color, exec_round_button->Pen_Width);
          if (exec_round_button->Height > exec_round_button->Width)
            TFT_Rectangle_Round_Edges(exec_round_button->Left + 1, exec_round_button->Top + 1,
                                      exec_round_button->Left + exec_round_button->Width - 2,
                                      exec_round_button->Top + exec_round_button->Height - 2, (exec_round_button->Width / 4));
          else if (exec_round_button->Width > exec_round_button->Height)
            TFT_Rectangle_Round_Edges(exec_round_button->Left + 1, exec_round_button->Top + 1,
                                      exec_round_button->Left + exec_round_button->Width - 2,
                                      exec_round_button->Top + exec_round_button->Height - 2, (exec_round_button->Height / 4));
          TFT_Set_Font(exec_round_button->FontName, exec_round_button->Font_Color, FO_HORIZONTAL);
          TFT_Write_Text_Return_Pos(exec_round_button->Caption, exec_round_button->Left, exec_round_button->Top);
          TFT_Write_Text(exec_round_button->Caption, (exec_round_button->Left + ((exec_round_button->Width - caption_length) / 2)),
                        (exec_round_button->Top + ((exec_round_button->Height - caption_height) / 2)));
        }
        PressedObject = (void *)exec_round_button;
        PressedObjectType = 1;
        if (exec_round_button->OnDownPtr != 0) {
          exec_round_button->OnDownPtr();
          return;
        }
      }
    }

    if (i == label_order) {
      if (exec_label->Active == 1) {
        PressedObject = (void *)exec_label;
        PressedObjectType = 2;
        if (exec_label->OnDownPtr != 0) {
          exec_label->OnDownPtr();
          return;
        }
      }
    }

    if (i == box_order) {
      if (exec_box->Active == 1) {
        if (exec_box->PressColEnabled == 1) {
          TFT_Set_Brush(exec_box->Transparent, exec_box->Press_Color, exec_box->Gradient, exec_box->Gradient_Orientation, exec_box->Gradient_End_Color, exec_box->Gradient_Start_Color);
          TFT_Set_Pen(exec_box->Pen_Color, exec_box->Pen_Width);
          TFT_Rectangle(exec_box->Left, exec_box->Top, exec_box->Left + exec_box->Width - 1, exec_box->Top + exec_box->Height - 1);
        }
        PressedObject = (void *)exec_box;
        PressedObjectType = 6;
        if (exec_box->OnDownPtr != 0) {
          exec_box->OnDownPtr();
          return;
        }
      }
    }

  }
}

void Check_TP() {
  if (TP_TFT_Press_Detect()) {
    // After a PRESS is detected read X-Y and convert it to Display dimensions space
    if (TP_TFT_Get_Coordinates(&Xcoord, &Ycoord) == 0) {
      Process_TP_Press(Xcoord, Ycoord);
      if (PenDown == 0) {
        PenDown = 1;
        Process_TP_Down(Xcoord, Ycoord);
      }
    }
  }
  else if (PenDown == 1) {
    PenDown = 0;
    Process_TP_Up(Xcoord, Ycoord);
  }
}

void Start_TP() {
  InitializeTouchPanel();

  // You can get calibration constants using touch panel calibration example
  TFT_Fill_Screen(0);
  Calibrate();
  TFT_Fill_Screen(0);

  InitializeObjects();
  display_width = Screen2.Width;
  display_height = Screen2.Height;
  DrawScreen(&Screen2);
}