/*
   This software is licensed under the MIT License. See the license file for details.
   Source: https://github.com/spacehuhntech/WiFiDuck
*/

// ===== WebSocket Actions ===== //
function load_settings() {
  ws_send("settings", function(msg) {
    var lines = msg.split(/\n/);

    var mode = lines[0].split("=")[1];
    var ssid = lines[1].split("=")[1];
    var password = lines[2].split("=")[1];
    var channel = lines[3].split("=")[1];
    var autorun = lines[4].split("=")[1];

    // Update dropdown instead of innerHTML
    var modeSelect = E("mode");
    if (modeSelect.tagName === "SELECT") {
      modeSelect.value = mode; // set correct option
    } else {
      E("mode").innerHTML = mode;
    }

    E("ssid").innerHTML = ssid;
    E("password").innerHTML = password;
    E("channel").innerHTML = channel;
    E("autorun").innerHTML = autorun;
  });
}

function ws_connected() {
  load_settings();
}


// ===== Startup ===== //
window.addEventListener("load", function() {
  // Auto-save mode on dropdown change
  E("mode").onchange = function() {
    var selectedMode = this.value;
    if (selectedMode === "STA" || selectedMode === "AP") {
      ws_send('set mode "' + selectedMode + '"', function(msg) {
        load_settings();
      });
    } else {
      alert("ERROR: Invalid mode selected");
    }
  };

  // SSID edit
  E("edit_ssid").onclick = function() {
    var newssid = prompt("SSID (1-32 chars)", E("ssid").innerHTML);

    if (newssid) {
      if (newssid.length >= 1 && newssid.length <= 32) {
        ws_send("set ssid \"" + newssid + "\"", function(msg) {
          load_settings();
        });
      } else {
        alert("ERROR: Invalid length");
      }
    }
  };

  // Password edit
  E("edit_password").onclick = function() {
    var newpassword = prompt("Password (8-64 chars)", E("password").innerHTML);

    if (newpassword) {
      if (newpassword.length >= 8 && newpassword.length <= 64) {
        ws_send("set password \"" + newpassword + "\"", function(msg) {
          load_settings();
        });
      } else {
        alert("ERROR: Invalid length");
      }
    }
  };

  // Channel edit
  E("edit_channel").onclick = function() {
    var newchannel = prompt("Channel (1-14)", E("channel").innerHTML);

    if (newchannel) {
      if (parseInt(newchannel) >= 1 && parseInt(newchannel) <= 13) {
        ws_send("set channel " + newchannel, function(msg) {
          load_settings();
        });
      } else {
        alert("ERROR: Invalid channel number");
      }
    }
  };

  // Autorun disable
  E("disable_autorun").onclick = function() {
    ws_send("set autorun \"\"", function(msg) {
      load_settings();
    });
  };

  // Reset settings
  E("reset").onclick = function() {
    if (confirm("Reset all settings to default?")) {
      ws_send("reset", function(msg) {
        load_settings();
      });
    }
  };

  ws_init();
}, false);