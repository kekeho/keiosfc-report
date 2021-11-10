let mic;
let fft;

let buffer;

let scaleSlider;
let velocitySlider;
let colors = new Array(1024);

function setColors() {
    for (let index = 0; index < colors.length; index++) {
        colors[index] = new createVector(random(0, 360), random(50, 100))
    }
}

function setup() {
    createCanvas(window.innerWidth, window.innerHeight);
    mic = new p5.AudioIn();
    mic.start();
    fft = new p5.FFT();
    fft.setInput(mic);
    userStartAudio();
    fill(20, 30, 190, 10);
    // noStroke();
    buffer = new Array();

    scaleSlider = createSlider(0, 10, 2);
    velocitySlider = createSlider(0, 30, 20);

    stroke(10);
    colorMode(HSB);

    setColors();
}

function draw() {
    background(0);
    scaleSlider.position(10, 10);
    let scale = scaleSlider.value();
    fill(255);
    text('scale', 10, 40);

    velocitySlider.position(200, 10);
    let velocity = velocitySlider.value();
    text('velocity', 200, 40);
    noFill();

    let spectrum = fft.analyze();
    // 過去のバッファを消す
    buffer.push(spectrum)
    while (buffer.length > velocity) {
        buffer.shift();
    }

    // 平均音量計算
    let avgBuffer = new Array(spectrum.length);
    for (let index = 0; index < avgBuffer.length; index++) {
        avgBuffer[index] = 0;        
    }
    for (let index = 0; index < buffer.length; index++) {
        const layer = buffer[index];
        for (let j = 0; j < layer.length; j++) {
            const val = layer[j];
            avgBuffer[j] += val / buffer.length;
        }
    }

    // beginShape();
    for (let index = 0; index < avgBuffer.length; index++) {
        const vol = avgBuffer[index];
        const dig = map(index, 0, avgBuffer.length, 0, 2*PI);
        let x = cos(dig) * scale * vol + width/2;
        let y = sin(dig) * scale * vol + height/2;
        stroke(colors[index].x, 30, 60);
        line(width/2, height/2, x, y);

        noStroke()
        fill(colors[index].x, colors[index].y, map(vol, 0, 100, 30, 100));
        circle(x, y, 3);
        stroke(10, 10);
    }
    // endShape();



}