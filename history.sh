 rec -r 16000 -b 16 -c 1 tt1.wav
 sox tt1.wav tt1.flac gain -n -5 silence 1 5 2%
 curl -H "Content-Type: audio/x-flac; rate=16000" "https://www.google.com/speech-api/v1/recognize?xjerr=1&client=chromium&lang=fr-FR&maxresults=6" -F myfile="@tt1.flac" -k -o"output.txt"


