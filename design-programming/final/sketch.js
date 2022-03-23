const FRAME_RATE = 16;
const LANE_COUNT = 5;
const DOT_COUNT = 8;


let animationQueue = [];


// iは0~100
function draw_rect(i) {
    noFill();
    stroke(0);
    strokeWeight(1);

    for (let index = i/5; index < i; index+=5) {
        wh = (max(width, height) / 100) * index;
        rect(width/2 - wh/2, height/2 - wh/2, wh, wh);
    }
    
}



function draw_balls(i) {
    noFill();
    stroke(0);
    strokeWeight(1);

    base_size = max(width, height) / 10;

    for (let index = 0; index < i; index++) {
        ellipse(width/100*i, height/5, base_size);
        ellipse(width/100*i*1.2, height/5*1.5, base_size*1.5);
        ellipse(width/100*i*0.9, height/5*3, base_size*2);
        ellipse(width/100*i*1.5, height/5*3.8, base_size*0.8);
        ellipse(width/100*i*1, height/5*4.1, base_size);
    }
}


function draw_ellipse(i) {
    noFill();
    stroke(0);
    strokeWeight(1);
    i = 100-i;

    for (let index = i/5; index < i; index+=5) {
        wh = (max(width, height) / 100) * index;
        ellipse(width/2 - wh/2, height/2 - wh/2, wh, wh);
    }
}


star_memory = []
function draw_stars(i) {
    if (i == 0) {
        let new_stars = []
        for (let index = 0; index < 20; index++) {
            new_stars.push([random(0, width), random(0, height)]);
        }
        star_memory.push({s: new_stars, i: 0});
    }

    next_star_memory = [];
    for (let index = 0; index < star_memory.length; index++) {
        const stars = star_memory[index];
        if (stars.i > FRAME_RATE) { 
            continue; 
        }

        for (let j = 0; j < stars.s.length; j++) {
            const point = stars.s[j];
            fill(100);
            noStroke();
            ellipse(point[0], point[1], stars.i*1.5, stars.i*1.5);
        }

        next_star_memory.push({s: stars.s, i: stars.i+1})
    }
    star_memory = next_star_memory;
}



function draw_lines(i) {
    noFill();
    stroke(0);
    for (let index = 0; index < 10; index++) {
        line((width/100*i)+index*20, 0, (width/100*i)+index*20, height);
    }
}




class Dot {
    constructor(dot_id, x, y, animation) {
        this.dot_id = dot_id;
        this.x = x; this.y = y;
        this.active = false;
        this.animation = animation;
    }

    draw() {
        if (frameCount % FRAME_RATE == this.dot_id) {
            stroke(200, 0, 0);
            if (this.active) {
                this.play();
            }
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
        animationQueue.push({func: this.animation, frame: 0});
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
    constructor(id, x, y, w, h, animation) {
        this.id = id;
        this.x = x; this.y = y;
        this.w = w; this.h = h;
        this.animation = animation;

        this.dots = [];
        for (let i = 0; i < DOT_COUNT; i++) {
            this.dots.push(new Dot(i, this.x + 20 + (i) * (this.w / DOT_COUNT+1), this.y + (this.h/2), this.animation));
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
    constructor(id, animation) {
        this.id = id;
        this.x = 0; this.y = id * (height/LANE_COUNT);
        this.w = width; this.h = height/LANE_COUNT;
        this.animation = animation;

        this.soundSelector = new SoundSelector(this.id, this.x, this.y, this.h, this.h);
        this.line = new Line(this.id, this.x+this.h, this.y, this.w - this.h, this.h, this.animation);
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
    let animations = [draw_balls, draw_rect, draw_ellipse, draw_stars, draw_lines, draw_rect, draw_balls, draw_rect, draw_balls, draw_rect, draw_balls, draw_rect];
    for (let i = 0; i < LANE_COUNT; i++) {
        lanelist.push(new Lane(i, animations[i]));
    }
}


function draw(params) {
    background(230);

    // draw animation
    let nextAnimationQueue = [];
    for (let i = 0; i < animationQueue.length; i++) {
        const animation = animationQueue[i];
        if (animation.frame > 100) {
            continue;
        }
        animation.func(animation.frame);
        nextAnimationQueue.push({func: animation.func, frame: animation.frame+10});
    }
    animationQueue = nextAnimationQueue;

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