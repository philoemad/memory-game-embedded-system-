//Team
//Name:philopater Emad DEMIAN     ID;20160179
//Name:Mahmoud kamal Ali          ID;20140253
//Name:Ahmed essam eldin mohamed   ID:20150023
//Name:Hassan Adel Hassan          ID:20160093
#include <xc.h>
#include  <pic18f4550.h>
#include <stdbool.h>
//up 8 down 2 right 6 left 4 (keys i keybad)
//logic of game i store in counter name count rigth and lift by plus it and - it when press write or left from keybad and i store up and down when press up and down from key pad  to know the exact place
// after store them i go to it from lcd cmd by two if condition t check this variable (updown) as up start with 0x80 and down 0xc0 by flags call 'u' and down flag call 'd'
// when press key 5 the logic of game start it count the clicks in variable clickcount as after 2 click if 2 picture or figure is true increase the score and store previouslocation that store left and right and orivous up_down variables to staore exact location of previous location and compare it to cuurent if true go to this location and witre 0x00 to remove it from lcd if not write oxff to return it to lcd

#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define EN PORTCbits.RC2

#define R1 PORTBbits.RB0
#define R2 PORTBbits.RB1
#define R3 PORTBbits.RB2
#define R4 PORTBbits.RB3

#define C1 PORTBbits.RB4
#define C2 PORTBbits.RB5
#define C3 PORTBbits.RB6
#define C4 PORTBbits.RB7



void lcdcmd(unsigned char);
void lcddata(unsigned char);
void delay(void);
unsigned char col1(unsigned char);
unsigned char col2(unsigned char);
unsigned char col3(unsigned char);
//unsigned char col4(unsigned char);
static  char up_down = 'u'; //to save in it where am i in the 2 line of 16 * 2 lcd up or down i use it with the return of the functions ex: col 1 2 3 4 to know the exact location
static unsigned char previousshape = '0';//i use it in the logic of the game to know the shape the user press it in the first time to compare it with the recent to know if true then increase score
static unsigned char clickcount = 0x00;// i use it to count the click to set the logic of game at second click as you remmber only two shapes
static unsigned char previouslocation = 0x00;//previous location of the shape the user press it wehther right or left
static unsigned char previousupdown = 0x80;// whether previous location up or down ;
static unsigned char score = 0x30;
unsigned char shapeline1[16] = "abcdibcdefghefgh";//first line shapes of lcd to choose from it in game as lcd 16*2
unsigned char shapeline2[16] = "ajklmnopijklmnop";//second line shape of lcd to choose from it in game

 
unsigned char col1(unsigned char count) {

    R1 = R2 = R3 = R4 = 1;
// R2,C1 : num 4 to move left

    R1 = 1;// to set row high and the col to know exact key pressed
    R2 = 0;
    if (C1 == 0) {
        while (C1 == 0);
        if (count == 0x00) {
            count = count;     // if i am in first pos don't - it
        } else {
            count = count - 0x1;   //decrease count to know where i am write or left as this key move it to left
        }
        unsigned char up_down_pointer = 0x80;
        if (up_down == 'u') {         //check up as lcd 16*2 and first row start with 0x80 command 
            up_down_pointer = 0x80;
            unsigned char x = up_down_pointer + count;

            lcdcmd(x);

        } else if (up_down == 'd') {  //check up as lcd 16*2 and first row start with 0xc0 command 
            up_down_pointer = 0xc0;
            unsigned char x = up_down_pointer + count;

            lcdcmd(x);

        }




    }
    //R4,C1  : ON/OFF for new Game and display message 
    R2 = 1;
    R4 = 0;
    if (C1 == 0) {
        while (C1 == 0);

        lcddata('W');
        lcddata('e');
        lcddata('l');
        lcddata('c');
        lcddata('o');
        lcddata('m');
        lcddata('e');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcdcmd(0x38);
        lcdcmd(0xc0);
        lcddata('N');
        lcddata('e');
        lcddata('w');
        lcddata(' ');
        lcddata('G');
        lcddata('a');
        lcddata('m');
        lcddata('e');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcdcmd(0x80); // Set Cursor Position To Address Of First Line Start
        // Set Cursor Position To Address Of First Line Start
        // Filled Shape Address Is 0xFF
        for (int i = 0; i < 10000; ++i) // Just Waiting A Bit For The Message To Be Read By User
        {
            delay();
        }
        for (int y = 0; y < 16; y++) {
            lcddata(0xff);
        } // Filled Shape Address Is 0xFF
        lcdcmd(0x38);
        lcdcmd(0xc0); // Set Cursor Position To Address Of Second Line Start
        for (int y = 0; y < 16; y++) {
            lcddata(0xff);
        }

        lcdcmd(0x80);
        
        up_down = 'u';
        previousshape = '0';
        clickcount = 0x00;
        previouslocation = 0x00;
        previousupdown = 0x80;
        score = 0x30;
        count=0x00;

    }
    R4 = 1;


    return count;

}


