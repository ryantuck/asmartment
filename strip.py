import particle

x = particle.post(
    device_name='lux',
    function_name='mode',
    command='green',
)

print x
