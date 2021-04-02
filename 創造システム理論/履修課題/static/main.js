var SpeechRecognition = SpeechRecognition || webkitSpeechRecognition
var SpeechGrammarList = SpeechGrammarList || webkitSpeechGrammarList
var SpeechRecognitionEvent = SpeechRecognitionEvent || webkitSpeechRecognitionEvent

let recognition = new SpeechRecognition();
let speechRecognitionList = new SpeechGrammarList();

recognition.continuous = true;
recognition.lang = 'ja-JP';
recognition.interimResults = true;
recognition.maxAlternatives = 1;


recognition.start();

recognition.onresult = function(event) {
    let results = event.results;
    console.log(results);
}

recognition.onend = function(event) {
    recognition.start();
}
