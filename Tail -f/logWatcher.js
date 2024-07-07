const events = require("events");
const fs = require("fs");
const bf = require("buffer");

const numberOfLogsFromLast = process.env.NUMBER_OF_LOGS_LINES || 10;
const buffer = new Buffer.alloc(bf.constants.MAX_STRING_LENGTH);

class LogWatcher extends events.EventEmitter {
  constructor(fileName) {
    super();
    this.file = fileName;
    this.log = [];
  }

  getLogs() {
    return this.log;
  }

  start() {
    const logWatcher = this;
    try {
      fs.open(this.file, (err, fd) => {
        if (err) {
          throw err;
        }

        console.log("Log File Opened in start function of log watcher");
        let data = "";
        let fileData = [];
        fs.read(fd, buffer, 0, buffer.length, 0, (err, bytesRead) => {
          if (err) {
            throw err;
          }
          console.log("Started Reading Logs in start function");
          if (bytesRead > 0) {
            data = buffer.slice(0, bytesRead).toString();
            fileData = data.split("\n");
            this.log = [];

            fileData
              .slice(-1 * numberOfLogsFromLast)
              .forEach((log) => this.log.push(log));
          }
          fs.close(fd);
          console.log("Log file closed in start function of log watcher");
        });

        fs.watchFile(this.file, { interval: 1000 }, (curr, prev) => {
          logWatcher.watch(curr, prev);
        });
      });
    } catch (error) {
      console.log("Error Occured in start function of LogWatcher", error);
    }
  }

  watch(curr, prev) {
    const logWatcher = this;
    try {
      fs.open(this.file, (err, fd) => {
        if (err) {
          throw err;
        }

        console.log("Log file opened in watch function of log watcher");

        let data = "";
        let fileData = [];
        console.log("--->prev", prev);
        fs.read(
          fd,
          buffer,
          0,
          buffer.length,
          prev.size - 1,
          (err, bytesRead) => {
            if (err) {
              throw err;
            }

            if (bytesRead > 0) {
              console.log(
                "Started reading log from size : ",
                prev.size,
                " in the watch function"
              );

              data = buffer.slice(0, bytesRead).toString();
              fileData = data.split("\n");
              console.log("1.fileData.length------------->", fileData.length);

              if (fileData.length >= numberOfLogsFromLast) {
                fileData
                  .slice(-1 * numberOfLogsFromLast)
                  .forEach((log) => this.log.push(log));
              } else {
                fileData.forEach((log) => {
                  if (this.log.length == numberOfLogsFromLast) {
                    this.log.shift();
                  }
                  this.log.push(log);
                });
              }
              logWatcher.emit("update-logs-server", fileData);
            }
          }
        );
      });
    } catch (error) {
      console.log("Error Occured in the watch function of LogWatcher", error);
    }
  }
}

module.exports = LogWatcher;
