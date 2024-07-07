const express = require("express");
const app = express();
const http = require("http").Server(app);
const io = require("socket.io")(http);
const path = require("path");

const LogWatcher = require("./logWatcher");

const port = process.env.PORT || 3000;

// instance of LogWatcher
let logWatcher = new LogWatcher("logs.txt");

// reads the initial file and store the last 10 logs
logWatcher.start();

// returns the status of server
app.get("/", (req, res) => {
  res.send("Working");
});

// route to access the logs
app.get("/log", (req, res) => {
  const fileName = "index.html";

  let options = {
    root: path.join(__dirname),
  };

  // sends the html file in response
  res.sendFile(fileName, options, (err) => {
    if (err) {
      console.log("Error while sending HTML file", err);
    } else {
      console.log("HTML file sent successfuly to client");
    }
  });
});

//  web-socket connection on
io.on("connection", (socket) => {
  console.log("Socket created with id : ", socket.id);

  socket.on("disconnect", function () {
    console.log("Socket disconnected with id: ", socket.id);
  });

  logWatcher.on("update-logs-server", (data) => {
    socket.emit("update-logs", data);
  });

  let logData = logWatcher.getLogs();
  socket.emit("init", logData);
});

http.listen(port, (req, res) => {
  console.log(`Server started on port ${port}`);
});
