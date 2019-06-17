var editor = ace.edit('editor');
editor.setTheme("ace/theme/monokai");
editor.session.setMode("ace/mode/java");
editor.setFontSize("18px");

var canvas = document.getElementById('canvas');

var ctx = canvas.getContext("2d");

var x;
var y;
var angle;
var feutreHaut;
var c = 20;
var str;

function avancer(u){
	x += c*u*Math.cos(angle);
	y += c*u*Math.sin(angle);
	if(!feutreHaut){
		ctx.lineTo(x,y);
	} else {
		ctx.moveTo(x,y);
	}
}

function reculer(u){
	avancer(-u);
}

function tourner(u){
	angle += u*Math.PI/180;
	angle%=2*Math.PI;
}

function tournerDroite(u){
	tourner(u);
}

function tournerGauche(u){
	tourner(-u);
}

function monterFeutre(){
	feutreHaut = true;
}

function descendreFeutre(){
	feutreHaut = false;
}

function delay(u){

}

function initialiser(){
	
}

function draw(){
	ctx.beginPath();
	ctx.ellipse(x, y, 6,6,0, 0, 2*Math.PI );
	ctx.fillStyle = "rgb(255,0,0)";
	ctx.fill();
	ctx.closePath();

	ctx.beginPath();
	ctx.moveTo(x, y);

	eval(str);
	

	ctx.stroke();
	ctx.closePath();

}

function types(correspondance, p1,p2, decalage, chaine){
	if(p1=="return"){
		return correspondance;
	} else {
		return "var "+p2;
	}
}

function argF(correspondance, p1,p2,p3, decalage, chaine){
	var regex = / *(\w*) (\w) */gm;
	p2 = p2.replace(regex, "$2");
	return "function"+p1+p2+p3;
}

function changeStr(){
	str = editor.getValue();
	
	var regexF = /(?:[a-zA-Z]+)( \w+\()(.*)(\) *)/gm;
	str = str.replace(regexF, argF);

	var regexT = /(\w+) (\w+ *(?:;|=[^;]+;))/gm;
	str = str.replace(regexT, types);

	ctx.clearRect(0,0,canvas.width, canvas.height);
	start();
}

function resizeCanvas() {
    canvas.width = 	document.getElementById("container").offsetWidth;
    canvas.height = document.getElementById("container").offsetHeight;
}

function start(){
	resizeCanvas();
	x = canvas.width/2;
	y = canvas.height/2;
	angle = -Math.PI/2;
	feutreHaut = false;
	draw();
}

window.addEventListener('resize', start, false);
document.getElementById('draw').addEventListener('click', changeStr,false);

start();