const FRAME_RATE = 16;
const LANE_COUNT = 10;
const DOT_COUNT = 16;


class Dot {
    constructor(dot_id, x, y) {
        this.dot_id = dot_id;
        this.x = x; this.y = y;
        this.active = false;
    }

    draw() {
        if (frameCount % FRAME_RATE == this.dot_id) {
            stroke(200, 0, 0);
            this.play();
        } else {
            noStroke();
        }

        if (this.active) {
            fill(0);
        } else {
            fill(255);
        }
        rect(this.x-5, this.y-5, 10, 10);
    }

    mouseOver() {
        if ((this.x-5 <= mouseX && mouseX <= this.x+5) && (this.y-5 <= mouseY && mouseY <= this.y+5)) {
            return true;
        } else {
            return false;
        }
    }

    click() {
        if (this.mouseOver()) {
            this.active = !this.active;
        }
    }

    play() {
        // TODO: play background
        // TODO: play sound
    }
}


class SoundSelector {
    constructor(id, x, y, w, h) {
        this.id = id;
        this.x = x; this.y = y;
        this.w = w; this.h = h;
    }

    draw() {
        stroke(0);
        fill(180);
        rect(this.x, this.y, this.w, this.h);
        fill(0);
        textAlign(LEFT);
        textSize(16);
        text(String(this.id), this.x, this.y, this.w, this.h);
    }
}


class Line {
    constructor(id, x, y, w, h) {
        this.id = id;
        this.x = x; this.y = y;
        this.w = w; this.h = h;

        this.dots = [];
        for (let i = 0; i < DOT_COUNT; i++) {
            this.dots.push(new Dot(i, this.x + 20 + (i) * (this.w / DOT_COUNT+1), this.y + (this.h/2)));
        }
    }

    draw() {
        // draw dots
        for (let i = 0; i < this.dots.length; i++) {
            const dot = this.dots[i];
            dot.draw();
        }
    }
}


class Lane {
    constructor(id) {
        this.id = id;
        this.x = 0; this.y = id * (height/LANE_COUNT);
        this.w = width; this.h = height/LANE_COUNT;

        this.soundSelector = new SoundSelector(this.id, this.x, this.y, this.h, this.h);
        this.line = new Line(this.id, this.x+this.h, this.y, this.w - this.h, this.h);
    }

    draw() {
        this.soundSelector.draw();
        this.line.draw();
    }
}


// MAIN

let lanelist = [];

function setup() {
    createCanvas(window.innerWidth, window.innerHeight);
    frameRate(FRAME_RATE);

    // init lane
    for (let i = 0; i < LANE_COUNT; i++) {
        lanelist.push(new Lane(i));
    }
}


function draw(params) {
    background(230);

    // draw lane
    for (let i = 0; i < lanelist.length; i++) {
        const lane = lanelist[i];
        lane.draw();
    }
    
}


function mouseClicked() {
    // dots
    for (let i = 0; i < lanelist.length; i++) {
        const lane = lanelist[i];
        for (let j = 0; j < lane.line.dots.length; j++) {
            const dot = lane.line.dots[j];
            dot.click();
        }
    }
}