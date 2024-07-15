const { exec } = require("child_process");

function kill_browser(browser_input) {
  let status = "browser killed";
  let browser;

  if (browser_input === "chrome") {
    browser = "chrome";
  } else if (browser_input === "firefox") {
    browser = "firefox";
  } else {
    status = "browser param invalid.";
    console.log(status);
    return { status };
  }

  console.log(`:test: ${browser} kill`);
  exec(`taskkill /IM ${browser}.exe /F`, (error) => {
    if (error) {
      console.error(`exec error: ${error}`);
      status += `  exec error: ${error}`;
    }
  });

  return { status };
}
function open_browser(browser_input, url) {
  let status = "";
  let browser;

  if (browser_input === "chrome") {
    browser = "chrome";
  } else if (browser_input === "firefox") {
    browser = "firefox";
  } else {
    status = "browser param invalid. Taking Firefox as a default browser.";
    console.log(status);
    browser = "firefox";
  }

  if (url === undefined) {
    console.error("Please enter a URL");
    status += "  invalid URL";
    return { status };
  }

  let command;
  if (process.platform === "win32") {
    command = `start ${browser} ${url}`;
  } else if (process.platform === "darwin") {
    command = `open -a "${browser}" ${url}`;
  } else if (process.platform === "linux") {
    if (browser_input === "chrome") {
      command = `google-chrome --no-sandbox ${url}`;
    } else {
      command = `firefox ${url}`;
    }
  } else {
    status += "  No platform detected";
    console.log(status);
    return { status };
  }

  console.log(`exec command: ${command}`);
  const child = exec(command, (error) => {
    if (error) {
      console.error(`exec error: ${error}`);
      status += `  exec error: ${error}`;
      return { status };
    }
  });

  return { status };
}

function cleanUp(browser_input) {
  let status = "browser killed";
  let browser;

  if (browser_input === "chrome") {
    browser = "chrome";
    exec(
      `rmdir /S /Q "%LOCALAPPDATA%\\Google\\Chrome\\User Data\\Default\\Cache"`,
      (error) => {
        if (error) {
          console.error(`exec error: ${error}`);
          status += `  exec error: ${error}`;
        }
      }
    );
  } else if (browser_input === "firefox") {
    browser = "firefox";
    exec(
      `del "%APPDATA%\\Mozilla\\Firefox\\Profiles\\*.default-release\\*.sqlite"`,
      (error) => {
        if (error) {
          console.error(`exec error: ${error}`);
          status += `  exec error: ${error}`;
        }
      }
    );
    exec(
      `rmdir /S /Q "%APPDATA%\\Mozilla\\Firefox\\Profiles\\*.default-release\\cache2"`,
      (error) => {
        if (error) {
          console.error(`exec error: ${error}`);
          status += `  exec error: ${error}`;
        }
      }
    );
  } else {
    status = "browser param invalid.";
    console.log(status);
    return { status };
  }

  return { status };
}

module.exports = {
  open_browser,
  kill_browser,
  cleanUp,
};
