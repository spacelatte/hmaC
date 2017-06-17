# HMAC implementation for C

This is a drop-in library for hmac and related hash functions to be used in
embedded projects which they don't have standard libraries or ssl-related
stuff inside.

Currently we have

 - MD5
 - SHA1

implemented, i will integrate other hash functions as well.

Note that I do not own or wrote the source for hash functions themselves,
I just took related working one from google. Also tested within arduino and
mbed.org...

License: This library and functions are free to use and do-whatever-you-want
kind of distribution. I do not care, really. You don't have to mention anything
about me. Since i did not do anything just put them together with some wrapper
stuff around it (implementing functions like `atob` and `btoa` or `bzero`
and `bcopy`)
**BUT** you have to follow license for included source files, eg: hash-sources.
