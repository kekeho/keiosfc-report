var SpeechRecognition = SpeechRecognition || webkitSpeechRecognition
var SpeechGrammarList = SpeechGrammarList || webkitSpeechGrammarList
var SpeechRecognitionEvent = SpeechRecognitionEvent || webkitSpeechRecognitionEvent

let recognition = new SpeechRecognition();
let speechRecognitionList = new SpeechGrammarList();

recognition.continuous = true;
recognition.lang = 'ja-JP';
recognition.interimResults = true;
recognition.maxAlternatives = 1;


// 最新の文章が格納される
let latestSentence = null;


recognition.start();

// 認識イベント
recognition.onresult = function(event) {
    let results = event.results;
    let latestResult = results[results.length - 1][0];

    if (latestSentence === null || latestResult.transcript !== latestSentence.transcript) {
        latestSentence = latestResult;
        console.log(latestSentence);
    }
}


// recognitionが終了したら, すぐに再起動する
recognition.onend = function(event) {
    recognition.start();
}
