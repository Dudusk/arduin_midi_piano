int DIGITAL_START_ADRESS_PIN_BUTTON = 2;

// 12x3 : 36 pins dont 1 pour changer les gammes
int buttonPin[36] = {0};
int buttonState[36] = {0};

//Switch octave button
//const int switchingOctaveButton = 1; // ? A voir (Sinon le last possible)
//int switchingOctaveButtonState = 0;
//int switchingOctaveButtonState_OLD = 0;

const int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
const int noteON = 144;//144 = 10010000 in binary, note on command
const int noteOFF = 128;//128 = 10000000 in binary, note off command


// Tableaux des octaves
int octave [12] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
int octave0 [12] = {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
int octave1 [12] = {24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
int octave2 [12] = {36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47};
int octave3 [12] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59};
int octave4 [12] = {60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71};
int octave5 [12] = {72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83};
int octave6 [12] = {84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95};
int octave7 [12] = {96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107};
int octave8 [12] = {108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119};
int octave9 [12] = {120, 121, 122, 123, 124, 125, 126, 127, 0, 0, 0, 0};

void setup() {
    Serial.begin(115200);
    // Serial.begin(31250); // => To test
    
    for(int i = 0; i < sizeof(buttonPin); i++){
        buttonPin[i] = DIGITAL_START_ADRESS_PIN_BUTTON;
        pinMode(buttonPin[i], INPUT);
        DIGITAL_START_ADRESS_PIN_BUTTON++;
    }
}

// Le problème est la note jouée.

void loop() {

    for(int i = 0; i < sizeof(buttonPin); i++){
        //Lecture de pin i
        buttonState[i] = digitalRead(buttonPin[i]);

        switch (i){
            case 0 ... 11 :
                // Octave
                // La note c'est i puisque octave est un tableau ente 0 et 11
                // On envoit le tableau
                sendNote(i, octave);
                break;
            case 12 ... 23 :
                // Octave1 => test avec -12 (y)
                sendNote(i-12, octave0);
                break;
            case 24 ... 35 :
                // Octave2 => test avec -24 (y) etc
                sendNote(i-24, octave1);
                break;
        }

        
    }
}


void sendNote(int noteSend, int octaveSend[]){
    
    if (buttonState[noteSend] == HIGH) {
        // Appuyé
        MIDImessage(noteON, octaveSend[noteSend], velocity);
    } else {
        // Relâché
        MIDImessage(noteOFF, octaveSend[noteSend], velocity);
    }
}


void octaveSwitcher(){

}


/** Fonction d'envoie de données MIDI */
void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
    Serial.write(command);//send note on or note off command 
    Serial.write(MIDInote);//send pitch data
    Serial.write(MIDIvelocity);//send velocity data
}