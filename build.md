# Build

Using Ubuntu, this method has also been used on Mac.

1) In the bin folder, enter: 
cmake ..
2) After cmake finishes, enter: 
make
3) After make finishes, use:
./app
to launch the application. The paint application can be used individually or as a network.
To create a network, one instance of the application must be a server. Multiple instances of ./app must be run, either using tmux or multiple terminals.

SERVER
To launch a server, launch the app with ./app, then enter 's' when prompted.
then pick a port ('d' will default to 50000)
and enter an ip address ('l' will default to your local ip address)

CLIENT
To launch a client, launch the app with ./app, then enter 'c' when prompted.
then enter a username (should be unique from other users on the network),
then enter a port number between 50001 and 50010,
and enter an ip address ('l' will default to your local ip address).
Next, enter the port number, and ip address for the server you want to join.

NOTES:
The application will not work if it has the same port and ip address as another application.
The client will not connect to a server if the server is created after the client.
The client will receive all previous data from the server upon joining, unless the data has been cleared.

