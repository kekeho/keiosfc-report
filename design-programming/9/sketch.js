let mic;
let sequencers = new Array(4);
let track;
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
        console.log("SET QUE", this.id);
        this.cuetime = map(mouseX, track.x, track.x+track.width, 0, track.sound.duration());
    }

    setDuration() {
        console.log("SET DUR",this.id);
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
        this.recorder.record(this.sound);
        this.soundvolume = new Array();
    }

    stopRec() {
        this.recorder.stop();
    }

    play(cuetime, duration) {
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
}

function draw() {
    background(90);
   // draw sequencer button 
    text("Sequencer", 160, 290)
    for (let i = 0; i < sequencers.length; i++) {
        const s = sequencers[i];
        s.draw();
    }

    // draw mictrack
    track.draw();

    // draw usage
    text("[キーボード操作]  Space: 押し続けて録音, 1/2/3/4: シーケンスの再生, q/w/e/r: シーケンスのセット", 10, 490);
}


function keyPressed() {
    if (keyCode === 32) {
        track.recmode = true;
        track.startRec();
        return;
    }

    if (key in ['1', '2', '3', '4']) {
        let s = sequencers[int(key)-1]
        track.play(s.cuetime, s.duration);
        return;
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