import json

import particle


def set_color(color):

    r = particle.post(
        device_name='strip',
        function_name='set_color',
        command=color,
    )

    return json.loads(r)


def on_off(cmd):

    r = particle.post(
        device_name='strip',
        function_name='on_off',
        command=cmd,
    )

    return json.loads(r)
