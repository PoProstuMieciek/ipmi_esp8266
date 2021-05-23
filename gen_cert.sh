cd ./data/certs/
rm esp8266.key.pem esp8266.cert.pem
openssl genrsa -out esp8266.key.pem 1024
openssl req -new -x509 -key esp8266.key.pem -out esp8266.cert.pem -days 90 -subj /C=PL/CN=ipmi.mieciuu.live/emailAddress=poprostumieciek@gmail.com