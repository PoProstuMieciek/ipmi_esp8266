read -p "Domain: " domain
read -p "Email: " email
read -p "Days: " days

mkdir -p ./data/certs

rm ./data/certs/key.pem ./data/certs/cert.pem

openssl genrsa \
    -out ./data/certs/key.pem \
    1024

openssl req \
    -new \
    -x509 \
    -key ./data/certs/key.pem \
    -out ./data/certs/cert.pem \
    -days "$days" \
    -subj /CN=$domain/emailAddress=$email