let vecVecLocation = [];
let colors = new Array(10);
let vecVelocity;

const size = 10;
const strokeWeightVal = 1

function setup() {
    createCanvas(windowWidth, windowHeight);
    background(0);
    strokeWeight(strokeWeightVal);
    noStroke();
    vecVelocity = createVector(random(-5, 5), random(-5, 5));
    frameRate(60);

    // create 10 points
    for (let i = 0; i < 10; i++) {
        vecVecLocation.push([]);
        vecVecLocation[i].push(createVector(width/4 + random(-10, 10), height/4 + i * 20));
        colors[i] = createVector(random(0, 255), random(0, 255), random(0, 255));
    }
}

function draw() {
    background(0);

    for (let i = 0; i < vecVecLocation.length; i++) {
        let opacity = 255;
        fill(colors[i].x, colors[i].y, colors[i].z, opacity);

        let prevLocation = vecVecLocation[i][vecVecLocation[i].length-1];

        let currentLocation = createVector(prevLocation.x+vecVelocity.x, prevLocation.y+vecVelocity.y);
        ellipse(currentLocation.x, currentLocation.y, size, size);

        for (let j = 1; j <= vecVecLocation[i].length; j++) {
            fill(colors[i].x, colors[i].y, colors[i].z, opacity);
            let l = vecVecLocation[i][vecVecLocation[i].length - j];
            ellipse(l.x, l.y, size, size);
            opacity -= 4;
        }

        // update
        vecVecLocation[i].push(currentLocation);

        if (currentLocation.x >= width || currentLocation.x <= 0) {
            vecVelocity.x = -1 * vecVelocity.x;
        }
        if (currentLocation.y >= height || currentLocation.y <= 0) {
            vecVelocity.y = -1 * vecVelocity.y;
        }
        
    }
}