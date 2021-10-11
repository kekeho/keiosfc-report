function setup(){
    createCanvas(windowWidth, windowHeight);
    background(230);
    strokeWeight(2);
    stroke(150);
    colorMode(HSB, 100);
}
 
let theta = 0
function draw() {
    if (theta > windowWidth) {
        theta = 0;
        stroke(Math.random() * 100, 80, 100);
    }
    for (let x = 0; x < windowWidth; x++) {
        let y = Math.sin((x+theta) * (2 * Math.PI/windowWidth)) * (windowHeight/2) + (windowHeight/2);
        point(x, y);
    }

    theta += 20;
}
