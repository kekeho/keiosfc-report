let node_count = 0;

class Tree {
    constructor(anchorPosition) {
        this.anchorPosition = anchorPosition;
        this.children = null;
        this.fire_count = 0;
        this.speed = random(300, 800);
        this.strokeColor = random(10, 40);
        this.strokeWeight = 1;
    }

    draw() {
        // ellipse(this.anchorPosition.x, this.anchorPosition.y, 10, 10);

        if (this.children !== null) {
            this.drawlineToChild();
            this.children.x.draw();
            this.children.y.draw();
        } else {
            if (int(random(100)) % 99 === 0) {
                this.createChildren();
            }
        }
    }

    drawlineToChild() {
        stroke(this.strokeColor);
        strokeWeight(this.strokeWeight);
        line(this.anchorPosition.x, this.anchorPosition.y, this.children.x.anchorPosition.x, this.children.x.anchorPosition.y);
        line(this.anchorPosition.x, this.anchorPosition.y, this.children.y.anchorPosition.x, this.children.y.anchorPosition.y);
        stroke(0);
        strokeWeight(0);
        this.drawFire();
    }

    drawFire() {
        // child x
        let diffX = this.children.x.anchorPosition.x - this.anchorPosition.x;
        let diffY = this.children.x.anchorPosition.y - this.anchorPosition.y;

        let fireX = (diffX / this.speed) * this.fire_count;
        let fireY = (diffY / this.speed) * this.fire_count;

        ellipse(this.anchorPosition.x + fireX, this.anchorPosition.y + fireY, 5, 5);

        // child y
        diffX = this.children.y.anchorPosition.x - this.anchorPosition.x;
        diffY = this.children.y.anchorPosition.y - this.anchorPosition.y;

        fireX = (diffX / this.speed) * this.fire_count;
        fireY = (diffY / this.speed) * this.fire_count;

        ellipse(this.anchorPosition.x + fireX, this.anchorPosition.y + fireY, 5, 5);

        this.fire_count += 1;
        if (this.fire_count > this.speed) {
            this.fire_count = 0;
        }
    }

    _gen_pos() {
        let range_min = 80;
        let range_max = 200;

        let x_o = random(-1*range_max, range_max);
        if (x_o > 0) {
            x_o += range_min;
        } else {
            x_o -= range_min;
        }
        
        let y_o = random(-1*range_max, range_max);
        if (y_o > 0) {
            y_o += range_min;
        } else {
            y_o -= range_min;
        }

        return createVector(x_o+this.anchorPosition.x, y_o+this.anchorPosition.y);
    }

    createChildren() {

        if (node_count > 300) {
            return;
        }

        this.children = createVector(
            new Tree(this._gen_pos()),
            new Tree(this._gen_pos()),
        );
        node_count += 2;
    }
}



let genericTree;
function setup() {
    createCanvas(window.innerWidth, window.innerHeight);
    colorMode(HSB, 100, 100, 100);
    genericTree = new Tree(createVector(window.innerWidth/2, window.innerHeight/2));
}

function draw() {
    background(0);
    genericTree.draw();
}

