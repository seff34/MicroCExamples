typedef struct Screen TScreen;

typedef struct  Image {
  TScreen       *OwnerScreen;
  char          Order;
  unsigned int  Left;
  unsigned int  Top;
  unsigned int  Width;
  unsigned int  Height;
  unsigned int  PictureWidth;
  unsigned int  PictureHeight;
  const char    *Picture_Name;
  char          Visible;
  char          Active;
  char          AutoSize;
  char          Picture_Type;
  char          Picture_Ratio;
  void          (*OnUpPtr)();
  void          (*OnDownPtr)();
  void          (*OnClickPtr)();
  void          (*OnPressPtr)();
} TImage;

struct Screen {
  unsigned int           Color;
  unsigned int           Width;
  unsigned int           Height;
  unsigned short         ObjectsCount;
  unsigned int           ImagesCount;
  TImage                 **Images;
  unsigned int           BoxesCount;

  unsigned int           LinesCount;

};

extern   TScreen                Screen1;
extern   TImage                 Image1;

/////////////////////////////////
// Caption variables Declarations
/////////////////////////////////

void DrawScreen(TScreen *aScreen);
void DrawImage(TImage *Aimage);
void Start_TP();