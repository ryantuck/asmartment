import json
import requests

# load in configs
with open('config.json') as f:
    cfg = json.load(f)

def post(device_name, function_name, command):

    # get device id
    base_url = cfg['base_url']
    access_token = cfg['access_token']
    device_id = cfg['devices'][device_name]['id']

    # configure headers and payload
    headers = {
        'Authorization': 'Bearer {}'.format(access_token),
    }
    payload = {'command': command}

    # make call!
    r = requests.post(
        url='{base_url}/{device_id}/{fn}'.format(
            base_url=base_url,
            device_id=device_id,
            fn=function_name,
        ),
        headers=headers,
        data=payload,
    )

    return r.text
