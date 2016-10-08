import json

import particle


def set_mode(cmd):

    r = particle.post(
        device_name='grid',
        function_name='set_mode',
        command=cmd,
    )

    return json.loads(r)


def all_on():

    r = particle.post(
        device_name='grid',
        function_name='set_mode',
        command='all on',
    )

    return json.loads(r)

def set_color(color):

    r = particle.post(
        device_name='grid',
        function_name='set_color',
        command=color,
    )

    return json.loads(r)


def set_num(count):

    r = particle.post(
        device_name='grid',
        function_name='set_num',
        command=str(count),
    )

    return json.loads(r)
