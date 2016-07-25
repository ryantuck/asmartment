import particle

x = particle.post(
    device_name='lux',
    function_name='set-color',
    command='magenta',
)

print x
