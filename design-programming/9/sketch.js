let mic;
let sequencers = new Array(4);
let track;
let filterPad;

let setCue = null;
let setDuring = null;


function max(seq) {
    let max = 0;
    for (let i = 0; i < seq.length; i++) {
        const x = seq[i];
        if (x > max) {
            max = x;
        }
    }
    return max;
}


class Sequencer {
    constructor(id, color, x, y, size) {
        this.id = id;
        this.color = color;
        this.x = x;
        this.y = y;
        this.size = size;

        this.cuetime = null;
        this.duration = null;
    }

    draw() {
        noFill();
        stroke(0);
        strokeWeight(1);
        rect(this.x, this.y, this.size, this.size);

        noStroke();
        fill(this.color);
        rect(this.x-1, this.y-1, this.size+2, 20);

        fill(0);
        text(str(this.id+1), this.x+85, this.y+90);

        this.drawQueBar()
        this.drawIndicator()
    }

    drawIndicator() {
        if (setCue == this.id) {
            text("Track上で, シーケンスの開始位置をクリック", this.x+5, this.y+25, 55, 95);
        } else if (setDuring == this.id) {
            text("Track上で, シーケンスの終了位置をクリック", this.x+5, this.y+25, 55, 95);
        }
    }

    drawQueBar() {
        if (this.cuetime == null || this.duration == null) {
            return;
        }

        let y = track.y + track.height / 2

        strokeWeight(5);
        stroke(this.color);
        line(
            map(this.cuetime, 0, track.sound.duration(), track.x, track.x+track.width), y,
            map(this.duration, 0, track.sound.duration(), track.x, track.x+track.width), y
        );
    }

    setCue() {
        this.cuetime = map(mouseX, track.x, track.x+track.width, 0, track.sound.duration());
    }

    setDuration() {
        this.duration = map(mouseX, track.x, track.x+track.width, 0, track.sound.duration());
    }
}


class MicTrack {
    constructor(mic, x, y, width) {
        this.mic = mic;
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = 40;

        this.recmode = false;
        this.sound = new p5.SoundFile();
        this.recorder = new p5.SoundRecorder();
        this.recorder.setInput(this.mic);
        this.soundvolume = new Array();
    }

    startRec() {
        this.sound = new p5.SoundFile();
        this.sound.disconnect();
        filterPad.filter.process(this.sound, 3, 2);
        this.recorder.record(this.sound);
        this.soundvolume = new Array();
    }

    stopRec() {
        this.recorder.stop();
    }

    play(cuetime, duration) {
        if (cuetime == null || duration == null) {
            return;
        }

        this.sound.play();
        this.sound.jump(cuetime, duration-cuetime);
    }

    draw() {
        this.drawGrid();
        this.drawWave();
    }

    drawWave() {
        noFill();
        beginShape();
        for (let i = 0; i < this.soundvolume.length; i++) {
            const v = this.soundvolume[i];
            curveVertex(
                map(i, 0, this.soundvolume.length, this.x, this.x + this.width),
                map(v, 0, max(this.soundvolume),this.y+this.height, this.y)
            ); 
        }
        endShape();

        if (this.recmode) {
            this.soundvolume.push(this.mic.getLevel());
        }
    }

    drawGrid() {
        stroke(0);
        strokeWeight(1);
        text("Track", this.x, this.y);

        stroke(60);
        if (this.recmode) {
            stroke(0, 80, 80);
        }
        strokeWeight(1);

        line(this.x, this.y, this.x, this.y+this.height);
        line(this.x+this.width, this.y, this.x+this.width, this.y+this.height);

        line(this.x, this.y+this.height/2, this.x+this.width, this.y+this.height/2);
        stroke(0);
    }
}


class FilterPad {
    constructor(x, y, width, height) {
        this.x = x;
        this.y = y;
        this.padx = this.x;
        this.pady = this.y+10;

        this.width = width;
        this.height = height;        
        this.padwidth = this.width;
        this.padheight = this.height-10;

        this.filter = new p5.Reverb();
        this.delay = new p5.Delay();
        this.filter.chain(this.delay);

        this.drywet = 0;
        this.delaytime = 0;
    }

