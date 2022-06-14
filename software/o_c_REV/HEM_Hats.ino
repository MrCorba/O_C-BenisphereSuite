// Copyright (c) 2018, Jason Justian
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

class Hats : public HemisphereApplet {
public:

    const char* applet_name() {
        return "Hats";
    }

    void Start() {
        step = 0;
    	max_steps = 15;
        output = 2;
        fire = 1;
        prob = 50;
    }

    void Controller() {
        if (Clock(0)) {
            if (step >= max_steps) step = -1;
            step++;

            int fire;
            if (step == 3 || step == 7 || step == 11 || step == 15) {
                output = 0;
                fire = 1;
            } else {
                output = 1;
                fire = (random(1, 100) <= prob) ? 0 : 1;
            }

            if (fire == 1) {
                ClockOut(output - 1);
            } else {
                output = 2;
            }
        }
       
    }

    void View() {
        gfxHeader("Hats");
        DrawInterface();
    }

    void OnButtonPress() {
        // choice = 1 - choice;
    }

    /* Change the pability */
    void OnEncoderMove(int direction) {
        prob = constrain(prob += direction, 0, 100);
    }

    uint64_t OnDataRequest() {
        uint64_t data = 0;
        // Pack(data, PackLocation {0,7}, p);
        return data;
    }

    void OnDataReceive(uint64_t data) {
        // p = Unpack(data, PackLocation {0,7});
    }

protected:
    void SetHelp() {
        help[HEMISPHERE_HELP_DIGITALS] = "1=Clock/Gate";
        help[HEMISPHERE_HELP_CVS] = "1=p Mod";
        help[HEMISPHERE_HELP_OUTS] = "A,B=Clock/Gate";
        help[HEMISPHERE_HELP_ENCODER] = "Set p";
    }

private:
	int step;
	int max_steps;
    int output;
    int fire;
    int prob;

	void DrawInterface() {
        gfxPrint(1, 15, hemisphere ? "d-prob=" : "b-prob=");
        gfxPrint(33 + pad(100, step), 15, prob);

        gfxCursor(15, 23, 18);
        
        gfxPrint(12, 45, hemisphere ? "C" : "A");
        gfxPrint(44, 45, hemisphere ? "D" : "B");
        
        if (output != 2) {
            gfxFrame(9 + (32 * output), 42, 13, 13);
        }
	}
};


////////////////////////////////////////////////////////////////////////////////
//// Hemisphere Applet Functions
///
///  Once you run the find-and-replace to make these refer to Hats,
///  it's usually not necessary to do anything with these functions. You
///  should prefer to handle things in the HemisphereApplet child class
///  above.
////////////////////////////////////////////////////////////////////////////////
Hats Hats[2];

void Hats_Start(bool hemisphere) {
    Hats[hemisphere].BaseStart(hemisphere);
}

void Hats_Controller(bool hemisphere, bool forwarding) {
	Hats[hemisphere].BaseController(forwarding);
}

void Hats_View(bool hemisphere) {
    Hats[hemisphere].BaseView();
}

void Hats_OnButtonPress(bool hemisphere) {
    Hats[hemisphere].OnButtonPress();
}

void Hats_OnEncoderMove(bool hemisphere, int direction) {
    Hats[hemisphere].OnEncoderMove(direction);
}

void Hats_ToggleHelpScreen(bool hemisphere) {
    Hats[hemisphere].HelpScreen();
}

uint64_t Hats_OnDataRequest(bool hemisphere) {
    return Hats[hemisphere].OnDataRequest();
}

void Hats_OnDataReceive(bool hemisphere, uint64_t data) {
    Hats[hemisphere].OnDataReceive(data);
}
