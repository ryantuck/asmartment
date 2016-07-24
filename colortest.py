import requests

url = "https://api.particle.io/v1/devices/2b0023000347343337373739/cc?access_token=26e4b7814fd17239de6b3c4fb0bbdb5f371284fc"

payload = {
        "command": "blue"
        }

r = requests.post(url, data=payload)

print r.text
