let chars = [];

function getNextXorZero(id) {
    if (id-1 < 0 || chars.length <= id-1) {
        return 0
    }
    return chars[id-1].x + chars[id-1].fontsize;
}


const G = 9.8;
class Char {
    constructor (id, char) {
        this.id = id;
        this.char = char;
        this.fontsize = random(40, 70);
        this.x = (getNextXorZero(id) % width) + random(0, 10);
        this.y = 0;
        this.t_offset = frameCount;
    }

    draw() {
        // draw text
        textSize(this.fontsize);
        textAlign(LEFT, TOP);
        text(this.char, this.x, this.y-this.fontsize);
        this.update();
    }

    update() {
        let y_ = 0.5*G*(pow(((frameCount-this.t_offset)/5), 2)); // 自由落下運動
        // 積み重ね
        for (let i = 0; i < chars.length; i++) {
            const c = chars[i];
            if (c.id == this.id) {
                continue;
            }

            // xの範囲
            if (c.x-this.fontsize <= this.x && this.x <= c.x+c.fontsize ) {
                if (c.y-this.fontsize < this.y && this.y <= c.y+c.fontsize ) {
                    return;
                }
            }
        }

        // 枠外に出たら止める
        if (this.y+this.fontsize > height) {
            return;
        }



        this.y = y_;
        
    }
}


let font;
function preload() {
    font = loadFont('NotoSerifJP-Regular.otf');
}


function setup() {
    createCanvas(window.innerWidth, window.innerHeight);
    frameRate(30);
}

function draw() {
    background(200);
    textFont(font);

    for (let i = 0; i < chars.length; i++) {
        const c = chars[i];
        c.draw();
    }
}


function keyPressed() {
    if (key.length == 1) {
        let c = new Char(chars.length, key);
        chars.push(c);
        cid++;
    } else if (key == 'Backspace') {
        chars.pop();
    }
}

