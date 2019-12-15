# KMRhttpd
kqueue based C++ non-blocking http server on Unix.

## Usage
put your text file in the ./static directory.  
<b>to compile:</b>  
`
$ cmake ./  
`  
`
$ make
`  
<b>to start a server:</b>  
`
$ ./KMRhttpd 8000 # 8000 as the listening port.
`  
If you cannot execute the Python cgi script, please try to set the mode of cgi script  
`
$ chmod +x *.cgi
`  
## Reference
https://github.com/EZLippi/Tinyhttpd (multithreaded tinyhttpd)
