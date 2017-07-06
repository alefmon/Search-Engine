# Alef Search Engine

## Indexer


1) Before running the Indexer code, you must add Gumbo folders.
  - Linux/Mac [download](https://github.com/google/gumbo-parser);

2) Gumbo folder must be renamed to only ``gumbo``. 

3) To build and install gumbo library, you should go to gumbo folder and run the following code in terminal:

	$ ./autogen.sh
	$ ./configure
	$ make
	$ sudo make install

4) HTML files must be inside folder ``/Indexer/collection``.

5) Once you have everything set up, you can run the code inside folder ``/Indexer``:
```
$ make
$ ./indexer
```

```make clean``` remove all compiled files, leaving only your source code.


## Searcher

1) Before running the query processor, you must add index files inside folder ``/Searcher/util``.

2) Once you have index files created inside folder ``/Searcher/util``, you can compile and run the server code. To do so, run the following code in terminal:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
$ cd ..
$ ./build/http_examples
```
3) Now, wait until the search engine load index files. After that, the server should be running ! Now, you just have to access <http://localhost:8080> and use Alef Search Engine !


##References

Eidheim Simple Web-Server <https://github.com/eidheim/Simple-Web-Server>
  