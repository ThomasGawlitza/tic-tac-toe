module InnerServer =
  BsSocket.Server.Make(Common);


/* ------------ Real API demo stars here ------------ */

let startSocketIOServer = http => {
  print_endline("starting socket server");
  let io = InnerServer.createWithHttp(http);  

  let player = {
    let next_player = ref(Common.X);
    (()) => {
      let result = next_player^;
      switch (result) {
      | Common.X => next_player := Common.O;
      | Common.O => next_player := Common.X;
      | Common.Empty => ()
      };
      result
    };
  };

  InnerServer.onConnect(
    io,
    (socket) => {
      open InnerServer;
      print_endline("Got a connection!");
      /* let socket = Socket.join(socket, "someRoom", (e) => print_endline(e)); */
      let handleWhoAmI(()) = {
        Js.log("handleWhoAmI()");
        Socket.emit(socket, Common.YouAre, player())
      };
      Socket.on(socket, Common.WhoAmI, handleWhoAmI);
      let handleChecked((player, idx)) = {
        Js.log("Someone clicked: " ++ string_of_int(idx));
        Socket.broadcast(socket, Common.Checked, (player, idx))
      };
      Socket.on(socket, Common.Checked, handleChecked);
      ()
      /*
      let pipe = (typ, data) => {
        Socket.broadcast(socket, typ, data);
        Socket.emit(socket, typ, data);
        /* Socket.emit(socket, Common.UnusedMessageType, data) */
      };
      */
      /* Polymorphic pipe which actually knows about ExampleCommon.t from InnerServer */
      /*
      Socket.on(socket, Common.Message, pipe(ExampleCommon.Message));
      Socket.on(socket, Common.MessageOnEnter, pipe(ExampleCommon.MessageOnEnter))
      */
    }
  );

};