#RabbitMQSetup.md

## RabbitMQ Broker

1) Installing rabbitMQ

In order to send messages, you must have a rabbitMQ server to send the messages to.
This can be installed [here](https://www.rabbitmq.com/) or via the package manager using:

`echo 'deb http://www.rabbitmq.com/debian/ testing main' | sudo tee /etc/apt/sources.list.d/rabbitmq.list && sudo apt-get update && sudo apt-get install rabbitmq-server`

### Start Server

`sudo rabbitmq-server` can be used to start the server on Linux.

### Refresh Server

On linux to refresh the contents of the server perform the following commands:

`rabbitmqctl stop_app`

`rabbitmqctl reset`

`rabbitmqctl start_app`
