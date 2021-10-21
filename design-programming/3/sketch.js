function setup() {
    createCanvas(windowWidth, windowHeight);
    stroke(80);
    strokeWeight(2);
    noFill();
    background(210);
}

let x = 0
let vertexArray = new Array();

function draw() {
    let beforeY = windowHeight/4;
    if (vertexArray.length > 0) {
        beforeY = vertexArray[vertexArray.length-1][1];
    }
    newVertex = [x + random(-5, 5), random(beforeY - 20, beforeY + 20)]
    vertexArray.push(newVertex);

    beginShape();
    for (let i = 0; i < vertexArray.length; i++) {
        const point = vertexArray[i];
        curveVertex(point[0], point[1]);
    }
    endShape();

    x += 20;

    if (x > windowWidth) {
        fill(80, 0, 30, 100);
        beginShape();
        curveVertex(0, windowHeight);
        for (let i = 0; i < vertexArray.length; i++) {
            const point = vertexArray[i];
            curveVertex(point[0], point[1]);
        }
        vertex(windowWidth, windowHeight);
        vertex(0, windowHeight);
        vertex(0, vertexArray[0][1]);
        endShape();
        noFill();

        vertexArray = new Array();
        let newY = beforeY+100;
        if (newY > windowHeight) {
            newY = windowHeight / 4;
            background(210);
        }
        vertexArray.push([0, newY]);
        x = 0;
    }
}