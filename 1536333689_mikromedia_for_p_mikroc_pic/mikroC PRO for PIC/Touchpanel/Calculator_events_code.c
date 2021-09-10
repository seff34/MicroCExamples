#include "Calculator_objects.h"
#include "Calculator_resources.h"

//--------------------- User code ---------------------//
TLabel *label_selected;
char temp_label[20];
float res = 0;

void ClearLabel( Tlabel *_label) {
  TFT_Set_Font(_label->FontName, Box3.Color, FO_HORIZONTAL);
  TFT_Write_Text(_label->Caption, _label->Left, _label->Top);
  strcpy(_label->Caption, " ");
}

void ClearLabels() {
  label_selected = &Label1;
  ClearLabel(&Label1);
  ClearLabel(&Label2);
  ClearLabel(&Label3);
  ClearLabel(&Label6);
}

void Set_Defaults() {
  ClearLabels();
}
//----------------- End of User code ------------------//

// Event Handlers

void Button16Click() {
unsigned int count;

  // Delete
  count = strlen(label_selected->Caption);
  if (count > 1) {
    if (label_selected == &Label1) {
      strcpy(temp_label, Label1_Caption);
      ClearLabel(&Label1);
      temp_label[count-1] = 0;
      strcpy(Label1_Caption, temp_label);
      DrawLabel(&Label1);
    }
    else
      if (label_selected == &Label2) {
        strcpy(temp_label, Label2_Caption);
        ClearLabel(&Label2);
        temp_label[count-1] = 0;
        strcpy(Label2_Caption, temp_label);
        DrawLabel(&Label2);
      }
      else
        if (label_selected == &Label3) {
          strcpy(temp_label, Label3_Caption);
          ClearLabel(&Label3);
          temp_label[count-1] = 0;
          strcpy(Label3_Caption, temp_label);
          DrawLabel(&Label3);
        }
  }
  else {
    if (label_selected == &Label1) {
      strcpy(Label1_Caption, " ");
      DrawLabel(&Label1);
    }
    else
      if (label_selected == &Label2) {
        strcpy(Label2_Caption, " ");
        DrawLabel(&Label2);
        label_selected = &Label1;
      }
      else
        if (label_selected == &Label3) {
          strcpy(Label3_Caption, " ");
          DrawLabel(&Label3);
          label_selected = &Label2;
        }
  }
}

void Button17Click() {
  // Clear
  ClearLabels();
}

void Button12Click() {
  // Divide
  ClearLabel(&Label2);
  label_selected = &Label2;
  strcpy(label_selected->Caption, " /");
  DrawLabel(label_selected);
  label_selected = &Label3;
}

void Button13Click() {
  // Multiply
  ClearLabel(&Label2);
  label_selected = &Label2;
  strcpy(label_selected->Caption, " *");
  DrawLabel(label_selected);
  label_selected = &Label3;
}

void Button19Click() {
  // Seven
  if (label_selected != 0) {
    strcat(label_selected->Caption, "7");
    DrawLabel(label_selected);
  }
}

void Button7Click() {
  // Eight
  if (label_selected != 0) {
    strcat(label_selected->Caption, "8");
    DrawLabel(label_selected);
  }
}

void Button8Click() {
  // Nine
  if (label_selected != 0) {
    strcat(label_selected->Caption, "9");
    DrawLabel(label_selected);
  }
}

void Button14Click() {
  // Subtract
  ClearLabel(&Label2);
  label_selected = &Label2;
  strcpy(label_selected->Caption, " -");
  DrawLabel(label_selected);
  label_selected = &Label3;
}

void Button1Click() {
  // Four
  if (label_selected != 0) {
    strcat(label_selected->Caption, "4");
    DrawLabel(label_selected);
  }
}

void Button2Click() {
  // Five
  if (label_selected != 0) {
    strcat(label_selected->Caption, "5");
    DrawLabel(label_selected);
  }
}

void Button9Click() {
  // Six
  if (label_selected != 0) {
    strcat(label_selected->Caption, "6");
    DrawLabel(label_selected);
  }
}

void Button15Click() {
  // Add
  ClearLabel(&Label2);
  label_selected = &Label2;
  strcpy(label_selected->Caption, " +");
  DrawLabel(label_selected);
  label_selected = &Label3;
}

void Button5Click() {
  // One
  if (label_selected != 0) {
    strcat(label_selected->Caption, "1");
    DrawLabel(label_selected);
  }
}

void Button3Click() {
  // Two
  if (label_selected != 0) {
    strcat(label_selected->Caption, "2");
    DrawLabel(label_selected);
  }
}

void Button10Click() {
  // Three
  if (label_selected != 0) {
    strcat(label_selected->Caption, "3");
    DrawLabel(label_selected);
  }
}

void Button6Click() {
  // Zero
  if (label_selected != 0) {
    strcat(label_selected->Caption, "0");
    DrawLabel(label_selected);
  }
}

void Button4Click() {
char temp[20] = " -";
  // Change sign
  if ((label_selected != 0) && (label_selected != &Label2)) {
    strcpy(temp_label, label_selected->Caption);
    ltrim(temp_label);
    switch (temp_label[0]) {
      case '-' : {
        temp_label[0] = " ";
        break;
      }
      default : {
        strcat(temp, temp_label);
        strcpy(temp_label, temp);
        break;
      }
    }

    ClearLabel(label_selected);
    strcpy(label_selected->Caption, temp_label);
    DrawLabel(label_selected);
  }
}

void Button11Click() {
  // Decimal point
  if ((label_selected != 0) && (label_selected != &Label2)) {
    strcat(label_selected->Caption, ".");
    DrawLabel(label_selected);
  }
}

void Button18Click() {
  // Calculate
int first_operand, second_operand;
float result;
char first_operand_str[6];
char second_operand_str[6];
unsigned short counter, i;
char temp[5] = " ";
  // Calculate
  // -32768 .. 32767
  first_operand = 0;
  second_operand = 0;
  i = 0;
  for (counter = 1; counter < 7; counter++) {
    first_operand_str[i]  = Label1_Caption[counter];
    second_operand_str[i] = Label3_Caption[counter];
    i++;
  }

  first_operand = atoi(first_operand_str);
  second_operand = atoi(second_operand_str);
  ClearLabel(&Label6);
  strcpy(temp_label, Label2.Caption);
  ltrim(temp_label);
  
  switch (temp_label[0]) {
    case '+' : {
         result = first_operand + second_operand;
         res = ceil(result);
         IntToStr((int)res, Label6_Caption);
         Ltrim(&Label6_Caption);
         break;
       }
    case '-' : {
         result = (first_operand - second_operand);
         res = ceil(result);
         IntToStr((int)res, Label6_Caption);
         Ltrim(&Label6_Caption);
         break;
       }
    case '*' : {
         result = (first_operand * second_operand);
         res = ceil(result);
         IntToStr((int)res, Label6_Caption);
         Ltrim(&Label6_Caption);
         break;
       }
    case '/': {
         result = (float)first_operand / second_operand;
         FloatToStr(result, Label6_Caption);
         break;
       }
  }
  DrawLabel(&Label6);
}

void ButtonRound1Click() {
  DrawScreen(&Screen1);
  Set_Defaults();
}