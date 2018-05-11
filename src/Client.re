module MyClient = BsSocket.Client.Make(Common);

let socket = MyClient.create();

include MyClient;
