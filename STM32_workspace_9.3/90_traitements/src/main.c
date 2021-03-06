#include<stdio.h>
#include "leds_control.h"

typedef struct{
	int RValue;
	int GValue;
	int BValue;
}RGB;

const RGB Red={255,0,0};
const RGB Green={0,255,0};
const RGB Blue={0,0,255};
const RGB White={255,255,255};
const RGB Purple={255,0,255};
const RGB Yellow={255,255,0};
const RGB Black={0,0,0};


void SetLedLine(RGB **TabLine, int TabSize){
	for (int line=0; line<TabSize; line++){
		for(int col = 0; col < TabSize; col++){
			setLedColor("R", line+1, col+1, TabLine[line][col].RValue, TabLine[line][col].GValue, TabLine[line][col].BValue, "\n");
		}
	}
}

void SetLedOneColor( int Line, RGB Color, int SizeLine){
	for (int col = 0; col < SizeLine; col++){
		setLedColor("R", Line, col+1, Color.RValue, Color.GValue, Color.BValue, "\n");
	}
}

void ResetAllBlack(){
	int Sizeline = 7;
	SetLedOneColor(1,Black, Sizeline);
	SetLedOneColor(2,Black, Sizeline);
	SetLedOneColor(3,Black, Sizeline);
	SetLedOneColor(4,Black, Sizeline);
	SetLedOneColor(5,Black, Sizeline);
	SetLedOneColor(6,Black, Sizeline);
	SetLedOneColor(7,Black, Sizeline);
}

void compteur(int TabSize){
	for(int compteur=9 ; compteur>=0; compteur--){
		if (compteur==9){
			RGB bckgrd = Black;
			RGB number = Red;
			RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,number,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==8){
			RGB bckgrd = Black;
			RGB number = White;
			RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,number,bckgrd};
			RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==7){
			RGB bckgrd = Black;
			RGB number = Green;
			RGB tabline_1[7]={bckgrd,number,number,number,number,number,bckgrd};
			RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_7[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==6){
			RGB bckgrd = Black;
			RGB number = Blue;
			RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_4[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==5){
			RGB bckgrd = Black;
			RGB number = Yellow;
			RGB tabline_1[7]={bckgrd,number,number,number,number,number,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_4[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==4){
			RGB bckgrd = Black;
			RGB number = Purple;
			RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,number,number,bckgrd,bckgrd};
			RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_4[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==3){
			RGB bckgrd = Black;
			RGB number = White;
			RGB tabline_1[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==2){
			RGB bckgrd = Black;
			RGB number = Green;
			RGB tabline_1[7]={bckgrd,number,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,bckgrd,bckgrd};
			RGB tabline_7[7]={bckgrd,number,number,number,number,number,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==1){
			RGB bckgrd = Black;
			RGB number = Blue;
			RGB tabline_1[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,bckgrd,bckgrd,number,number,bckgrd,bckgrd};
			RGB tabline_3[7]={bckgrd,bckgrd,number,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_4[7]={bckgrd,number,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_5[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_6[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,bckgrd,bckgrd,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		if (compteur==0){
			RGB bckgrd = Black;
			RGB number = Red;
			RGB tabline_1[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB tabline_2[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_3[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_4[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_5[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_6[7]={bckgrd,number,bckgrd,bckgrd,bckgrd,number,bckgrd};
			RGB tabline_7[7]={bckgrd,bckgrd,number,number,number,bckgrd,bckgrd};
			RGB *matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			SetLedLine(matrice,TabSize);
		}
		sleep(3);
	}
}
int main(int argc, char* argv[]){

	//ResetAllBlack();

	int TabSize;
	TabSize = 7;
	compteur(TabSize);

	return 0;
}
