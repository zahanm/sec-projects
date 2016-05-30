Project 3

Zahan Malkani
Megan Kanne

Part 1
=======
1.
www.l.google.com 74.125.19.104
bestbuy.com.122.207.net 66.235.143.54
crypto.stanford.edu 171.64.78.27

---

2.
This is tracking an https connection to 74.125.19.104 (google.com)
name of certificate issuing authority:
Thawte Consulting (Pty) Ltd.

encryption algorithm:
RSAEncryption

key and size of key used for encryption:
I was unsure of whih key we were expected to provide, so this is the client key, provided during the ClientKeyExchange step of TLS.
client key:
8715431518426a9b3dea9437d1304c506b792893ffbf9fdfe61ced0213b83847c243c64735da68a28d20f429aba0a823eca4c47dd21d79749c9fdb4001ca7420a5d383dcde005e34b2fa45447acfc995e7f8d617edbc37c719796aceaf63d410d10a43ca2c89471e4116a8bf88a5af5d13be39de6c82c79217a8f23c1002ff84
Length: 128

expiration date and time on issued certificate:
utcTime: 11-12-18 23:59:59 (UTC)

browser supported:
Cipher Spec: TLS_RSA_WITH_RC4_128_SHA (0x000005)
Cipher Spec: TLS_RSA_WITH_3DES_EDE_CBC_SHA (0x00000a)
Cipher Spec: TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA (0x000013)
Cipher Spec: TLS_RSA_WITH_RC4_128_MD5 (0x000004)
Cipher Spec: SSL2_RC4_128_WITH_MD5 (0x010080)
Cipher Spec: SSL2_DES_192_EDE3_CBC_WITH_MD5 (0x0700c0)

server supported:
Cipher Suite: TLS_RSA_WITH_RC4_128_SHA (0x0005)

---

3.
login name and password for connecting to ftp server finitestatemachine.stanford.edu (172.24.73.102):
username: harinym
password: harinym

identify active and passive ftp, explain difference:
The server defaults to active mode, and the PORT command specifies a port to connect to for a RETR.
For example
  PORT 192,168,113,129,236,11
where,
Active IP address: 192.168.113.129 (192.168.113.129)
Active port: 60427

In this trace, the second ftp session uses active transfers.
The ftp server (finitestatemachine.stanford.edu) connects to the client (192.168.113.129), on the port specified and then starts the transfer.
The server software seems to think passive mode is preferable though, it warns 'consider using PASV' on using PORT.

The PASV command puts the server into passive mode.
The server respondes with something like
  227 Entering Passive Mode (172,24,73,102,38,15)
where,
Passive IP address: finitestatemachine.stanford.edu (172.24.73.102)
Passive port: 9743

In passive mode, the server will wait for the client to establish a connection with it rather than attempting to connect to a client-specified port.
All the files in the first session are downloaded this way.

What file(s) were downloaded? Give complete download path and their sizes:
First session,
ftp/README : 55 bytes
ftp/pine.tar.gz : 4218629 bytes

Second session,
ftp/thrift.tgz : 682730 bytes
wget-1.12.tar.gz : 2464747 bytes

---

4.
It appears there are three tracert's from that source address.
I am going to focus on the chronologically first one.

Destination: www.l.google.com (74.125.19.103)

Src: dn800cad0e.stanford.edu (128.12.173.14)
Hop: 128.12.172.1 (128.12.172.1)
Hop: 172.20.10.33 (172.20.10.33)
Hop: boundaryb-rtr.stanford.edu (171.64.1.137)
Hop: dc-oak-dc2--ucd-3ge.cenic.net (137.164.23.41)
Hop: dc-svl-core1--oak-agg1-10ge.cenic.net (137.164.47.115)
Hop: dc-svl-px1--svl-core1-10ge-1.cenic.net (137.164.46.205)
Hop: 137.164.131.61 (137.164.131.61)
Hop: 137.164.130.94 (137.164.130.94)
Hop: 216.239.49.250 (216.239.49.250)
Hop: 209.85.249.30 (209.85.249.30)
Dst: www.l.google.com (74.125.19.103)

---

5.
user: cs155@dummymail.com
password: whitehat

emails: 5 messages

1
From: joe <cs155@dummymail.com>
Subject: foobar
Date: Fri, 23 Apr 2010 08:20:52 -0700

2
From: hariny <harinym@stanford.edu>
Subject: wassup
Date: Fri, 23 Apr 2010 08:21:50 -0700

3
From: hariny <harinym@stanford.edu>
Subject: geology rocks!
Date: Fri, 23 Apr 2010 08:22:28 -0700

4
From: joe <cs155@dummymail.com>
Subject: can you see this subject?
Date: Fri, 23 Apr 2010 08:23:25 -0700

5
From: hariny <harinym@stanford.edu>
Subject: test message
Date: Fri, 23 Apr 2010 10:25:00 -0700
