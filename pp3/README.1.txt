CS 155 Project 3

Zahan Malkani

Part 1
=======
1.
www.l.google.com 74.125.19.104
bestbuy.com.122.207.net 66.235.143.54
crypto.stanford.edu 171.64.78.27

---

2.
name of certificate issuing authority:
Comodo CA Limited

encryption algorithm:
Algorithm Id: 1.2.840.113549.1.1.5 (shaWithRSAEncryption)

key and size of key used for encryption:

                                     46 fa cb 59 84 3e   ........ .<F..Y.>
00d0  59 d2 5c 71 22 86 1d 1f  08 51 38 a3 e9 09 dc 02   Y.\q"... .Q8.....
00e0  fe 70 06 3c d0 71 76 82  45 51 32 ce 2a 10 a4 ad   .p.<.qv. EQ2.*...
00f0  4e b2 f0 31 b6 64 d0 1a  96 d8 9d 15 3b ce bb 0d   N..1.d.. ....;...
0100  bc e3 3d 0f 9e 33                                  ..=..3

Length: 128

expiration date and time on issued certificate:
utcTime: 10-07-23 23:59:59 (UTC)

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
login name and password for connecting to ftp server:
username: anonymous
password: IEUser@

identify active and passive ftp, explain difference:
The server defaults to active mode, and the PORT command would specify a port to connect to for a RETR.
But in this trace, there seems to be no instance of an active ftp transfer.
Probably because the Stanford ResComp firewall would block incoming connections.

The PASV command puts the server into passive mode.
The server respondes with something like
  227 Entering Passive Mode (64,4,30,34,53,188).
where,
Passive IP address: ftp.microsoft.akadns.net (64.4.30.34)
Passive port: 13756

In passive mode, the server will wait for the client to establish a connection with it rather than attempting to connect to a client-specified port.
All the files are downloaded this way.

What file(s) were downloaded? Give complete download path and their sizes:
/Softlib/MSLFILES/110to130.exe
size: 587201

/Softlib/MSLFILES/11P32UPD.EXE
size: 169648

/Softlib/MSLFILES/120to130.exe
size: 495102

/Softlib/MSLFILES/1TOMANY.EXE
size: 22055

/Softlib/MSLFILES/211SP295.EXE
size: 3848297

/Softlib/MSLFILES/211SP2AC.EXE
size: 6882562

/Softlib/MSLFILES/211SP2AS.EXE
size: 12015436

/Softlib/MSLFILES/211SP2CL.EXE
size: 4168041

/Softlib/MSLFILES/211SP2EA.EXE
size: 6045055

/Softlib/MSLFILES/211SP2EI.EXE
size: 5289251

/Softlib/MSLFILES/211SP2IC.EXE
size: 4393740

/Softlib/MSLFILES/211SP2IS.EXE
size: 9911981

/Softlib/MSLFILES/211SP2TN.EXE
size: 2660776

/Softlib/MSLFILES/216641up.exe
size: 135680

/Softlib/MSLFILES/21P32UPD.EXE
size: 218288

/Softlib/MSLFILES/30SP395R.EXE
size: 7901424

/Softlib/MSLFILES/30SP395U.EXE
size: 3637560

/Softlib/MSLFILES/30SP3ACR.EXE
size: 22757448

/Softlib/MSLFILES/30SP3ACU.EXE
size: 10105944

/Softlib/MSLFILES/30SP3AHS.EXE
size: 1137784

/Softlib/MSLFILES/30SP3AS.EXE
size: 25298776

/Softlib/MSLFILES/30SP3CLR.EXE
size: 3869376

/Softlib/MSLFILES/30SP3CLU.EXE
size: 3698160

/Softlib/MSLFILES/30SP3ICR.EXE
size: 18824648

---

4.
