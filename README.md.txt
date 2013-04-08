
* brief introduction to the project *

TODO

*****************************************************************
************************ Dev Setup ******************************

* build *
Refer to the included BUILD file for building the required dependencies

* Local dev setup *
- start a test messaging server
	This will be used by the UI to make test requests to the messaging server and get responses back. 
	This will also test if the messaging libraries are getting loaded successfully.
	From the project top folder, do the following:

>> cd utils
>> hwserver.exe

  The above command will start the messaging server. When the UI connects to the server, you should see messages in the server console. 

- start mongoDB
	MongoDB is our default data cloud for the moment. Start a local instance of the mongodb server.
	This will test UI connection with the data cloud.

From the mongoDB directory (whereever you installed mongoDB from the build instructions for required dependency), do the following:
>> cd bin
>> mkdir data (this is one time only. Location where db persists the data)
>> mongod.exe --dbpath=data

- You should now be ready to fire up an instance of the UI from the visual studio debug option
