let shivInp = [];
let usrInp = [];
let begin = false;
let level = 0;
let score = 0;
let highScore = 0;

let btns = document.querySelectorAll('.btn');
let title = document.querySelector('.ins p');
let brd = document.querySelector('.brd p');
let scrBrd = document.querySelector('.scrBrd p');


let red = document.querySelector('#red');
let blue = document.querySelector('#blue');
let green = document.querySelector('#green');
let purple = document.querySelector('#purple');

let btnChoice = [red, blue, green, purple];

// TO Begin Game
document.addEventListener('keypress', () => {
    if (level === 0 && !begin) {
        gameBegin();
    }
});

// Game Starter Function
function gameBegin() {
    begin = true;
    score = 0;
    levelup();
}

// Game Ender Function
function gameOver() {
    level = 0;
    begin = false
    shivInp = [];
    usrInp = [];
    title.innerText = `Game Over!!, Your Score: ${score}`
    brd.innerHTML = `<p>Press Any Key to Restart</p>`
    scrBrd.innerHTML =  `<p>Current High Score: ${highScore}</p>`
}

// Leveling function
function levelup() {
    level++;
    usrInp = [];
    score = level - 1;
    if (highScore < score) { highScore = score }
    title.innerText = `Level ${level}`
    brd.innerHTML = `<p>High Score: ${highScore} &nbsp; Current Score: ${score}</p>`
    title.classList.add('start');
    brd.classList.add('brd');

    main();
}

// Main Function 
function main(){
    let rand = Math.ceil(Math.random() * 3)
    setTimeout(() => {
        aiFlashBtn(btnChoice[rand]);
    }, 500)
    shivInp.push(btnChoice[rand].id);
    console.log(shivInp);
}

// Button Press function
function btnPress() {
    if(!begin) return;
    usrInp.push(this.id);
    Check(usrInp.length - 1, this);
    if (begin && usrInp.length === shivInp.length) levelup();
}

// Event Listener
for (let btn of btns) {
    btn.addEventListener('click',btnPress)
}

// Checker 
function Check(i, btn) {
    if (usrInp[i] !== shivInp[i]) {
        wrgFlashBtn(btn)
        setTimeout(gameOver,100);
    } else {
        crtFlashBtn(btn)
    }
}


// Fash Functions
function aiFlashBtn(btn) {
    btn.classList.add('aiFlash')
    setTimeout(() => {
        btn.classList.remove('aiFlash')
    }, 300)
}
function crtFlashBtn(btn) {
    btn.classList.add('crtFlash')
    setTimeout(() => {
        btn.classList.remove('crtFlash')
    }, 200)
}
function wrgFlashBtn(btn) {
    btn.classList.add('wrgFlash')
    setTimeout(() => {
        btn.classList.remove('wrgFlash')
    }, 200)
}