    draw() {
        text("Filter Pad", this.x, this.y);
        rect(this.x, this.pady, this.padwidth, this.padheight);

        if ((this.padx <= mouseX && mouseX <= this.padx+this.padwidth) && (this.pady <= mouseY && mouseY <= this.pady+this.padheight)) {
            text("(reverb: " + Math.round(this.drywet*1000)/1000 + ", delay: " + Math.round(this.delaytime*1000)/1000 + ")", mouseX, mouseY-10);
            circle(mouseX, mouseY, 10);
        }

        this.dryWet();
        this.delayTime();
    }

    dryWet() {
        if ((this.padx <= mouseX && mouseX <= this.padx+this.padwidth) && (this.pady <= mouseY && mouseY <= this.pady+this.padheight)) {
            this.drywet = map(mouseX, this.padx, this.padx+this.padwidth, 0, 1);
        }

        this.filter.drywet(this.drywet);
    }

    delayTime() {
        if ((this.padx <= mouseX && mouseX <= this.padx+this.padwidth) && (this.pady <= mouseY && mouseY <= this.pady+this.padheight)) {
            this.delaytime = map(mouseY, this.pady, this.pady+this.padheight, 0, 1);
        }

        this.delay.delayTime(this.delaytime);
    }
}


function setup() {
    createCanvas(800, 500);
    colorMode(HSB, 100);

    // create mic track
    mic = new p5.AudioIn();
    mic.start();
    userStartAudio();
    track = new MicTrack(mic, 160, 430, 460);

    // create four sequencers
    let sColors = [[0, 70, 90], [14, 70, 90], [30, 70, 80], [60, 70, 90]];
    for (let i = 0; i < 4; i++) {
        sequencers[i] = new Sequencer(i, sColors[i], 160+i*120, 300,100);
    }

    // create filterpad
    filterPad = new FilterPad(160, 20, 460, 250);
}

function draw() {
    background(90);
   // draw sequencer button 
    text("Sequence Pad", 160, 290)
    for (let i = 0; i < sequencers.length; i++) {
        const s = sequencers[i];
        s.draw();
    }

    // draw mictrack
    track.draw();

    // draw filterPad
    filterPad.draw();

    // draw usage
    text("[キーボード操作]  Space: 押し続けて録音, 1/2/3/4: シーケンスの再生, q/w/e/r: シーケンスのセット   [マウス] Filter Pad上でReverb操作", 10, 490);
}


function keyPressed() {
    if (keyCode === 32) {
        track.recmode = true;

        // reset
        for (let i = 0; i < sequencers.length; i++) {
            const s = sequencers[i];
            s.cuetime = null;
            s.duration = null;
        }

        track.startRec();
        return;
    }


    for (let i = 0; i < 4; i++) {
        if (key == str(i+1)) {
            let s = sequencers[i]
            track.play(s.cuetime, s.duration);
            return;
        }
    }

    if (key == 'q') {
        setCue = 0;
        sequencers[setCue].cuetime = null;
        sequencers[setCue].duration = null;
        return
    }
    if (key == 'w') {
        setCue = 1;
        sequencers[setCue].cuetime = null;
        sequencers[setCue].duration = null;
        return
    } 
    if (key == 'e') {
        setCue = 2;
        sequencers[setCue].cuetime = null;
        sequencers[setCue].duration = null;
        return
    } 
    if (key == 'r') {
        setCue = 3;
        sequencers[setCue].cuetime = null;
        sequencers[setCue].duration = null;
        return
    } 

    return false;
}


function keyReleased() {
    if (keyCode === 32) {
        track.recmode = false;
        track.stopRec();
    }
    return false;
}


function mouseClicked() {
    if (setCue == null && setDuring == null) {
        return false;
    }

    // カーソルがいい感じの位置にいるかどうか
    if (!(track.x <= mouseX && mouseX <= track.x+track.width)) {
        return false;
    } else if (!(track.y <= mouseY && mouseY <= track.y+track.height )) {
        return false;
    }


    if (setCue != null) {
        sequencers[setCue].setCue()
        setDuring = setCue;
        setCue = null;
        return
    }

    if (setDuring != null) {
        sequencers[setDuring].setDuration();
        setCue = null;
        setDuring = null;
        return
    } 

}
