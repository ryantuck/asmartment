import json

import particle


def set_mode(cmd):

    r = particle.post(
        device_name='grid',
        function_name='set_mode',
        command=cmd,
    )

    return json.loads(r)
