const dgram = require('dgram')

var broadcaster = dgram.createSocket("udp4");

broadcaster.bind(function(){
    broadcaster.setBroadcast(true);
    setInterval(broadcast, 1000);
})

function broadcast()
{
    var message = new Buffer("SERVER\n");
    //console.log("Broadcasting server ip\n");
    broadcaster.send(message, 0, message.length, 5555, "192.168.0.255");
}