unsigned char col2(unsigned char count) {
//num 8 : move up      R1,C2
    R1 = R2 = R3 = R4 = 1;
    R1 = 0;
    if (C2 == 0) {

        while (C2 == 0);
        unsigned char x = 0x80 + count; // to move the cursor to exact pos up as we store right and left in count and he press 8 so we make it first line which start with 0x80 +count to know exact location of up
        lcdcmd(0x38);
        lcdcmd(x);
        up_down = 'u';// store where am i now (up)  for next postion

    }
// num 5 : select specific location   R2,C2 
    R1 = 1;
    R2 = 0;
    if (C2 == 0) {

        while (C2 == 0);
        if (up_down == 'u') {    //know where am i up or down 
            if (clickcount == 0x00) { // this condition have first click to choose the shape and store it 
                previousshape = shapeline1[count]; // store shape for second click to compare
                clickcount = clickcount + 0x01; 
                previouslocation = count;
                previousupdown = 0x80;
                lcddata(shapeline1[count]);
                lcdcmd(0x80+count);
            } else if (clickcount == 0x01) { // this condition have second click logic if the second shape he choose = first shape increase the score and reset the variables previous location and updown for next try from user
                if (previousshape == shapeline1[count]) {
                    clickcount = 0x00;
                    previousshape = '0';
                    lcddata(0x00);
                    unsigned char xs = previousupdown + previouslocation;
                    lcdcmd(xs);
                    lcddata(0x00);
                    lcdcmd(xs);
                    lcdcmd(0x80+count);
                     score = score + 0x01;
                    
                }
                else if (previousshape != shapeline1[count]) {
                    clickcount = 0x00;
                    previousshape = '0';
                    unsigned char xs = previousupdown + previouslocation;
                    lcdcmd(xs);
                    lcddata(0xff);
                    lcdcmd(xs);
                    lcdcmd(0x80+count);
                }

            }
        } else if (up_down == 'd') { // same logic for up but for next line of lcd as lcd =16*2
            if (clickcount == 0x00) {
                previousshape = shapeline2[count];
                clickcount = clickcount + 0x01;
                previouslocation = count;
                previousupdown = 0xc0;
                lcddata(shapeline2[count]);
                lcdcmd(0xc0+count);
            } else if (clickcount == 0x01) {
                if (previousshape == shapeline2[count]) {
                    clickcount = 0x00;
                    previousshape = '0';
                    lcddata(0x00);
                    unsigned char xs = previousupdown + previouslocation;
                    lcdcmd(xs);
                    lcddata(0x00);
                    lcdcmd(xs);
                    score = score + 0x01;
                    lcdcmd(0xc0+count);
                }
                else if (previousshape != shapeline2[count]) {
                    clickcount = 0;
                    previousshape = '0';
                    unsigned char xs = previousupdown + previouslocation;
                    lcdcmd(xs);
                    lcddata(0xff);
                    lcdcmd(xs);
                    lcdcmd(0xc0+count);
                }

            }
        }

    }
    R2 = 1;

    R3 = 0;
// num 2 : move down   R3,C2
    if (C2 == 0) {

        while (C2 == 0);
        unsigned char x = 0xc0 + count; // to move the cursor to exact pos down as we store right and left in count and he press 2 so we make it second line which start with 0xc0 +count to know exact location of down
        lcdcmd(0x38);
        lcdcmd(x);
        up_down = 'd';// store where am i now  (down) for next postion

    }

    R3 = 1;
    return count;

}

unsigned char col3(unsigned char count) {
//num 6  to move right     R2,C3

    R1 = R2 = R3 = R4 = 1;

    R2 = 0;

    if (C3 == 0) {

        while (C3 == 0);
        count = count + 0x1;
        unsigned char up_down_pointer = 0x80;
        if (up_down == 'u') {
            up_down_pointer = 0x80;
            unsigned char x = up_down_pointer + count;

            lcdcmd(x);

        } else if (up_down == 'd') {
            up_down_pointer = 0xc0;
            unsigned char x = up_down_pointer + count;

            lcdcmd(x);

        }
    }
// =  to end game R4,C3
    //show the score 
    R2 = 1;
    R4 = 0;
    if (C3 == 0) {

        while (C3 == 0);
        up_down = 0xff;
        previousshape = '0'; // reset this variable for new game
        clickcount = 0x00;
        previouslocation = 0x00;
        previousupdown = 0x80;
        //score = 0x30;
        lcddata(' ');
        lcddata('E');
        lcddata('n');
        lcddata('d');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata('G');
        lcddata('a');
        lcddata('m');
        lcddata('e');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcdcmd(0x38);
        lcdcmd(0xc0);
        lcddata('S');
        lcddata('c');
        lcddata('o');
        lcddata('r');
        lcddata('e');
        lcddata(' ');
        lcddata(':');
        lcddata(' ');
        lcddata(' ');
        lcddata(score);
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
        lcddata(' ');
       
        count=0x00;
    }
    R4 = 1;

    return count;
}

void delay() {
    int counter = 0;
    for (counter = 0; counter < 1; counter++) {
        ;
    }
}

void lcdcmd(unsigned char a1) {

    LATD = a1;
    RS = 0;
    RW = 0;
    EN = 0;
    delay();
    EN = 1;

}

void lcddata(unsigned char a2) {

    LATD = a2;
    RS = 1;
    RW = 0;
    EN = 0;
    delay();
    EN = 1;

}

void main(void) {
    ADCON1 = 0X0F;
    TRISD = 0X00;
    TRISC = 0X00;
    TRISB = 0XF0;
    PORTC = 0X00;
    LATD = 0X00;



    INTCON2bits.RBPU = 0;// set pull up and down for the board as this kind have built in pull up and down

    lcdcmd(0x38);
    lcdcmd(0x0e);
    lcdcmd(0x01);
    lcdcmd(0x80);

    C1 = C2 = C3 = C4 = 1;
    unsigned char counter = 0x0;
    while (1) {
        R1 = R2 = R3 = R4 = 0;
        while (C1 == 1 && C2 == 1 && C3 == 1 && C4 == 1);
        if (C1 == 0) {
            counter = col1(counter);
        }
        if (C2 == 0) {
            counter = col2(counter);
        }
        if (C3 == 0) {
            counter = col3(counter);
        }


    }

    return;
}